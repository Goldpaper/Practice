#include <iostream>
#include <string>
using namespace std;

struct Node{
	string text;
	Node* tail; //뒤의 노드를 가리키는 link
	Node* front; //앞의 노드를 가리키는 link
};

class DLinkedList
{
public:
	Node* LinkHead;
	Node* LinkTail;
	Node* tempPoint;
	int count;

	DLinkedList(){
		LinkHead = NULL;
		LinkTail = NULL;
		count = 0;
	}

	void insertingAtTheHead(string txt){
		Node* temp = new Node();
		temp->text = txt;
		temp->tail = LinkHead;
		temp->front = NULL;
		if (count == 0)
			LinkTail = temp;
		else
			LinkHead->front = temp;

		LinkHead = temp;
		count++;
	}

	void deletingAtTheHead(){
		Node* temp;
		temp = LinkHead;
		LinkHead = LinkHead->tail;
		LinkHead->front = NULL;

		delete(temp);
		count--;
	}

	void insertingAtTheTail(string txt){
		Node* temp = new Node();
		temp->text = txt;
		temp->tail = NULL;
		temp->front = LinkTail;
		if (count == 0)
			LinkHead = temp;
		else
			LinkTail->tail = temp;

		LinkTail = temp;
		count++;
	}

	void deletingAtTheTail(){
		Node* temp;
		temp = LinkTail;
		LinkTail = LinkTail->front;
		LinkTail->tail = NULL;

		delete(temp);
		count--;
	}

	void inserting(string txt, int number){
		Node* temp = new Node();
		Node* p;
		temp->text = txt;
		tempPoint = LinkHead;
		for (int i = 1; i < number; i++){
			tempPoint = tempPoint->tail;
		}
		p = tempPoint;
		tempPoint = LinkHead;
		for (int i = 1; i < number - 1; i++){
			tempPoint = tempPoint->tail;
		}
		tempPoint->tail = temp;
		temp->front = tempPoint;
		temp->tail = p;
		p->front = temp;

		count++;
	}

	void deleting(int number){
		Node* p;
		Node* q;
		tempPoint = LinkHead;
		for (int i = 0; i < number; i++){
			tempPoint = tempPoint->tail;
		}
		p = tempPoint; // number+1 번째의 노드
		tempPoint = LinkHead;
		for (int i = 1; i < number; i++){
			tempPoint = tempPoint->tail;
		}
		q = tempPoint;
		tempPoint = LinkHead;
		for (int i = 1; i < number - 1; i++){
			tempPoint = tempPoint->tail;
		}
		tempPoint->tail = p; // tempPoint = number-1 번째의 노드
		p->front = tempPoint;

		delete(q);

		count--;
	}

	void printAll(){
		tempPoint = LinkHead;

		while (tempPoint->tail != NULL){
			cout << tempPoint->text << " -> ";
			tempPoint = tempPoint->tail;
		}
		cout << tempPoint->text << endl;
		cout << "현재까지의 노드 수는 " << count << "개 입니다." << endl;
	}
};

int main()
{
	DLinkedList *myDLinkedList = new DLinkedList();

	myDLinkedList->insertingAtTheTail("빨강");
	myDLinkedList->insertingAtTheHead("주황");
	myDLinkedList->insertingAtTheHead("노랑");
	myDLinkedList->insertingAtTheHead("초록");
	myDLinkedList->insertingAtTheHead("파랑");
	myDLinkedList->insertingAtTheHead("남색");
	myDLinkedList->insertingAtTheHead("보라");
	myDLinkedList->printAll();

	myDLinkedList->deletingAtTheHead();
	myDLinkedList->printAll();

	myDLinkedList->insertingAtTheTail("뭘까");
	myDLinkedList->printAll();

	myDLinkedList->deletingAtTheTail();
	myDLinkedList->printAll();

	myDLinkedList->inserting("4번째", 4);
	myDLinkedList->printAll();

	myDLinkedList->deleting(4);
	myDLinkedList->printAll();

	return 0;
}
