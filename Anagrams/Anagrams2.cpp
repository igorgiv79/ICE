
// 
// Copyright ©2019 Igor Gomon
//

#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <iterator>

void split (std::string const &str, std::vector<std::string> &vstr, char ch)
{
	vstr.clear ();

	std::string nstr;
	bool wp = false;	// within parenthesis;
	for (char c : str) {
		if (c == '\r')
			continue;
		else if (c == '\n')
			c = ' ';

		if (c == ch) {
			vstr.push_back (nstr);
			nstr.clear ();
		}
		else {
			nstr += c;
		}
	}

	if (nstr.length () > 0)
		vstr.push_back (nstr);
}

typedef std::list<std::string> StringList;
using StringListPtr = std::shared_ptr<std::list<std::string>>;

std::ostream& operator << (std::ostream &os, StringListPtr sl) {
	std::copy (sl->begin (), sl->end (), std::ostream_iterator<std::string> (std::cout, " "));
	return os;
}

int main (int argc, char *argv[])
{
	std::cout << "Please enter a group of English words, separated by space:\n";

	std::string text;
	std::getline (std::cin, text);
	if (text.empty ()) {
		std::cout << "No input provided";
		return -1;
	}

	// abc -> bca, cba, abc

	std::vector<std::string> words;  
	split (text, words, ' ');

	std::unordered_map<std::string, StringListPtr> map;
	for (auto w1: words) {
		
		std::string sw1 (w1);
		std::sort (sw1.begin (), sw1.end ());

		if (map.find (sw1) == map.end ()) {
			auto anagramList = std::make_shared<StringList> ();
			anagramList->push_back (w1);
			map[sw1]=anagramList;
		}
		else {
			auto list = map[sw1];
			list->push_back (w1);
		}
	}

	// printing the result;
	std::cout << "Results:\n";
	for (auto pair : map) {
		auto &list = pair.second;
		std::cout << list << std::endl;
	}

	return 0;
}