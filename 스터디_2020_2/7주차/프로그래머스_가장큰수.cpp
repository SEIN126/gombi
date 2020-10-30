#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//숫자 순서에 따라 어떤 것이 큰지 판별하는 bigS함수 생성
bool bigS(const string& a, const string& b) {
	return a + b > b + a ? true : false;
}

string solution(vector<int> numbers) {

	string answer = "";
	vector<string> strArr;

	//numbers의 정수들을 string으로 형변환 하여 strArr에 넣음
	for (int i = 0; i < numbers.size(); i++) {
		strArr.push_back(to_string(numbers.at(i)));
	}

	//위에서 만든 bigS를 이용해 sort(<algorithm>헤더파일에 존재)
	sort(strArr.begin(), strArr.end(), bigS);

	//정렬한 것들을 이어붙임
	for (string str : strArr) {
		answer += str;
	}

	//만약에 0 한개이면 문자열 "0"반환
	if (answer[0] == '0') {
		return "0";
	}
	return answer;
}