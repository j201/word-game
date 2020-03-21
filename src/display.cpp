// Game display, wrapper for ncurses
// Highly stateful and honestly not a good way to do graphics, but This Is C++

#include <thread>
#include "display.h"

const std::chrono::milliseconds Display::tick = std::chrono::milliseconds(20);

Display::Display(const std::string& dict_filepath) : dict(dict_filepath),
	game(board_rows,board_cols,dict) {
	// Init ncurses
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	auto board_win_w = board_cols*2+2;
	auto board_win_h = board_win_w;
	score_win = newwin(1, board_win_w, 0, 0);
	board_win = newwin(board_win_h, board_win_w, 1, 0);
	words_win = newwin(LINES, board_win_w + board_rows*board_cols, 0, board_win_w);
	cur_word_win = newwin(1, board_win_w, 1+board_win_h, 0);
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
