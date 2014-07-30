#pragma once

#include <iostream>
#include <fstream>

#include "entry.hpp"

class Traverser
{
private:
   off_t position;
   std::ifstream file;

public:
   Traverser();

   Entry next();
   bool eof();
};
