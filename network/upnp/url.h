// Forward declaration

namespace network
{
	namespace upnp
	{
		class url;
	};
};

#if !defined(__forward__) && !defined(__cdncore__network__upnp__url__h)
#define __cdncore__network__upnp__url__h

// Includes

#include "../../data/string.h"

namespace network :: upnp
{
	struct url
	{
    // Members
    
    data ::string host;
    uint16_t port;
    data :: string path;
    
    bool valid;
    
    // Constructors
    
    url();
    url(const data :: string &);
    url(const url &);
	};
};

#endif
