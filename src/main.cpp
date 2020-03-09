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
	Dictionary dict("words/3of6game.txt");
	printf("Initializing game...\n");
	Game g(4, 4, dict);
	printf("Number of words: %d\n", (int)g.get_all_words().size());
	printf("Total score: %d\n", g.get_all_words_score());
	for (auto row : g.get_board()) {
		for (auto c : row) {
			std::cout << c << " ";
		}
		std::cout << "\n";
	}
	for (auto w : g.get_all_words()) {
		std::cout << w << "\n";
	}
	/* Display* d = Display::getDisplay(); */
	/* d->test(); */

	return 0;
}
