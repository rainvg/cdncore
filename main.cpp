#include <iostream>

#include "data/string.hpp"
#include "network/address.hpp"

int main()
{
  data :: string x = data :: string :: forge(network :: address("127.0.0.1", 1234));
  std :: cout << x.read <network :: address> (0) << std :: endl;
}