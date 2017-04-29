/*
프로그램 : 버스 운행 일정관려 프로그램 구현 (AVL Tree)

수행기능
	버스의 추가 편성 (노드의 삽입)
	버스 확인 (노드의 탐색)
	버스 예매 (노드의 탐색)
	(+ 노드의 깊이 출력)

인하대학교 컴퓨터정보공학과 2학년
학번:12131540, 이름:송금종
*/

#include <iostream>
#include <string>
#include <fstream>

#define Max 1000

using namespace std;

int Nodecount = 0;	//루트노드 여부 확인
					//(0 = 루트노드가 없다, 1 = 루트노드가 존재)


//노드(버스)가 저장할 정보
class Node
{
public:
	Node();
	__int64 start_time;	//20억 이상의 값을 입력 받을 수 있으므로 int형 사용불가
	int fixed_num;		// 버스의 정원
	int reservation_seat;	//버스의 예약된 좌석 수
	int bus_charge;		//버스의 요금
	Node* left;			//트리에서 왼쪽 자식의 주소를 저장
	Node* right;		//트리에서 오른쪽 자식의 주소를 저장
};

//생성자
Node::Node()
{
	left = NULL;
	right = NULL;
	reservation_seat = 0;	//예매 좌석은 초기에 0이다.
}

//트리의 높이를 측정하는 함수
int tree_height(Node* root)
{
	int height = 0;
	if (root != NULL)
		height = ((tree_height(root->left) > tree_height(root->right)) ? tree_height(root->left) : tree_height(root->right)) + 1;
	return height;
}

//트리의 깊이를 출력해 주는 함수
void deep(Node* root, __int64 start)
{
	int deep = 0;
	while (root->start_time != start)
	{
		if (root->start_time > start)
			root = root->left;
		else
			root = root->right;

		deep++;
		//트리에서 루트로부터 내려갈 때 마다 1씩 더한다.
		if (root == NULL)
			return;
	}
	cout << deep << endl;
}

//트리의 균형이 맞는지 확인해주는 함수
int balance_height(Node* root)
{
	if (root == NULL)
		return 0;
	return tree_height(root->left) - tree_height(root->right);
	//양수라면 왼쪽 서브트리의 높이가 크고, 음수라면 오른쪽 서브트리의 높이가 크다.
}

//트리의 균형을 맞춰주는 기능을 수행한다.
Node* avl_tree(Node* root)
{
	int balanceNum = balance_height(root);
	Node* temp, *temp2;

	if (balanceNum > 1)	//만약 왼쪽 서브트리가 오른쪽보다 2이상 크다면 균형을 맞춰줘야 하므로
	{
		if (balance_height(root->left) > 0)	//균형이 맞지않는 서브트리가 Left, Left의 형태를 띌 때
		{
			temp = root->left;
			
			root->left = temp->right;
			temp->right = root;
			return temp;
		}
		else  //균형이 맞지않는 서브트리가 Left, Right의 형태를 띌 때
		{
			temp = root->left->right;
			temp2 = root->left;

			temp2->right = temp->left;
			temp->left = temp2;
			root->left = temp->right;
			temp->right = root;
			return temp;
		}
	}
	else if (balanceNum < -1) //만약 오른쪽 서브트리가 왼쪽보다 2이상 크다면 균형을 맞춰줘야 하므로
	{
		if (balance_height(root->right) < 0) //균형이 맞지않는 서브트리가 Right, Right의 형태를 띌 때
		{
			temp = root->right;
			
			root->right = temp->left;
			temp->left = root;
			return temp;
		}
		else  //균형이 맞지않는 서브트리가 Right, Lift의 형태를 띌 때
		{
			temp = root->right->left;
			temp2 = root->right;
			root->right = temp->left;
			temp->left = root;
			temp2->left = temp->right;
			temp->right = temp2;
			return temp;
		}
	}
	return root;
}

