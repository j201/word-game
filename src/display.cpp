// Game display, wrapper for ncurses
// Highly stateful and honestly not a good way to do graphics, but This Is C++

#include <curses.h>
#include "display.h"

Display* Display::instance = 0;

Display::Display() {
	// Init ncurses
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	clear();
}

Display* Display::getDisplay() {
	if (!instance) {
		instance = new Display;
	}
	return instance;
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
