#include <iostream>
#include <thread>

#include <miniupnpc/miniupnpc.h>

#include "network/socket/udp.hpp"

int main()
{
  std :: cout << "Local: " << network :: address :: local() << std :: endl;
  std :: cout << "External: " << network :: address :: external() << std :: endl;
}