//불러온 텍스트 파일을 기반으로 트리를 만들어준다.
Node* insert_txt(Node* root, __int64 start, int people, int reserv, int money)
{
	Node* Arr[Max];			//루트로부터 노드까지의 노드들을 저장해 준다.
	int arr_count = 0;
	
	if (Nodecount == 0)		//만약 루트노드가 생성되지 않았다면
	{
		//루트노드를 만들어준다.
		root->start_time = start;
		root->fixed_num = people;
		root->reservation_seat = reserv;
		root->bus_charge = money;
		Nodecount++;	//값을 더하여 루트노드가 이미 생성되었음을 알린다.
		return root;
	}
	
	Node* temp = root;
	while (temp != NULL)	//일단 leaf에 노드를 넣기위해 temp가 NULL이 될때까지 들어갈 위치를 찾아준다.
	{
		Arr[arr_count] = temp;
		arr_count++;
		//AVL트리는 왼쪽에서 오른쪽으로 갈수록 start_time 값이 커지므로
		if (temp->start_time > start)
			temp = temp->left;
		else if (temp->start_time < start)
			temp = temp->right;
		else
		{
			cout << "Error : 출발시간이 같습니다" << endl;
			return root;
		}
	}

	//새로운 노드를 만든다.
	Node* temp2 = new Node;
	temp2->start_time = start;
	temp2->fixed_num = people;
	temp2->reservation_seat = reserv;
	temp2->bus_charge = money;

	//루트에 노드를 추가해준다 (아직 균형 맞추기 전)
	if (Arr[arr_count-1]->start_time > start)
		Arr[arr_count-1]->left = temp2;
	else
		Arr[arr_count-1]->right = temp2;

	//temp3를 이용, 삽입한 노드로부터 조상노드를 따라 트리를 올라간다.
	Node* temp3 = Arr[arr_count];
	while (arr_count != 0)		//루트까지 확인한다.
	{
		if (temp3 == Arr[arr_count])		//값이 같다면 한칸씩 올라갈 수 있게 세팅
		{
			arr_count--;
			temp3 = Arr[arr_count];
			Arr[arr_count] = avl_tree(Arr[arr_count]);	//높이차가 2이상 있다면 값이 달라지고, 아니라면 값은 같다. 
		}
		else
			break;
	}

	//만약 루트까지 확인햇지만 두 값이 같다면 이미 균형이 맞는 상태이므로 바로 리턴
	if (temp3 == Arr[arr_count])
		return root;

	//균형이 맞지 않는다면
	Node* temp4 = root;
	while (1)
	{
		if (arr_count == 0)	//루트에서 균형이 맞지 않아 균형을 맞춘 경우
			return Arr[arr_count];

		if (temp4->left->start_time == temp3->start_time)	//만약 왼쪽 자식에서 균형을 맞추었다면
		{
			temp4->left = Arr[arr_count];
			return root;
		}
		else if (temp4->right->start_time == temp3->start_time)	//만약 오른쪽 자식에서 균형을 맞추었다면
		{
			temp4->right = Arr[arr_count];
			return root;
		}

		//삽입된 노드가 왼쪽에 있었는지 오른쪽에 있었는지 찾는다.
		if(temp4->start_time > temp3->start_time)
			temp4 = temp4->left;
		else if (temp4->start_time < start)
			temp4 = temp4->right;
		else
			cout << "Error : 일어날 수 없는 오류" << endl;
	}
}


//사용자로 부터 입력받은 값을 트리에 추가해 준다.
Node* insert_bus(Node* root, __int64 start, int people, int money)
{
	Node* Arr[Max];	//루트로부터 노드까지의 노드들을 저장해 준다.
	int arr_count = 0;

	Node* temp = root;

	while (temp != NULL)	//일단 leaf에 노드를 넣기위해 temp가 NULL이 될때까지 들어갈 위치를 찾아준다.
	{
		Arr[arr_count] = temp;
		arr_count++;
		//AVL트리는 왼쪽에서 오른쪽으로 갈수록 start_time 값이 커지므로
		if (temp->start_time > start)
			temp = temp->left;
		else if (temp->start_time < start)
			temp = temp->right;
		else
		{
			cout << "Error : 출발시간이 같습니다" << endl;
			return root;
		}
	}

	//새로운 노드를 만든다.
	Node* temp2 = new Node;
	temp2->start_time = start;
	temp2->fixed_num = people;
	temp2->bus_charge = money;

	//루트에 노드를 추가해준다 (아직 균형 맞추기 전)
	if (Arr[arr_count-1]->start_time > start)
		Arr[arr_count-1]->left = temp2;
	else
		Arr[arr_count-1]->right = temp2;

	//temp3를 이용, 삽입한 노드로부터 조상노드를 따라 트리를 올라간다.
	Node* temp3 = Arr[arr_count];
	while (arr_count != 0)		//루트까지 확인한다.
	{
		if (temp3 == Arr[arr_count])		//값이 같다면 한칸씩 올라갈 수 있게 세팅
		{
			arr_count--;
			temp3 = Arr[arr_count];
			Arr[arr_count] = avl_tree(Arr[arr_count]);	//높이차가 2이상 있다면 값이 달라지고, 아니라면 값은 같다. 
		}
		else
			break;
	}

	//만약 루트까지 확인햇지만 두 값이 같다면 이미 균형이 맞는 상태이므로 바로 리턴
	if (temp3 == Arr[arr_count])
		return root;

	//균형이 맞지 않는다면
	Node* temp4 = root;
	while (1)
	{
		if (arr_count == 0)	//루트에서 균형이 맞지 않아 균형을 맞춘 경우
			return Arr[arr_count];

		if (temp4->left->start_time == temp3->start_time)	//만약 왼쪽 자식에서 균형을 맞추었다면
		{
			temp4->left = Arr[arr_count];
			return root;
		}
		else if (temp4->right->start_time == temp3->start_time)	//만약 오른쪽 자식에서 균형을 맞추었다면
		{
			temp4->right = Arr[arr_count];
			return root;
		}

		//삽입된 노드가 왼쪽에 있었는지 오른쪽에 있었는지 찾는다.
		if (temp4->start_time > temp3->start_time)
			temp4 = temp4->left;
		else if (temp4->start_time < start)
			temp4 = temp4->right;
		else
			cout << "Error : 일어날 수 없는 오류" << endl;
	}
}

