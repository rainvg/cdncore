#include "udp.hpp"

namespace network :: socket
{
  // Constructors
  
  udp :: udp()
  {
    this->_descriptor = :: socket(PF_INET, SOCK_DGRAM, 0);
    
    int optreuse = true;
    if (:: setsockopt(this->_descriptor, SOL_SOCKET, SO_REUSEADDR, &optreuse, sizeof(int)))
      throw exception <enetwork, esocket, eudp, esetsockopt_failed> {};
  }
  
  // Getters
  
  uint16_t udp :: port()
  {
    return this->_port;
  }
  
  // Methods
  
  void udp :: bind(const uint16_t & port)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, eudp, esocket_closed> {};
    
    network :: address bind_address("0.0.0.0", port);
    
    if(:: bind(this->_descriptor, (struct sockaddr *) &bind_address, sizeof(sockaddr_in)))
      throw exception <enetwork, esocket, eudp, ebind_failed> {};
    
    this->_port = port;
  }
  
  void udp :: send(const address & remote, const data :: string & message)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, eudp, esocket_closed> {};
    
    if(:: sendto(this->_descriptor, message, message.size(), 0, (struct sockaddr *) &remote, sizeof(sockaddr_in)) < 0)
    {
      if(errno == EAGAIN)
        throw exception <enetwork, esocket, eudp, etimeout> {};
      else
        throw exception <enetwork, esocket, eudp, esend_failed> {};
    }
  }
  
  data :: string udp :: receive()
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, eudp, esocket_closed> {};
    
    struct sockaddr_in source;
    socklen_t source_len = sizeof(sockaddr_in);
    
    char buffer[1024];
    
    long int bytes_received;
    
    if((bytes_received = :: recvfrom(this->_descriptor, buffer, 1024, 0, (sockaddr *) &source, &source_len)) < 0)
    {
      if(errno == EAGAIN)
        throw exception <enetwork, esocket, eudp, etimeout> {};
      else
        throw exception <enetwork, esocket, eudp, ereceive_failed> {};
    }
    
    return data :: string(buffer, bytes_received);
  }
  
  void udp :: enable_broadcast(const bool & enable)
  {
    int option = enable;
    if(setsockopt(this->_descriptor, SOL_SOCKET, SO_BROADCAST, &option, sizeof(int)))
      throw exception <enetwork, esocket, eudp, esetsockopt_failed> {};
  }
};