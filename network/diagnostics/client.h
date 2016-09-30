// Forward declaration

namespace network
{
	namespace diagnostics
	{
		class client;
	};
};

#ifndef __cdncore__network__diagnostics__client__h__settings
#define __cdncore__network__diagnostics__client__h__settings

namespace settings
{
  namespace network
  {
    namespace diagnostics
    {
      namespace client
      {
        static constexpr unsigned long int timeout = 1000;
        static constexpr unsigned int retries = 5;
      };
    };
  };
};

#endif

#if !defined(__forward__) && !defined(__cdncore__network__diagnostics__client__h)
#define __cdncore__network__diagnostics__client__h

// Forward includes

#define __forward__
#include "server.h"
#undef __forward__

// Includes

#include "../../exception.h"
#include "../socket/udp.h"

namespace network :: diagnostics
{
	class client
	{
    // Members
    
    address _remote;
    socket :: udp _socket;
    
    bool _online;
    bool _udp;
    bool _cone;
    bool _public_ip;
    
  public:
    
    // Constructors
    
    client(const address &);
    
    // Getters
    
    bool udp();
    bool cone();
    bool public_ip();
    
    // Methods
    
    void refresh();
    
  private:
    
    // Private methods
    
    address __request(const address &);
	};
};

#endif
