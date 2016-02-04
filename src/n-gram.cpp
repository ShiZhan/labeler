#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include "options.h"

void ngram(int n, char seperator, std::istream &in, std::ostream &out) {
	std::string line;
	while (getline(in, line)) {
		std::stringstream ss(line);
		std::list<std::string> grams(n, "*");
		std::string token;
		while (getline(ss, token, seperator)) {
			grams.push_back(token);
			grams.pop_front();
			for (auto g: grams) out << g << " ";
			out << std::endl;
		}
	}
}

void ngram(int n, char seperator, const char *input_file, const char *output_file) {
	if (input_file) {
		std::ifstream ifs(input_file);
		if (ifs) {
			if (output_file) {
				std::ofstream ofs(output_file);
				if (ofs) {
					ngram(n, seperator, ifs, ofs);
					ofs.close();
				}
				else {
					ngram(n, seperator, ifs, std::cout);
				}
			}
			else {
				ngram(n, seperator, ifs, std::cout);
			}
			ifs.close();
		}
	}
	else {
		ngram(n, seperator, std::cin, std::cout);
	}
}

int main(int argc, char* argv[]) {
	using namespace std;
	using namespace opt;

	if (chkOption(argv, argv + argc, "-h")) {
		cout << "n-gram [options]" << endl
			<< " -h:\t ask for help" << endl
			<< " -n:\t ?-gram,      default: 2" << endl
			<< " -s:\t seperator,   default: space" << endl
			<< " -i:\t input file,  default: stdin" << endl
			<< " -o:\t output file, default: stdout" << endl;
		return 0;
	}

	int n = getValue(argv, argv + argc, "-n", 2);
	char* seperator = getOption(argv, argv + argc, "-s");
	char* input_file = getOption(argv, argv + argc, "-i");
	char* output_file = getOption(argv, argv + argc, "-o");

	char s = seperator ? seperator[0] : ' ';
	ngram(n, s, input_file, output_file);

	return 0;
}
