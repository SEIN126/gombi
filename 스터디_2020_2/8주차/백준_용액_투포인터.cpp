#include <iostream>
using namespace std;

const int MAX = 100000 + 1;

int N;
long long int arr[MAX];
long long int resA, resB;

int main() {

	//전체 용액 수 N입력
	cin >> N;
	//용액들의 특성 값 입력
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	//양쪽에서 중심으로 다가오는 index의 초기값
	int left = 0;
	int right = N - 1;

	//결과값의 초기값
	int resLiquid = abs(arr[left] + arr[right]);
	resA = arr[left];
	resB = arr[right];

	//양쪽에서 중심으로 오는 것을 반복(투포인터), 모든 경우 탐색 완료 후 종료
	while (left < right) {
		int tempLiquid = arr[left] + arr[right];
		if (abs(tempLiquid) < resLiquid) {
			resLiquid = abs(tempLiquid);
			resA = arr[left];
			resB = arr[right];
		}

		if (tempLiquid < 0) {
			left++;
		}
		else {
			right--;
		}
	}

	//만족하는 용액의 특성값 2개 출력
	cout << resA << " " << resB << "\n";
}