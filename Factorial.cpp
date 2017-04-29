//		Factorial.cpp
//	설명 : n!을 구하는 프로그램
//	작성자 : 12131540 송금종

#include <iostream>
#include <safeint.h>								//SafeInt 라이브러리를 사용하기위해 헤더파일 포함시킨다.

using namespace std;
using namespace msl::utilities;						//SafeInt를 사용하기 위해 utilities 이름공간 선언

__int64 fact_iter(int, SafeInt<__int64>);					//반복문을 통한 팩토리얼 출력
__int64 fact_rec(int, SafeInt<__int64>);					//재귀함수를 통한 팩토리얼 출력

int main()
{
	int num;							//사용자가 정하는 값 (n 입력 => n! 계산하도록)
	__int64 sum = 1;					//팩토리얼의 값
	cin >> num;							//사용자가 값을 입력해서 num에 저장한다.
	
	try									//이곳에서 오류가 발생하면 (ex:오버플로우) try를 빠져나와 catch 명령을 시행하게 된다.
	{
		cout << "반복 " << num << "! = " << fact_iter(num, sum) << endl;		//fact_iter의 결과가 출력됨
		cout << "재귀 " << num << "! = " << fact_rec(num, sum) << endl;			//fact_rec의 결과가 출력됨
	}
	
	catch (SafeIntException e)									//try 안에서 예외(오버플로우)가 발생하면 이 명령 실행 
	{															//(가능한 크게 하려고 __int64를 사용하였지만 20자리를 넘어서면 catch문으로 이동)
		cout << "Overflow가 발생하였습니다." << endl;
		cout << "에러 코드 : " << e.m_code << endl;				//에러코드 : 1 (1이 오버플로우를 의미)
		cout << "프로그램을 종료합니다." << endl;
		return -1;												//비정상 종료를 의미한다.
	}

	return 0;													//프로그램의 정상적인 종료를 의미함
}

__int64 fact_iter(int n, SafeInt<__int64> s)		//반복문을 통한 팩토리얼 출력
{
		for (int i = n; i > 1; i--)		// 반복문 돌림 (n-1번)
			s *= i;						// i값이 감소하면서 곱하기 수행
		return s;						// 계산된 팩토리얼 값 출력	
}

__int64 fact_rec(int n, SafeInt<__int64> s)			//재귀함수를 통한 팩토리얼 출력
{
	if (n > 1)							// n이 1보다 크면 (아직 팩토리얼이 나오기 위해 2까지 곱해지지 않았다면)
	{
		s *= n;							// s에 n을 곱한다. 
		return fact_rec(n - 1, s);		// n의 값을 하나 줄여서 fact_rec의 값을 출력한다.
	}
	else
		return s;						// 모두 곱해지면(팩토리얼 값 나오면) 값을 반환
}