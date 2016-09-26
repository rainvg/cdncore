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
  
  // Destructor
  
  udp :: ~udp()
  {
    this->close();
  }
  
  // Getters
  
  int udp :: descriptor()
  {
    return this->_descriptor;
  }
  
  uint16_t udp :: port()
  {
    return this->_port;
  }
  
  address udp :: interface()
  {
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if(getsockname(this->_descriptor, (struct sockaddr *) &sin, &len))
      throw exception <enetwork, esocket, eudp, egetsockname_failed> {};
    
    return sin;
  }
  
  // Methods
  
  void udp :: bind(const uint16_t & port)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, eudp, esocket_closed> {};
    
    network :: address bind_address("0.0.0.0", port);
    
    if(:: bind(this->_descriptor, (struct sockaddr *) &bind_address, sizeof(sockaddr_in)))
      throw exception <enetwork, esocket, eudp, ebind_failed> {};
    
    if(port)
      this->_port = port;
    else
    {
      struct sockaddr_in sin;
      socklen_t len = sizeof(sin);
      if(getsockname(this->_descriptor, (struct sockaddr *) &sin, &len))
        throw exception <enetwork, esocket, eudp, egetsockname_failed> {};
      
      this->_port = ntohs(sin.sin_port);
    }
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
  
  udp :: packet udp :: receive()
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
    
    return {.remote = source, .message = data :: string(buffer, bytes_received)};
  }
  
  void udp :: enable_broadcast(const bool & enable)
  {
    int option = enable;
    if(setsockopt(this->_descriptor, SOL_SOCKET, SO_BROADCAST, &option, sizeof(int)))
      throw exception <enetwork, esocket, eudp, esetsockopt_failed> {};
  }
  
  void udp :: send_timeout(const unsigned long int & ms)
  {
    struct timeval tv;
    
    tv.tv_sec = ms / 1000;
    tv.tv_usec = (ms % 1000) * 1000;
    
    if(:: setsockopt(this->_descriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(struct timeval)))
      throw exception <enetwork, esocket, eudp, esetsockopt_failed> {};
  }
  
  void udp :: receive_timeout(const unsigned long int & ms)
  {
    struct timeval tv;
    
    tv.tv_sec = ms / 1000;
    tv.tv_usec = (ms % 1000) * 1000;
    
    if(:: setsockopt(this->_descriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval)))
      throw exception <enetwork, esocket, eudp, esetsockopt_failed> {};
  }
  
  void udp :: close()
  { 
    :: close(this->_descriptor);
    this->_descriptor = -1;
  }
};