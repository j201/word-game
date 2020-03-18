// Game display, wrapper for ncurses
// Highly stateful and honestly not a good way to do graphics, but This Is C++

#include <thread>
#include <curses.h>
#include "display.h"

const std::chrono::milliseconds Display::tick = std::chrono::milliseconds(20);

Display::Display(const std::string& dict_filepath) : dict(dict_filepath), game(4,4,dict) {
	// Init ncurses
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	clear();
}

Display::~Display() {
	endwin();
}

void Display::test() {
	addch('F');
	addch('o');
	addch('o');
	getch();
}

void Display::run() {
	draw_game();
	while (handle_input()) {
		std::this_thread::sleep_for(tick);
		tick_update();
	}
}

void Display::draw_game() {
	// TODO
}

void Display::tick_update() {
	// TODO
}

bool Display::handle_input() {
	int ch = getch();
	if (ch >= 'A' && ch <= 'Z')
		ch = tolower(ch);
	if (ch >= 'a' && ch <= 'z') {
		word_in_progress.push_back(ch);
		if (game.try_play(word_in_progress)) {
			// TODO
		}
	}
	return true;
}
