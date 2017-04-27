/*
���α׷� : ����Ʈ��(binary tree) ����
(����� ����, ������ȸ, ������ȸ, ����� ��ǥ ��� ����)

���ϴ��б� ��ǻ���������а� 2�г�
�й�:12131540, �̸�:�۱���
*/

#include <iostream>
using namespace std;

//Ʈ�� Ŭ����
class bTree
{
public:
	bTree* left;	//���� ��带 ����Ŵ
	bTree* right;	//������ ��带 ����Ŵ
	int data;		//��ȣ�� �����Ѵ�
};

bTree* btemp1;		//��带 ã������ ���� �ӽ÷� �����ϱ� ���� �뵵 
int k = 0;			//��带 ã���� �Լ��� ã�Ҵ��� Ȯ���ϴ� �뵵(0 or 1)

//�ش��ϴ� ��ȣ�� ������ ����� �ּҸ� ã�� �Լ�
void whereIs(bTree*, int);

//��Ʈ��� (���� ó������ �����)�� ����� �Լ�
bTree* makeRoot(int node_num)
{
	bTree* node = (bTree*)malloc(sizeof(bTree));
	node->left = NULL;
	node->right = NULL;
	node->data = node_num;
	return node;
}

//���ʿ� �ڽ��� ����� �Լ�
void makeLeft(bTree* root, int node_num, int parent_num)
{
	bTree* node = (bTree*)malloc(sizeof(bTree));	//���ο� ��带 ����

	whereIs(root, parent_num);	//�θ��尡 ����ִ��� ã��
	root = btemp1;

	if (root->left == NULL){	//����ٸ� ��������
		root->left = node;
		node->data = node_num;
		node->left = NULL;
		node->right = NULL;
	}
	else
		root->left->data = node_num;	//�̹� ��尡 �ִٸ� ��ȣ�� �ٲ���
}

//�����ʿ� �ڽ��� ����� �Լ�
void makeRight(bTree* root, int node_num, int parent_num)
{
	bTree* node = (bTree*)malloc(sizeof(bTree));

	whereIs(root, parent_num);	//�θ��尡 ����ִ��� ã��
	root = btemp1;

	if (root->right == NULL){	//����ٸ� ���������
		root->right = node;
		node->data = node_num;
		node->left = NULL;
		node->right = NULL;
	}
	else
		root->left->data = node_num;	//�̹� ��尡 �ִٸ� ��ȣ�� �ٲ���
}

//�ش��ϴ� ��ȣ�� ������ ����� �ּҸ� ã�� �Լ� 
void whereIs(bTree* root, int data)
{
	int c = 0;		//����Լ� ȣ��ɶ����� �ʱ�ȭ�ȴ�.
	if (k == 1)		//���� �ش��ϴ� ��ȣ�� ã�Ҵٸ� �Լ��� ���������� ���� ��� ���ϸ� ���ִ� ���� 
		return;

	if (root->data == data){
		btemp1 = root;
		k = 1;
	}

	if (root->left == NULL)		//���� ���� ��尡 ����ٸ�
		c += 1;

	if (root->right == NULL)	//���� ������ ��尡 ����ٸ�
		c += 2;


	switch (c)
	{
	case 0:{						//c=0 �̶�� ���� ���ʳ�尡 ��� ������� ���� �����̹Ƿ� ������ ��� ã�ƺ���.
		whereIs(root->left, data);
		whereIs(root->right, data);
		break;
	}
	case 1:{						//c=1 �̶�� ���� ������ ��常 �ִ� ����
		whereIs(root->right, data);
		break;
	}
	case 2:{						//c=2 ��� ���� ���� ��常 �ִ� ����
		whereIs(root->left, data);
		break;
	}
	case 3:							//���� ��尡 �����Ƿ� break(�Լ��� ����)
		break;

	default:						//�Ͼ�� ��������..
		cout << "Error" << endl;
	}
	k = 0;	//�������� k=0 ���� �ʱ�ȭ �����ش�
}

