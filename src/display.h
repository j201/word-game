#pragma once

#include <string>
#include <chrono>
#include "game.h"

class Display {
	public:
		Display(const std::string& dict_filepath);
		~Display();

		void test();
		void run();
	private:
		static const std::chrono::milliseconds tick;

		void draw_game();
		bool handle_input();
		void tick_update();

		Game game;
		Dictionary dict;
		int word_line;
		std::string word_in_progress;
};
