#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

/* sample input
3
1 2 1
3 2 1
1 3 1
*/

using namespace std;

int main() {
    // get first number
    int n;
    fstream file;
    file.open("shell.in", ios::in);
    file >> n;
    int switches[n][3];
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<3; j++) {
            file >> switches[i][j];
        }
    }

    int scores[3] = {0, 0, 0};

    // assuming that the ball is in the first cup
    int ball = 1;
    for(int i = 0; i<n; i++) {
        int a = switches[i][0];
        int b = switches[i][1];
        int g = switches[i][2];
        if (ball == a) {
            ball = b;
        } else if (ball == b) {
            ball = a;
        }

        if (ball == g) {
            scores[0]++;
        }
    }

    // assuming that the ball is in the second cup
    ball = 2;
    for(int i = 0; i<n; i++) {
        int a = switches[i][0];
        int b = switches[i][1];
        int g = switches[i][2];
        if (ball == a) {
            ball = b;
        } else if (ball == b) {
            ball = a;
        }

        if (ball == g) {
            scores[1]++;
        }
    }

    // assuming that the ball is in the third cup
    ball = 3;
    for(int i = 0; i<n; i++) {
        int a = switches[i][0];
        int b = switches[i][1];
        int g = switches[i][2];
        if (ball == a) {
            ball = b;
        } else if (ball == b) {
            ball = a;
        }

        if (ball == g) {
            scores[2]++;
        }
    }

    // cout << max(scores[0], max(scores[1], scores[2])) << endl;
    file.close();
    file.open("shell.out", ios::out);
    file << max(scores[0], max(scores[1], scores[2])) << endl;
}