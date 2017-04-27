// ���� ���� ����Ʈ�� ������, ������, ��������, ��������, �߰�����, �߰�����

#include <iostream>
#include <string>
using namespace std;

struct Node{
	string text;
	Node* tail;
};

class SLinkedList
{
public:
	Node* LinkHead;
	Node* tempPoint;
	int count;

	SLinkedList(){
		LinkHead = NULL;
		count = 0;
	}

	void insertingAtTheHead(string txt){
		Node* temp = new Node();
		temp->text = txt;
		temp->tail = LinkHead;

		LinkHead = temp;
		count++;
	}

	void deletingAtTheHead(){
		Node* temp;
		temp = LinkHead;
		LinkHead = LinkHead->tail;

		delete(temp);
		count--;
	}

	void insertingAtTheTail(string txt){
		Node* temp = new Node();
		temp->text = txt;
		temp->tail = NULL;
		tempPoint = LinkHead;
		while(tempPoint->tail != NULL){
			tempPoint = tempPoint->tail;
		}
		tempPoint->tail = temp;
		count++;
	}

	void deletingAtTheTail(){
		Node* p;
		tempPoint = LinkHead;
		while((tempPoint->tail)->tail != NULL){
			tempPoint = tempPoint->tail;
		}
		p = tempPoint->tail;
		tempPoint->tail = NULL;

		delete(p);
		count--;
	}

	void inserting(string txt, int number){
		Node* temp = new Node();
		Node* p;
		temp->text = txt;
		tempPoint = LinkHead;
		for(int i = 1; i < number; i++){
			tempPoint = tempPoint->tail;
		}
		p = tempPoint;
		tempPoint = LinkHead;
		for(int i = 1; i < number-1; i++){
			tempPoint = tempPoint->tail;
		}
		tempPoint->tail = temp;
		temp->tail = p;

		count++;
	}

	void deleting(int number){
		Node* p;
		Node* q;
		tempPoint = LinkHead;
		for(int i = 0; i < number; i++){
			tempPoint = tempPoint->tail;
		}
		p = tempPoint; // number+1 ��°�� ���
		tempPoint = LinkHead;
		for(int i = 1; i < number; i++){
			tempPoint = tempPoint->tail;
		}
		q = tempPoint;
		tempPoint = LinkHead;
		for(int i = 1; i < number-1; i++){
			tempPoint = tempPoint->tail;
		}
		tempPoint->tail = p; // tempPoint = number-1 ��°�� ���

		delete(q);

		count--;
	}

	void printAll(){
		tempPoint = LinkHead;

		while(tempPoint->tail != NULL){
			cout << tempPoint->text << " -> ";
			tempPoint = tempPoint->tail;
		}
		cout << tempPoint->text << endl;
		cout << "��������� ��� ���� " << count << "�� �Դϴ�." << endl;
	}
};

int main()
{
	SLinkedList *mySLinkedList = new SLinkedList();

	mySLinkedList->insertingAtTheHead("����");
	mySLinkedList->insertingAtTheHead("��Ȳ");
	mySLinkedList->insertingAtTheHead("���");
	mySLinkedList->insertingAtTheHead("�ʷ�");
	mySLinkedList->insertingAtTheHead("�Ķ�");
	mySLinkedList->insertingAtTheHead("����");
	mySLinkedList->insertingAtTheHead("����");
	mySLinkedList->printAll();
	
	mySLinkedList->deletingAtTheHead();
	mySLinkedList->printAll();

	mySLinkedList->insertingAtTheTail("����");
	mySLinkedList->printAll();

	mySLinkedList->deletingAtTheTail();
	mySLinkedList->printAll();

	mySLinkedList->inserting("4��°", 4);
	mySLinkedList->printAll();

	mySLinkedList->deleting(4);
	mySLinkedList->printAll();

	system("pause");
	return 0;
}