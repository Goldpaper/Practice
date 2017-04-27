#include <iostream>
#include <string>
using namespace std;

struct Node{
	string text;
	Node* tail; //���� ��带 ����Ű�� link
	Node* front; //���� ��带 ����Ű�� link
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
		p = tempPoint; // number+1 ��°�� ���
		tempPoint = LinkHead;
		for (int i = 1; i < number; i++){
			tempPoint = tempPoint->tail;
		}
		q = tempPoint;
		tempPoint = LinkHead;
		for (int i = 1; i < number - 1; i++){
			tempPoint = tempPoint->tail;
		}
		tempPoint->tail = p; // tempPoint = number-1 ��°�� ���
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
		cout << "��������� ��� ���� " << count << "�� �Դϴ�." << endl;
	}
};

int main()
{
	DLinkedList *myDLinkedList = new DLinkedList();

	myDLinkedList->insertingAtTheTail("����");
	myDLinkedList->insertingAtTheHead("��Ȳ");
	myDLinkedList->insertingAtTheHead("���");
	myDLinkedList->insertingAtTheHead("�ʷ�");
	myDLinkedList->insertingAtTheHead("�Ķ�");
	myDLinkedList->insertingAtTheHead("����");
	myDLinkedList->insertingAtTheHead("����");
	myDLinkedList->printAll();

	myDLinkedList->deletingAtTheHead();
	myDLinkedList->printAll();

	myDLinkedList->insertingAtTheTail("����");
	myDLinkedList->printAll();

	myDLinkedList->deletingAtTheTail();
	myDLinkedList->printAll();

	myDLinkedList->inserting("4��°", 4);
	myDLinkedList->printAll();

	myDLinkedList->deleting(4);
	myDLinkedList->printAll();

	return 0;
}
