/********************************************************************* 
** Program name: tsp_mst_approx
** Author: Ryan Ellis and Daniel Garlock
** Date: 6/8/18
** Description: Solution to Traveling Salesperson Problem using a Minimum Spanning Tree (Primm's Algorithm) as an approximation algorithm.
*********************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// data structure that holds the x and y coords for each city
typedef struct {
	int x;
	int y;
} city;

// gets the x and y coords for the cities from user specified file
city* file_input(string a_filename){

	// intialize a pointer to hold a list of cities
	city* city_list = NULL;
	// initialize file stream to get list of cities
	ifstream input_file;

	// open up user specified file
	input_file.open(a_filename);



	// close up file
	input_file.close();

	return city_list;
}

int main(int argc, string* argv){

	// intialize var to hold name of file to open up
	string input_filename;


	return 0;
}