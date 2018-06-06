/********************************************************************* 
** Program name: tsp_mst_approx
** Author: Ryan Ellis and Daniel Garlock
** Date: 6/8/18
** Description: Solution to Traveling Salesperson Problem using a Minimum Spanning Tree (Primm's Algorithm) as an approximation algorithm.
** Note: Below link used as guidance in designing Primm's Algo.
** https://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <climits>

using namespace std;

// data structure that holds the x and y coords for each city
typedef struct {
	int x;
	int y;
} city;

typedef struct {
	int i;
	int j;
	int weight;
} edge;

// utility function that calculates the distance from city to city
// based off their x and y coords
int distance(city i, city j){
	float ans = sqrt(((i.x - j.x)*(i.x - j.x)) + ((i.y - j.y)*(i.y - j.y)));
	if (ans - int(ans) >= 0.5)
	{
		ans = int(ans) + 1;
	}
	return int(ans);
}

// gets the x and y coords for the cities from user specified file
vector<city> file_input(string a_filename){

	// initial vector to hold list or cities
	vector<city> city_list;
	// initialize file stream to get list of cities
	ifstream input_file;
	// holds data getting pulled from file
	string data;
	// temporarily holds new city while getting data from file
	city* temp_city = NULL;

	// open up user specified file
	input_file.open(a_filename);

	if(!input_file.is_open()){
		cout << "Unable to open file." << endl;
	}
	else{
		while(input_file >> data){
			temp_city = new city;
			input_file >> data;
			temp_city->x = stoi(data);
			input_file >> data;
			temp_city->y = stoi(data);
			city_list.push_back(*temp_city);
			delete temp_city;
			temp_city = NULL;
		}
		// close up file
		input_file.close();
	}

	return city_list;
}

void build_graph(vector<city> city_list, int** city_graph){
	for(int i = 0; i < city_list.size(); i++){
		for (int j = i + 1; j < city_list.size(); j++)
		{
			city_graph[i][j] = distance(city_list[i], city_list[j]);
		}
	}
}

int minKey(int* key, bool* mst_set, int num_cities){
	// holds min value we will use to traverse key list
	int min;
	// holds the key index where the smallest val is located
	int min_index;

	// intialize min value
	min = INT_MAX;

	// traverse the key/mst lists to find the smallest distance
	// that goes across the cut
	for (int i = 0; i < num_cities; i++)
	{
		if(mst_set[i] == false && key[i] < min){
			min = key[i];
			min_index = i;
		}
	}

	// return the index of this next city to go to
	return min_index;
}

int tsp_primms_approx(int** city_graph, int* tour_list, int num_cities){
	// holds tour length
	int tour_distance = 0;
	// holds current shortest dist from cities in cut to city
	// ex. key[3] would hold the shortest dist from a city in cut to 
	// city 3
	int* key = new int[num_cities];
	// holds bool values that keep track of what city is in the cut
	bool* mst_set = new bool[num_cities];
	// holds the city from which currently in
	int current_city;

	// intialize key values to inf and mst set values to false
	for(int i = 0; i < num_cities; i++){
		key[i] = INT_MAX;
		mst_set[i] = false;
	}

	// city 0 will be root. 
	key[0] = 0;

	for(int i = 0; i < num_cities; i++){
		// get next city to explore
		current_city = minKey(key, mst_set, num_cities);
		// add this to list of cities in cut
		mst_set[current_city] = true;
		// add this to the tour list
		tour_list[i] = current_city;
		// add key value to tour distance 
		//tour_distance += city_graph[tour_list[i - 1]][tour_list[i]];

		// update the key values as applicable from this new city
		for (int j = 0; j < num_cities; j++)
		{
			if(current_city != j && mst_set[j] == false && city_graph[current_city][j] < key[j]){
				key[j] = city_graph[current_city][j];
			}	
		}
	}

	// FOR TESTING display complete tour list
	for(int i = 0; i < num_cities; i++){
		cout << tour_list[i] << " ";
		if(i != 0){
			tour_distance += city_graph[tour_list[i - 1]][tour_list[i]];
		}
	}
	tour_distance += city_graph[tour_list[num_cities-1]][tour_list[0]];
	cout << endl;

	// cleanup for mem allocated
	delete [] mst_set;
	delete [] key;
 
	return tour_distance;
}

int main(int argc, char* argv[]){

	// intialize var to hold name of file to open up
	char* input_filename = argv[1];
	// holds list of cities
	vector<city> city_list;
	// holds number of cities
	int num_cities;
	// holds graph with distance between cities
	int** city_graph = NULL;
	// holds the tour list from primm's algo
	int* tour_list = NULL;
	// holds tour distance
	int tour_distance = 0;

	city_list = file_input(input_filename);

	num_cities = city_list.size();

	// allow mem to city graph
	city_graph = new int*[num_cities];
	for(int i = 0; i < num_cities; i++){
		city_graph[i] = new int[num_cities];
	}

	// allow mem to tour list
	tour_list = new int[num_cities];

	// build graph using x and y coords from city list
	build_graph(city_list, city_graph);

	tour_distance = tsp_primms_approx(city_graph, tour_list, num_cities);

	cout << "Tour Dist: " << tour_distance << endl;

	// cleanup mem allocated to the city graph
	for(int i = 0; i < num_cities; i++){
		delete [] city_graph[i];
	}
	delete [] city_graph;
	city_graph = NULL;

	return 0;
}