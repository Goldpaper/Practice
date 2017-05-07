#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int N;				// ���̺��� ũ��
int q;				// N���� ���� �Ҽ� q
int n = 0;			// �Էµ� ������ ��

typedef struct Bus_data
{
	__int64 start_time;		// ���� �ð�
	int fixed_num;			// ����
	int reservation_seat;	// ������ �¼�
	int bus_charge;			// ���� ����
}Bus;

//�ҷ��� txt ���Ͼȿ� �ִ� ���� ������ �������� ����(struct)�� �迭�� insert�Ѵ�
Bus* insert_txt(Bus* table, __int64 start_time, int fixed_num, int reservation_seat, int bus_charge)
{
	int Array_num = (start_time % N);	// 1�� �ؽ� (�迭���� ������ ��� ��ġ)
	for (int i = 0; i < N; i++)	// N�� �����ϰ� �Ǹ� ���ڸ��� �ִ��� �ݵ��� �����. (���ڸ��� ������ �������� ��������)
	{
		if (table[Array_num].start_time == NULL)	//���� ������ ��� ��ġ(�迭�� Array_num��)�� �����ٸ� ������ �� ��ġ�� �־��ش�.
		{
			table[Array_num].start_time = start_time;
			table[Array_num].fixed_num = fixed_num;
			table[Array_num].reservation_seat = reservation_seat;
			table[Array_num].bus_charge = bus_charge;
			n++;									//������ �߰��Ǿ����Ƿ� 1 �����ش�.
			return table;							
		}
		else	//���� ������ ��� ��ġ�� �̹� �ٸ� ������ �ִٸ� 2�� �ؽ�
			Array_num=(Array_num+(q-start_time%q))%N;	//���� Arraynum�� 2�� �ؽ̰��� ���ϰ�, �迭 ũ�� �Ʒ����� ��ȯ�ϰ� N�� �������� �־��ش�.
	}
	cout << "�Ͼ �� ���� ��" << endl;
	return NULL;
}

// �Է����ǰ� �������� ����(struct)�� ���������� �Բ� �迭�� insert�Ѵ�
Bus* insert_bus(Bus* table, __int64 start_time, int fixed_num, int bus_charge)
{
	int Array_num = (start_time % N);	// 1�� �ؽ� (�迭���� ������ ��� ��ġ)
	for (int i = 0; i < N; i++)	// N�� �����ϰ� �Ǹ� ���ڸ��� �ִ��� �ݵ��� �����. (���ڸ��� ������ �������� ��������)
	{
		if (table[Array_num].start_time == NULL)	//���� ������ ��� ��ġ(�迭�� Array_num��)�� �����ٸ� ������ �� ��ġ�� �־��ش�.

		{
			table[Array_num].start_time = start_time;
			table[Array_num].fixed_num = fixed_num;
			table[Array_num].reservation_seat = 0;
			table[Array_num].bus_charge = bus_charge;
			n++;						//������ �߰��Ǿ����Ƿ� 1 �����ش�.
			cout << i + 1 << " ";
			
			float load_factor = static_cast<float>(n) / N;		//�Ҽ��� ���ϸ� �����ϱ� ���� static_cast�� �̿��Ͽ� ����ȯ
				cout << setprecision(2) << load_factor << endl;	//setprecision�� �̿��Ͽ� �Ҽ��� 2°�ڸ����� ���� (setprecision�� ���� �ڵ� �ݿø� �ȴ�.)
			return table;
		}
		else	//���� ������ ��� ��ġ�� �̹� �ٸ� ������ �ִٸ� 2�� �ؽ�
			Array_num = (Array_num + (q - start_time%q)) % N;	//���� Arraynum�� 2�� �ؽ̰��� ���ϰ�, �迭 ũ�� �Ʒ����� ��ȯ�ϰ� N�� �������� �־��ش�.
	}
	cout << "�Ͼ �� ���� ��" << endl;
	return NULL;
}

