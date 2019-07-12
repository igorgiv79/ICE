// 
// Copyright ©2019 Igor Gomon
//

#include "pch.h"

#include <iostream>
#include <string>
#include <vector>

void split (std::string const &str, std::vector<std::string> &vstr, char ch)
{
	vstr.clear ();

	std::string nstr;
	bool wp = false;	// within parenthesis;
	for (char c: str) {
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

int main (int argc, char *argv[])
{
	std::cout << "Please enter a group of English words, separated by space:\n";

	std::string text;
	std::getline (std::cin, text);
	if (text.empty ()) {
		std::cout << "No input provided";
		return -1;
	}

	std::vector<std::string> words;
	split (text, words, ' ');
	for (auto w1 = words.begin (); w1 != words.end (); ++w1) {
		// discard empty strings;
		if (w1->empty ())
			continue;
		std::cout << "anagrams for " << *w1 << ":";
		for (auto w2 = words.begin(); w2 != words.end (); ++w2) {
			// ignore duplicates
			if (*w1 == *w2)
				continue;
			// discard words that are different in length;
			if (w1->length() != w2->length())
				continue;
			// for each character in w1 check that it is present exactly once in w2;
			bool anagram = true;
			for (auto c : *w1) {
				int numOcc1 = std::count (w1->begin (), w1->end (), c);
				int numOcc2 = std::count (w2->begin (), w2->end (), c);
				if (numOcc1 == numOcc2) {
					continue;
				}
				else {
					// not an anagram;
					anagram = false;
					break;
				}
			}

			if (anagram) {
				std::cout << " " << *w2;
			}
		}
		std::cout << std::endl;
	}

	return 0;
}
