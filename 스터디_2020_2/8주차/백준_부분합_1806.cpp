/*작성자: 변준영
알고리즘: 이분탐색(정해는 투포인터)
기출문제 출처: 불명
문제 이름: 부분합
*/
#include<stdio.h>

#pragma warning(disable:4996)
int N, S;
bool isitpossible(int length);
int numbers[200001];
int isitcan(int start, int ends);
int main(void) {
	//용액의 갯수, 목표 합 찾기
	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; i++)
		scanf("  %d", &numbers[i]);
	//길이가 N인 것이 불가능하면 실패 출력(더 작은건 당연히 S를 넘지 못함)
	if (isitpossible(N) == false) {
		printf("0");
	}	
	else
		//이분탐색으로 용액의 부분합을 출력
		printf("%d",isitcan(1, N));

}
//이분탐색
int isitcan(int start, int ends){
	//시작을 ends는 가능하게 하였으므로 무조건 탐색 값이 나옴
	if (start == ends) {
		return ends;
	}

	int middle = (start + ends) / 2;
	//미들 부분이 가능하다
	if (isitpossible(middle) == true)
		//start 모름, middle 가능
		return isitcan(start, middle);
	else
		//middle+1 모름, ends 가능
		return isitcan(middle + 1, ends);
}
//길이 확인하는 함수
bool isitpossible(int length) {
	int num = 0;
	int first = 0;//처음 가리키는거
	int end = length-1;//끝에 가리키는거
	for (int i = 0; i < length; i++) 
	{
		num += numbers[i];
	}
	while (end < N){
		//하나라도 넘으면 참 출력
		if (num >= S) {
			return true;
		}
		//아닌경우 젤 첫번째와 제일 끝에꺼 빼면서 확인
		num -= numbers[first++];
		num += numbers[++end];
	} 
	//탐색했을때 없는경우 실패 출력
	return false;

}
