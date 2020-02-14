#pragma once

#include <vector>

enum class SearchResult { NOT_WORD, PREFIX, WORD };

class Dictionary {
	public:
		Dictionary(std::string filepath);
		SearchResult search(std::string s);
	private:
		std::vector<std::string> words;
};

class Game {
	public:
		Game(int rows, int cols);
		~Game();
	private:
		void gen_board(int rows, int cols);
		void populate_all_words();
		std::vector<std::vector<char>> board;
		std::set<std::string> all_words;
};
