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
  public:
    
    // Nested classes
    
    struct packet
    {
      address remote;
      data :: string message;
    };
    
  private:
    
    // Members
    
    int _descriptor;
    uint16_t _port;
    
  public:
    
    // Constructors
    
    udp();
    
    // Destructor
    
    ~udp();
    
    // Getters
    
    int descriptor();
    uint16_t port();
    
    address interface();
    
    // Methods
    
    void bind(const uint16_t & = 0);
    void send(const address &, const data :: string &);
    packet receive();
    
    void enable_broadcast(const bool &);
    
    void send_timeout(const unsigned long int &);
    void receive_timeout(const unsigned long int &);
    
    void close();
	};
};

#endif
