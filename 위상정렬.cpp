/*
	프로그램 : 위상정렬 알고리즘(cmd 환경에서 사용가능)
	(사용방법 cmd에서 exe파일 있는 경로로 이동 후
	 "프로그램 이름" input.txt output.txt 같은 방법으로 사용가능)

	 인하대학교 컴퓨터정보공학과 2학년
	 학번:12131540, 이름:송금종
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
	string input = argv[1];			//cmd 창에서 입력받음
	const char* output = argv[2];	//cmd 창에서 입력받음2

	int count = 0;
	int data_count = 0;

	string arr[100];
	for (int i = 0; i < 100; i++)	//초기화
		arr[i] = "0";

	string alldata[2][100];			//input.txt의 모든 데이터 저장

	ifstream ifs;
	ifs.open(input);

	//노드, 아크의 갯수 측정 & 노드 저장
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

	//input.txt의 문자열을 정수로 바꾼다 (배열을 이용, 정수와 문자열간의 관계를 만듦)
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
	//temp에 있는 값을 넣자
	for (int i = 1; i <= data_count; i++)
	{
		fscanf(fin, "%d%d", &a, &b);
		data[a].push_back(b);
		index[b]++;
	}

	for (int i = 1; i <= count; i++)
	if (index[i] == 0)
		stack[++tail] = i;

	//일관성 표식을 찾아보자
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
	//사이클이 있니? 없니?
	if (head != count)
	{
		fprintf(fout, "Cycles exist ");
		return -1;
	}
	else
		fprintf(fout, "No cycle\n");

	//output.txt에 일관성표식 저장
	for (int i = 1; i <= count; i++)
	{
		char* content = (char*)arr[node[i] - 1].c_str();
		fputs(content, fout);
		fputs(" ", fout);
	}

	fcloseall();	//모든 open된 파일 닫음
	return 0;
}