#pragma once

#include <string>
#include <vector>

extern const size_t record_marker_length;

std::string filename();
std::string now();
std::vector<std::string> trim_lines(const std::vector<std::string>& lines);
bool edit(const std::string& filename);
