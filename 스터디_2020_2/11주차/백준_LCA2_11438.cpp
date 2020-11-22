#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

vector<vector<int>> tree;
vector<int> tree_depth;
vector<vector<int>> tree_parent;
int N;
int ans;

void tree_traverse();
void find_parent(int a, int b);
void make_parent();
void tree_traverse2(int depth, int start, int prev);

int main(){
    //Input
    scanf("%d", &N);
    tree = vector<vector<int>>(N+1, vector<int>());
    int a, b;
    for(int i=0; i< N-1;i++){
        scanf("%d %d", &a, &b);
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    tree_depth = vector<int>(N+1, 0);
    //N+1 * 18 vector. Rows for I node, Cols for I'th 2^j parent
    //Before You watch make_parent dp.
    //You can guess 50000 input and 2^18 have correlations.
    tree_parent = vector<vector<int>>(N+1, vector<int>(18, 0));
    //Traverse tree with dfs methods.
    tree_traverse2(0, 1, 0);
    //Make Tree parent dp.
    make_parent();
    
    int M;
    scanf("%d", &M);
    for(int i=0; i< M;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        //Find parent with parent dp table.
        find_parent(a, b);
    }
    return 0;
}

void tree_traverse2(int depth, int start, int prev){
    tree_parent[start][0] = prev;
    tree_depth[start] = depth;
    for(auto next : tree[start]){
        if(next == prev) continue;
        tree_traverse2(depth+1, next, start);
    }
}

void make_parent(){
    for(int i=1; i<18;i++){
        for(int j=1; j<N+1;j++){
            //Suppose Parent1 as tree_parent[j][i-1] means j's 2^(i-1)th parent .
            //Suppose Parent2 as tree_parent[tree_parent[j][i-1]][i-1] means Parent1's 2^(i-1)th parent.
            //If Parent1 and Parent2 Exists.
            //You can guess j's 2^ith parent equal to Parent2
            //Because Parent 2 is 2^(i-1)th + 2^(i-1)th parent same with 2^ith.
            tree_parent[j][i] = tree_parent[tree_parent[j][i-1]][i-1];
        }
    }
}

void find_parent(int a, int b){
    //Make a is always deeper
    if(tree_depth[a] < tree_depth[b]) swap(a, b);
    
    int diff = tree_depth[a] - tree_depth[b];
    //Make them have same depth.
    for(int i=0; diff; i++){
        //Bit operator & 1 means & 000000000001.
        //tree_parent[a][i] means if 1001(9) move when 2^0 and 2^3.
        if(diff & 1) a = tree_parent[a][i];
        diff /= 2;
    }
    if(a == b){
        printf("%d\n", a);
        return;
    }
    if(a != b){
        //Think in respect to binary.
        //If != operator means that they still don't have parent. so you must go up.
        //If == operator means that they have same parent int 2^j th. 
        //But we have to find their Lowest.
        for(int j= 17;j>=0;j--){
            if(tree_parent[a][j] != tree_parent[b][j]){
                a = tree_parent[a][j];
                b = tree_parent[b][j];
            }
        }
    }
    printf("%d\n", tree_parent[a][0]);
    return;
}
