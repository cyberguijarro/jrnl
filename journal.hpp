#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "entry.hpp"

class Journal 
{
private:
   off_t position;
   std::fstream file;

public:
   Journal(const std::string& path = std::string());

   Entry next();
   bool eof();
   void push(const std::vector<std::string>& lines);
   void pop();
   void reset();
};
