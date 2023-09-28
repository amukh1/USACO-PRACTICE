#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

/* sample in:
3
2 1
8 3
5 7
*/

int main() {
    std::fstream file;
    file.open("cowqueue.in", std::ios::in);
    int n;
    file >> n;
    int* arriv = new int[n];
    int* timeup = new int[n];

    for (int i = 0; i < n; i++) {
        file >> arriv[i] >> timeup[i];
    }

    std::map<int, int> cowqueue;
    for(int i = 0; i<n; i++) {
        if(cowqueue.count(arriv[i]) > 0) cowqueue[arriv[i]] += timeup[i];
        else cowqueue.insert(std::pair<int, int>(arriv[i], timeup[i]));
        // cowqueue.insert(std::pair<int, int>(arriv[i], timeup[i]));
    }

    // for(int i = 0; i<n; i++) std::cout << i << " " << cowqueue[arriv[i]] << std::endl;

    // sorting
    // for(int i = 0; i<n-1; i++) {
    //     if(arriv[i] > arriv[i+1]) { 
    //         int a = arriv[i];
    //         arriv[i] = arriv[i+1];
    //         arriv[i+1] = a;

    //         int b = timeup[i];
    //         timeup[i] = timeup[i+1];
    //         timeup[i+1] = b;
    //      }else continue;
    // }

    // try sorting (again) :sob:
    // for(int i = 0; i<n-1; i++) {
    //     if(arriv[i] > arriv[i+1]) { 
    //         std::swap(arriv[i], arriv[i+1]);
    //         std::swap(timeup[i], timeup[i+1]);
    //      }else continue;
    // }

    // sort MAP by key from greatest to least
    std::map<int, int>::iterator it = cowqueue.begin();
    for(int i = 0; i<n; i++) {
        arriv[i] = it->first;
        timeup[i] = it->second;
        it++;
    }



    // if arriv doesnt equal map sorted with c++ sort function, log error
    // if(!std::is_sorted(arriv, arriv+n)) std::cout << "error" << std::endl;

    // for(int i = 0; i<n; i++) std::cout << arriv[i] << " " << timeup[i] << std::endl;
    int time = 0;
    // for(int i = 0; i<n; i++) {
    //     if (time < arriv[i]) time = arriv[i];
    //     time += timeup[i];
    // }

    for(std::pair<int,int> cow : cowqueue){
        if (time < cow.first) time = cow.first;
        time += cow.second;
    }

    file.close();
    file.open("cowqueue.out", std::ios::out);
    file << time;
}