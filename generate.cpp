// #pragma GCC diagnostic ignored "-Wenum-deprecated"
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "connector.h"

using namespace std;
using namespace sf;

const int N = 4;

Vector2i Up(0,-1);
Vector2i Down(0,1);
Vector2i Right(1,0);
Vector2i Left(-1,0);

Vector2i DIR[4] = {Up,Right,Down,Left};


Connector grid[N][N];

Connector& cell(Vector2i v) {
    return grid[v.x][v.y];
}

bool isOut(Vector2i v) {
    return !IntRect(0, 0, N, N).contains(v);
}

void generate() {
    std::vector<Vector2i> nodes;
    nodes.push_back(Vector2i(rand()%N, rand()%N));

    while(!nodes.empty()) {
        int n = rand()%nodes.size();
        Vector2i v = nodes[n];
        Vector2i d = DIR[rand()%4];

        if(cell(v).dirs.size() == 3) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(cell(v).dirs.size() == 2) {
            if(rand()%50) continue;
        }

        bool complete = true;
        for(int i = 0; i < 4; i++) {
            Vector2i D = DIR[i];
            if(!isOut(v + D) and cell(v + D).dirs.empty()) {
                complete = false;
                break;
            }
        }

        if(complete) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(isOut(v + d)) continue;

        if(!cell(v + d).dirs.empty()) continue;

        cell(v).dirs.push_back(d);
        cell(v+d).dirs.push_back(-d);

        nodes.push_back(v+d);


    }

}

int main() {
    srand(time(0));
    cout << "All okay\n";
    generate();
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << grid[i][j].dirs.size() << " ";
        }
        cout << endl;
    }
    return 0;
}