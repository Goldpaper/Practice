#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
struct tree
{
	struct tree *left_child;
	int root;
	struct tree *right_child;
	int heigh;
};
struct tree* Input(struct tree*);   //난수를 생성
struct tree* Avl(struct tree*, int);   //난수가 생성되면 입력값에따라 avl트리를 유지
int Heigh(struct tree*);     //서브트리의 높이차이를 계산
int Ab(int);        //높이차이에 절대값으로 계산
int Ave(struct tree*, int);     //높이의 평균을 
void Print(struct tree*);      //트리를 inorder로 출력
void Free(struct tree*);       //트리에 사용된 메모리를 반환

int main()
{
	int ave = 1;
	struct tree *root = NULL;
	root = Input(root);
	Print(root);
	ave = Ave(root, ave);
	printf("\n평균 높이 : %d\n", ave / 50);    //모두 합한 높이를 50으로 나눈다.
	Free(root);

}
struct tree *Input(struct tree* root)
{
	int i = 0;
	struct tree * input;
	struct tree * temp;
	struct tree * pre;
	while (i<50)
	{
		input = (struct tree*)malloc(sizeof(struct tree));
		input->left_child = NULL;
		input->root = rand() % 200;
		input->right_child = NULL;
		input->heigh = 0;
		if (root == NULL)
			root = input;
		else
		{
			temp = root;
			while (temp != NULL)
		
				pre = temp;
				if (temp->root<input->root)
					temp = temp->right_child;
				else
					temp = temp->left_child;
			}
			if (pre->root<input->root)
				pre->right_child = input;
			else
				pre->left_child = input;
		}
		temp = root;

		i++;
		root->heigh = Ab(Heigh(root));
		if (root->heigh >= 3)
			root = Avl(root, input->root);
	}
	return root;
}    
struct tree*Avl(struct tree *root, int input)
{
	struct tree* head, *p1, *p2, *p3;
	head = root;
	if (root->root<input)     //오른쪽 서브트리에 입력될경우
	{
		if (root->right_child->root<input) //오른쪽서브트리의 오른쪽자식(RR)
		{
			p1 = root;
			p2 = root->right_child;
			p1->right_child = p2->left_child;
			p2->left_child = p1;
			return p2;
		}
		else        //오른쪽트리의 왼쪽자식(RL)
		{
			p1 = root, p2 = p1->right_child, p3 = p2->left_child;
			p1->right_child = p3->left_child;
			p3->left_child = p1;
			p2->left_child = p3->right_child;
			p3->right_child = p2;
			return p3;
		}
	}
	else         //왼쪽트리에 입력될경우
	{
		if (root->left_child->root>input) //왼쪽서브트리의 왼쪽자식(LL)
		{
			p1 = root;
			p2 = root->left_child;
			p1->left_child = p2->right_child;
			p2->right_child = p1;
			return p2;
		}
		else        //왼쪽서브트리의 오른쪽자식(LR)
		{
			p1 = root, p2 = p1->left_child, p3 = p2->right_child;
			p2->right_child = p3->left_child;
			p3->left_child = p2;
			p1->left_child = p3->right_child;
			p3->right_child = p1;

			return p3;
		}
	}
}
int Heigh(struct tree *root)
{
	int r, l;
	if (root == NULL)
		return 0;
	else
	{
		r = Heigh(root->right_child) + 1;
		l = Heigh(root->left_child) + 1;
		if (r>l)
		{
			root->heigh = Ab(r);
			return r;
		}
		else
		{
			root->heigh = Ab(l);
			return l;
		}
	}
}
void Free(struct tree*root)
{
	if (root != NULL)
	{
		Free(root->left_child);
		Free(root->right_child);
		free(root);
	}
}
int Ab(int input)
{
	if (input<0)
		return -input;
	else
		return input;
}
void Print(struct tree *root)     //inorder로 출력
{
	if (root != NULL)
	{
		Print(root->left_child);
		printf("%d\t", root->root);
		Print(root->right_child);
	}
}
int Ave(struct tree*root, int ave)
{
	int av = ave;
	if (root != NULL)
	{
		ave += Ave(root->left_child, av + 1);
		ave += Ave(root->right_child, av + 1);
		return ave;
	}
	return 0;
}