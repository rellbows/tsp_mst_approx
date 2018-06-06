/********************************************************************* 
** Program name: tsp_mst_approx
** Author: Ryan Ellis and Daniel Garlock
** Date: 6/8/18
** Description: Solution to Traveling Salesperson Problem using a Minimum Spanning Tree (Primm's Algorithm) as an approximation algorithm.
*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

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

/* TESTING mod_build_graph
vector<edge> build_graph(vector<city> city_list){
	// initialze vector to hold all the edges
	vector<edge> edge_list;
	// temporarily holds new edge while getting data
	edge* temp_edge = NULL;

	for (int i = 0; i < city_list.size(); i++)
	{
		for (int j = i + 1; j < city_list.size(); j++)
		{
			temp_edge = new edge;
			temp_edge->i = i;
			temp_edge->j = j;
			temp_edge->weight = distance(city_list[i], city_list[j]);
			edge_list.push_back(*temp_edge);
			delete temp_edge;
			temp_edge = NULL;
		}
	}

	assert(edge_list.size() == ((city_list.size() * (city_list.size() - 1))/2));

	return edge_list;

}
*/

void build_graph(vector<city> city_list, int** city_graph){
	for(int i = 0; i < city_list.size(); i++){
		for (int j = 0; j < city_list.size(); j++)
		{
			city_graph[i][j] = distance(city_list[i], city_list[j]);
		}
	}
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
	
	// TESTING mod_build_graph
	// holds list of edges
	//vector<edge> edge_list;

	city_list = file_input(input_filename);

	// TESTING mod_build_graph
	//edge_list = build_graph(city_list);

	num_cities = city_list.size();

	// make city graph
	city_graph = new int*[num_cities];
	for(int i = 0; i < num_cities; i++){
		city_graph[i] = new int[num_cities];
	}

	build_graph(city_list, city_graph);

	for (int i = 0; i < num_cities; ++i)
	{
		for (int j = 0; j < num_cities; ++j)
		{
			cout << city_graph[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}