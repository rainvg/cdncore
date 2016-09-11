#include <iostream>

#include "data/string.hpp"
#include "network/address.hpp"

int main()
{
  data :: string x = data :: string :: forge(data :: string("pippo"), data :: string("cane"), data :: string("pluto"));
  
  data :: string a, b, c;
  x.read(0, a, b, c);
  
  std :: cout << a << std :: endl;
  std :: cout << b << std :: endl;
  std :: cout << c << std :: endl;
}