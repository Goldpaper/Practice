/*
���α׷� : ���� ���� �������� ���α׷� ���� (AVL Tree)

������
	������ �߰� �� (����� ����)
	���� Ȯ�� (����� Ž��)
	���� ���� (����� Ž��)
	(+ ����� ���� ���)

���ϴ��б� ��ǻ���������а� 2�г�
�й�:12131540, �̸�:�۱���
*/

#include <iostream>
#include <string>
#include <fstream>

#define Max 1000

using namespace std;

int Nodecount = 0;	//��Ʈ��� ���� Ȯ��
					//(0 = ��Ʈ��尡 ����, 1 = ��Ʈ��尡 ����)


//���(����)�� ������ ����
class Node
{
public:
	Node();
	__int64 start_time;	//20�� �̻��� ���� �Է� ���� �� �����Ƿ� int�� ���Ұ�
	int fixed_num;		// ������ ����
	int reservation_seat;	//������ ����� �¼� ��
	int bus_charge;		//������ ���
	Node* left;			//Ʈ������ ���� �ڽ��� �ּҸ� ����
	Node* right;		//Ʈ������ ������ �ڽ��� �ּҸ� ����
};

//������
Node::Node()
{
	left = NULL;
	right = NULL;
	reservation_seat = 0;	//���� �¼��� �ʱ⿡ 0�̴�.
}

//Ʈ���� ���̸� �����ϴ� �Լ�
int tree_height(Node* root)
{
	int height = 0;
	if (root != NULL)
		height = ((tree_height(root->left) > tree_height(root->right)) ? tree_height(root->left) : tree_height(root->right)) + 1;
	return height;
}

//Ʈ���� ���̸� ����� �ִ� �Լ�
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
		//Ʈ������ ��Ʈ�κ��� ������ �� ���� 1�� ���Ѵ�.
		if (root == NULL)
			return;
	}
	cout << deep << endl;
}

//Ʈ���� ������ �´��� Ȯ�����ִ� �Լ�
int balance_height(Node* root)
{
	if (root == NULL)
		return 0;
	return tree_height(root->left) - tree_height(root->right);
	//������ ���� ����Ʈ���� ���̰� ũ��, ������� ������ ����Ʈ���� ���̰� ũ��.
}

