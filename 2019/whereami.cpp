#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

// int counts(std::string s, int n) {
//     std::map<std::string, int> m;
//     for (int i = 0; i < s.length() - n + 1; i++) {
//         m[s.substr(i, n)]++;
//     }
//     for (auto it = m.begin(); it != m.end(); it++) {
//         if (it->second > 1) {
//             return 0;
//         }
//     }
//     return 1;
// }

int main() {
    std::fstream file;
    file.open("whereami.in", std::ios::in);

    int n;
    file >> n;
    std::string s;
    file >> s;

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

    int smallest = s.length();
    for(int k = 1; k<s.length(); k++) {
        std::vector<std::string> nCk;
        for(int i = 0; i < powerset.size(); i++) {
            if(powerset[i].length() == k) {
                nCk.push_back(powerset[i]);
            }
        }

        bool unique = true;
        for(int i = 0; i < nCk.size(); i++) {
            for(int j = 0; j < nCk.size(); j++) {
                if(i != j) {
                    if(nCk[i] == nCk[j]) {
                        unique = false;
                    }
                }
            }
        }
        if(unique && k < smallest) {
            smallest = k;
            continue;
        }
    }

    // std::cout << smallest << std::endl;
    file.close();
    file.open("whereami.out", std::ios::out);
    file << smallest << std::endl;
    file.close();
}