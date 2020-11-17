'''
작성자: 박세인
  사용 알고리즘: strassen 알고리즘
  문제 이름: 백준_10830_행렬곱셈
  핵심 포인트
    - 분할 정복(divide & conquer)로 행렬 곱셈을 풀어보자.
    - 기존의 곱셈 횟수(8번)로 인한 시간 복잡도(O(n^3))를 7번의 곱셈 횟수로 줄임으로써 시간 복잡도를 O(n^2.8xxx) 까지 줄일 수 있다.
  참고
    - 이 코드에서 실행 가능한 행렬은 2^k의 square matrix 입니다.
    - square matrix가 아닌 행렬에 대해서 strassen 알고리즘을 수행하기 위해서는 matrix의 width가 2^k가 될 때 까지 0으로 padding 해줘야 합니다.

'''
import sys

# 일반적인 행렬 곱셈식 => O(n^3)
def mulM_basic(A , B):
  matt = [[0]*len(A) for _ in range(len(A))]
  for r in range(len(A)):
    for c in range(len(A)):
      sum = 0
      for k in range(len(A)):
        sum += A[r][k] * B[k][c]
      matt[r][c] = sum
  # print(matt)
  return matt

# 대규모 행렬의 경우 4부분으로 분할
def divM(M):
  n = int(len(M)/2)# n = 2^k
  M11 = [[0]*n for _ in range(n)]
  M12 = [[0]*n for _ in range(n)]
  M21 = [[0]*n for _ in range(n)]
  M22 = [[0]*n for _ in range(n)]
  for r in range(n):
    for c in range(n):
      M11[r][c] = M[r][c]
      M12[r][c] = M[r][n+c]
      M21[r][c] = M[n+r][c]
      M22[r][c] = M[r+n][c+n]
  return M11, M12, M21, M22

def sumM(A,B):
  n = len(A)
  M = [[0]*n for _ in range(n)]
  for r in range(n):
    for c in range(n):
      M[r][c] = A[r][c] + B[r][c]
  return M

def subM(A,B):
  n = len(A)
  M = [[0]*n for _ in range(n)]
  for r in range(n):
    for c in range(n):
      M[r][c] = A[r][c] - B[r][c]
  return M

# 분할 된 행렬에 대해서 연산 실행
def conquer(M1,M2,M3,M4,M5,M6,M7):
     
  C11 = sumM(subM(sumM(M1,M4),M5),M7)
  C12 = sumM(M3,M5)
  C21 = sumM(M2,M4)
  C22 = sumM(subM(sumM(M1,M3),M2),M6)

  n = len(C11)
  C = [[0]*n*2 for _ in range(2*n)] 

  for r in range(n):
    for c in range(n):
      C[r][c] = C11[r][c]
      C[r][n+c] = C12[r][c]
      C[n+r][c] = C21[r][c]
      C[n+r][n+c] = C22[r][c]
  return C

# strassen 알고리즘으로 인해 7개의 곱셈으로 분할
def strassen(A,B):
  n = len(A)
  if (n <= 2):
    return mulM_basic(A,B)
  A11, A12, A21, A22 = divM(A)
  B11, B12, B21, B22 = divM(B)

  M1 = strassen(sumM(A11,A22),sumM(B11,B22))
  M2 = strassen(sumM(A21,A22),B11)
  M3 = strassen(A11,subM(B12,B22))
  M4 = strassen(A22,subM(B21,B11))
  M5 = strassen(sumM(A11,A12),B22)
  M6 = strassen(subM(A21,A11),sumM(B11,B12))
  M7 = strassen(subM(A12,A22),sumM(B21,B22))

  return conquer(M1,M2,M3,M4,M5,M6,M7)

if __name__ == '__main__':
  width, i = map(int,sys.stdin.readline().strip().split())
  mat =[]

  for w in range(width):
    mat.append(list(map(int,sys.stdin.readline().strip().split())))
  print(mat)
  print(f'matmul_basic: {mulM_basic(mat, mat)}')
  print(f'strassen: {strassen(mat,mat)}')