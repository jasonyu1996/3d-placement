#include "naivecontourstructure.h"
#include <algorithm>

using namespace std;

NaiveContourStructure::NaiveContourStructure(int n, int m) {
	++n, ++m;
	this->n = n;
	this->m = m;
	grid = new int[n * m];
	for (int i = 0; i < n * m; ++i) {
		grid[i] = 0;
	}
}

NaiveContourStructure::~NaiveContourStructure() {
	delete[] grid;
}

int NaiveContourStructure::Update(int x1, int y1, int x2, int y2, int add) {
	++x2, ++y2;
	// [a, b] -> [a, b)
	int maxv = 0;
	for (int x = x1; x < x2; ++x)
		for (int y = y1; y < y2; ++y) {
			maxv = max(maxv, grid[x * m + y]);
		}
	maxv += add;
	for (int x = x1; x < x2; ++x)
		for (int y = y1; y < y2; ++y) {
			grid[x * m + y] = maxv;
		}
	return maxv;
}