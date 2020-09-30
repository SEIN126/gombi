#프로그래머스_해시_전화번호_목록_42577

import copy

def solution(phone):
    answer = True

    for p in phone:
        set1 = copy.deepcopy(phone) # deepcopy로 복사
        set1.remove(p) # 복사본에서 p 제거 
        #제거한 p가 set1에 존재하는 어떤 k의 앞부분(p길이만큼)에 존재하는지를 any함수로 확인
        if any(p in k[:len(p)] for k in set1): #시간복잡도?? -> 알아볼필요가 있음
            answer = False #존재
            break
        else: True #존재 x
        
    return answer
