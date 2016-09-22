// Forward declaration

namespace network
{
	namespace socket
	{
		class tcp;
	};
};

#ifndef __cdncore__network__socket__tcp__h__settings
#define __cdncore__network__socket__tcp__h__settings

// Types for settings

#include <stddef.h>

namespace settings
{
  namespace network
  {
    namespace socket
    {
      namespace tcp
      {
        static constexpr size_t listen_buffer_size = 16;
      };
    };
  };
};

#endif

#if !defined(__forward__) && !defined(__cdncore__network__socket__tcp__h)
#define __cdncore__network__socket__tcp__h

// Libraries

#include <arpa/inet.h>
#include <unistd.h>

// Includes

#include "../address.h"
#include "../../data/string.h"
#include "../../exception.h"

namespace network :: socket
{
	class tcp
	{
    // Members
    
    int _descriptor;
    uint16_t _port;
    address _remote;
    
  public:
    
    // Constructors
    
    tcp();
    
  private:
    
    tcp(const int &, const uint16_t &, const address &);
    
  public:
    
    // Getters
    
    int descriptor();
    uint16_t port();
    address remote();
    
    // Methods
    
    void bind(const uint16_t & = 0);
    void listen();
    
    tcp accept();
    void connect(const address &);
    
    void send(const data :: string &);
    data :: string receive(const size_t &);
    
    void close();
	};
};

#endif
