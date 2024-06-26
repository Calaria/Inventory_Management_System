// Algorithm.h
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>
#include <unordered_set>

int common_sequence_length(std::string s1, std::string s2);
int largest_common_sequence(std::string s, std::vector<std::string> choices);
void prompt_info(int &id, std::string &name, std::string &category, double &price, int &quantity, std::unordered_set<std::string> Inquiry_content);
#endif // ALGORITHM_H