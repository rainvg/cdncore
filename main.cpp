#include "data/string.hpp"
#include "network/address.hpp"
#include "platform/endianess.hpp"
#include "network/socket/udp.hpp"
#include "network/socket/tcp.hpp"

#include <iostream>
#include <thread>

int main()
{
  network :: socket :: tcp s;
  
  s.bind(1235);
  s.connect({"localhost", 1234});
  s.send("Ciao! Come va la vita??");
  std :: cout << s.receive(16) << std :: endl;
  s.close();
}