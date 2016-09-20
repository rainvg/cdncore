// Forward declaration

namespace network
{
	namespace socket
	{
		class udp;
	};
};

#if !defined(__forward__) && !defined(__cdncore__network__socket__udp__h)
#define __cdncore__network__socket__udp__h

// Libraries

#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>

// Includes

#include "../../exception.h"
#include "../address.h"
#include "../../data/string.h"

namespace network :: socket
{
	class udp
	{
    // Members
    
    int _descriptor;
    uint16_t _port;
    
  public:
    
    // Constructors
    
    udp();
    
    // Getters
    
    uint16_t port();
    
    // Methods
    
    void bind(const uint16_t &);
    void send(const address &, const data :: string &);
    data :: string receive();
    
    void enable_broadcast(const bool &);
	};
};

#endif