//������ȸ �ϴ� �Լ�
void Preorder(bTree* root)
{
	if (root == NULL)		//Ż�� ����
		return;

	cout << root->data << " ";
	Preorder(root->left);
	Preorder(root->right);
}

//������ȸ�ϴ� �Լ�
void Postorder(bTree* root)
{
	if (root == NULL)		//Ż�� ����
		return;

	Postorder(root->left);
	Postorder(root->right);
	cout << root->data << " ";
}

//��ǥ�� ã�� �Լ� (������ȸ�� ����)
void Coordinate(bTree* root, int num, int& x, int y)
{
	if (root == NULL)		//root�� NULL�̸� �����ϰ�
	{
		y -= 1;				//�����ϸ� ���� �ö󰡹Ƿ� y�� ���ҽ�Ų��.
		return;
	}

	Coordinate(root->left, num, x, y + 1);	//left�� �ִ� ���� �̵��Ҷ��� �������Ƿ� y�� ������Ų��.

	if (root->data == num)			//�ش��ϴ� ��ȣ�� �� ��忡 �ִ�?
	{
		cout << x << " " << y;		//�׷��ٸ� ��ǥ�� ���
		return;
	}
	x = x + 1;	//x��ǥ�� ���������ش� (������ȸ�̹Ƿ� x��ǥ�� �������� �����ϸ� 1�� �����ϸ鼭 Ž���Ѵ�)

	Coordinate(root->right, num, x, y + 1);	//right�� �ִ� ���� �̵��Ҷ��� �������Ƿ� y�� ������Ų��.

}

int main()
{
	bTree* root;	//root��� bTree�� �����͸� �����.

	//�Է¹�����
	char insert_num;	//���� ���Ǹ� �����Ѵ� (I,P,T,C �����ϴ� �뵵)	
	int node_num;		//���Ե� ����� ��ȣ�� 2��°�� �Է¹޴´�
	int parent_num;		//���Ե� ����� �θ��� ��ȣ�� �Է¹޴´� (3��°�� �Է¹޴´�)
	char left_right;	//���Ե� ��尡 �������� ���������� �����Ѵ� (4��°�� �Է¹޴´�)

	int x = 1;			//����� x��ǥ�� ǥ���ϴ� ����
	int y = 0;			//����� y��ǥ�� ǥ���ϴ� ����

	int count = 0;		//��Ʈ��尡 ȣ������� �ִ°�? (0=����)

	while (cin >> insert_num){		//���� ���Ǹ� �Է¹޴´�. 
		switch (insert_num){		//����ġ�� ���Ǹ� ����
		case 'I':
		{
			cin >> node_num >> parent_num >> left_right;		//�������� ������� �Է¹޴´�.

			if (left_right == 'L' && parent_num == -1){			//�θ����� ��ȣ�� -1�̰�, ���ʻ����̶��
				if (count != 0)			//��Ʈ��尡 �̹� �ִٸ�
					root->data = node_num;	//��Ʈ����� ��ȣ�� �ٲ��ش�
				else{					//��Ʈ��尡 ���ٸ�
					root = makeRoot(node_num);	//������ش�
					count++;			//count�� �������� ��Ʈ���� �ݵ�� �ѹ��� ���������.
				}
				continue;
			}

			if (left_right == 'L'){						//���ʿ� ��带 �����
				makeLeft(root, node_num, parent_num);
				continue;
			}
			else{
				makeRight(root, node_num, parent_num);	//�����ʿ� ��带 �����
				continue;
			}
		}

		//���� ��ȸ
		case 'P':
		{
			Preorder(root);
			cout << endl;
			continue;
		}


		//���� ��ȸ
		case 'T':
		{
			Postorder(root);
			cout << endl;
			continue;
		}


		//��ǥ���
		case 'C':{
			cin >> node_num;		//ã�� ��带 �Է¹޴´�.
			Coordinate(root, node_num, x, y);
			x = 1;
			cout << endl;
			continue;
		}


		//���� �߻��� (�߻��Ҹ� ���ٰ� ����������) 
		default:
			cout << "Error" << endl;
		}
	}
}