#pragma once

#include <vector>
#include <set>

enum class SearchResult { NOT_WORD, PREFIX, WORD };

class Dictionary {
	public:
		Dictionary(std::string filepath);
		SearchResult search(std::string s) const;
	private:
		std::vector<std::string> words;
};

typedef std::pair<int, int> Coord;
typedef std::vector<Coord> Path;

class Game {
	public:
		Game(int rows, int cols, const Dictionary& dict);
		const int rows, cols;
		const int min_length;
		const Dictionary& dict;

		std::string from_path(const Path& path) const;
		std::vector<std::string> words_starting_with(const Path& prefix) const;
		int word_score(const std::string& word) const;
		const std::set<std::string>& get_all_words() const;
		const std::vector<std::vector<char>>& get_board() const;
		int get_all_words_score() const;
		int get_score() const;

		bool try_play(const std::string& word);
	private:
		std::vector<int> word_scores;
		std::set<std::string> all_words;
		std::vector<std::vector<char>> board;
		int all_words_score;
		std::set<std::string> played_words;
		int score;

		void gen_board(int rows, int cols);
		void populate_all_words();
};
