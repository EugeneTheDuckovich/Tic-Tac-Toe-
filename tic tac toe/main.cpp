#include "Header.h"

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	while (true) {
		system("cls");
		cout << "������ ����� �������, �� ������ ��������:\n1. ������ ���\n2. ����� � ���\n";
		int command;
		cin >> command;
		CheckCommand(command);
		switch (command)
		{
		case 1:
		{
			cout << "������� ������ ���:\n1. ����� ����� ������\n2. ����� ����� ����'�����\n";
			int versus_who, bot = 0, size, n, turn, do_you_want_to_continue = 0;
			int** board;
			string player_name;
		
			input_format(size, n, versus_who, board, turn, bot, do_you_want_to_continue, player_name);


			int turn_check = size * size + 1;

			cout << "��� ����������\n";
			Sleep(500);

			criss_cross(size, board, n, bot, turn, turn_check, player_name, versus_who, do_you_want_to_continue);

			for (int i = 0; i < size; i++)
				delete[] board[i];
			delete[] board;
			break;
		}

		case 2:
			cout << "����� � ����\n";
			Sleep(1000);
			return 0;
		default:
			cout << "����������� �������, ��������� �����\n";
			Sleep(1000);
		}
	}
}

//��� ������ ���
void input_format(int& size, int& n, int& versus_who, int**& board, int& turn, int& bot, int& do_you_want_to_continue, string& player_name)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
format:
	cin >> versus_who;
	CheckCommand(versus_who);

	switch (versus_who)
	{
	case 1:
		input_all_inf_about_game_state(size, n, turn);
		board = board_not_from_file(size);
		break;
	case 2:
	{
		cout << "������ ��'� ������\n";
		cin >> player_name;
		board = output_of_file(size, n, bot, turn, player_name, do_you_want_to_continue);
		break;
	}

	default:
		cout << "������ �������";
		goto format;
	}
}

//����� ����� ����������� ��� �� ��� ����� � �����
int** output_of_file(int& size, int& n, int& bot, int& turn, string player_name, int& do_you_want_to_continue)
{
	ifstream fin(player_name + ".txt");
	int** temp;
	if (fin.is_open()) {
		cout << "���� ����������� ���, �� ���� ���� ����������. ������ ����������?\n1. ���\n2. �\n";
		
	start:
		cin >> do_you_want_to_continue;
		CheckCommand(do_you_want_to_continue);
		switch (do_you_want_to_continue)
		{
		case 1:
			fin >> size >> n >> bot >> turn;
			cout << "����� �����: " << size << endl <<
				"ʳ������ ����� ����� ��� ��������: " << n << endl <<
				"ճ�, �� ����� ��� ���� ���������: " << turn << endl <<
				"��������� ����: ";
			if (bot == 1)
				cout << "������\n";
			else
				cout << "��������\n";
			temp = new int* [size];
			for (int i = 0; i < size; i++)
				temp[i] = new int[size];

			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					fin >> temp[i][j];
			fin.close();
			Sleep(1000);
			break;
		case 2:
			goto not_from_file;
		default:
			cout << "����������� �������\n";
			goto start;
		}
	}
	else {
	not_from_file:
		input_all_inf_about_game_state(size, n, turn);
		input_bot(bot);
		temp = board_not_from_file(size);
	}
	return temp;
}

//��� ����� ���������
void input_all_inf_about_game_state(int& size, int& n, int& turn)
{	
	while (true)
	{
		cout << "������ ����� �����: ";
		cin >> size;
		CheckCommand(size);
		if (size < 3) {
			cout << "������������ �����, ��������� �����\n";
			continue;
		}
		if (size > 50) {
			cout << "��� ������ ����� ����� ���� ���� �������������� ���������� ��� �����. ������ ����������?\n1. ���\n2. �\n";
			int too_big_size;
			cin >> too_big_size;
			switch (too_big_size)
			{
			case 1:
				break;
			case 2:
				continue;
			default:
				cout << "���������� �������, ��������� �����\n";
				continue;
			}
		}
		break;
	}
	
	cout << "������ ������� ����� ����� ��� ��������: ";
	while (true)
	{
		cin >> n;
		if (n<3 || n>size) {
			cout << "���������� ������� ����� �����\n";
			continue;
		}
		break;
	}
	

	turn = 1;
}


void input_bot(int& bot)
{
	cout << "������� ����� ���������:\n1. ������\n2. ��������\n";
	while (true) {
		bool break_if_all_ok = 0;
		cin >> bot;
		CheckCommand(bot);
		switch (bot)
		{
		case 1:
			++break_if_all_ok;
			break;
		case 2:
			++break_if_all_ok;
			break;
		default:
			cout << "������� ������ ���������\n";
		}
		if (break_if_all_ok)
			break;
	}	
}


int** board_not_from_file(int& size)
{
	int** temp = new int* [size];
	for (int i = 0; i < size; i++)
		temp[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			temp[i][j] = 0;

	return temp;
}

//�������� �������� ����� �� ����������
void CheckCommand(int& command)
{
	while (TRUE)
	{
		if (!cin)
		{
			cout << "����������� �������, ��������� �����\n";
			cin.clear();
			while (cin.get() != '\n');
			    cin >> command;
		}
		else
			break;
	}
}