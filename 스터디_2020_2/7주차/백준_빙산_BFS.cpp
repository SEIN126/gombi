#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> arctic;
vector<vector<int>> melt;
int N, M;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int melting();
int find_union();
void dfs(int cnt, int x, int y);

int main(){
    cin >> N >> M; //Input row size and col size
    arctic = vector<vector<int>>(N, vector<int>(M, 0)); //Make N*M vector with initialized to 0
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arctic[i][j]; //Update current state of iceberg
        }
    }
    int year =0;
    while(1){
        year++;
        if(!melting()){ //If all iceberg melted
            cout << 0 << endl;
            break;
        }
        if(find_union() != 1){ //If there is two or more Iceberg company
            cout << year<< endl;
            break;
        }
    }
    return 0;
}

int melting(){ 
    //1. Check and save how many iceberg's heights will decreased
    //2. Decrease each iceberg's heights and count reamaining iceberg
    //3. Return Iceberg count(ice)
    melt = vector<vector<int>>(N, vector<int>(M, 0));
    int ice =0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(arctic[i][j] > 0){ //If iceberg exists
                int cnt = 0;
                for(int a = 0; a<4; a++){ // dx[4] and dx[y] have right, left, down, up
                    int x = i+dx[a]; 
                    int y = j+dy[a];
                    if(x >=0 && y >= 0 && x <=N-1 && y<=M-1){ //Boundary check
                        if(arctic[x][y]==0){ //If iceberg not exists
                            cnt++;
                        }
                    }
                }
                melt[i][j] = cnt; //cnt means "how many water(0) around Iceberg" 
                //cout << "i : " << i << " J : " << j << " cnt : " << melt[i][j] << endl;
            }
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(arctic[i][j] > melt[i][j]){ //Decrease iceberg's height if remaining height exists
                arctic[i][j] -= melt[i][j]; 
                ice++; //Remain == iceberg exists
            }
            else{ //Decrease iceberg's height to 0 if remaining height not exist
                arctic[i][j] = 0;
            }
        }
    }
    return ice;
}

int find_union(){
    //1. Find iceberg and check already checked or not
    //2. Check all connected iceberg
    int cnt = 0;
    melt = vector<vector<int>>(N, vector<int>(M, 0)); //Use for check iceberg is connected
    for(int i=0; i< N; i++){
        for(int j=0; j< M; j++){
            if(melt[i][j] ==0 && arctic[i][j] !=0){ 
                cnt++;
                dfs(cnt, i, j); // cnt'th iceberg company
            }
        }
    }
    return cnt;
}

void dfs(int cnt, int x, int y){ //Find all connected iceberg 
    if(arctic[x][y] !=0 && melt[x][y] == 0){
        melt[x][y] = cnt;
    }
    else{ //If melt[x][y] already visited.
        return;
    }
    for(int der = 0; der<4; der++){
        if(x+dx[der] >= 0 && x+dx[der] <= N-1 && y+dy[der] >=0 && y+dy[der] <= M-1){ //Boundary check
            dfs(cnt, x+dx[der], y+dy[der]);//visit left, right, up, down with recursive algorithm.
        }
    }
}