//Ʈ���� ������ �����ִ� ����� �����Ѵ�.
Node* avl_tree(Node* root)
{
	int balanceNum = balance_height(root);
	Node* temp, *temp2;

	if (balanceNum > 1)	//���� ���� ����Ʈ���� �����ʺ��� 2�̻� ũ�ٸ� ������ ������� �ϹǷ�
	{
		if (balance_height(root->left) > 0)	//������ �����ʴ� ����Ʈ���� Left, Left�� ���¸� �� ��
		{
			temp = root->left;
			
			root->left = temp->right;
			temp->right = root;
			return temp;
		}
		else  //������ �����ʴ� ����Ʈ���� Left, Right�� ���¸� �� ��
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
	else if (balanceNum < -1) //���� ������ ����Ʈ���� ���ʺ��� 2�̻� ũ�ٸ� ������ ������� �ϹǷ�
	{
		if (balance_height(root->right) < 0) //������ �����ʴ� ����Ʈ���� Right, Right�� ���¸� �� ��
		{
			temp = root->right;
			
			root->right = temp->left;
			temp->left = root;
			return temp;
		}
		else  //������ �����ʴ� ����Ʈ���� Right, Lift�� ���¸� �� ��
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

//�ҷ��� �ؽ�Ʈ ������ ������� Ʈ���� ������ش�.
Node* insert_txt(Node* root, __int64 start, int people, int reserv, int money)
{
	Node* Arr[Max];			//��Ʈ�κ��� �������� ������ ������ �ش�.
	int arr_count = 0;
	
	if (Nodecount == 0)		//���� ��Ʈ��尡 �������� �ʾҴٸ�
	{
		//��Ʈ��带 ������ش�.
		root->start_time = start;
		root->fixed_num = people;
		root->reservation_seat = reserv;
		root->bus_charge = money;
		Nodecount++;	//���� ���Ͽ� ��Ʈ��尡 �̹� �����Ǿ����� �˸���.
		return root;
	}
	
	Node* temp = root;
	while (temp != NULL)	//�ϴ� leaf�� ��带 �ֱ����� temp�� NULL�� �ɶ����� �� ��ġ�� ã���ش�.
	{
		Arr[arr_count] = temp;
		arr_count++;
		//AVLƮ���� ���ʿ��� ���������� ������ start_time ���� Ŀ���Ƿ�
		if (temp->start_time > start)
			temp = temp->left;
		else if (temp->start_time < start)
			temp = temp->right;
		else
		{
			cout << "Error : ��߽ð��� �����ϴ�" << endl;
			return root;
		}
	}

	//���ο� ��带 �����.
	Node* temp2 = new Node;
	temp2->start_time = start;
	temp2->fixed_num = people;
	temp2->reservation_seat = reserv;
	temp2->bus_charge = money;

	//��Ʈ�� ��带 �߰����ش� (���� ���� ���߱� ��)
	if (Arr[arr_count-1]->start_time > start)
		Arr[arr_count-1]->left = temp2;
	else
		Arr[arr_count-1]->right = temp2;

	//temp3�� �̿�, ������ ���κ��� �����带 ���� Ʈ���� �ö󰣴�.
	Node* temp3 = Arr[arr_count];
	while (arr_count != 0)		//��Ʈ���� Ȯ���Ѵ�.
	{
		if (temp3 == Arr[arr_count])		//���� ���ٸ� ��ĭ�� �ö� �� �ְ� ����
		{
			arr_count--;
			temp3 = Arr[arr_count];
			Arr[arr_count] = avl_tree(Arr[arr_count]);	//�������� 2�̻� �ִٸ� ���� �޶�����, �ƴ϶�� ���� ����. 
		}
		else
			break;
	}

	//���� ��Ʈ���� Ȯ�������� �� ���� ���ٸ� �̹� ������ �´� �����̹Ƿ� �ٷ� ����
	if (temp3 == Arr[arr_count])
		return root;

	//������ ���� �ʴ´ٸ�
	Node* temp4 = root;
	while (1)
	{
		if (arr_count == 0)	//��Ʈ���� ������ ���� �ʾ� ������ ���� ���
			return Arr[arr_count];

		if (temp4->left->start_time == temp3->start_time)	//���� ���� �ڽĿ��� ������ ���߾��ٸ�
		{
			temp4->left = Arr[arr_count];
			return root;
		}
		else if (temp4->right->start_time == temp3->start_time)	//���� ������ �ڽĿ��� ������ ���߾��ٸ�
		{
			temp4->right = Arr[arr_count];
			return root;
		}

		//���Ե� ��尡 ���ʿ� �־����� �����ʿ� �־����� ã�´�.
		if(temp4->start_time > temp3->start_time)
			temp4 = temp4->left;
		else if (temp4->start_time < start)
			temp4 = temp4->right;
		else
			cout << "Error : �Ͼ �� ���� ����" << endl;
	}
}


//����ڷ� ���� �Է¹��� ���� Ʈ���� �߰��� �ش�.
Node* insert_bus(Node* root, __int64 start, int people, int money)
{
	Node* Arr[Max];	//��Ʈ�κ��� �������� ������ ������ �ش�.
	int arr_count = 0;

	Node* temp = root;

	while (temp != NULL)	//�ϴ� leaf�� ��带 �ֱ����� temp�� NULL�� �ɶ����� �� ��ġ�� ã���ش�.
	{
		Arr[arr_count] = temp;
		arr_count++;
		//AVLƮ���� ���ʿ��� ���������� ������ start_time ���� Ŀ���Ƿ�
		if (temp->start_time > start)
			temp = temp->left;
		else if (temp->start_time < start)
			temp = temp->right;
		else
		{
			cout << "Error : ��߽ð��� �����ϴ�" << endl;
			return root;
		}
	}

	//���ο� ��带 �����.
	Node* temp2 = new Node;
	temp2->start_time = start;
	temp2->fixed_num = people;
	temp2->bus_charge = money;

	//��Ʈ�� ��带 �߰����ش� (���� ���� ���߱� ��)
	if (Arr[arr_count-1]->start_time > start)
		Arr[arr_count-1]->left = temp2;
	else
		Arr[arr_count-1]->right = temp2;

	//temp3�� �̿�, ������ ���κ��� �����带 ���� Ʈ���� �ö󰣴�.
	Node* temp3 = Arr[arr_count];
	while (arr_count != 0)		//��Ʈ���� Ȯ���Ѵ�.
	{
		if (temp3 == Arr[arr_count])		//���� ���ٸ� ��ĭ�� �ö� �� �ְ� ����
		{
			arr_count--;
			temp3 = Arr[arr_count];
			Arr[arr_count] = avl_tree(Arr[arr_count]);	//�������� 2�̻� �ִٸ� ���� �޶�����, �ƴ϶�� ���� ����. 
		}
		else
			break;
	}

	//���� ��Ʈ���� Ȯ�������� �� ���� ���ٸ� �̹� ������ �´� �����̹Ƿ� �ٷ� ����
	if (temp3 == Arr[arr_count])
		return root;

	//������ ���� �ʴ´ٸ�
	Node* temp4 = root;
	while (1)
	{
		if (arr_count == 0)	//��Ʈ���� ������ ���� �ʾ� ������ ���� ���
			return Arr[arr_count];

		if (temp4->left->start_time == temp3->start_time)	//���� ���� �ڽĿ��� ������ ���߾��ٸ�
		{
			temp4->left = Arr[arr_count];
			return root;
		}
		else if (temp4->right->start_time == temp3->start_time)	//���� ������ �ڽĿ��� ������ ���߾��ٸ�
		{
			temp4->right = Arr[arr_count];
			return root;
		}

		//���Ե� ��尡 ���ʿ� �־����� �����ʿ� �־����� ã�´�.
		if (temp4->start_time > temp3->start_time)
			temp4 = temp4->left;
		else if (temp4->start_time < start)
			temp4 = temp4->right;
		else
			cout << "Error : �Ͼ �� ���� ����" << endl;
	}
}

//���� ��߽ð� �Է¹޾� �׿� ���� ������ ã�� ������ ������ ����Ѵ�.
void bus_info(Node* root, __int64 start)
{
	//while���� Ȱ���� �Է¹��� ���� ��� �ð��� ���� ���� ��� �ð��� ������ ��带 ã�´�.
	Node* temp = root;
	while (root->start_time != start)
	{
		if (root->start_time > start)
			root = root->left;
		else
			root = root->right;

		//���� ���ٸ�
		if (root == NULL)
		{
			cout << "Not found!" << endl;
			return;
		}
	}

	//������ ������ ���
	cout << root->start_time << " " << root->fixed_num << " ";
	cout << root->reservation_seat << " " << root->bus_charge << " ";
	deep(temp, start);
}

//���� ��� �ð��� �Է¹޾� �׿� ���� ���� ��� �ð��� ������ �������� �¼��� �����ϴ� �Լ�
void reservation(Node* root, __int64 start, int reserv)
{
	Node* temp = root;
	//�Է¹��� ���� ��� �ð��� ���� ���� ��� �ð��� ������ ��带 ã�´�.
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

	//���� �̹� ����� ���� �����ϰ��� �ϴ� ���� ������ �ʰ��Ѵٸ� �����޼��� ���
	if (root->reservation_seat + reserv > root->fixed_num)
	{
		cout << "No more seats available!" << endl;
		return;
	}

	//������ �����ϴٸ� ���� �¼��� �����ϰ� ���̸� ����Ѵ�.
	root->reservation_seat += reserv;
	deep(temp, start);
}

int main()
{
	Node* root = new Node;
	
	char insert;	// ����, Ȯ��, ���� ���� Ȯ��
	__int64 start;	// ���� ��� �ð� 
	int people;		// ������ ����
	int reserv;		// �����ϰ��� �ϴ� �ο�
	int money;		// ���� ��� 
	
	//����ڷκ��� ���ϸ��� �Է¹޾� �Է¹��� ���ϸ� �ش��ϴ� ������ ����.
	string txt;
	cin >> txt;
	ifstream ifs;
	ifs.open(txt);

	if (ifs.is_open())		//���� ���� ���⿡ �����ߴٸ�
	{
		//����Ǿ��ִ� ������ �ҷ��´�.
		while (ifs >> start >> people >> reserv >> money)
			root=insert_txt(root, start, people, reserv, money);	//�׸��� �� ����� Ʈ���� �����.				
	}
	ifs.close();
	
	while (cin >> insert){
		switch (insert)
		{
			case 'I':	//���� �߰� �� ���ǰ� ���Դٸ�
			{
				cin >> start >> people >> money;
				root=insert_bus(root, start, people, money);
				deep(root, start);
				continue;
			}

			case 'P':	//���� ���� Ȯ�� ���ǰ� ���Դٸ�
			{
				cin >> start;
				bus_info(root, start);
				continue;
			}
			case 'R':	//���� ���� ���� ���ǰ� ���Դٸ�
			{
				cin >> start >> reserv;
				reservation(root, start, reserv);
				continue;
			}
			
			//�Է� ���� �߻���
			default:
				cout << "Error" << endl;
		}
	}
}