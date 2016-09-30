#include <iostream>
#include <thread>

#include "network/upnp/client.hpp"

int main()
{
  network :: upnp :: client my_client(14);
  my_client.discover();
  
  if(my_client.available() && my_client.online())
  {
    // Test that everything works.
  }
}
