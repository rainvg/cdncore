#include "address.hpp"

namespace network
{
  // ip
  
  // Constructors
  
  address :: ip :: ip()
  {
    this->_ip = htonl(INADDR_ANY);
  }
  
  address :: ip :: ip(const char * host)
  {
    hostent * record = gethostbyname(host);
    
    if(record)
      memcpy(&(this->_ip), record->h_addr, sizeof(in_addr_t));
    else
      throw exception <enetwork, eaddress, ehost_not_found> {};
  }
  
  address :: ip :: ip(const address & address) : _ip(address._address.sin_addr.s_addr)
  {
  }
  
  address :: ip :: ip(const ip & that) : _ip(that._ip)
  {
  }
  
  // port
  
  // Constructors
  
  address :: port :: port() : _port(htons(0))
  {
  }
  
  address :: port :: port(const uint16_t & port) : _port(htons(port))
  {
  }
  
  address :: port :: port(const address & address) : _port(address._address.sin_port)
  {
  }
  
  address :: port :: port(const port & that) : _port(that._port)
  {
  }
  
  // address
  
  // Constructors
  
  address :: address()
  {
  }
  
  address :: address(const class ip & ip, const class port & port)
  {
    this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr = ip._ip;
    this->_address.sin_port = port._port;
    
    #ifdef __APPLE__
    memset(this->_address.sin_zero, '\0', sizeof(this->_address.sin_zero));
    #endif
  }
  
  address :: address(const char * host, const uint16_t & port)
  {
    this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr = ((class ip)(host))._ip;
    this->_address.sin_port = ((class port)(port))._port;
    
    #ifdef __APPLE__
    memset(this->_address.sin_zero, '\0', sizeof(this->_address.sin_zero));
    #endif
  }
  
  address :: address(const address & that) : _address(that._address)
  {
  }
  
  // Getters
  
  class address :: ip address :: ip() const
  {
    return (class ip)(*this);
  }
  
  class address :: port address :: port() const
  {
    return (class port)(*this);
  }
  
  // Casting
  
  address :: operator sockaddr_in & ()
  {
    return this->_address;
  }
  
  address :: operator const sockaddr_in & () const
  {
    return this->_address;
  }
  
  // Ostream integration
  
  std :: ostream & operator << (std :: ostream & out, const class address :: ip & that)
  {
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &((const in_addr &) that._ip), ipstr, INET_ADDRSTRLEN);
    out << ipstr;
    return out;
  }
  
  std :: ostream & operator << (std :: ostream & out, const class address :: port & that)
  {
    out << ntohs((const in_port_t &) that._port);
    return out;
  }
  
  std :: ostream & operator << (std :: ostream & out, const address & that)
  {
    out << "[" << that.ip() << ":" << that.port() << "]";
    return out;
  }
};