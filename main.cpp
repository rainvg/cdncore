#include "data/string.hpp"
#include "network/address.hpp"
#include "platform/endianess.hpp"

#include <iostream>

int main()
{
  data :: string x = data :: string :: forge(1, data :: string("pippo"), network :: address("1.2.3.4", 8080), 2, data :: string("cane"), 3, data :: string("pluto"));
  
  data :: string a, b, c;
  int aa, bb, cc;
  network :: address d;
  
  x.read(0, aa, a, d, bb, b, cc, c);
  
  std :: cout << aa << std :: endl;
  std :: cout << a << std :: endl;
  std :: cout << d << std :: endl;
  std :: cout << bb << std :: endl;
  std :: cout << b << std :: endl;
  std :: cout << cc << std :: endl;
  std :: cout << c << std :: endl;
}