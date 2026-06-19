#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <thread>
#include "evaluator.hpp"
#include "environment.hpp" 

void parse_command(std::string command) {
	if(command == "") return;

	command.erase(0, command.find_first_not_of(" \t\r\n"));

	if(command.rfind("write(", 0) == 0) {
		int left_parenth_pos = command.find("(");
		int right_parenth_pos = command.find(")");

		if(right_parenth_pos != std::string::npos) {
			std::string content = command.substr(left_parenth_pos + 1, right_parenth_pos - left_parenth_pos - 1);

			if (str_variables.find(content) != str_variables.end()) {
				std::cout << str_variables[content] << std::endl;
			} else if (!content.empty() && content.front() == '"' && content.back() == '"') {
				std::cout << content.substr(1, content.length() - 2) << std::endl;
			} else {
				std::cout << evaluate_expression(content) << std::endl;
			}
		}
	}

	else if(command.rfind("read(", 0) == 0) {
		int left_parenth_pos = command.find("(");
		int right_parenth_pos = command.find(")");

		if(right_parenth_pos != std::string::npos) {
			std::string key = command.substr(left_parenth_pos + 1, right_parenth_pos - left_parenth_pos - 1);

			key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
			std::cin >> variables[key];

		}
	}

	else if(command.rfind("if", 0) == 0) {
		size_t left_parenth_pos = command.find("(");
		size_t right_parenth_pos = command.find(")");

		if(left_parenth_pos != std::string::npos && right_parenth_pos != std::string::npos) {
			std::string condition = command.substr(left_parenth_pos + 1, right_parenth_pos - left_parenth_pos - 1);
			std::string instruct_to_run_if_true = command.substr(right_parenth_pos + 1);

			if(parse_if(condition)) {
				parse_command(instruct_to_run_if_true);
			}
		}
	}

	else if(command.rfind("for", 0) == 0) {
		size_t left_parenth_pos = command.find("(");
		size_t right_parenth_pos = command.find(")");

		if(left_parenth_pos != std::string::npos && right_parenth_pos != std::string::npos) {

			//for(i = 0, i < 10, 1) comando.

			int pos_first_comma = command.find(',');
			int pos_second_comma = command.find(",", pos_first_comma + 1);

			std::string attribution = command.substr(left_parenth_pos + 1, right_parenth_pos - left_parenth_pos - 1);
			std::string condition = command.substr(pos_first_comma + 1, pos_second_comma - pos_first_comma - 1);
			std::string increment = command.substr(pos_second_comma + 1, right_parenth_pos - pos_second_comma - 1);
			std::string command_to_run = command.substr(right_parenth_pos + 1);
			command_to_run.erase(0, command_to_run.find_first_not_of(" \t\r\n"));

			std::string variable = attribution.substr(0, attribution.find('='));
			variable.erase(std::remove(variable.begin(), variable.end(), ' '), variable.end());

			parse_command(attribution);

			int step = parseValue(increment);

			while(parse_if(condition) == true) {
				parse_command(command_to_run);

				std::string variable = attribution.substr(0, attribution.find('='));
				variable.erase(remove(variable.begin(), variable.end(), ' '), variable.end());

				variables[variable] = variables[variable] + step;
			}
		}
	}

	else if(command.rfind("sc_open(", 0) == 0 || command.rfind("import(", 0) == 0) {
		size_t left = command.find("(");
		size_t right = command.find(")");
		
		if(left != std::string::npos && right != std::string::npos) {
			std::string filename = command.substr(left + 1, right - left - 1);
			filename.erase(std::remove(filename.begin(), filename.end(), ' '), filename.end());
			
			std::ifstream file(filename);
			if(file.is_open()) {
				std::string file_line;
				while(std::getline(file, file_line)) {
					parse_command(file_line);
				}
				file.close();
			} else {
				std::cout << "[Erro] Arquivo nao encontrado: " << filename << std::endl;
			}
		}

	} else if(command.rfind("delay(", 0) == 0) {
		size_t left = command.find("(");
		size_t right = command.find(")");
		
		if(left != std::string::npos && right != std::string::npos) {
			std::string time_str = command.substr(left + 1, right - left - 1);
			
			int miliseconds = parseValue(time_str);
			
			std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
		}

	} else if(command == "clear()") {
		#ifdef _WIN32
			std::system("cls");
		#else
			std::system("clear");
		#endif

	} else {
		int eq_sign_pos = command.find("=");

		if (eq_sign_pos != std::string::npos) {
			std::string left = command.substr(0, eq_sign_pos);
			std::string right = command.substr(eq_sign_pos + 1);

			left.erase(std::remove(left.begin(), left.end(), ' '), left.end());

			right.erase(0, right.find_first_not_of(" \t\r\n"));
			size_t last = right.find_last_not_of(" \t\r\n");
			if (last != std::string::npos) {
				right.erase(last + 1);
			}

			if(!right.empty() && right.front() == '"' && right.back() == '"'){
				std::string parsed_str = right.substr(1, right.length() - 2);
				str_variables[left] = parsed_str;
			} else {
				variables[left] = evaluate_expression(right);
			}
		}
	}
}