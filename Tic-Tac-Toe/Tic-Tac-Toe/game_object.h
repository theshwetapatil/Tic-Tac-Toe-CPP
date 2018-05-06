// game_object.h : Defines header for the console application.
// C++ Game: Tic-Tac-Toe
// Gameplay features: pattern-matching, bitboard, multi-player mode
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#pragma once
#include <iostream>
#include <bitset>
#include <limits>
#include <vector>

#define MAXROW 3
#define MAXCOL 3

typedef struct game_object
{
	private:
		std::bitset<12> bit_board[3];
		std::vector<std::vector<int>> grid_count = std::vector<std::vector<int>>(MAXROW, std::vector<int>(MAXCOL, 0));
		std::vector<bool> grid_flag = std::vector<bool>(MAXROW*MAXCOL, false);
		char player = '.';
		bool game_over = false;
		bool play_again = false;

	public:
		game_object();
		void display_board();
		bool check_valid(int num);
		bool check_valid(char ch);
		void reset_grid();
		void reset_grid_count();
		void reset_grid_flag();
		void game_reset();
		void update_board(char player);
		bool check_win(std::bitset<12> &bit_board);
		void flip_player();
		char get_winner();
		bool is_win();
		bool is_full();
		bool is_game_over();
		void display_game_over();
		void get_response();
		void default_mode();
}GRID;
