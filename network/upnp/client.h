// Forward declaration

namespace network
{
	namespace upnp
	{
		class client;
	};
};

#ifndef __cdncore__network__upnp__client__h__settings
#define __cdncore__network__upnp__client__h__settings

// Types for settings

#include <stdint.h>

namespace settings
{
  namespace network
  {
    namespace upnp
    {
      namespace client
      {
        static constexpr const char description_header[] = "Rain CDN";
        static constexpr uint16_t preferential_port = 80;
      };
    };
  };
};

#endif

#if !defined(__forward__) && !defined(__cdncore__network__upnp__client__h)
#define __cdncore__network__upnp__client__h

// Libraries

#include <miniupnpc/miniupnpc.h>
#include <miniupnpc/upnpcommands.h>

#include <stdio.h>

#include <iostream>

// Includes

#include "../socket/tcp.h"
#include "../socket/udp.h"

namespace network :: upnp
{
	class client
	{
  public:
    
    // Nested classes
    
    class portmap
    {
    public:
      
      // Members
      
      uint16_t local;
      uint16_t external;
      
    private:
      
      bool _null;
      
    public:
      
      // Constructors
      
      portmap();
      portmap(const uint16_t &, const uint16_t &);
      
      // Casting
      
      operator bool () const;
    };
    
  private:
    
    // Members
    
    uint64_t _id;
    char _description[sizeof(settings :: network :: upnp :: client :: description_header) + 19];
    
    struct UPNPDev * _devices;
    struct UPNPUrls _urls;
    struct IGDdatas _data;
    
    char _local_ip[64];
    
    bool _available;
    bool _online;
    
  public:
    
    // Constructors
    
    client(const uint64_t &);
    
    // Getters
    
    uint64_t id();
    
    bool available();
    bool online();
    
    // Methods
    
    void discover();
    
    portmap current();
    
    portmap map(const socket :: tcp &);
    portmap map(const socket :: udp &);
    
    void clear();
    
    // Private methods
    
    portmap __map(const uint16_t &, const char *);
	};
};

#endif
