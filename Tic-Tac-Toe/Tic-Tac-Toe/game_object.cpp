// game_object.cpp : Defines struct for the console application.
// C++ Game: Tic-Tac-Toe
// Gameplay features: pattern-matching, bitboard, multi-player mode
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#include "stdafx.h"
#include "game_object.h"

game_object::game_object()
{
	default_mode();
}

void game_object::display_board()
{
	std::cout << std::endl << " ";
	for (int j = 0; j < MAXCOL; j++)
		std::cout << " " << (j + 1) ;

	char ch;

	for (int i = 0; i < MAXCOL*MAXROW; i++)
	{
		if (bit_board[0].test(i))
			ch = 'X';
		else
			if (bit_board[1].test(i))
				ch = 'O';
			else
				ch = '.';

		if ((i) % MAXCOL == 0)
			std::cout << std::endl << ((i / MAXCOL) + 1) << " " << ch;
		else
			std::cout << " " << ch;
	}
	std::cout << std::endl;
}

bool game_object::check_valid(int num)
{
	return (num > 0 && num <= MAXCOL);
}

bool game_object::check_valid(char ch)
{
	return (tolower(ch) == 'y' || tolower(ch) == 'n');
}

void game_object::reset_grid()
{
	bit_board[0] = 0ULL;
	bit_board[1] = 0ULL;
	bit_board[2] = 0ULL;
}

void game_object::reset_grid_count()
{
	int size = MAXROW * MAXCOL;
	int k = 0;
	while (k < size)
	{
		for (int i = 0; i<MAXROW; i++)
			for (int j = 0; j < MAXCOL; j++)
			{
				grid_count[i][j] = k++;
			}	
	}
}

void game_object::reset_grid_flag()
{
	for (auto flag : grid_flag)
		flag = false;
}

void game_object::game_reset()
{
	game_over = false;
	reset_grid();
	reset_grid_count();
	reset_grid_flag();
	player = 'O';
	system("cls");
}

void game_object::update_board(char player)
{
	std::cout << std::endl;

	int col = 1, row = 1, digit = 0;

	do
	{
		std::cout << "Player::" << player << "::Enter row::";
		//Check for valid row number
		while (!(std::cin >> row) || !check_valid(row))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (!check_valid(row))
				std::cout << "Error::Please enter row within the range of 1-6..." << std::endl;
			else
				std::cout << "Error::Please enter an integer value..." << std::endl;

			std::cout << std::endl;
			std::cout << "Player::" << player << "::Enter row::";
		}

		std::cout << "Player::" << player << "::Enter column::";
		//Check for valid column number
		while (!(std::cin >> col) || !check_valid(col))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (!check_valid(col))
				std::cout << "Error::Please enter column within the range of 1-6..." << std::endl;
			else
				std::cout << "Error::Please enter an integer value..." << std::endl;

			std::cout << std::endl;
			std::cout << "Player::" << player << "::Enter column::";
		}

		std::cout << std::endl;

		digit = grid_count[row - 1][col - 1];
		
		if (grid_flag[digit])
			std::cout << "This grid is full. Please enter some other grid..." << std::endl;
	} while (grid_flag[digit]);

	if (player == 'X')
		bit_board[0].set(digit);
	else
	if (player == 'O')
		bit_board[1].set(digit);

	bit_board[2] = bit_board[0] | bit_board[1];

	if (bit_board[2].test(digit))
		grid_flag[digit] = true;
}

bool game_object::check_win(std::bitset<12> &bit_board)
{
	std::bitset<12> bs = 0ULL;
	std::bitset<12> bs1;
	std::bitset<12> bs2;
	std::bitset<12> bs3;

	//Horizontal match
	bs = bit_board;
	bs1 = std::bitset<12>(std::string("111000000"));
	bs2 = std::bitset<12>(std::string("000111000"));
	bs3 = std::bitset<12>(std::string("000000111"));

	if ( ((bs & bs1) == bs1) || ((bs & bs2) == bs2) || ((bs & bs3) == bs3) )
	{
		return true;
	}
		
	//Vertical match
	bs1 = std::bitset<12>(std::string("100100100"));
	bs2 = std::bitset<12>(std::string("010010010"));
	bs3 = std::bitset<12>(std::string("001001001"));
	if (((bs & bs1) == bs1) || ((bs & bs2) == bs2) || ((bs & bs3) == bs3))
	{
		return true;
	}

	//Diagonal match /
	bs = bit_board;
	bs1 = std::bitset<12>(std::string("001010100"));
	if ((bs & bs1) == bs1)
	{
		return true;
	}

	//Diagonal match \	
	bs = bit_board;
	bs1 = std::bitset<12>(std::string("100010001"));
	if ((bs & bs1) == bs1)
	{
		return true;
	}
}

void game_object::flip_player()
{
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
}

char game_object::get_winner()
{
	if (check_win(bit_board[0]))
		return 'X';

	if (check_win(bit_board[1]))
		return 'O';
}

bool game_object::is_win()
{
	return (get_winner() == 'X' || get_winner() == 'O');
}

bool game_object::is_full()
{
	int cells = MAXROW*MAXCOL;
	return !(bit_board[2].count() < cells);
}

bool game_object::is_game_over()
{
	if (is_win())
		game_over = true;

	if (is_full())
		game_over = true;

	return game_over;
}

void game_object::display_game_over()
{
	if (is_win())
		std::cout << "Winner::" << get_winner() << std::endl;
	else
		std::cout << "GAME OVER:: Grid is full..." << std::endl;

	std::cout << "\nThe final board is::" << std::endl;
	display_board();
	std::cout << std::endl;
}

void game_object::get_response()
{
	char ch;
	std::cout << "\nWould you like to play again? : \'Y\': Yes \'N\': No :: ";
	while (!(std::cin >> ch) || !check_valid(ch))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error::Please enter Y or N..." << std::endl;
		std::cout << "Would you like to play again? : \'Y\': Yes \'N\': No :: ";
	}

	if (tolower(ch) == 'y')
	{
		play_again = true;
		game_reset();
	}

	if (tolower(ch) == 'n')
		play_again = false;
}

void game_object::default_mode()
{
	std::cout << "Welcome to Tic-Tac-Toe..." << std::endl;

	//Loop till player would like to play
	do
	{
		while (!is_game_over())
		{
			reset_grid_count();
			flip_player();
			display_board();
			update_board(player);
		}

		display_game_over();
		get_response();

	} while (play_again);

	std::cout << "\nThank you for playing...\n" << std::endl;
}
