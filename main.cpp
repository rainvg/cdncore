#include "data/string.hpp"
#include "network/address.hpp"
#include "platform/endianess.hpp"
#include "network/socket/udp.hpp"

#include <iostream>
#include <thread>

network :: socket :: udp my_socket;

void receiver()
{
  while(true)
  {
    std :: cout << my_socket.receive() << std :: endl;
  }
}

int main()
{
  my_socket.bind(1234);
  
  std :: thread receiver_thread(receiver);
  
  while(true)
  {
    char buffer[1024];
    std :: cin.getline(buffer, 1024);
    
    my_socket.send({"127.0.0.1", 1235}, buffer);
  }
}