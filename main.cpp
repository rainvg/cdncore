#include "data/string.hpp"

#include <iostream>
#include <thread>

int main()
{
  data :: string haystack("monsino is beautiful.");
  std :: cout << haystack.find(".") << std :: endl;
}