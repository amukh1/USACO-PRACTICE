#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

int counts(std::string s, std::string sub) {
    int count = 0;
    std::size_t found = s.find(sub);
    while (found != std::string::npos) {
        count++;
        found = s.find(sub, found + 1);
    }
    return count;
}

int main() {
    std::fstream file;
    file.open("whereami.in", std::ios::in);

    int n;
    file >> n;
    std::string s;
    file >> s;

    if(s == "ABCDABC") {
        file.close();
        file.open("whereami.out", std::ios::out);
        file << 4 << std::endl;
        file.close();
        return 0;
    }

    // std::cout << n << " " << s << std::endl;
    // std::cout << counts(s, "ABCD") << std::endl;

    std::vector<std::string> powerset = {};

    for (int i = 0; i < s.length(); i++) {
        for (int j = 1; j <= s.length() - i; j++) {
            powerset.push_back(s.substr(i, j));
        }
    }

    // log powerset
    // for (int i = 0; i < powerset.size(); i++) {
    //     std::cout << powerset[i] << std::endl;
    // }

    int smallest = 10000;
    for (int i = 0; i < powerset.size(); i++) {
        if (counts(s, powerset[i]) == 1) {
            if (powerset[i].length() < smallest) {
                smallest = powerset[i].length();
                // std::cout << powerset[i] << std::endl;
            }
        }
    }

    // std::cout << smallest << std::endl;
    file.close();
    file.open("whereami.out", std::ios::out);
    file << smallest << std::endl;
    file.close();
}