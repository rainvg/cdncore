// Forward declaration

namespace network
{
	namespace upnp
	{
		class client;
	};
};

#if !defined(__forward__) && !defined(__cdncore__network__upnp__client__h)
#define __cdncore__network__upnp__client__h

// Libraries

#include <miniupnpc/miniupnpc.h>
#include <iostream>

namespace network :: upnp
{
	class client
	{
    // Members
    
    struct UPNPDev * _devices;
    struct UPNPUrls _urls;
    struct IGDdatas _data;
    
    bool _available;
    bool _online;
    
  public:
    
    // Constructors
    
    client();
    
    // Getters
    
    bool available();
    bool online();
    
    // Methods
    
    void discover();
	};
};

#endif
