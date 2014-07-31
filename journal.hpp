#pragma once

#include <iostream>
#include <fstream>

#include "entry.hpp"

class Journal 
{
private:
   off_t position;
   std::ifstream file;

public:
   Journal();

   Entry next();
   bool eof();
};
