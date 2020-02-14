#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "display.h"
#include "game.h"

int main(int argc, char** argv) {
	srand(time(0));

	printf("Loading dictionary...\n");
	Dictionary dic("words.txt");
	printf("%d\n", (int)dic.search("atom"));
	printf("%d\n", (int)dic.search("onoma"));
	printf("%d\n", (int)dic.search("dgldsf"));

	Display* d = Display::getDisplay();
	d->test();

	return 0;
}
