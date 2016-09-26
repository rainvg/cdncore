// Forward declaration

namespace network
{
	namespace diagnostics
	{
		class server;
	};
};

#ifndef __cdncore__network__diagnostics__server__h__settings
#define __cdncore__network__diagnostics__server__h__settings

// Types for settings

#include <stdint.h>

namespace settings
{
  namespace network
  {
    namespace diagnostics
    {
      namespace server
      {
        namespace ports
        {
          static constexpr uint16_t alpha = 7777;
          static constexpr uint16_t beta = 7778;
        };
      };
    };
  };
};

#endif

#if !defined(__forward__) && !defined(__cdncore__network__diagnostics__server__h)
#define __cdncore__network__diagnostics__server__h

// Libraries

#include <thread>

// Includes

#include "../socket/udp.h"

namespace network :: diagnostics
{
	class server
	{
    // Members
    
    bool _started;
    
    socket :: udp _alpha;
    socket :: udp _beta;
    
    std :: thread _service_alpha;
    std :: thread _service_beta;
    
  public:
    
    // Constructors
    
    server();
    
    // Destructor
    
    ~server();
    
    // Methods
    
    void start();
    
  private:
    
    // Private methods
    
    void __run(socket :: udp *);
	};
};

#endif
