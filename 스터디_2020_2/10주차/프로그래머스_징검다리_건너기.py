//stones  : list value of stone's capacity
//k       : max possible jump.
def solution(stones, k):
    answer = 0
    left = 0
    right = max(stones) //Stone's max capacity may be possible.
    while left <= right: //Binary search
        mid = (left+right)//2
        cont = 0
        for i in range(len(stones)):
            if stones[i]-mid < 0: //If stone can't afford mid number of person 
                cont+=1 //They jump until max jump 
                if cont == k: //Impossible jump continue
                    break
            else: //If one possible stone
                cont = 0
        if cont == k: //If mid number can't pass stones. 
            right = mid-1
        else: //If mid number of people can pass stones.
            left = mid+1
    return left-1
