#ifndef MAIN_GAME
#define MAIN_GAME
using namespace sf;


Connector grid[MAX][MAX];

Connector& node(Vector2i v) {
    return grid[v.x][v.y];
}


bool isOutOfWindow(Vector2i v, int N) {
    return !IntRect(0, 0, N, N).contains(v);
}

void generate(int N) {
    std::vector<Vector2i> nodes;
    nodes.push_back(Vector2i(rand()%N, rand()%N));

    while(!nodes.empty()) {
        int n = rand()%nodes.size();
        Vector2i v = nodes[n], d = DIR[rand()%4];

        if(node(v).dirs.size() == 3) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(node(v).dirs.size() == 2) {
            if(rand()%50) continue;
        }

        bool complete = true;
        for(int i = 0; i < 4; i++) {
            Vector2i D = DIR[i];
            if(!isOutOfWindow(v + D, N) and node(v + D).dirs.empty()) {
                complete = false;
                break;
            }
        }

        if(complete) {
            nodes.erase(nodes.begin() + n);
            continue;
        }

        if(isOutOfWindow(v + d, N)) continue;

        if(!node(v + d).dirs.empty()) continue;

        node(v).dirs.push_back(d);
        node(v+d).dirs.push_back(-d);

        nodes.push_back(v+d);
    }

}

void show(int N) {
    for(int i = 0; i < N; i++, std::cout << std::endl) {
        for(int j = 0; j < N; j++) {
            std::cout << grid[i][j].dirs.size() << " ";
        }
    }
    std::cout << "----------------\n";
}


void drop(Vector2i v,int N) {
   if (node(v).on) return;
   node(v).on = true;

   for(auto d : DIR)
    if (!isOutOfWindow(v + d, N))
     if (node(v).isConnected(d) && node(v + d).isConnected(-d))
       drop(v + d, N);
}





#endif
