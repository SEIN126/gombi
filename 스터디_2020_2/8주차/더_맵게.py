#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    //On c++ multiset is default RBT min heap structure
    multiset<int> sco; 
    for(int i=0; i<scoville.size(); i++){
        //Insert all the scoville to heap
        //RBT heapify with all insert with (log n) complexity
        sco.insert(scoville[i]);
    }
    int ans = 0;
    int a = *sco.begin();
    if(a >= K){
        return 0;
    }
    while(!sco.empty()){
        //Smallest scoville = first
        int first = *sco.begin();
        //Satisfy the conditon
        if(first >= K){
            return ans;
        }
        //If empty.
        if(sco.size()<=1){
            break;
        }
        //Mix
        ans++;
        //Erase smallest
        sco.erase(sco.begin());
        int second = *sco.begin();
        //Erase samllest
        sco.erase(sco.begin());
        //Insert scoville mixture and auto heapify with insert
        sco.insert( first +second*2 );
    }
    //If Can't make more than K scoville
    return -1;
}
