#include <iostream>
#include <thread>

#include "network/upnp/client.hpp"

int main()
{
  network :: upnp :: client my_client;
  my_client.discover();
  
  std :: cout << "Available: " << my_client.available() << std :: endl;
  std :: cout << "Online: " << my_client.online() << std :: endl;
}
