#pragma once

#include <vector>
#include <set>

enum class SearchResult { NOT_WORD, PREFIX, WORD };

class Dictionary {
	public:
		Dictionary(std::string filepath);
		SearchResult search(std::string s);
	private:
		std::vector<std::string> words;
};

typedef std::pair<int, int> Coord;
typedef std::vector<Coord> Path;

class Game {
	public:
		Game(int rows, int cols, Dictionary& dict);
		std::set<std::string> all_words;
		std::vector<std::vector<char>> board;
		/* ~Game(); */
	private:
		const int rows, cols;
		const int min_length;
		Dictionary& dict;
		void gen_board(int rows, int cols);
		void populate_all_words();
		std::string from_path(Path path);
		std::vector<std::string> words_starting_with(Path prefix);
};
