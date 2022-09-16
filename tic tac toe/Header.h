#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;
using namespace sf;

void input_format(int& size, int& n, int& versus_who, int**& board, int& turn, int& bot, int& do_you_want_to_continue, string& player_name);
int** output_of_file(int& size, int& n, int& bot, int& turn, string player_name, int& do_you_want_to_continue);
void create_file(int& size, int& n, int& bot, int& turn, int** board, string player_name);
void input_all_inf_about_game_state(int& size, int& n, int& turn);
void input_bot(int& bot);
int** board_not_from_file(int& size);
void bot_easy(int** board, int size, int& turn);
void bot_hard(int** board, int size, int& turn);
bool diagonal_check(int** board, int size, int n, int sign);
bool vertical_check(int** board, int size, int n, int sign);
bool horisontal_check(int** board, int size, int n, int sign);
void CheckCommand(int& command);
void player_turn(int size, int** board, int wind, int& turn, RenderWindow& window, int sign);
bool win_check(int size, int** board, int n, int versus_who, int do_you_want_to_continue, string player_name, RenderWindow& window, int sign, int& turn_check);
bool draw_check(int turn, int turn_check, RenderWindow& window, int do_you_want_to_continue, string player_name);
void window_draw(int size, int** board, Sprite ult_sprt, int bias, Vector2f scale, RenderWindow& window);
void end_if_Escape_is_pressed(int size, int** board, int n, int bot, int& turn, string player_name, int versus_who, RenderWindow& window);
void criss_cross(int size, int** board, int n, int bot, int& turn, int turn_check, string player_name, int versus_who, int do_you_want_to_continue);
void null_turn(int size, int** board, int wind, int& turn, int versus_who, int bot, RenderWindow& window);