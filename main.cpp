#include <iostream>
#include <thread>

#include <miniupnpc/miniupnpc.h>

#include "network/socket/udp.hpp"
#include "network/socket/tcp.hpp"

int main()
{
  network :: socket :: tcp sock;
  
  sock.bind();
  
  std :: cout << sock.port() << std :: endl;
  
  sock.listen();
  
  sock.accept();
  
  std :: cout << "Andiamolo" << std :: endl;
}