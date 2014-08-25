#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <functional>

#include "entry.hpp"

class Journal 
{
private:
   std::fstream file;
   std::string path;

   void open();
   void close();

public:
   Journal(const std::string& path = std::string());

   void each(std::function<bool(const Entry&)> callback);
   Entry back();
   void push(const std::vector<std::string>& lines);
   void pop();
   void reset();
};
