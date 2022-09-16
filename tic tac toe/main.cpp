#include "Header.h"

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	while (true) {
		system("cls");
		cout << "Введіть номер команди, що бажаєте виконати:\n1. почати гру\n2. вийти з гри\n";
		int command;
		cin >> command;
		CheckCommand(command);
		switch (command)
		{
		case 1:
		{
			cout << "Виберіть формат гри:\n1. ігрок проти ігрока\n2. ігрок проти комп'ютера\n";
			int versus_who, bot = 0, size, n, turn, do_you_want_to_continue = 0;
			int** board;
			string player_name;
		
			input_format(size, n, versus_who, board, turn, bot, do_you_want_to_continue, player_name);


			int turn_check = size * size + 1;

			cout << "гра починається\n";
			Sleep(500);

			criss_cross(size, board, n, bot, turn, turn_check, player_name, versus_who, do_you_want_to_continue);

			for (int i = 0; i < size; i++)
				delete[] board[i];
			delete[] board;
			break;
		}

		case 2:
			cout << "Вихід з ігри\n";
			Sleep(1000);
			return 0;
		default:
			cout << "Неправильна команда, спробуйте знову\n";
			Sleep(1000);
		}
	}
}

//ввід режиму гри
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
		cout << "Введіть ім'я ігрока\n";
		cin >> player_name;
		board = output_of_file(size, n, bot, turn, player_name, do_you_want_to_continue);
		break;
	}

	default:
		cout << "Невірна команда";
		goto format;
	}
}

//запис стану незавершеної гри та ввід даних з файлу
int** output_of_file(int& size, int& n, int& bot, int& turn, string player_name, int& do_you_want_to_continue)
{
	ifstream fin(player_name + ".txt");
	int** temp;
	if (fin.is_open()) {
		cout << "Існує незавершена гра, що може бути продовжена. Бажаєте продовжити?\n1. так\n2. ні\n";
		
	start:
		cin >> do_you_want_to_continue;
		CheckCommand(do_you_want_to_continue);
		switch (do_you_want_to_continue)
		{
		case 1:
			fin >> size >> n >> bot >> turn;
			cout << "Розмір дошки: " << size << endl <<
				"Кількість знаків підряд для перемоги: " << n << endl <<
				"Хід, на якому гра була перервана: " << turn << endl <<
				"Складність бота: ";
			if (bot == 1)
				cout << "легкий\n";
			else
				cout << "складний\n";
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
			cout << "Неправильна команда\n";
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

//ввід даних самостійно
void input_all_inf_about_game_state(int& size, int& n, int& turn)
{	
	while (true)
	{
		cout << "Введіть розмір дошки: ";
		cin >> size;
		CheckCommand(size);
		if (size < 3) {
			cout << "Некорректний розмір, спробуйте знову\n";
			continue;
		}
		if (size > 50) {
			cout << "При такому розмірі дошки поле може відрисовуватися некоректно або довго. Бажаєте продовжити?\n1. так\n2. ні\n";
			int too_big_size;
			cin >> too_big_size;
			switch (too_big_size)
			{
			case 1:
				break;
			case 2:
				continue;
			default:
				cout << "Некоректна команда, спробуйте знову\n";
				continue;
			}
		}
		break;
	}
	
	cout << "Введіть кількість знаків підряд для перемоги: ";
	while (true)
	{
		cin >> n;
		if (n<3 || n>size) {
			cout << "Некоректна кількість знаків підряд\n";
			continue;
		}
		break;
	}
	

	turn = 1;
}


void input_bot(int& bot)
{
	cout << "Виберіть рівень складності:\n1. легкий\n2. складний\n";
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
			cout << "Введена невірна складність\n";
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

//перевірка вводимих даних на коректність
void CheckCommand(int& command)
{
	while (TRUE)
	{
		if (!cin)
		{
			cout << "Неправильна команда, спробуйте знову\n";
			cin.clear();
			while (cin.get() != '\n');
			    cin >> command;
		}
		else
			break;
	}
}