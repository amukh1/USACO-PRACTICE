// Source: https://usaco.guide/general/io

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>
using namespace std;

int main() {
	int k;
	int n;

	cin >> k >> n;

	int rankings[k][n];

	for(int i = 0; i<k; i++) {
		for(int j = 0; j<n; j++) {
			cin >> rankings[i][j];
		}
	}

	int consistencies = 0;

	for(int i = 0; i<n; i++) {
		int ranks[k];
		// int peers[n];
		for(int j = 0; j<k; j++) {
			int rank;
			for(int c = 0; c<n; c++) {
				if(rankings[j][c] == i+1) ranks[j] = (c + 1);
				break;
			}
			// ranks[j] = k;
		}
		// if(i == 0)
		for(int j = 0; j<k; j++) cout << ranks[j] << endl;
	}

	return 0;
}
