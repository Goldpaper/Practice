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
		cout << "현재" << count << " 개의 큐가 남아 있습니다." << endl;
		cout << "큐를 꺼냈더니 " << arr[temp-1] << " 이네!" << endl << endl;
		count--;
	}


};
int main()
{
	Queue q;
	
	cout << "큐 넣는다!" << endl;
	q.putqueue("바보");
	q.putqueue("멍충이");
	q.putqueue("메롱");

	cout << "큐에 바보, 멍충이, 메롱을 차례로 넣었다. 이제 하나씩 빼보자" << endl << endl;

	q.getqueue();
	q.getqueue();
	q.getqueue();

	cout << endl << "끝" << endl;

	

}