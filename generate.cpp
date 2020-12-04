// #pragma GCC diagnostic ignored "-Wenum-compare"
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#define ll long long 
using namespace std;
using namespace sf;
const int N = 7;

pair<int,int> Up(0,-1);
pair<int,int> Down(0,1);
pair<int,int> Right(1,0);
pair<int,int> Left(-1,0);

pair<int,int> DIR[4] = {Up,Right,Down,Left};

struct connector
{
  vector<pair<int,int>> dirs;
};


connector grid[N][N];
connector& point(pair<int,int> v,pair<int,int>d={0,0}) 
{
    return grid[v.first+d.first][v.second+d.second];
}
#define isOut(v,D)(!IntRect(0,0,N,N).contains(Vector2i(v.first+D.first,v.second+D.second))) 

void generatePuzzle()
{
  vector<pair<int,int>> nodes;
  nodes.push_back(pair<int,int>{rand()%N,rand()%N});

  while(!nodes.empty())
  {
    int n = rand()%nodes.size();
    pair<int,int> v = nodes[n];
    pair<int,int> d = DIR[rand()%4];

    if (point(v).dirs.size()==3) {nodes.erase(nodes.begin() + n); continue;}
    if (point(v).dirs.size()==2) if (rand()%50) continue;

    bool complete=1;
    for(auto D:DIR)
     if (!isOut(v,D) && point(v,D).dirs.empty()) complete=0;
    if (complete) {nodes.erase(nodes.begin() + n); continue; }

    if (isOut(v,d)) continue;
    if (!point(v,d).dirs.empty()) continue;
    point(v).dirs.emplace_back(d);
    point(v,d).dirs.emplace_back(-d.first,-d.second);
    nodes.emplace_back(v.first+d.first,v.second+d.second);
  }
}

int main(){
    generatePuzzle();
    for(int i=0;i<N;i++,cout<<"\n"){
        for(int j=0;j<N;j++){
            cout<<grid[i][j].dirs.size()<<" ";
        }
    }
}
