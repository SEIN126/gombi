##프로그래머스_입국심사_43238
##문제 풀면서 고려한 생각들
##문제, 보통 상황에서는 심사관이 여러번 사용될 때가 많음
##안쓰는 심사관이 있는 경우는 정렬후 비교하면 오히려 편한데
##나머지 같은 경우 처리가 곤란해짐
##그렇기에, 심사관들의 사용 여부를 따져가면서, 한번에 최소시간을 도출하는건, 무리라고 판단
##특정 시간에서 모든 사람이 심사를 받을 수 있는지 확인하고, 이분탐색을 통해 그 범위를 좁혀나가기로 결정
def solution(n, times):
    ##시간 정렬을 하는 이유는 나중에 검사하기 편해짐
    times.sort()
    ##이분탐색에서 maxtime은 무조건 탐색이 가능하도록 만듬 즉 최소심사시간*인원수->대략적으로 계산 할 수 있는 최대     시간
    minmaxtime=n*times[0]
    ##이분탐색 실행
    answer=findtime(1,minmaxtime,times,n)
    return answer

## min 안된거, max 된거
## 시간 복잡도 O(logn)
##maxt는 무조건 가능하게 해둠 이유는 찾아야 할 때 무조건 넣어두어야지 오류가 나지 않음
##가능한지에 대해서 확인하는 함수
def findtime(mint,maxt,times,n):
    if(mint==maxt):##같다는 것은 더이상 탐색이 불가능하다, 즉 가장 최소시간을 의미함
        return mint
    middle=int((mint+maxt)/2)
    #중간 시간이 가능한지에 대해서 확인
    if(isitcanfind(times,middle,n)==True):
        #가능한 경우 시간을 더 줄일 수 있음(즉 찾아야 할 최소 시간은 mint~middle 사이에 있음)
        return findtime(mint,middle,times,n)
    else:
        #불가능한 경우 시간을 더 길게 해서 찾아야 함(즉 찾아야 할 최소 시간은 middle+1~maxt 사이에 있음)
        return findtime(middle+1,maxt,times,n)
    
##주어진 특정 시간인 time안에 인원 n을 다 검사할 수 있는지 확인하는 함수, 
def isitcanfind(times,time,n):
    ##손님을 어디 배치하는 것을 고민하는건 어렵기에
    ##그냥 주어진 시간동안, 각 심사관이 심사할 수 있는 최대 인원을 구해서 다 더해줌
    maxcustomer=0
    for i in times:
        maxcustomer+=int((time/i));
        ##최대 심사가능인원수가 목표인원을 넘으면
        if(maxcustomer>=n):
            #참 반환
            return True
    #반복문을 나갔다는 것은 불가능 하다는 것을 의미(즉 위에 if문에서 걸리지 않았다는 것을 의미)
    return False
