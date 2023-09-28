#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>

int main() {
    int n;
    int q;

    std::cin >> n;
    std::cin >> q;

    int a[n];
    
    for(int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int l[q], r[q];

    for(int i = 0; i<q; i++) {
        std::cin >> l[i] >> r[i];
    }

    // std::cout << "-------" << std::endl;

    // // stdout check
    // for(int i = 0; i<q; i++) {
    //     std::cout << l[i] << " " << r[i] << std::endl;
    // }

    for(int i = 0; i<q; i++) {
        int sum = 0;
        for(int j = l[i]; j<=r[i]; j++) {
            sum+=a[j];
        }
        std::cout << sum << std::endl;
    }

    return 0;
}