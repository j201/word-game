#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
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

Game::Game(int rows, int cols, Dictionary& dict) :
		rows(rows), cols(cols), dict(dict), min_length(3) {
	gen_board(rows, cols);
	populate_all_words();
}

void Game::gen_board(int rows, int cols) {
	board = std::vector<std::vector<char>>(rows);
	for (int i = 0; i < rows; i++) {
		board[i] = std::vector<char>(cols);
	}
	if (rows == 4 && cols == 4) {
		auto my_dice(dice);
		std::random_shuffle(my_dice.begin(), my_dice.end());
		for (int i = 0; i < 16; i++) {
			board[i/4][i%4] = dice[i][rand() % 6];
		}
	} else {
		throw std::invalid_argument("Only 4x4 boards currently supported");
	}
}

std::string Game::from_path(Path path) {
	std::string s;
	for (Coord coord : path) {
		s.push_back(board[coord.first][coord.second]);
	}
	return s;
}

std::vector<std::string> Game::words_starting_with(Path prefix) {
	std::string prefix_word = from_path(prefix);
	SearchResult sr = dict.search(prefix_word);
	if (sr == SearchResult::NOT_WORD)
		return std::vector<std::string>();
	std::vector<std::string> ss;
	if (sr == SearchResult::WORD && prefix_word.size() >= min_length)
		ss.push_back(prefix_word);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j<= 1; j++) {
			Coord next_coord = Coord(prefix.back());
			next_coord.first += i;
			next_coord.second += j;
			if ((i == 0 && j == 0) ||
					next_coord.first >= rows || next_coord.first < 0 ||
					next_coord.second >= rows || next_coord.second < 0 ||
					std::find(prefix.begin(), prefix.end(), next_coord) != prefix.end())
				continue;
			Path next_path(prefix);
			next_path.push_back(next_coord);
			auto rest = words_starting_with(next_path);
			ss.insert(ss.end(), rest.begin(), rest.end());
		}
	}
	return ss;
}

void Game::populate_all_words() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Coord c = Coord(i,j);
			Path p = Path({c});
			auto words = words_starting_with(p);
			all_words.insert(words.begin(), words.end());
		}
	}
}
