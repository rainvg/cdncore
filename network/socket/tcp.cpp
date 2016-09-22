#include "tcp.hpp"

namespace network :: socket
{
  // Constructors
  
  tcp :: tcp()
  {
    this->_descriptor = :: socket(PF_INET, SOCK_STREAM, 0);
    
    int optreuse = true;
    if (:: setsockopt(this->_descriptor, SOL_SOCKET, SO_REUSEADDR, &optreuse, sizeof(int)))
      throw exception <enetwork, esocket, etcp, esetsockopt_failed> {};
  }
  
  tcp :: tcp(const int & descriptor, const uint16_t & port, const address & remote) : _descriptor(descriptor), _port(port), _remote(remote)
  {
  }
  
  // Getters
  
  int tcp :: descriptor()
  {
    return this->_descriptor;
  }
  
  uint16_t tcp :: port()
  {
    return this->_port;
  }
  
  address tcp :: remote()
  {
    return this->_remote;
  }
  
  // Methods
  
  void tcp :: bind(const uint16_t & port)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    network :: address bind_address("0.0.0.0", port);
    
    if(:: bind(this->_descriptor, (struct sockaddr *) &bind_address, sizeof(sockaddr_in)))
      throw exception <enetwork, esocket, eudp, ebind_failed> {};
    
    this->_port = port;
  }
  
  void tcp :: listen()
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    if(:: listen(this->_descriptor, settings :: network :: socket :: tcp :: listen_buffer_size))
      throw exception <enetwork, esocket, etcp, elisten_failed> {};
  }
  
  tcp tcp :: accept()
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    network :: address remote;
    socklen_t socklen;
    
    int descriptor = :: accept(this->_descriptor, (sockaddr *) &((sockaddr_in &) remote), &socklen);
    
    if(descriptor < 0)
      throw exception <enetwork, esocket, eudp, eaccept_failed> {};
    
    return tcp(descriptor, this->_port, remote);
  }
  
  void tcp :: connect(const address & remote)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    if(:: connect(this->_descriptor, (const sockaddr *) &((const sockaddr_in &) remote), sizeof(sockaddr_in)))
      throw exception <enetwork, esocket, etcp, econnect_failed> {};
    
    this->_remote = remote;
  }
  
  void tcp :: send(const data :: string & message)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    if(:: write(this->_descriptor, message, message.size()) < 0)
      throw exception <enetwork, esocket, etcp, esend_failed> {};
  }
  
  data :: string tcp :: receive(const size_t & size)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    data :: string message(size);
    
    for(size_t cursor = 0; cursor < size;)
    {
      ssize_t res = :: read(this->_descriptor, (char *) message + cursor, size - cursor);
      
      if(res < 0)
      {
        if(errno == EAGAIN)
          throw exception <enetwork, esocket, etcp, etimeout> {};
        else
          throw exception <enetwork, esocket, etcp, ereceive_failed> {};
      }
      
      cursor += res;
    }
    
    return message;
  }
  
  void tcp :: close()
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    :: close(this->_descriptor);
    this->_descriptor = -1;
  }
};