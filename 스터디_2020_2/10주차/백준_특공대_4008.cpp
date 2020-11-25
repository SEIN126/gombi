/*작성자: 변준영
  사용 알고리즘: 컨벡스헐 트릭, 다이나믹 프로그래밍,
  사용 자료구조: 스택
  문제 이름: 특공대
  [출처]: 라이 나무자르기 코드 변형
*/

#include <stdio.h>
#include <cstdio>
#include <algorithm>
#pragma warning(disable:4996)
int N;
long long a, b, c;
long long sum[1000001];
using namespace std;
const int MAX = 1000001;
struct LinearFunc {
	long long gradient, intercept;
	double startpoint;
	LinearFunc() : LinearFunc(1, 0) {}
	LinearFunc(long long a1, long long b1) : gradient(a1), intercept(b1), startpoint(0) {}
};
inline double cross(LinearFunc& f, LinearFunc& g)
{
	return (double)(g.intercept - f.intercept) / (f.gradient - g.gradient);
}
//스택
LinearFunc f[MAX];
//dp
long long dp[MAX] = { 0 };
long long y_intercept(int j) {

	return (a * sum[j] * sum[j]) - (b * sum[j]) + dp[j];
}
long long Quadratic(long long num)
{
	long long output = (a * (num) * (num)) + b * (num)+c;
	return output;
}
void init() {
	scanf("%d", &N);
	scanf("%lld %lld %lld", &a, &b, &c);
	for (int i = 1, number; i <= N; i++)
	{
		scanf("%d", &number);
		sum[i] = sum[i - 1] + (long long)number;
	}

}


int main(void)
{

	init();

	//스택
	int top = 0;
	//그 전값이 위치해 있는 함수 찾기
	int fpos = 0;

	/*
	시간복잡도 O(N^2)인 DP 풀이

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j < i; j++) 
		{
			dp[i] = max(dp[j]+Quadratic(sum[i]-sum[j]),dp[i]);
		}
	}
		printf("%lld", dp[N]);
	*/
	

	/*DP와 컨벡스헐 트릭을 사용하여서 시간복잡도가 O(N)인 풀이 컨벡스헐 트릭은 나무자르기에서 설명*/
	//dp식을 변형하면
	/*dp[i]=max[  (-2*a*sum[j])*sum[i] + (a * sum[j]^2) - (b * sum[j]) + dp[j] ]+ Quadratic(sum[i]) (0<=j<i)*/
	/*이때 -2a*sum[j] 즉 일차함수의 기울기가 단조증가하고, sum[i], x좌표 또한 증가하므로, 컨벡스헐 트릭의 변형을 이용해 시간복잡도 O(N)의 풀이가 가능해진다. */
	for (int i = 1; i <= N; ++i) {
		//갱신된 dp를 이용해 일차함수 생성, 첫 시작은 0번째 부터(암것도 없)
		LinearFunc g(sum[i-1], y_intercept(i-1));
		//Convex hull trick
		while (top > 0) {
			//교점 구하기
			g.startpoint = cross(f[top - 1], g);
			/*새로 생성된 함수의 교점(s)이 그전 스택에 위치해 있는
			함수의 s보다 작으면 현재 스택의 가장 위에 있는 일차함수는 사용하지 않음*/
			if (f[top - 1].startpoint < g.startpoint) break;

			//줄어든 이후 함수의 스택이 그 전에 참조한 곳 까지 오면 fpos 또한 감수
			if (--top == fpos) --fpos;
		}
		//스택에 g 추가
		f[top++] = g;

		long long x =(long long)(-2)*a*sum[i];
		// fpos가 x좌표를 포함할 때까지 증가시킴
		while (fpos + 1 < top && f[fpos + 1].startpoint < x) ++fpos;
		//dp[i] 갱신
		dp[i] = (f[fpos].gradient * x) + (f[fpos].intercept)+ Quadratic(sum[i]);
	}


	
	printf("%lld", dp[N]);
}
