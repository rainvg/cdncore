#include "data/string.hpp"
#include "network/address.hpp"
#include "platform/endianess.hpp"
#include "network/socket/udp.hpp"

#include <iostream>
#include <thread>

int main()
{
  network :: socket :: udp my_socket;
  my_socket.bind(1234);
  my_socket.enable_broadcast(true);
}