// CSE2122HWK2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
File name: (your file name)
Created by: (your name)
Created on: (date)
Synopsis: ...
*/

#include <iostream>

using namespace std;

const char ALIVE = '*';
const char DEAD = ' ';

// ATTENTION: comments in this code are hints, they don't follow the format discussed in lectures i.e. making the code understandable you should delete them and write your own comments before submitting your code

void initialization(bool **world, int nrows, int ncols);
// prompts and reads the alive cells to initialize the world initializes the world

int neighbor_count(bool **world, int nrows, int ncols, int i, int j);
// counts how many neighbor cells are occupied for the input cell

void generation(bool **world, bool **copy, int nrows, int ncols);
// input parameters: original world, an array to make a copy, dimensions of the array updates the world
// generates the world by one step

void display(bool **world, int nrows, int ncols);
// prints the world to the console

// feel free to define more functions if necessary


int main() {
	// Variable declarations. You can add more if necessary
	bool **world, **copy;
	int nrows, ncols;
	char next;

	cout << "Enter world dimensions (rows and columns): ";
	cin >> nrows >> ncols;

	// allocate memory for dynamic 2d-arrays 'world' and 'copy'
	/* your code here */

	// creates bool pointers of nrows for world and copy
	world = new bool*[nrows];
	copy = new bool*[nrows];
	// creates bool arrays of ncols for world and copy
	for (int i = 0; i < nrows; i++) {
		world[i] = new bool[ncols];
		copy[i] = new bool[ncols];
	}

	// initialize the world and display
	initialization(world, nrows, ncols);
	display(world, nrows, ncols);

	// prompt user input, Generation/Quit
	cout << "next Generation or Quit (g/q): ";
	cin >> next;
	while (next == 'g' || next == 'G') {
		// generate and show the new world
		generation(world, copy, nrows, ncols);
		display(world, nrows, ncols);
		cout << "next Generation or Quit (g/q): ";
		cin >> next;
	}

	// deallocate memory for dynamic 2d-arrays 'world' and 'copy'
	/* your code here */

	// deallocate memory for bool arrays
	for (int i = 0; i < nrows; i++) {
		delete[] world[i];
		delete[] copy[i];
	}
	// deallocate memory for bool pointers
	delete[] world;
	delete[] copy;

	return 0;
}


void initialization(bool **world, int nrows, int ncols) {
	for (int i = 0; i < nrows; i++) {
		world[i] = new bool[ncols];
	}
}


int neighbor_count(bool **world, int nrows, int ncols, int i, int j) {
	/*
		00 01 02
		10 11 12
		20 21 22
	*/
	int num_neighbors = 0; // number of neighbors
	for (int di = i-1; di <= i+1; ++di) { // x coordinates
		for (int dj = j-1; dj <= j+1; ++dj) { // y coordinates
			if (!(di == i && dj == j)) { // make sure they are not the same cell
				if ((di < nrows && di >= 0) && (dj < ncols && dj >= 0)) { // check if within the map
					if (world[dj][di]) {
						num_neighbors++; // if adjacent neighbor cell is alive increment count
					}
				}
			}
		}
	}
	return num_neighbors;
}


void generation(bool **world, bool **copy, int nrows, int ncols) {
	/*  Checks neighbors of cell then changes cell to dead or alive depending on results
		If the cell is occupied and neighbors is 0 or 1, cell becomes dead
		If cell is empty and neighbors is 3 cell, becomes alive
	*/
	int neighbors; // number of neighbors
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			neighbors = neighbor_count(copy, nrows, ncols, i, j); // find neighbors
			cout << neighbors << endl;
			if (copy[i][j]){ // if the cell is alive
				if (!(neighbors == 2 || neighbors == 3)){ // if the number of neighbors is not 2 or 3, kill the cell.
					world[i][j] = false; 
				}
			}
			else if (neighbors == 3){ // if cell is empty or dead and there are 3 neighbors a new cell is born
				world[i][j] = true;
			}
		}
	}
}


void display(bool **world, int nrows, int ncols) {
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (world[i][j]) {
				cout << ALIVE;
			}
			else
			{
				cout << DEAD;
			}
		}
		cout<< endl;
	}
}


// More function definitions
/* your code here */

