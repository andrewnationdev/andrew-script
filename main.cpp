#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include "evaluator.hpp"
#include "environment.hpp"
#include "parser.hpp"

std::map<std::string, int> variables;
std::map<std::string, std::string> str_variables;

int main() {
	std::string command = "";

	while(command != "return") {
		std::cout << "andrew-script: ";
		std::getline(std::cin, command);

		parse_command(command);
	}

	return 0;
}