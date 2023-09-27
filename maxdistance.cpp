// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <fstream>
// #include <cmath>

// /* sample in:
// 3
// 321 -15 -525
// 404 373 990
// */

// int main() {
//     int n;
//     std::cin >> n;
//     long coordinates[n][2];

//     for(int i = 0; i<n; i++) {
//         std::cin >> coordinates[i][0];
//     }

//     for(int i = 0; i<n; i++) {
//         std::cin >> coordinates[i][1];
//     }

//     long max = 0;

//     for(int i = 0; i<n; i++) {
//         for(int j = 0; j<n; j++) {
//             long distance = (std::pow(coordinates[i][0] - coordinates[j][0], 2) + std::pow(coordinates[i][1] - coordinates[j][1], 2));
//             if(distance > max) {
//                 max = distance;
//             }
//         }
//     }

//     std::cout << std::pow(max,1) << std::endl;
//     // std::cout << coordinates[0][0] << std::endl;
//     // std::cout << coordinates[0][1] << std::endl;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> x(n), y(n);

	for (int &t : x) { cin >> t; }
	for (int &t : y) { cin >> t; }

	int max_squared = 0;                   // stores the current maximum
	for (int i = 0; i < n; i++) {          // for each first point
		for (int j = i + 1; j < n; j++) {  // and each second point
			int dx = x[i] - x[j];
			int dy = y[i] - y[j];
			int square = dx * dx + dy * dy;

			/*
			 * if the square of the distance between the two points is
			 * greater than our current maximum, then update the maximum
			 */
			max_squared = max(max_squared, square);
		}
	}

	cout << max_squared << endl;
}