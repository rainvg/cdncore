#include "client.hpp"

namespace network :: upnp
{
  // Constructors
  
  client :: client() : _available(false), _online(false)
  {
  }
  
  // Getters
  
  bool client :: available()
  {
    return this->_available;
  }
  
  bool client :: online()
  {
    return this->_online;
  }
  
  // Methods
  
  void client :: discover()
  {
    this->_available = false;
    this->_online = false;
    
    const char * multicastif = nullptr;
    const char * minissdpdpath = nullptr;
    
    int localport = UPNP_LOCAL_PORT_ANY;
    int ipv6 = 0;
    
    unsigned char ttl = 2;
    char lanaddr[64] = "unset";
    
    int error = 0;
    
    this->_devices = upnpDiscover(2000, multicastif, minissdpdpath, localport, ipv6, ttl, &error);
    
    if(!this->_devices)
      return;
    
    int status = UPNP_GetValidIGD(this->_devices, &(this->_urls), &(this->_data), lanaddr, sizeof(lanaddr));
    
    switch(status)
    {
      case 1:
        this->_available = true;
        this->_online = true;
        break;
        
      case 2:
        this->_available = true;
        this->_online = false;
        break;
        
      default:
        break;
    };
  }
};
