#pragma once

#include <string>
#include <chrono>
#include <curses.h>
#include "game.h"

class Display {
	public:
		Display(const std::string& dict_filepath);
		~Display();

		void test();
		void run();
	private:
		static const std::chrono::milliseconds tick;
		static const int board_rows = 4;
		static const int board_cols = 4;

		void draw_game();
		void draw_board();
		void draw_score();
		bool handle_input();
		void tick_update();

		Dictionary dict;
		Game game;
		int word_line;
		std::string word_in_progress;
		WINDOW* board_win;
		WINDOW* score_win;
		WINDOW* words_win;
		WINDOW* cur_word_win;
};
