#include <iostream>

using namespace std;

class Node
{
public:
	int data;
	Node* node;
};

class SLL	//single linked list
{
public:
	Node* linkhead;
	Node* temppoint;
	int count;

	SLL();
	void inshead(int);
	void ins(int,int);
	void instail(int);
	void delhead();
	void del(int);
	void deltail();
	void print();
};

SLL::SLL()
{
	linkhead = NULL;
	count = 0;
}

void SLL::inshead(int data)			//링크의 제일 앞에 데이터를 만들어서 연결
{
	Node* temp = new Node();
	temp->data = data;
	temp->node = linkhead;
	linkhead = temp;
	count++;
}

void SLL::ins(int data, int tempnum)	//tempnum번째로 하겠다.
{
	if (count == 0 || tempnum==1)
		inshead(data);
	else
	{
		Node* temp = new Node;
		Node* temp2 = linkhead->node;
		temp->data = data;
		temppoint = linkhead;
		while (tempnum != 2)
		{
			temppoint = temppoint->node;
			temp2 = temp2->node;
			tempnum--;
		}
		temppoint->node = temp;
		temp->node = temp2;
		count++;
	}
}

void SLL::instail(int data)
{
	if (count == 0)
		inshead(data);
	else
	{
		Node* temp = new Node();
		temp->data = data;
		temp->node = NULL;
		temppoint = linkhead;
		while (temppoint->node != NULL)
		{
			temppoint = temppoint->node;
		}
		temppoint->node = temp;
		count++;
	}
}

void SLL::delhead()
{
	Node* temp;
	temp = linkhead;
	linkhead = linkhead->node;
	delete(temp);
	count--;
}

void SLL::del(int tempnum)
{
	Node* temp = linkhead;
	Node* p;
	if (tempnum == 1)
		delhead();
	else
	{
		while (tempnum != 2)
		{
			temp = temp->node;
			tempnum--;
		}
		p = temp->node;
		temp->node = temp->node->node;
		delete(p);
		count--;
	}
}

void SLL::deltail()
{
	Node* temp;
	temppoint = linkhead;
	while ((temppoint->node)->node != NULL)
	{
		temppoint = temppoint->node;
	}
	temp = temppoint->node;
	temppoint->node = NULL;
	delete(temp);
	count--;
}

void SLL::print()
{
	temppoint = linkhead;
	while (temppoint->node != NULL)
	{
		cout << temppoint->data << ", ";
		temppoint = temppoint->node;
	}
	cout << temppoint->data << endl;
}

int main()
{
	cout << "시작한다!!!!" << endl;
	SLL* sll=new SLL();

	sll->inshead(0);
	sll->ins(1,1);
	sll->ins(2,2);
	sll->ins(3,3);
	
	sll->del(2);
	sll->print();
}