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
  
  // Destructor
  
  tcp :: ~tcp()
  {
    this->close();
  }
  
  // Getters
  
  int tcp :: descriptor() const
  {
    return this->_descriptor;
  }
  
  uint16_t tcp :: port() const
  {
    return this->_port;
  }
  
  address tcp :: remote() const
  {
    return this->_remote;
  }
  
  address tcp :: interface() const
  {
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if(getsockname(this->_descriptor, (struct sockaddr *) &sin, &len))
      throw exception <enetwork, esocket, etcp, egetsockname_failed> {};
    
    return sin;
  }
  
  // Methods
  
  void tcp :: bind(const uint16_t & port)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    network :: address bind_address("0.0.0.0", port);
    
    if(:: bind(this->_descriptor, (struct sockaddr *) &bind_address, sizeof(sockaddr_in)))
      throw exception <enetwork, esocket, etcp, ebind_failed> {};
    
    if(port)
      this->_port = port;
    else
    {
      struct sockaddr_in sin;
      socklen_t len = sizeof(sin);
      if(getsockname(this->_descriptor, (struct sockaddr *) &sin, &len))
        throw exception <enetwork, esocket, etcp, egetsockname_failed> {};
      
      this->_port = ntohs(sin.sin_port);
    }
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
      throw exception <enetwork, esocket, etcp, eaccept_failed> {};
    
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
  
  data :: string tcp :: receive()
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    data :: string buffer(settings :: network :: socket :: tcp :: default_receive_size);
    
    ssize_t res = :: read(this->_descriptor, buffer, settings :: network :: socket :: tcp :: default_receive_size);
    
    if(res < 0)
    {
      if(errno == EAGAIN)
        throw exception <enetwork, esocket, etcp, etimeout> {};
      else
        throw exception <enetwork, esocket, etcp, ereceive_failed> {};
    }
    
    return buffer(0, res);
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
  
  data :: string tcp :: receive(const data :: string & terminator, const size_t & size)
  {
    if(this->_descriptor < 0)
      throw exception <enetwork, esocket, etcp, esocket_closed> {};
    
    data :: string buffer(size);
    
    for(size_t cursor = 0; cursor < size;)
    {
      ssize_t res = :: read(this->_descriptor, (char *) buffer + cursor, 1);
      
      if(res < 0)
      {
        if(errno == EAGAIN)
          throw exception <enetwork, esocket, etcp, etimeout> {};
        else
          throw exception <enetwork, esocket, etcp, ereceive_failed> {};
      }
      
      cursor++;
      
      if(cursor > terminator.size())
      {
        if(!memcmp(terminator, (char *) buffer + cursor - terminator.size(), terminator.size()))
          return buffer(0, cursor);
      }
    }
    
    throw exception <enetwork, esocket, etcp, ebuffer_overflow> {};
  }
  
  void tcp :: send_timeout(const unsigned long int & ms)
  {
    struct timeval tv;
    
    tv.tv_sec = ms / 1000;
    tv.tv_usec = (ms % 1000) * 1000;
    
    if(:: setsockopt(this->_descriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(struct timeval)))
      throw exception <enetwork, esocket, etcp, esetsockopt_failed> {};
  }
  
  void tcp :: receive_timeout(const unsigned long int & ms)
  {
    struct timeval tv;
    
    tv.tv_sec = ms / 1000;
    tv.tv_usec = (ms % 1000) * 1000;
    
    if(:: setsockopt(this->_descriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval)))
      throw exception <enetwork, esocket, etcp, esetsockopt_failed> {};
  }
  
  void tcp :: blocking(const bool & value)
  {
    int flags = fcntl(this->_descriptor, F_GETFL, 0);
    
    if (flags == -1)
      throw exception <enetwork, esocket, etcp, efcntl_failed> {};
    
    if(value)
      flags &= ~O_NONBLOCK;
    else
      flags |= O_NONBLOCK;
    
    if(fcntl(this->_descriptor, F_SETFL, flags) == -1)
      throw exception <enetwork, esocket, etcp, efcntl_failed> {};
  }
  
  void tcp :: close()
  {
    :: close(this->_descriptor);
    this->_descriptor = -1;
  }
};
