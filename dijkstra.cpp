#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>

/*
N - Nodes
E - Edges
A-B FIRST EDGE
X - Weight
...
C-D LAST EDGE
Y - Weight
W--H - Path
*/

auto dijkstra(int w, int h, std::vector<std::pair<int, int>> edges, std::vector<int> weights, int& length) {
    for(int i = 0; i<edges.size(); i++) {
        
    }
    return 0;
}

int main() {
    auto file = fopen("dijkstra.in", "r");
    int n, e;
    fscanf(file, "%d %d", &n, &e);

    std::vector<std::pair<int, int>> edges;
    std::vector<int> weights;

    for(int i = 0; i<e; i++) {
        int a, b, x;
        fscanf(file, "%d %d %d", &a, &b, &x);
        edges.push_back(std::make_pair(a, b));
        weights.push_back(x);
    }

    int w, h;
    fscanf(file, "%d %d", &w, &h);

    // close
    fclose(file);

    // print out the graph
    for(int i = 0; i<e; i++) {
        std::cout << edges[i].first << "- " << weights[i] << " -" << edges[i].second << std::endl;
    }

    std::cout << ".------------------------." << std::endl;
    
    // start of algorithm
    int length;
    dijkstra(w, h, edges, weights, length);

    return 0;
}