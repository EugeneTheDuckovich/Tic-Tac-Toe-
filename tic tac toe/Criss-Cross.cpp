#include "Header.h"

//графіка та логіка гри
void criss_cross(int size, int** board, int n, int bot, int& turn, int turn_check, string player_name, int versus_who, int do_you_want_to_continue)
{
	int wind = GetSystemMetrics(SM_CYSCREEN) * 1.25, bias = wind / size + 1;
	RenderWindow window(VideoMode(wind + size - 1, wind + size - 1), "Tic Tac Toe");
	Vector2f scale((float)wind / (300 * size), (float)wind / (300 * size));
	ContextSettings settings;
	settings.antialiasingLevel = 19;

	Texture ult_tex;
	ult_tex.loadFromFile("C:\\крестики-нолики\\ultimate texture.png");
	Sprite ult_sprt(ult_tex);

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();		

		end_if_Escape_is_pressed(size, board, n, bot, turn, player_name, versus_who, window);

		window_draw(size, board, ult_sprt, bias, scale, window);

		if (win_check(size, board, n, versus_who, do_you_want_to_continue, player_name, window, 1, turn_check))
			return;
		if (win_check(size, board, n, versus_who, do_you_want_to_continue, player_name, window, 2, turn_check))
			return;
		if (draw_check(turn, turn_check, window, do_you_want_to_continue, player_name))
			return;		

		if (turn % 2 == 1)
			player_turn(size, board, wind, turn, window, 1);

		else 
			null_turn(size, board, wind, turn, versus_who, bot, window);
	}
}

//відрисовка вікна
void window_draw(int size, int** board, Sprite ult_sprt, int bias, Vector2f scale, RenderWindow& window)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			ult_sprt.setTextureRect(IntRect(board[i][j] * 300, 0, 300, 300));
			ult_sprt.setScale(scale);
			ult_sprt.setPosition(i * bias, j * bias);
			window.draw(ult_sprt);
		}
	window.display();
}

//перевірки на перемогу або нічию
bool win_check(int size, int** board, int n, int versus_who, int do_you_want_to_continue, string player_name, RenderWindow& window, int sign, int& turn)
{
	if (diagonal_check(board, size, n, sign) || vertical_check(board, size, n, sign) || horisontal_check(board, size, n, sign)) {
		Sleep(1000);
		window.close();

		if(sign==1)
		    cout << "Хрестики перемогли!";
		else
			cout << "Нулики перемогли!";

		if (do_you_want_to_continue == 1)
			remove((player_name + ".txt").c_str());

		turn = 1;

		Sleep(1000);
		return 1;
	}
	return 0;
}
bool draw_check(int turn, int turn_check, RenderWindow& window, int do_you_want_to_continue, string player_name)
{
	if (turn == turn_check) {
		Sleep(1000);
		window.close();
		cout << "Нічия!\n";
		if (do_you_want_to_continue == 1)
			remove((player_name + "txt").c_str());
		turn = 1;
		Sleep(1000);
		return 1;
	}
	return 0;
}

bool diagonal_check(int** board, int size, int n, int sign) //перевірка по всім диагоналям поля
{
	int checking_1, checking_2, checking_3, checking_4;
	for (int i = 0; i < size; i++) {
		checking_1 = checking_2 = checking_3 = checking_4 = 0;
		if (size - i >= n) {			
			for (int j = 0; j + i < size; j++) {
				if (board[j][i + j] == sign) {
					++checking_1;
					if (checking_1 == n)
						return 1;
				}
				else
					checking_1 = 0;

				if (board[i + j][j] == sign) {
					++checking_2;
					if (checking_2 == n)
						return 1;
				}
				else
					checking_2 = 0;

				if (board[size - j - 1][j + i] == sign) {
					++checking_3;
					if (checking_3 == n)
						return 1;
				}
				else
					checking_3 = 0;
			}			
		}	
		if(i >= n - 1)
			for (int j = 0; j <= i; j++) {
			if (board[i - j][j] == sign) {
				++checking_4;
				if (checking_4 == n)
					return 1;
			}
			else
				checking_4 = 0;
		}		
	}

	return 0;
}
bool vertical_check(int** board, int size, int n, int sign) // перевірка по всім горизонталям поля
{
	int checking;
	for (int i = 0; i < size; i++) {
		checking = 0;
		for (int k = 0; k < size; k++) {
			if (board[k][i] == sign) {
				++checking;
				if (checking == n)
					return 1;
			}
			else
				checking = 0;
		}
	}

	return 0;
}
bool horisontal_check(int** board, int size, int n, int sign) // перевірка по всім вертикалям поля
{
	int checking;
	for (int i = 0; i < size; i++) {
		checking = 0;
		for (int k = 0; k < size; k++) {
			if (board[i][k] == sign) {
				checking++;
				if (checking == n)
					return 1;
			}
			else
				checking = 0;
		}
	}
	return 0;
}

