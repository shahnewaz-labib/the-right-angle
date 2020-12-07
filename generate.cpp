// #pragma GCC diagnostic ignored "-Wenum-deprecated"
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
const int N = 4; // grid dimension

Vector2i Up(0,-1),Down(0,1),Right(1,0),Left(-1,0);

Vector2i DIR[4] = {Up,Right,Down,Left},v,d;

struct connector
{
  vector<Vector2i> dirs;
} grid[N][N];


connector& point(Vector2i v) {
    return grid[v.x][v.y];
}

#define invalid(v)(!IntRect(0,0,N,N).contains(v)) 

void generatedirs()
{
  vector<Vector2i> nodes;
  nodes.emplace_back(Vector2i(rand()%N,rand()%N));
  int n;
  bool alldone;
  while(!nodes.empty())
  {
    n = rand()%nodes.size();
    
    v = nodes[n],d = DIR[rand()%4];

    if(point(v).dirs.size()==3) {
        nodes.erase(nodes.begin() + n); 
        continue;
    }

    alldone=1;
    for(auto D:DIR){
        if (!invalid(v+D) && point(v+D).dirs.empty()) {
            alldone=0;
            break;
        }
    }
    
    if(alldone) {
        nodes.erase(nodes.begin() + n); 
        continue; 
    }

    if (invalid(v+d) || !point(v+d).dirs.empty()) continue;

    point(v).dirs.emplace_back(d);
    point(v+d).dirs.emplace_back(-d);

    nodes.emplace_back(v+d);
  }
}

int main(){
    srand(time(0));
    generatedirs();
    for(int i=0;i<N;i++,cout<<"\n"){
        for(int j=0;j<N;j++){
            cout<<grid[i][j].dirs.size()<<" ";
        }
    }
}
