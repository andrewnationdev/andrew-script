#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include "evaluator.hpp"
#include "environment.hpp" 

bool parse_if(std::string condition) {
	condition.erase(std::remove(condition.begin(), condition.end(), ' '), condition.end());

	int pos_greater_than = condition.find(">");
	int pos_less_than = condition.find("<");
	int pos_not_eq_to = condition.find("!=");
	int pos_eq_to = condition.find("==");

	if(pos_greater_than != std::string::npos) {
		std::string left = condition.substr(0, pos_greater_than);
		std::string right = condition.substr(pos_greater_than + 1);

		return parseValue(left) > parseValue(right);
	}

	if(pos_less_than != std::string::npos) {
		std::string left = condition.substr(0, pos_less_than);
		std::string right = condition.substr(pos_less_than + 1);

		return parseValue(left) < parseValue(right);
	}

	if(pos_not_eq_to != std::string::npos) {
		std::string left = condition.substr(0, pos_not_eq_to);
		std::string right = condition.substr(pos_not_eq_to + 2);

		return parseValue(left) != parseValue(right);
	}

	if(pos_eq_to != std::string::npos) {
		std::string left = condition.substr(0, pos_eq_to);
		std::string right = condition.substr(pos_eq_to + 2);

		return parseValue(left) == parseValue(right);
	}

	return true;
}

int parseValue(std::string token) {
	token.erase(remove(token.begin(), token.end(), ' '), token.end());

	if(token.empty()) return 0;

	if(variables.find(token) != variables.end()) {
		return variables[token];
	}

	return std::stoi(token);
}

int evaluate_expression(std::string expr) {
	expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end());

	size_t posMais = expr.find('+');
	if (posMais != std::string::npos) {
		std::string esquerda = expr.substr(0, posMais);
		std::string direita = expr.substr(posMais + 1);

		return parseValue(esquerda) + parseValue(direita);
	}

	size_t posMenos = expr.find('-');
	if (posMenos != std::string::npos) {

		std::string esquerda = expr.substr(0, posMenos);
		std::string direita = expr.substr(posMenos + 1);

		return parseValue(esquerda) - parseValue(direita);
	}

	size_t posMultipl = expr.find('*');
	if (posMultipl != std::string::npos) {

		std::string left = expr.substr(0, posMultipl);
		std::string right = expr.substr(posMultipl + 1);

		return parseValue(left) * parseValue(right);
	}

	size_t posDiv = expr.find('/');
	if (posDiv != std::string::npos) {

		std::string left = expr.substr(0, posDiv);
		std::string right = expr.substr(posDiv + 1);

		return parseValue(left) / parseValue(right);
	}

	return parseValue(expr);
}