/*
	���α׷� : �������� �˰���(cmd ȯ�濡�� ��밡��)
	(����� cmd���� exe���� �ִ� ��η� �̵� ��
	 "���α׷� �̸�" input.txt output.txt ���� ������� ��밡��)

	 ���ϴ��б� ��ǻ���������а� 2�г�
	 �й�:12131540, �̸�:�۱���
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define ArrSize 1000

using namespace std;

vector<int> data[ArrSize];

int stack[ArrSize], head, tail;
int node_data, node[ArrSize];
int index[ArrSize];

int main(int argc, char* argv[])
{
	string start;
	string end;
	string input = argv[1];			//cmd â���� �Է¹���
	const char* output = argv[2];	//cmd â���� �Է¹���2

	int count = 0;
	int data_count = 0;

	string arr[100];
	for (int i = 0; i < 100; i++)	//�ʱ�ȭ
		arr[i] = "0";

	string alldata[2][100];			//input.txt�� ��� ������ ����

	ifstream ifs;
	ifs.open(input);

	//���, ��ũ�� ���� ���� & ��� ����
	while (ifs >> start >> end)
	{
		alldata[0][data_count] = start;
		alldata[1][data_count] = end;
		data_count++;

		for (int i = 0; i <= count; i++)
		{
			if (arr[i] == start)
				break;
			else if (arr[i] != "0")
				continue;
			else
			{
				arr[count] = start;
				count++;
				break;
			}
		}

		for (int i = 0; i <= count; i++)
		{
			if (arr[i] == end)
				break;
			else if (arr[i] != "0")
				continue;
			else
			{
				arr[count] = end;
				count++;
				break;
			}
		}
	}
	ifs.close();

	//input.txt�� ���ڿ��� ������ �ٲ۴� (�迭�� �̿�, ������ ���ڿ����� ���踦 ����)
	ofstream ofs;
	ofs.open("temp.txt");

	for (int i = 0; i < data_count; i++)
	{
		for (int j = 0; j < count; j++)
		if (alldata[0][i] == arr[j])
			ofs << j + 1;

		ofs << " ";

		for (int j = 0; j < count; j++)
		if (alldata[1][i] == arr[j])
			ofs << j + 1;

		ofs << endl;
	}
	ofs.close();

	FILE *fin = fopen("temp.txt", "r");
	FILE *fout = fopen(output, "w");

	int a, b;
	//temp�� �ִ� ���� ����
	for (int i = 1; i <= data_count; i++)
	{
		fscanf(fin, "%d%d", &a, &b);
		data[a].push_back(b);
		index[b]++;
	}

	for (int i = 1; i <= count; i++)
	if (index[i] == 0)
		stack[++tail] = i;

	//�ϰ��� ǥ���� ã�ƺ���
	while (head != tail)
	{
		head++;
		node[++node_data] = stack[head];
		for (int i = 0; i<data[stack[head]].size(); i++)
		{
			index[data[stack[head]][i]]--;
			if (index[data[stack[head]][i]] == 0)
				stack[++tail] = data[stack[head]][i];
		}
	}
	//����Ŭ�� �ִ�? ����?
	if (head != count)
	{
		fprintf(fout, "Cycles exist ");
		return -1;
	}
	else
		fprintf(fout, "No cycle\n");

	//output.txt�� �ϰ���ǥ�� ����
	for (int i = 1; i <= count; i++)
	{
		char* content = (char*)arr[node[i] - 1].c_str();
		fputs(content, fout);
		fputs(" ", fout);
	}

	fcloseall();	//��� open�� ���� ����
	return 0;
}