#include <iostream>
#include <thread>

#include "network/diagnostics/server.hpp"
#include "network/diagnostics/client.hpp"

int main()
{
  network :: diagnostics :: server server;
  server.start();
  
  usleep(1E6);
  
  network :: diagnostics :: client client({"localhost", 0});
  std :: cout << client.udp() << std :: endl;
  
  while(true) pause();
}