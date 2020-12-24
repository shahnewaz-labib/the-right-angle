// #pragma GCC diagnostic ignored "-Wenum-deprecated"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "connector.h"
#include "variables.h"

Connector grid[MAX][MAX];

Connector& cell(sf::Vector2i v) {
    return grid[v.x][v.y];
}

bool isOut(sf::Vector2i v, int N) {
    return !sf::IntRect(0, 0, N, N).contains(v);
}

void generate(int N) {
    std::vector<sf::Vector2i> nodes;
    nodes.push_back(sf::Vector2i(rand()%N, rand()%N));

    while(!nodes.empty()) {
        int n = rand()%nodes.size();
        sf::Vector2i v = nodes[n];
        sf::Vector2i d = DIR[rand()%4];

        if(cell(v).dirs.size() == 3) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(cell(v).dirs.size() == 2) {
            if(rand()%50) continue;
        }

        bool complete = true;
        for(int i = 0; i < 4; i++) {
            sf::Vector2i D = DIR[i];
            if(!isOut(v + D, N) and cell(v + D).dirs.empty()) {
                complete = false;
                break;
            }
        }

        if(complete) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(isOut(v + d, N)) continue;

        if(!cell(v + d).dirs.empty()) continue;

        cell(v).dirs.push_back(d);
        cell(v+d).dirs.push_back(-d);

        nodes.push_back(v+d);
    }

}

int main() {
    srand(time(0));
    std::cout << "All okay\n";
    int n = rand()%10+1;
    generate(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            std::cout << grid[i][j].dirs.size() << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}