//������ ������ �����ϴ� �Լ�
void bus_info(Bus* table, __int64 start_time)
{
	int Array_num = (start_time % N);	// 1�� �ؽ� (�迭���� ������ ��� ��ġ)
	for (int i = 0; i < N; i++)	// N�� �����ϰ� �Ǹ� ���ڸ��� �ִ��� �ݵ��� �����. (���ڸ��� ������ �������� ��������)
	{
		if (table[Array_num].start_time == start_time)	//���� ������ ��ġ�� ã�Ҵٸ� ������ ���� ����
		{
			cout << table[Array_num].start_time << " " << table[Array_num].fixed_num << " ";
			cout << table[Array_num].reservation_seat << " " << table[Array_num].bus_charge << " ";
			cout << i + 1 << endl;
			return;
		}
		else	//���� ������ ��� ��ġ�� �ƴ϶��� 2�� �ؽ�
			Array_num = (Array_num + (q - start_time%q)) % N;
	}
	cout << "Not found!" << endl;	//�� ã�Ҵٸ� Not found! ����
	return;
}

//������ �¼��� �����ϴ� �Լ�
void reservation(Bus* table, __int64 start_time, int reservation_seat)
{
	int Array_num = (start_time % N);	// 1�� �ؽ� (�迭���� ������ ��� ��ġ)
	for (int i = 0; i < N; i++)	// N�� �����ϰ� �Ǹ� ���ڸ��� �ִ��� �ݵ��� �����. (���ڸ��� ������ �������� ��������)
	{
		if (table[Array_num].start_time == start_time)	//���� ������ ��ġ�� ã�Ҵٸ� ��������
		{
			if (table[Array_num].reservation_seat + reservation_seat > table[Array_num].fixed_num)
			{
				//���� �����ϰ��� �ϴ� �¼��� �̹� ������ �¼��� ������ �ʰ��� ����
				cout << "No seats available!" << endl;
				return;
			}
			else
			{
				table[Array_num].reservation_seat += reservation_seat;	//�����Ѵ�.
				cout << i + 1 << endl;
				return;
			}
		}
		else
			Array_num = (Array_num + (q - start_time%q)) % N;	//���� ������ ��� ��ġ�� �ƴ϶��� 2�� �ؽ�
	}
	cout << "Not found!" << endl;	//�� ã�Ҵٸ� Not found! ����
	return;
}

int main()
{
	string txt;			//�Է¹��� �ؽ�Ʈ ũ��
	
	char insert_type;		//���� ����

	__int64 start_time;		//���� �ð�
	int fixed_num;			//����
	int reservation_seat;	//������ �¼�
	int bus_charge;			//���� ����
	
	cin >> txt;			//�ؽ�Ʈ �Է� �޾Ƽ� open
	ifstream ifs;
	ifs.open(txt);
	
	Bus* table;			//����ü�� ����

	if (ifs.is_open())		//���� ���� ���⿡ �����ߴٸ�
	{

		ifs >> N >> q;
		table = new Bus[N];		//�迭�� �����Ҵ�
		
		for (int i = 0; i < N;i++)		//����ü �迭 �ʱ�ȭ
			table[i].start_time = NULL;

		//�����Ǿ��ִ� ������ �ҷ��´�.
		while (ifs >> start_time >> fixed_num >> reservation_seat >> bus_charge)
			table=insert_txt(table, start_time, fixed_num, reservation_seat, bus_charge);	//�׸��� �� ������ ���̺��� ������.				
	}
	ifs.close();

	//�������� �Ϸ�!
	while (cin >> insert_type)
	{
		switch (insert_type)
		{
			//���� insert ����
			case 'I':
			{
				cin >> start_time >> fixed_num >> bus_charge;
				insert_bus(table, start_time, fixed_num, bus_charge);
				continue;
			}

			//���� ���� ���� ����
			case 'P':
			{
				cin >> start_time;
				bus_info(table, start_time);
				continue;
			}
			//���� ���� ����
			case 'R':
			{ 
				cin >> start_time >> reservation_seat;
				reservation(table, start_time, reservation_seat);
				continue;
			}
			default:
				cout << "Error : �߸��� ���� �Է��Դϴ�" << endl;
		}
	}
	return 0;
}