//переривання гри та запис стану гри у файл при нажатті Escape
void end_if_Escape_is_pressed(int size, int** board, int n, int bot, int& turn, string player_name, int versus_who, RenderWindow& window)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape) && versus_who == 2) {
		window.close();
		create_file(size, n, bot, turn, board, player_name);
		cout << "Ви зможете продовжити гру пізніше, " << player_name;
		Sleep(1000);
	}
}

void create_file(int& size, int& n, int& bot, int& turn, int** board, string player_name)
{
	ofstream fout(player_name + ".txt");
	fout << size << endl << n << endl << bot << endl << turn << endl;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			fout << board[i][j] << endl;
}

//боти
void bot_easy(int** board, int size, int& turn)
{
	srand(time(NULL));
	Sleep(1000);
	while (TRUE) {
		int i = rand() % size;
		int j = rand() % size;
		if (!board[i][j]) {
			board[i][j] = 2;
			turn++;
			return;
		}
	}
}
void bot_hard(int** board, int size, int& turn)
{
	Sleep(500);
	turn++;
	srand(time(NULL));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] == 2) {
				if (j + 1 < size && j - 1 >= 0 && board[i][j - 1] == 2 && !board[i][j + 1]) {
					board[i][j + 1] = 2;
					return;
				}
				if (i + 1 < size && j + 1 < size && i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == 2 && !board[i + 1][j + 1]) {
					board[i + 1][j + 1] = 2;
					return;
				}
				if (i + 1 < size && i - 1 >= 0 && board[i - 1][j] == 2 && !board[i + 1][j]) {
					board[i + 1][j] = 2;
					return;
				}
				if (i + 1 < size && j - 1 >= 0 && i - 1 >= 0 && j + 1 < size && board[i - 1][j + 1] == 2 && !board[i + 1][j - 1]) {
					board[i + 1][j - 1] = 2;
					return;
				}
				if (j - 1 >= 0 && j + 1 < size && board[i][j + 1] == 2 && !board[i][j - 1]) {
					board[i][j - 1] = 2;
					return;
				}
				if (i - 1 >= 0 && j - 1 >= 0 && i + 1 < size && j + 1 < size && board[i + 1][j + 1] == 2 && !board[i - 1][j - 1]) {
					board[i - 1][j - 1] = 2;
					return;
				}
				if (i - 1 >= 0 && i + 1 < size && board[i + 1][j] == 2 && !board[i - 1][j]) {
					board[i - 1][j] = 2;
					return;
				}
				if (i - 1 >= 0 && j + 1 < size && i + 1 < size && j - 1 >= 0 && board[i + 1][j - 1] == 2 && !board[i - 1][j + 1]) {
					board[i - 1][j + 1] = 2;
					return;
				}
			}	

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] == 2)
				for (int k = 0; k < 16; k++) {
					int random = rand() % 8;
					if (random == 0 && j + 1 < size && !board[i][j + 1]) {
						board[i][j + 1] = 2;
						return;
					}
					if (random == 1 && i + 1 < size && j + 1 < size && !board[i + 1][j + 1]) {
						board[i + 1][j + 1] = 2;
						return;
					}
					if (random == 2 && i + 1 < size && !board[i + 1][j]) {
						board[i + 1][j] = 2;
						return;
					}
					if (random == 3 && i + 1 < size && j - 1 >= 0 && !board[i + 1][j - 1]) {
						board[i + 1][j - 1] = 2;
						return;
					}
					if (random == 4 && j - 1 >= 0 && !board[i][j - 1]) {
						board[i][j - 1] = 2;
						return;
					}
					if (random == 5 && i - 1 >= 0 && j - 1 >= 0 && !board[i - 1][j - 1]) {
						board[i - 1][j - 1] = 2;
						return;
					}
					if (random == 6 && i - 1 >= 0 && !board[i - 1][j]) {
						board[i - 1][j] = 2;
						return;
					}
					if (random == 7 && i - 1 >= 0 && j + 1 < size && !board[i - 1][j + 1]) {
						board[i - 1][j + 1] = 2;
						return;
					}
				}

	while (TRUE) {
		int i = rand() % size;
		int j = rand() % size;
		if (!board[i][j]) {
			board[i][j] = 2;
			return;
		}
	}
}

//хід гравця
void player_turn(int size, int** board, int wind, int& turn, RenderWindow& window, int sign)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (IntRect((wind / size + 1) * i, (wind / size + 1) * j, wind / size, wind / size).contains(Mouse::getPosition(window)))
				if (Mouse::isButtonPressed(Mouse::Left) && board[i][j] == 0) {
					board[i][j] = sign;
					turn++;
				}
}

//хід нуликів
void null_turn(int size, int** board, int wind, int& turn, int versus_who, int bot, RenderWindow& window)
{
	if (versus_who == 1)
		player_turn(size, board, wind, turn, window, 2);

	else {
		if (bot == 1)
			bot_easy(board, size, turn);
		else
			bot_hard(board, size, turn);
	}
}