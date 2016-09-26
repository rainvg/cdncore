#include <iostream>
#include <thread>

#include "network/diagnostics/server.hpp"

int main()
{
  network :: diagnostics :: server server;
  server.start();
  
  while(true) pause();
}