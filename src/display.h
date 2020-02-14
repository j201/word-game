#pragma once

#include <string>

class Display {
	public:
		static Display* getDisplay();
		void test();
	private:
		static Display* instance;
		Display();
		~Display();
		int word_line;
		std::string word_in_progress;
};
