#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>
#include <string>
#include <cctype>

std::vector<std::string> negate(std::vector<std::string> A, std::vector<std::string> B) {
    std::vector<std::string> C;
    for(int i = 0; i<A.size(); i++) {
        if(std::find(B.begin(), B.end(), A[i]) == B.end()) {
            C.push_back(A[i]);
        }
    }
    return C;
}

int main() {
    std::vector<std::string> cows = {"Beatrice", "Belinda", "Bella", "Bessie", "Betsy", "Blue", "Buttercup", "Sue"};
    std::vector<std::string> ccows = {};
    // input first number (lineup.in)
    std::ifstream fin("lineup.in");
    int N;
    fin >> N;

    std::string del;
    std::getline(fin, del);

    // input names (lineup.in)
    std::vector<std::pair<std::string,std::string>> constraints;
    for(int i = 0; i<N; i++) {
        std::string constr;
        //fin entire line
        std::getline(fin, constr);
        //split line into two names
        std::pair<std::string,std::string> names;
        names.first = constr.substr(0, constr.find("|"));
        names.second = constr.substr(constr.find("|")+1, constr.length()); // out of range
        constraints.push_back(names);
        ccows.push_back(names.first);
        ccows.push_back(names.second);
    }

    // std::cout << constraints.size() << std::endl;

    for(int i = 0; i<cows.size(); i++) {
        if(std::find(ccows.begin(), ccows.end(), cows[i]) == ccows.end()) {
            // make looping pair
            constraints.push_back(std::make_pair(cows[i], cows[i]));
            ccows.push_back(cows[i]);
        }
    }

    // cout names in pairs

    for(int i = 0; i<constraints.size(); i++) {
        std::cout << constraints[i].first << "-----" << constraints[i].second << std::endl;
    }
    std::cout << ".--------------------------." << std::endl;

    // sort names
    std::vector<std::string> visited = {""};
    std::map<std::string,std::vector<std::string>> waitlist;

    std::sort(cows.begin(), cows.end());

    for(int i = 0; i<8; i++) {
        // if cow isnt in the waitlist
        if(waitlist.find(cows[i]) == waitlist.end()) {
        // if cows[i] isnt visited yet
        if(std::find(visited.begin(), visited.end(), cows[i]) == visited.end()) {
            // visited.push_back(cows[i]);
            // get all cows that share a constraint with cows[i]
            std::vector<std::string> shared = {};
            for(int j = 0; j<constraints.size(); j++) {
                if(constraints[j].first == cows[i]) {
                    shared.push_back(constraints[j].second);
                }
                else if(constraints[j].second == cows[i]) {
                    shared.push_back(constraints[j].first);
                }
            }
            // order list in alphabetical order
            std::sort(shared.begin(), shared.end());
            // logs: cout shared
            std::cout << "Cows sharing " << cows[i] << ": ";
            for(int j = 0; j<shared.size(); j++) {
                std::cout << shared[j] << " ";
            }
            std::cout << std::endl;

            if(shared.size() == 1 && shared[0] == cows[i]) {
                visited.push_back(cows[i]);
                continue;
            }else if(shared.size() == 1 && shared[0] != cows[i]) {
                std::vector<std::string> ttemp = {cows[i], shared[0]};
                std::sort(ttemp.begin(), ttemp.end());
                visited.push_back(ttemp[0]);
                visited.push_back(ttemp[1]);
                continue;
            }else if(shared.size() == 2) {
                visited.push_back(shared[0]);
                visited.push_back(cows[i]);
                visited.push_back(shared[1]);
                continue;
            }
            continue;
            
            // for(int j = 0; j<shared.size(); j++) {
            //     if(std::find(visited.begin(), visited.end(), shared[j]) == visited.end())
            //     visited.push_back(shared[j]);
            // }
        }else continue;
        }else {
            for(int k = 0; k<waitlist[cows[i]].size(); k++) {
                if(std::find(visited.begin(), visited.end(), waitlist[cows[i]][k]) == visited.end()) {
                    visited.push_back(waitlist[cows[i]][k]);
                }
            }
        }
    }

    for(int i = 0; i<visited.size(); i++) {
        std::cout << visited[i] << std::endl;
    }

    return 0;
}