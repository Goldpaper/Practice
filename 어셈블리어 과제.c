/*
#������� ����

���α׷� ���� : �Է¹��� ���� ����� ���� ����Ÿ���� ����ڰ� ���ϴ� ��� ���� �� �� �ִ� ���α׷�
				(ex) 16������ �Է¹޾� 8������ ����Ѵ�.

�̸� : �۱���
�й� : 12131540

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int input = 0;

int main()
{
	int type;
	char arrinput[100];
	void inputtwo(char);
	int twotype(int);

	printf("------���� ��ȯ ���α׷�------\n");
	
	while (1)
	{
		printf("�������� �Է��Ͻðڽ��ϱ�? (2, 8, 10, 16 �Է°���): ");
		scanf("%d", &type);
		if (type == 2 || type == 8 || type == 10 || type == 16)
			break;
		printf("%d�������δ� ��ȯ �� �� �����ϴ�. �ٽ� ������ �ּ���.\n", type);
	}
	
	switch (type)
	{
	case 2:
		printf("���ڸ� �Է��ϼ���: ");
		scanf("%s", arrinput);
		inputtwo(arrinput);
		break;
	case 8:
		printf("���ڸ� �Է��ϼ���: ");
		scanf("%o", &input);
		break;
	case 10:
		printf("���ڸ� �Է��ϼ���: ");
		scanf("%d", &input);
		break;
	case 16:
		printf("���ڸ� �Է��ϼ���: ");
		scanf("%X", &input);
		break;
	default:
		printf("�� �� ���� ���� �Դϴ�. ���α׷��� �����մϴ�.\n");
		return -1;
	}

	while (1)
	{
		printf("�������� ����Ͻðڽ��ϱ�? (2, 8, 10, 16 �Է°���): ");
		scanf("%d", &type);
		if (type == 2 || type == 8 || type == 10 || type == 16)
			break;
		printf("%d�������δ� ��ȯ �� �� �����ϴ�. �ٽ� ������ �ּ���.\n", type);
	}

	switch (type)
	{
	case 2:
		printf("��ȯ�� ���ڴ� ");
		twotype(input);
		printf(" �Դϴ�.\n");
		break;
	case 8:
		printf("��ȯ�� ���ڴ� %o �Դϴ�\n", input);
		break;
	case 10:
		printf("��ȯ�� ���ڴ� %d �Դϴ�\n", input);
		break;
	case 16:
		printf("��ȯ�� ���ڴ� %X �Դϴ�\n", input);
		break;
	default:
		printf("�� �� ���� ���� �Դϴ�. ���α׷��� �����մϴ�.\n");
		return -1;
	}
	return 0;
}

void inputtwo(char temp[])
{
	int length = 0;
	while (temp[length] != 0)
		length++;
	for (int i = 0; i < length; i++)
	{
		input += (temp[i] % 2) * pow(2,length-i-1);
	}
}

int twotype(int temp)
{
	if (temp<1)
		return temp;
	else
	{
		twotype(temp / 2);
		printf("%d", temp % 2);
	}
}