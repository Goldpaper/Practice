//		Factorial.cpp
//	���� : n!�� ���ϴ� ���α׷�
//	�ۼ��� : 12131540 �۱���

#include <iostream>
#include <safeint.h>								//SafeInt ���̺귯���� ����ϱ����� ������� ���Խ�Ų��.

using namespace std;
using namespace msl::utilities;						//SafeInt�� ����ϱ� ���� utilities �̸����� ����

__int64 fact_iter(int, SafeInt<__int64>);					//�ݺ����� ���� ���丮�� ���
__int64 fact_rec(int, SafeInt<__int64>);					//����Լ��� ���� ���丮�� ���

int main()
{
	int num;							//����ڰ� ���ϴ� �� (n �Է� => n! ����ϵ���)
	__int64 sum = 1;					//���丮���� ��
	cin >> num;							//����ڰ� ���� �Է��ؼ� num�� �����Ѵ�.
	
	try									//�̰����� ������ �߻��ϸ� (ex:�����÷ο�) try�� �������� catch ����� �����ϰ� �ȴ�.
	{
		cout << "�ݺ� " << num << "! = " << fact_iter(num, sum) << endl;		//fact_iter�� ����� ��µ�
		cout << "��� " << num << "! = " << fact_rec(num, sum) << endl;			//fact_rec�� ����� ��µ�
	}
	
	catch (SafeIntException e)									//try �ȿ��� ����(�����÷ο�)�� �߻��ϸ� �� ��� ���� 
	{															//(������ ũ�� �Ϸ��� __int64�� ����Ͽ����� 20�ڸ��� �Ѿ�� catch������ �̵�)
		cout << "Overflow�� �߻��Ͽ����ϴ�." << endl;
		cout << "���� �ڵ� : " << e.m_code << endl;				//�����ڵ� : 1 (1�� �����÷ο츦 �ǹ�)
		cout << "���α׷��� �����մϴ�." << endl;
		return -1;												//������ ���Ḧ �ǹ��Ѵ�.
	}

	return 0;													//���α׷��� �������� ���Ḧ �ǹ���
}

__int64 fact_iter(int n, SafeInt<__int64> s)		//�ݺ����� ���� ���丮�� ���
{
		for (int i = n; i > 1; i--)		// �ݺ��� ���� (n-1��)
			s *= i;						// i���� �����ϸ鼭 ���ϱ� ����
		return s;						// ���� ���丮�� �� ���	
}

__int64 fact_rec(int n, SafeInt<__int64> s)			//����Լ��� ���� ���丮�� ���
{
	if (n > 1)							// n�� 1���� ũ�� (���� ���丮���� ������ ���� 2���� �������� �ʾҴٸ�)
	{
		s *= n;							// s�� n�� ���Ѵ�. 
		return fact_rec(n - 1, s);		// n�� ���� �ϳ� �ٿ��� fact_rec�� ���� ����Ѵ�.
	}
	else
		return s;						// ��� ��������(���丮�� �� ������) ���� ��ȯ
}