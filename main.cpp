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

using namespace std;

// data structure that holds the x and y coords for each city
typedef struct {
	int x;
	int y;
} city;

// gets the x and y coords for the cities from user specified file
vector<city> file_input(string a_filename){

	// initial vector to hold list or cities
	vector<city> city_list;
	// initialize file stream to get list of cities
	ifstream input_file;
	// holds data getting pulled from file
	string data;
	// temporarily holds new city while getting data from file
	city* temp_city = nullptr;

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
			temp_city = nullptr;
		}
		// close up file
		input_file.close();
	}

	return city_list;
}

int main(int argc, char* argv[]){

	// intialize var to hold name of file to open up
	char* input_filename = argv[1];
	// holds list of cities
	vector<city> city_list;

	city_list = file_input(input_filename);

	return 0;
}