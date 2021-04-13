/*
File name: CSE2122HWK2.cpp
Created by: Surya Tej Kodali
Created on: 1/31/20
Synopsis: Game of life simulator. Asks user for grid size, number of alive cells, and coordinates 
of those cells. For each cell if the adjacent neighbor count is equal to 3 and the cell is empty
a new cell is born. If there are 0 or 1 neighbors the cell will die. If there are 2 or 3 neighbors
for an alive cell then it will live. The user is asked whether to continue or quit and if they 
continue to the next generation the grid will cycle through the generation.
*/

#include <iostream>

using namespace std;

const char ALIVE = '*';
const char DEAD = ' ';

void initialization(bool **world, int nrows, int ncols, int *coordinates, int num_alive);
// prompts and reads the alive cells to initialize the world initializes the world

int neighbor_count(bool **world, int nrows, int ncols, int i, int j);
// counts how many neighbor cells are occupied for the input cell

void generation(bool **world, bool **copy, int nrows, int ncols);
// input parameters: original world, an array to make a copy, dimensions of the array updates the world
// generates the world by one step

void display(bool **world, int nrows, int ncols);
// prints the world to the console

void printRows(int ncols);
// prints border of '='

void world_to_copy(bool **world, bool **copy, int nrows, int ncols);
// copies world array into copy


int main() {
	// Variable declarations. You can add more if necessary
	bool **world, **copy;
	int nrows, ncols;
	int num_alive;
	char next;

	cout << "Enter world dimensions (rows and columns): ";
	cin >> nrows >> ncols;
	cout << "Enter number of alive cells: ";
	cin >> num_alive;
	num_alive *= 2; // because x and y coordinates
	int* coordinates = new int[num_alive];
	cout << "Enter coordinates of alive cells: " << endl;
	for (int i = 0; i < num_alive; i++) {
		cin >> coordinates[i];
	}

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
	initialization(world, nrows, ncols, coordinates, num_alive);
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
	delete[] coordinates;

	return 0;
}

void initialization(bool **world, int nrows, int ncols, int *coordinates, int num_alive) {
	// sets world to all false except for coordinates which are true
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			world[i][j] = false;
		}
	}
	for (int i = 0; i < num_alive; i+=2) {
		int x = coordinates[i];
		int y = coordinates[i + 1];
		world[x][y] = true;
	}
}

int neighbor_count(bool **world, int nrows, int ncols, int i, int j) {
	// returns number of neighbors
	int num_neighbors = 0; // number of neighbors
	for (int di = i-1; di <= i+1; ++di) { // x coordinates
		for (int dj = j-1; dj <= j+1; ++dj) { // y coordinates
			if (!(di == i && dj == j)) { // make sure they are not the same cell
				if ((di < nrows && di >= 0) && (dj < ncols && dj >= 0)) { // check if within the map
					if (world[di][dj]) {
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
	world_to_copy(world, copy, nrows, ncols);
	int neighbors; // number of neighbors
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			neighbors = neighbor_count(copy, nrows, ncols, i, j); // find neighbors
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
	// prints grid of cells
	printRows(ncols);
	for (int i = 0; i < nrows; i++) {
		cout << '|';
		for (int j = 0; j < ncols; j++) {
			if (world[i][j]) {
				cout << ALIVE;
			}
			else
			{
				cout << DEAD;
			}
		}
		cout<< '|' << endl;
	}
	printRows(ncols);
}

void printRows(int ncols) {
	// prints rows
	for (int i = -2; i < ncols; i++) {
		cout << '=';
	}
	cout << endl;
}

void world_to_copy(bool **world, bool **copy, int nrows, int ncols) {
	// copies world to copy
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			copy[i][j] = world[i][j];
		}
	}
}