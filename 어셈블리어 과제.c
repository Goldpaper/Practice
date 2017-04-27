/*
#어셈블리어 과제

프로그램 설명 : 입력받을 수와 출력할 수의 진수타입을 사용자가 원하는 대로 변형 할 수 있는 프로그램
				(ex) 16진수를 입력받아 8진수로 출력한다.

이름 : 송금종
학번 : 12131540

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

	printf("------진수 변환 프로그램------\n");
	
	while (1)
	{
		printf("몇진수로 입력하시겠습니까? (2, 8, 10, 16 입력가능): ");
		scanf("%d", &type);
		if (type == 2 || type == 8 || type == 10 || type == 16)
			break;
		printf("%d진법으로는 변환 할 수 없습니다. 다시 실행해 주세요.\n", type);
	}
	
	switch (type)
	{
	case 2:
		printf("숫자를 입력하세요: ");
		scanf("%s", arrinput);
		inputtwo(arrinput);
		break;
	case 8:
		printf("숫자를 입력하세요: ");
		scanf("%o", &input);
		break;
	case 10:
		printf("숫자를 입력하세요: ");
		scanf("%d", &input);
		break;
	case 16:
		printf("숫자를 입력하세요: ");
		scanf("%X", &input);
		break;
	default:
		printf("알 수 없는 오류 입니다. 프로그램을 종료합니다.\n");
		return -1;
	}

	while (1)
	{
		printf("몇진수로 출력하시겠습니까? (2, 8, 10, 16 입력가능): ");
		scanf("%d", &type);
		if (type == 2 || type == 8 || type == 10 || type == 16)
			break;
		printf("%d진법으로는 변환 할 수 없습니다. 다시 실행해 주세요.\n", type);
	}

	switch (type)
	{
	case 2:
		printf("변환된 숫자는 ");
		twotype(input);
		printf(" 입니다.\n");
		break;
	case 8:
		printf("변환된 숫자는 %o 입니다\n", input);
		break;
	case 10:
		printf("변환된 숫자는 %d 입니다\n", input);
		break;
	case 16:
		printf("변환된 숫자는 %X 입니다\n", input);
		break;
	default:
		printf("알 수 없는 오류 입니다. 프로그램을 종료합니다.\n");
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