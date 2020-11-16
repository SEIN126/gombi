#include <string>
#include <vector>
#include <iostream>
using namespace std;
int n;
vector<vector<int>> tree;
vector<int> visit;
int dist;
int dest;
int cnt;
void dfs(int start, int depth);

int solution(int n_, vector<vector<int>> edges) {
    int answer = 0;
    n = n_;
    tree = vector<vector<int>>(n, vector<int>());
    //Make Tree.
    for(int i=0; i<edges.size(); i++){
        tree[ edges[i][0]-1 ].push_back(edges[i][1]-1);
        tree[ edges[i][1]-1 ].push_back(edges[i][0]-1);
    }
    //Find Tree's diameter by dfs twice.
    visit=vector<int>(n,0);
    dist = 0;
    dfs(0, 0);
    visit=vector<int>(n,0);
    dist = 0;
    dfs(dest, 0);
    if(cnt >=2){ //If there is more than two diameter, second largest must be diameter
        return dist;
    }
    else{
        //Find diameter again in perspective of diameter's another edge.
        visit=vector<int>(n,0);
        dist = 0;
        dfs(dest, 0);
        if(cnt>=2){ //If there is more than two diameters, second largest must be diameter
            return dist;
        }
        else{ //If only one diameter exist. Three number must be diameter, diameter-1, 1
            return dist-1;
        }
    }
    return -1;
}

void dfs(int start, int depth){
    if(visit[start] == 1){
        return; 
    }
    if(dist < depth){ //If deepest depth show first
        dest = start;
        cnt = 1;
        dist = depth;
    }
    else if(dist == depth){ //If deepest depth show again
        cnt++;
    }
    visit[start] = 1;
    for(int i=0; i<tree[start].size(); i++){
        dfs(tree[start][i], depth+1);
    }
    return;
}
