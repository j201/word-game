#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <iostream>
#include "display.h"
#include "game.h"

int main(int argc, char** argv) {
	srand(time(0));

	printf("Loading dictionary...\n");
	Dictionary dict("words.txt");
	printf("Initializing game...\n");
	Game g(4, 4, dict);
	printf("Number of words: %d\n", (int)g.all_words.size());
	for (auto row : g.board) {
		for (auto c : row) {
			std::cout << c << " ";
		}
		std::cout << "\n";
	}
	for (auto w : g.all_words) {
		std::cout << w << "\n";
	}
	/* Display* d = Display::getDisplay(); */
	/* d->test(); */

	return 0;
}
