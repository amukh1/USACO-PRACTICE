#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

/* sample input:
10 3
11 4
12 5
*/

int main() {
    std::fstream file;

    file.open("mixmilk.in", std::ios::in);
    int capacities[3] = {0,0,0};
    int milk[3] = {0,0,0};
    file >> capacities[0] >> milk[0] >> capacities[1] >> milk[1] >> capacities[2] >> milk[2];

    for(int i = 0; i<100; i++) {
        if(milk[i % 3] > (capacities[(i+1) % 3] - milk[(i+1) % 3])) {
            int oc = capacities[(i+1) % 3] - milk[(i+1) % 3];
            milk[(i+1) % 3] = capacities[(i+1) % 3];
            milk[i % 3] = milk[i % 3] - oc;
        } else {
            milk[(i+1) % 3] = milk[(i+1) % 3] + milk[i % 3];
            milk[i % 3] = 0;
        }
    }

    file.close();
    file.open("mixmilk.out", std::ios::out);
    file << milk[0] << std::endl << milk[1] << std::endl << milk[2] << std::endl;
}