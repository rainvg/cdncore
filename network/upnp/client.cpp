#include "client.hpp"

namespace network :: upnp
{
  // portmap
  
  // Constructors
  
  client :: portmap :: portmap() : _null(true)
  {
  }
  
  client :: portmap :: portmap(const uint16_t & local, const uint16_t & external) : _null(false), local(local), external(external)
  {
  }
  
  // Casting
  
  client :: portmap :: operator bool () const
  {
    return !(this->_null);
  }
  
  // client
  
  // Constructors
  
  client :: client(const uint64_t & id) : _id(id), _available(false), _online(false)
  {
    sprintf(this->_description, "%s (%016llx)", settings :: network :: upnp :: client :: description_header, this->_id);
  }
  
  // Getters
  
  uint64_t client :: id()
  {
    return this->_id;
  }
  
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
    sprintf(this->_local_ip, "unset");
    
    int error = 0;
    
    this->_devices = upnpDiscover(2000, multicastif, minissdpdpath, localport, ipv6, ttl, &error);
    
    if(!this->_devices)
      return;
    
    int status = UPNP_GetValidIGD(this->_devices, &(this->_urls), &(this->_data), this->_local_ip, sizeof(this->_local_ip));
    
    switch(status)
    {
      case 1:
        this->_online = true;
        
      case 2:
        this->_available = true;
        break;
    };
  }
  
  client :: portmap client :: current()
  {
    portmap current;
    
    for(unsigned int i = 0;; i++)
    {
      char index[6];
      snprintf(index, 6, "%d", i);
      
      char local_ip[40] = {'\0'};
      char local_port[6] = {'\0'};
      char external_port[6] = {'\0'};
      
      char protocol[4];
      char description[80] = {'\0'};
      
      char enabled[6] = {'\0'};
      char remote_host[64] = {'\0'};
      char duration[16] = {'\0'};
      
      int response = UPNP_GetGenericPortMappingEntry(this->_urls.controlURL, this->_data.first.servicetype, index, external_port, local_ip, local_port, protocol, description, enabled, remote_host, duration);
      
      if(response)
        break;
      
      if(!strcmp(description, this->_description))
      {
        if(!current && !strcmp(local_ip, this->_local_ip))
          current = portmap(atoi(local_port), atoi(external_port));
        else
          UPNP_DeletePortMapping(this->_urls.controlURL, this->_data.first.servicetype, external_port, protocol, remote_host);
      }
    }
    
    return current;
  }
  
  client :: portmap client :: map(const socket :: tcp & socket)
  {
    return this->__map(socket.port(), "TCP");
  }
  
  client :: portmap client :: map(const socket :: udp & socket)
  {
    return this->__map(socket.port(), "UDP");
  }
  
  void client :: clear()
  {
    for(unsigned int i = 0;; i++)
    {
      char index[6];
      snprintf(index, 6, "%d", i);
      
      char local_ip[40] = {'\0'};
      char local_port[6] = {'\0'};
      char external_port[6] = {'\0'};
      
      char protocol[4];
      char description[80] = {'\0'};
      
      char enabled[6] = {'\0'};
      char remote_host[64] = {'\0'};
      char duration[16] = {'\0'};
      
      char preferential_port_string[6];
      snprintf(preferential_port_string, 6, "%d", settings :: network :: upnp :: client :: preferential_port);
      
      int response = UPNP_GetGenericPortMappingEntry(this->_urls.controlURL, this->_data.first.servicetype, index, external_port, local_ip, local_port, protocol, description, enabled, remote_host, duration);
      
      if(response)
        break;
      
      if(!strcmp(description, this->_description))
        UPNP_DeletePortMapping(this->_urls.controlURL, this->_data.first.servicetype, external_port, protocol, remote_host);
    }
  }
  
  // Private methods
  
  client :: portmap client :: __map(const uint16_t & port, const char * protocol)
  {
    this->clear();

    char external_port[6];
    snprintf(external_port, 6, "%d", settings :: network :: upnp :: client :: preferential_port);

    char local_port[6];
    snprintf(local_port, 6, "%d", port);

    char reserved_port[6];

    int status = UPNP_AddAnyPortMapping(this->_urls.controlURL, this->_data.first.servicetype, external_port, local_port, this->_local_ip, this->_description, protocol, 0, "0", reserved_port);
    
    // FIXME: Find out why this doesn't work. I need a working UPnP connection to get that to work!
    
    if(status != UPNPCOMMAND_SUCCESS)
      throw exception <enetwork, eupnp, eclient, emap_failed> {};

    return portmap(port, atoi(reserved_port));
  }
};
