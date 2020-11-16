```     
작성자: 박세인      
  사용 알고리즘: strassen 알고리즘    
  문제 이름: 백준_10830_행렬곱셈    
  핵심 포인트    
    - 분할 정복(divide & conquer)로 행렬 곱셈을 풀어보자.   
    - 기존의 곱셈 횟수(8번)로 인한 시간 복잡도(O(n^3))를 7번의 곱셈 횟수로 줄임으로써 시간 복잡도를 O(n^2.8xxx) 까지 줄일 수 있다.    
  참고    
    - 이 코드에서 실행 가능한 행렬은 2^k의 square matrix 입니다.   
    - square matrix가 아닌 행렬에 대해서 strassen 알고리즘을 수행하기 위해서는 matrix의 width가 2^k가 될 때 까지 0으로 padding 해줘야 합니다.    
```     
<hr>

# Strassen algorithm
strassen algorithm 설명입니다.  

## 기존의 행렬 곱셈
![image](https://user-images.githubusercontent.com/53332252/99227187-3c49ac80-282e-11eb-9ed9-5e42fa94a725.png)

-> 이런식으로 기존의 행렬 곱셈은 총 8번의 곱셈으로 인해 시간복잡도가 O(n^3)이 된다.

![image](https://user-images.githubusercontent.com/53332252/99227285-600cf280-282e-11eb-8972-9835c3ac4a13.png)


-> 하지만 strassen은 8번의 곱셈을 위와같이 7번의 곱셈과 18번의 덧셈으로 행렬 곱셈을 구현하였다.

![image](https://user-images.githubusercontent.com/53332252/99227137-2e942700-282e-11eb-9eac-814384eac2ef.png)

-> 대규모 행렬의 경우 위 처럼 분할 후 각각의 분할된 행렬에 대해서 strassen 알고리즘을 재귀적으로 실행한다.

![image](https://user-images.githubusercontent.com/53332252/99227362-774be000-282e-11eb-8702-3210b4a3aa87.png)

-> 위와같이 strassen 점화식을 통해 다음과 같은 시간복잡도를 구할 수 있다.

## Strassen Algorithm의 사용시 알아야 할 점
1. O-Notation 상의 속도는 더 빠르나,
  * 재귀적으로 돌려 시간이 더 오래걸릴 수 있다. (행렬의 크기가 특정 임계점 이상일 때 유용하다)
  * 7번의 곱셈을 수행할 때 이 결과를 담아둘 메모리가 필요하다 -> 행렬의 크기가 너무 클 경우 요구되는 메모리 공간이 너무 많다.

2. 실제 컴퓨터에서 이 알고리즘을 실행시키면, 속도가 더 느리게 나오는 경우가 많다.
이는 Strassen 알고리즘의 O-Notation 앞에 매우 큰 상수가 곱해지기 때문인데, 결국 Strassen 알고리즘이 일반적인 행렬 곱셈보다
더 빠르게 수행되기 위해서는 매우 큰 행렬이 필요하다. 결국 이러한 행렬의 연산은 주로 슈퍼 컴퓨터에서 사용된다.   

3. 그냥 strassen 알고리즘을 통해 절때 깨지지 않을 것 같던 O(n^3)의 벽을 넘은, 기념비적인 알고리즘 이란 것 정도만 알면 될 것 같다.
실제로 strassen 알고리즘 보다 더 빠른 행렬 곱셈이 몇가지 존재한다.
