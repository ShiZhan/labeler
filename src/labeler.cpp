#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "options.h"

typedef std::map<std::string, uint64_t> dict_t;

uint64_t dict_load(const char *dict_file, dict_t &dict) {
	uint64_t max = 0;
	if (dict_file) {
		std::ifstream dict_fs(dict_file);
		if(dict_fs) {
			std::string line;
			while (getline(dict_fs, line)) {
				std::stringstream ss(line);
				std::string token;
				uint64_t id;
				ss >> token;
				ss >> id;
				dict[token] = id;
				if (id > max) max = id;
			}
			dict_fs.close();
		}
	}
	return max;
}

void dict_store(const char *dict_file, dict_t &dict) {
	if (dict_file) {
		std::ofstream dict_fs(dict_file);
		if(dict_fs) {
			for (auto elem: dict) {
				dict_fs << elem.first << " " << elem.second << std::endl;
			}
			dict_fs.close();
		}
	}
}

void permutate(dict_t &dict, uint64_t &id, char seperator) {
	std::string line;
	while (getline(std::cin, line)) {
		std::stringstream ss(line);
		std::string token;
		while (getline(ss, token, seperator)) {
			auto itr = dict.find(token);
			if (itr == dict.end()) {
				id++;
				dict[token] = id;
			}
			std::cout << dict[token] << " ";
		}
		std::cout << std::endl;
	}
}

int main (int argc, char* argv[]) {
	using namespace std;
	using namespace opt;

	if (chkOption(argv, argv + argc, "-h")) {
		cout << "labeler [options]" << endl
			<< " -h:\t ask for help" << endl
			<< " -d:\t dictionary" << endl
			<< " -s:\t seperator" << endl;
		return 0;
	}

	char* dict_file = getOption(argv, argv + argc, "-d");
	char* seperator = getOption(argv, argv + argc, "-s");

	dict_t dict;
	uint64_t id = dict_load(dict_file, dict);

	char s = seperator ? seperator[0] : ' ';
	permutate(dict, id, s);

	dict_store(dict_file, dict);

	return 0;
}
