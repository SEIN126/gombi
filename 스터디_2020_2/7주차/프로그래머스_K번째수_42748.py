#프로그래머스_정렬_K번째수_42748.py

def solution(array, commands):
    answer = []
    
    for a in commands:
        arr = array[a[0]-1:a[1]] # 해당 번호까지 slicing
        arr.sort() # 정렬
        answer.append(arr[a[2]-1]) # 원하는 순번의 번호 저장

    return answer
