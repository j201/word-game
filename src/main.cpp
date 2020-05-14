#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <iostream>
#include "display.h"
#include "game.h"

int main(int argc, char** argv) {
	srand(time(0));

	Display* d = new Display("words/3of6game.txt");
	d->run();

	return 0;
}
