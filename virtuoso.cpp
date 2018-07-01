#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unistd.h>
#include <utility>
#include <vector>
using namespace std;

#include "helpers.cpp"

// vector: list of pairs that result in a real word
// pair  : a single modification made to base_word resulting in another real word
//         if the char is a space (" ") then treat it as a removal at the int index
// Example: potential_letters[2] == pair<"saome_word", pair<'a', 1>>
//          base_word can form at least 3 potential new words
//          in particular, inserting 'a' at position 1 results in a "saome_word"
// Example: potential_letters[0] == pair<"someword", pair<' ', 4>>
//          base_word can form at least 1 potential new words
//          in particular, removing the letter at position 4 results in "someword"
class malleable_word
{
public:
	string base_word;
	vector<pair<string, pair<char, int>>> potential_letters;

	malleable_word()
	{
		;
	}

	explicit malleable_word(const string &base_word) : base_word(base_word)
	{
		;
	}

	void record_new_modification(string s, char c, int pos)
	{
		potential_letters.push_back(make_pair(s, make_pair(c, pos)));
	}

	friend ostream& operator << (ostream &os, const malleable_word &mw)
	{
		os << mw.base_word;
		if (!mw.potential_letters.empty())
		{
			os << ": ";
			os << mw.potential_letters;
		}
		return os;
	}
};


class virtuoso_solver
{
	vector<malleable_word> words;

	// The set of words to be used as a lookup table. 
	// Keeps track of what is considered a "real" word
	set<string> dictionary_words;

public:

	virtuoso_solver()
	{
		;
	}

	explicit virtuoso_solver(ifstream &dictionary_ifs)
	{
		read_dictionary_words(dictionary_ifs);
	}

	explicit virtuoso_solver(ifstream &dictionary_ifs, ifstream &words_ifs)
	{
		read_dictionary_words(dictionary_ifs);
		read_words(words_ifs);
	}

	// Read words from an input stream (one word per line) to build into dictionary_words
	// This dictionary will be used as a list of "real" words when building words
	void read_dictionary_words(ifstream &ifs)
	{
		dictionary_words.clear();
		for (string word; getline(ifs, word);)
		{
			transform(all(word), word.begin(), ::tolower);
			dictionary_words.insert(word);
		}
	}

	void read_words(ifstream &ifs)
	{
		words.clear();
		for (string word; getline(ifs, word);)
		{
			transform(all(word), word.begin(), ::tolower);
			words.push_back(malleable_word(word));
		}
	}

	void process()
	{
		// For each word
		for (malleable_word &mw : words)
		{
			// For each position in the word
			string word = mw.base_word;
			for (size_t j=0; j<word.size()+1; j++)
			{
				if (j < word.size())
				{
					// Attempt a remove on current position
					string remove = word;
					remove.erase(remove.begin() + j);
					if (is_a_word(remove))
					{
						mw.record_new_modification(remove, ' ', j);
					}
				}

				// Attempt additions of a-z on current position
				for (char c = 'a'; c <= 'z'; c++)
				{
					string add = word;
					add.insert(add.begin() + j, c);

					if (is_a_word(add))
					{
						mw.record_new_modification(add, c, j);
					}
				}
			}
		}
	}

	vector<malleable_word> get_words()
	{
		return words;
	}

private:
	bool is_a_word(const string &s)
	{
		return (dictionary_words.find(s) != dictionary_words.end());
	}
};

class config
{
public:
	string dictionary; // file to which words are compared, should have one word per line
	string words; // file containing input word

	config()
	{
		;
	}
};

void usage(char *program)
{
	cout << "Usage:" << endl;
	cout << program << " [options]" << endl;
	cout << endl;

	cout << "Options:" << endl;
	cout << "  -d  : dictionary (of words) to use" << endl;
	cout << "  -q  : list of words to test" << endl;
	cout << "  -h  : show this help and exit" << endl;
	cout << endl;
}

void parse_args(int argc, char **argv, config &c)
{
	// Default values
	c.dictionary = "enable1.txt";
	c.words = "virtuoso.txt"; // three-letter numbers

	// Read arguments
	int ch;
	while ((ch = getopt(argc, argv, "hd:w:")) != -1)
	{
		switch (ch)
		{
			case 'h':
				usage(argv[0]);
				exit(0);
				break;
			case 'd':
				c.dictionary = optarg;
				break;
			case 'w':
				c.words = optarg;
				break;
			default:
				usage(argv[0]);
				exit(1);
		}
	}
}

int main(int argc, char **argv)
{
	config c;
	parse_args(argc, argv, c);

	ifstream dictionary_ifs(c.dictionary);
	if (!dictionary_ifs.is_open())
	{
		cerr << "Error, unable to open dictionary file " << c.dictionary << endl;
		return 1;
	}
	ifstream words_ifs(c.words);
	if (!words_ifs.is_open())
	{
		cerr << "Error, unable to open words file " << c.words << endl;
		return 2;
	}


	virtuoso_solver vs(dictionary_ifs, words_ifs);
	dictionary_ifs.close();
	words_ifs.close();

	vs.process();

	for (malleable_word mw : vs.get_words())
	{
		cout << mw.base_word << endl;
		for (auto p : mw.potential_letters)
		{
			cout << "\t" << p << endl;
		}
	}
}
