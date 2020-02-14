#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "game.h"

Dictionary::Dictionary(std::string filepath) {
	std::ifstream ifs;
	ifs.open(filepath);
	for (std::string line; std::getline(ifs, line);) {
		words.push_back(line);
	}
	ifs.close();
	std::sort(words.begin(), words.end());
}

SearchResult Dictionary::search(std::string s) {
	int left_limit = 0;
	int right_limit = words.size();
	int i = (left_limit + right_limit)/2;
	while (true) {
		int c = s.compare(words[i]);
		if (c == 0)
			return SearchResult::WORD;
		if (c < 0)
			right_limit = i;
		else
			left_limit = i;
		i = (left_limit + right_limit)/2;
		if (i == left_limit || i == right_limit) {
			if (s == words[right_limit].substr(0, s.size()))
				return SearchResult::PREFIX;
			return SearchResult::NOT_WORD;
		}
	}
}

const std::vector<std::vector<char>> dice = {
	{'r', 'i', 'f', 'o', 'b', 'x'},
	{'i', 'f', 'e', 'h', 'e', 'y'},
	{'d', 'e', 'n', 'o', 'w', 's'},
	{'u', 't', 'o', 'k', 'n', 'd'},
	{'h', 'm', 's', 'r', 'a', 'o'},
	{'l', 'u', 'p', 'e', 't', 's'},
	{'a', 'c', 'i', 't', 'o', 'a'},
	{'y', 'l', 'g', 'k', 'u', 'e'},
	{'q', 'b', 'm', 'j', 'o', 'a'},
	{'e', 'h', 'i', 's', 'p', 'n'},
	{'v', 'e', 't', 'i', 'g', 'n'},
	{'b', 'a', 'l', 'i', 'y', 't'},
	{'e', 'z', 'a', 'v', 'n', 'd'},
	{'r', 'a', 'l', 'e', 's', 'c'},
	{'u', 'w', 'i', 'l', 'r', 'g'},
	{'p', 'a', 'c', 'e', 'm', 'd'}
};

Game::Game(int rows, int cols) {
	this->gen_board(rows, cols);
	this->populate_all_words();
}

void Game::gen_board(int rows, int cols) {
	if (rows == 4 && cols == 4) {
		auto my_dice(dice);
		std::random_shuffle(my_dice.begin(), my_dice.end());
		for (int i = 0; i < 16; i++) {
			board[i/4][i%4] = dice[i][rand() % 6];
		}
	}
}

void Game::populate_all_words() {
}
