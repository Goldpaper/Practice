/*
프로그램 : 이진트리(binary tree) 구현
(노드의 삽입, 전위순회, 후위순회, 노드의 좌표 출력 가능)

인하대학교 컴퓨터정보공학과 2학년
학번:12131540, 이름:송금종
*/

#include <iostream>
using namespace std;

//트리 클래스
class bTree
{
public:
	bTree* left;	//왼쪽 노드를 가리킴
	bTree* right;	//오른쪽 노드를 가리킴
	int data;		//번호를 저장한다
};

bTree* btemp1;		//노드를 찾았을때 값을 임시로 저장하기 위한 용도 
int k = 0;			//노드를 찾을때 함수를 찾았는지 확인하는 용도(0 or 1)

//해당하는 번호를 가지는 노드의 주소를 찾는 함수
void whereIs(bTree*, int);

//루트노드 (가장 처음에만 실행됨)를 만드는 함수
bTree* makeRoot(int node_num)
{
	bTree* node = (bTree*)malloc(sizeof(bTree));
	node->left = NULL;
	node->right = NULL;
	node->data = node_num;
	return node;
}

//왼쪽에 자식을 만드는 함수
void makeLeft(bTree* root, int node_num, int parent_num)
{
	bTree* node = (bTree*)malloc(sizeof(bTree));	//새로운 노드를 생성

	whereIs(root, parent_num);	//부모노드가 어디있는지 찾자
	root = btemp1;

	if (root->left == NULL){	//비었다면 만들어줘라
		root->left = node;
		node->data = node_num;
		node->left = NULL;
		node->right = NULL;
	}
	else
		root->left->data = node_num;	//이미 노드가 있다면 번호만 바꿔줘
}

//오른쪽에 자식을 만드는 함수
void makeRight(bTree* root, int node_num, int parent_num)
{
	bTree* node = (bTree*)malloc(sizeof(bTree));

	whereIs(root, parent_num);	//부모노드가 어디있는지 찾자
	root = btemp1;

	if (root->right == NULL){	//비었다면 만들어주자
		root->right = node;
		node->data = node_num;
		node->left = NULL;
		node->right = NULL;
	}
	else
		root->left->data = node_num;	//이미 노드가 있다면 번호만 바꿔줘
}

//해당하는 번호를 가지는 노드의 주소를 찾는 함수 
void whereIs(bTree* root, int data)
{
	int c = 0;		//재귀함수 호출될때마다 초기화된다.
	if (k == 1)		//만약 해당하는 번호를 찾았다면 함수를 빠져나오기 위해 계속 리턴만 해주는 역할 
		return;

	if (root->data == data){
		btemp1 = root;
		k = 1;
	}

	if (root->left == NULL)		//만약 왼쪽 노드가 비었다면
		c += 1;

	if (root->right == NULL)	//만약 오른쪽 노드가 비었다면
		c += 2;


	switch (c)
	{
	case 0:{						//c=0 이라는 말은 양쪽노드가 모두 비어있지 않은 상태이므로 양쪽을 모두 찾아본다.
		whereIs(root->left, data);
		whereIs(root->right, data);
		break;
	}
	case 1:{						//c=1 이라는 말은 오른쪽 노드만 있는 상태
		whereIs(root->right, data);
		break;
	}
	case 2:{						//c=2 라는 말은 왼쪽 노드만 있는 상태
		whereIs(root->left, data);
		break;
	}
	case 3:							//양쪽 노드가 없으므로 break(함수를 종료)
		break;

	default:						//일어날리 없겠지만..
		cout << "Error" << endl;
	}
	k = 0;	//마지막에 k=0 으로 초기화 시켜준다
}

//전위순회 하는 함수
void Preorder(bTree* root)
{
	if (root == NULL)		//탈출 조건
		return;

	cout << root->data << " ";
	Preorder(root->left);
	Preorder(root->right);
}

//후위순회하는 함수
void Postorder(bTree* root)
{
	if (root == NULL)		//탈출 조건
		return;

	Postorder(root->left);
	Postorder(root->right);
	cout << root->data << " ";
}

//좌표를 찾는 함수 (중위순회의 응용)
void Coordinate(bTree* root, int num, int& x, int y)
{
	if (root == NULL)		//root가 NULL이면 리턴하고
	{
		y -= 1;				//리턴하면 위로 올라가므로 y를 감소시킨다.
		return;
	}

	Coordinate(root->left, num, x, y + 1);	//left에 있는 노드로 이동할때는 내려가므로 y를 증가시킨다.

	if (root->data == num)			//해당하는 번호가 그 노드에 있니?
	{
		cout << x << " " << y;		//그렇다면 좌표를 출력
		return;
	}
	x = x + 1;	//x좌표를 증가시켜준다 (중위순회이므로 x좌표를 기준으로 생각하면 1씩 증가하면서 탐색한다)

	Coordinate(root->right, num, x, y + 1);	//right에 있는 노드로 이동할때는 내려가므로 y를 증가시킨다.

}

int main()
{
	bTree* root;	//root라는 bTree형 포인터를 만든다.

	//입력받을때
	char insert_num;	//삽입 질의를 구분한다 (I,P,T,C 구분하는 용도)	
	int node_num;		//삽입될 노드의 번호를 2번째로 입력받는다
	int parent_num;		//삽입될 노드의 부모노드 번호를 입력받는다 (3번째로 입력받는다)
	char left_right;	//삽입될 노드가 왼쪽인지 오른쪽인지 구별한다 (4번째로 입력받는다)

	int x = 1;			//노드의 x좌표를 표시하는 변수
	int y = 0;			//노드의 y좌표를 표시하는 변수

	int count = 0;		//루트노드가 호출된적이 있는가? (0=없다)

	while (cin >> insert_num){		//삽입 질의를 입력받는다. 
		switch (insert_num){		//스위치로 질의를 구별
		case 'I':
		{
			cin >> node_num >> parent_num >> left_right;		//나머지를 순서대로 입력받는다.

			if (left_right == 'L' && parent_num == -1){			//부모노드의 번호가 -1이고, 왼쪽삽입이라면
				if (count != 0)			//루트노드가 이미 있다면
					root->data = node_num;	//루트노드의 번호만 바꿔준다
				else{					//루트노드가 없다면
					root = makeRoot(node_num);	//만들어준다
					count++;			//count를 증가시켜 루트노드는 반드시 한번만 만들어진다.
				}
				continue;
			}

			if (left_right == 'L'){						//왼쪽에 노드를 만든다
				makeLeft(root, node_num, parent_num);
				continue;
			}
			else{
				makeRight(root, node_num, parent_num);	//오른쪽에 노드를 만든다
				continue;
			}
		}

		//전위 순회
		case 'P':
		{
			Preorder(root);
			cout << endl;
			continue;
		}


		//후위 순회
		case 'T':
		{
			Postorder(root);
			cout << endl;
			continue;
		}


		//좌표출력
		case 'C':{
			cin >> node_num;		//찾을 노드를 입력받는다.
			Coordinate(root, node_num, x, y);
			x = 1;
			cout << endl;
			continue;
		}


		//예외 발생시 (발생할리 없다고 가정했지만) 
		default:
			cout << "Error" << endl;
		}
	}
}