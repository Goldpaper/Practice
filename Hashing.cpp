#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int N;				// 테이블의 크기
int q;				// N보다 작은 소수 q
int n = 0;			// 입력된 버스의 수

typedef struct Bus_data
{
	__int64 start_time;		// 출발 시간
	int fixed_num;			// 정원
	int reservation_seat;	// 예약된 좌석
	int bus_charge;			// 버스 요금
}Bus;

//불러온 txt 파일안에 있는 버스 정보를 바탕으로 버스(struct)를 배열에 insert한다
Bus* insert_txt(Bus* table, __int64 start_time, int fixed_num, int reservation_seat, int bus_charge)
{
	int Array_num = (start_time % N);	// 1차 해싱 (배열에서 버스가 들어갈 위치)
	for (int i = 0; i < N; i++)	// N번 수행하게 되면 빈자리가 있는한 반드시 들어간다. (빈자리가 없으면 빠져나와 오류출력)
	{
		if (table[Array_num].start_time == NULL)	//만약 버스가 들어갈 위치(배열의 Array_num값)가 비었다면 버스를 그 위치에 넣어준다.
		{
			table[Array_num].start_time = start_time;
			table[Array_num].fixed_num = fixed_num;
			table[Array_num].reservation_seat = reservation_seat;
			table[Array_num].bus_charge = bus_charge;
			n++;									//버스가 추가되었으므로 1 더해준다.
			return table;							
		}
		else	//만약 버스가 들어갈 위치에 이미 다른 버스가 있다면 2차 해싱
			Array_num=(Array_num+(q-start_time%q))%N;	//기존 Arraynum에 2차 해싱값을 더하고, 배열 크기 아래에서 순환하게 N의 나머지를 넣어준다.
	}
	cout << "일어날 수 없는 일" << endl;
	return NULL;
}

// 입력질의가 들어오면 버스(struct)를 버스정보와 함께 배열에 insert한다
Bus* insert_bus(Bus* table, __int64 start_time, int fixed_num, int bus_charge)
{
	int Array_num = (start_time % N);	// 1차 해싱 (배열에서 버스가 들어갈 위치)
	for (int i = 0; i < N; i++)	// N번 수행하게 되면 빈자리가 있는한 반드시 들어간다. (빈자리가 없으면 빠져나와 오류출력)
	{
		if (table[Array_num].start_time == NULL)	//만약 버스가 들어갈 위치(배열의 Array_num값)가 비었다면 버스를 그 위치에 넣어준다.

		{
			table[Array_num].start_time = start_time;
			table[Array_num].fixed_num = fixed_num;
			table[Array_num].reservation_seat = 0;
			table[Array_num].bus_charge = bus_charge;
			n++;						//버스가 추가되었으므로 1 더해준다.
			cout << i + 1 << " ";
			
			float load_factor = static_cast<float>(n) / N;		//소수점 이하를 출력하기 위해 static_cast를 이용하여 형변환
				cout << setprecision(2) << load_factor << endl;	//setprecision을 이용하여 소수점 2째자리까지 출력 (setprecision의 경우 자동 반올림 된다.)
			return table;
		}
		else	//만약 버스가 들어갈 위치에 이미 다른 버스가 있다면 2차 해싱
			Array_num = (Array_num + (q - start_time%q)) % N;	//기존 Arraynum에 2차 해싱값을 더하고, 배열 크기 아래에서 순환하게 N의 나머지를 넣어준다.
	}
	cout << "일어날 수 없는 일" << endl;
	return NULL;
}

//버스의 정보를 출력하는 함수
void bus_info(Bus* table, __int64 start_time)
{
	int Array_num = (start_time % N);	// 1차 해싱 (배열에서 버스가 들어갈 위치)
	for (int i = 0; i < N; i++)	// N번 수행하게 되면 빈자리가 있는한 반드시 들어간다. (빈자리가 없으면 빠져나와 오류출력)
	{
		if (table[Array_num].start_time == start_time)	//만약 버스의 위치를 찾았다면 버스의 정보 출력
		{
			cout << table[Array_num].start_time << " " << table[Array_num].fixed_num << " ";
			cout << table[Array_num].reservation_seat << " " << table[Array_num].bus_charge << " ";
			cout << i + 1 << endl;
			return;
		}
		else	//만약 버스가 들어갈 위치가 아니라면 2차 해싱
			Array_num = (Array_num + (q - start_time%q)) % N;
	}
	cout << "Not found!" << endl;	//못 찾았다면 Not found! 출력
	return;
}

//버스의 좌석을 예약하는 함수
void reservation(Bus* table, __int64 start_time, int reservation_seat)
{
	int Array_num = (start_time % N);	// 1차 해싱 (배열에서 버스가 들어갈 위치)
	for (int i = 0; i < N; i++)	// N번 수행하게 되면 빈자리가 있는한 반드시 들어간다. (빈자리가 없으면 빠져나와 오류출력)
	{
		if (table[Array_num].start_time == start_time)	//만약 버스의 위치를 찾았다면 버스예약
		{
			if (table[Array_num].reservation_seat + reservation_seat > table[Array_num].fixed_num)
			{
				//만약 예약하고자 하는 좌석과 이미 예약된 좌석이 정원을 초과할 경우
				cout << "No seats available!" << endl;
				return;
			}
			else
			{
				table[Array_num].reservation_seat += reservation_seat;	//예약한다.
				cout << i + 1 << endl;
				return;
			}
		}
		else
			Array_num = (Array_num + (q - start_time%q)) % N;	//만약 버스가 들어갈 위치가 아니라면 2차 해싱
	}
	cout << "Not found!" << endl;	//못 찾았다면 Not found! 출력
	return;
}

int main()
{
	string txt;			//입력받을 텍스트 크기
	
	char insert_type;		//질의 형식

	__int64 start_time;		//출발 시간
	int fixed_num;			//정원
	int reservation_seat;	//예약된 좌석
	int bus_charge;			//버스 요금
	
	cin >> txt;			//텍스트 입력 받아서 open
	ifstream ifs;
	ifs.open(txt);
	
	Bus* table;			//구조체형 변수

	if (ifs.is_open())		//만약 파일 열기에 성공했다면
	{

		ifs >> N >> q;
		table = new Bus[N];		//배열로 동적할당
		
		for (int i = 0; i < N;i++)		//구조체 배열 초기화
			table[i].start_time = NULL;

		//저장되어있는 값들을 불러온다.
		while (ifs >> start_time >> fixed_num >> reservation_seat >> bus_charge)
			table=insert_txt(table, start_time, fixed_num, reservation_seat, bus_charge);	//그리고 그 값들로 테이블을 만든다.				
	}
	ifs.close();

	//여기까진 완료!
	while (cin >> insert_type)
	{
		switch (insert_type)
		{
			//버스 insert 질의
			case 'I':
			{
				cin >> start_time >> fixed_num >> bus_charge;
				insert_bus(table, start_time, fixed_num, bus_charge);
				continue;
			}

			//버스 정보 출력 질의
			case 'P':
			{
				cin >> start_time;
				bus_info(table, start_time);
				continue;
			}
			//버스 예약 질의
			case 'R':
			{ 
				cin >> start_time >> reservation_seat;
				reservation(table, start_time, reservation_seat);
				continue;
			}
			default:
				cout << "Error : 잘못된 질의 입력입니다" << endl;
		}
	}
	return 0;
}