//버스 출발시각 입력받아 그와 같은 버스를 찾아 버스의 정보를 출력한다.
void bus_info(Node* root, __int64 start)
{
	//while문을 활용해 입력받은 버스 출발 시각과 같은 버스 출발 시각을 가지는 노드를 찾는다.
	Node* temp = root;
	while (root->start_time != start)
	{
		if (root->start_time > start)
			root = root->left;
		else
			root = root->right;

		//만약 없다면
		if (root == NULL)
		{
			cout << "Not found!" << endl;
			return;
		}
	}

	//버스의 정보를 출력
	cout << root->start_time << " " << root->fixed_num << " ";
	cout << root->reservation_seat << " " << root->bus_charge << " ";
	deep(temp, start);
}

//버스 출발 시각을 입력받아 그와 같은 버스 출발 시각을 가지는 버스에서 좌석을 예약하는 함수
void reservation(Node* root, __int64 start, int reserv)
{
	Node* temp = root;
	//입력받은 버스 출발 시각과 같은 버스 출발 시각을 가지는 노드를 찾는다.
	while (root->start_time != start)
	{
		if (root->start_time > start)
			root = root->left;
		else
			root = root->right;
	
		if (root == NULL)
		{
			cout << "Not found!" << endl;
			return;
		}
	}

	//만약 이미 예약된 수와 예약하고자 하는 수가 정원을 초과한다면 오류메세지 출력
	if (root->reservation_seat + reserv > root->fixed_num)
	{
		cout << "No more seats available!" << endl;
		return;
	}

	//예약이 가능하다면 버스 좌석을 예약하고 깊이를 출력한다.
	root->reservation_seat += reserv;
	deep(temp, start);
}

int main()
{
	Node* root = new Node;
	
	char insert;	// 삽입, 확인, 예매 질의 확인
	__int64 start;	// 버스 출발 시각 
	int people;		// 버스의 정원
	int reserv;		// 예약하고자 하는 인원
	int money;		// 버스 요금 
	
	//사용자로부터 파일명을 입력받아 입력받은 파일명에 해당하는 파일을 연다.
	string txt;
	cin >> txt;
	ifstream ifs;
	ifs.open(txt);

	if (ifs.is_open())		//만약 파일 열기에 성공했다면
	{
		//저장되어있는 값들을 불러온다.
		while (ifs >> start >> people >> reserv >> money)
			root=insert_txt(root, start, people, reserv, money);	//그리고 그 값들로 트리를 만든다.				
	}
	ifs.close();
	
	while (cin >> insert){
		switch (insert)
		{
			case 'I':	//만약 추가 편성 질의가 들어왔다면
			{
				cin >> start >> people >> money;
				root=insert_bus(root, start, people, money);
				deep(root, start);
				continue;
			}

			case 'P':	//만약 버스 확인 질의가 들어왔다면
			{
				cin >> start;
				bus_info(root, start);
				continue;
			}
			case 'R':	//만약 버스 예약 질의가 들어왔다면
			{
				cin >> start >> reserv;
				reservation(root, start, reserv);
				continue;
			}
			
			//입력 예외 발생시
			default:
				cout << "Error" << endl;
		}
	}
}