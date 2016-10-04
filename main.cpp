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
    
    std :: cout << "Here I am!" << std :: endl;
    
    network :: socket :: tcp sock;
    sock.bind();
    
    auto portmap = my_client.map(sock);
    
    std :: cout << portmap.local << std :: endl;
    std :: cout << portmap.external << std :: endl;
  }
}
