#include <iostream>
#include <string>
using namespace std;

class Data
{
public:
	string text;
	Data()
	{}
};

class Queue
{
public:
	int count;
	string* arr = new string[100];
	Data d;

	Queue()
	{
		count = 0;
	}

	void putqueue(string text)
	{
		d.text = text;
		arr[count] = d.text;
		count++;
	}

	void getqueue()
	{
		int temp = count;
		cout << "����" << count << " ���� ť�� ���� �ֽ��ϴ�." << endl;
		cout << "ť�� ���´��� " << arr[temp-1] << " �̳�!" << endl << endl;
		count--;
	}


};
int main()
{
	Queue q;
	
	cout << "ť �ִ´�!" << endl;
	q.putqueue("�ٺ�");
	q.putqueue("������");
	q.putqueue("�޷�");

	cout << "ť�� �ٺ�, ������, �޷��� ���ʷ� �־���. ���� �ϳ��� ������" << endl << endl;

	q.getqueue();
	q.getqueue();
	q.getqueue();

	cout << endl << "��" << endl;

	

}