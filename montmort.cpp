#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <cmath>

int main() {
    int n;
    int m;

    std::cin >> n >> m;

    std::vector<int> v;

    for(int i = 1; i<n; i++) {
        v.push_back(static_cast<int>(std::round(std::tgamma(n+1)/std::tgamma(i+1))) % m);
    }

    // output vector as string
    std::string s = "";
    for(int i = 0; i<n; i++) {
        s += std::to_string(v[i]);
        if(i != n-1)
        s += " ";
    }

    std::cout << s << std::endl;
}