// Forward declaration

namespace network
{
	class address;
};

#ifndef __cdncore__network__address__h__settings
#define __cdncore__network__address__h__settings

// Types for settings

#include <stdint.h>

namespace settings
{
  namespace network
  {
    namespace address
    {
      namespace external_route_host
      {
        static constexpr const char * ip = "3.3.3.3";
        static constexpr uint16_t port = 80;
      };
    };
  };
};

#endif

#if !defined(__forward__) && !defined(__cdncore__network__address__h)
#define __cdncore__network__address__h

// Libraries

#include <iostream>
#include <stddef.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <string.h>

// Includes

#include "../exception.h"

namespace network
{
	class address
	{
  public:
    
    // Nested classes
    
    class ip
    {
      // Friends
      
      friend class address;
      friend std :: ostream & operator << (std :: ostream &, const ip &);
      
      // Members
      
      in_addr_t _ip;
      
    public:
      
      // Constructors
      
      ip();
      ip(const char *);
      
    private:
      
      ip(const address &);
      
    public:
    
      ip(const ip &);
    };
    
    class port
    {
      // Friends
      
      friend class address;
      friend std :: ostream & operator << (std :: ostream &, const port &);
      
      // Members
      
      in_port_t _port;
      
      // Constructors
      
    public:
      
      port();
      port(const uint16_t &);
    
    private:
    
      port(const address &);
      
    public:
      
      port(const port &);
    };
    
  private:
    
    // Members
    
    sockaddr_in _address;
    
  public:
    
    // Constructors
    
    address();
    address(const ip &, const port &);
    address(const char *, const uint16_t &);
    address(const sockaddr_in &);
    address(const address &);
    
    // Getters
    
    port port() const;
    ip ip() const;
    
    // Operators
    
    bool operator == (const address &) const;
    bool operator != (const address &) const;
    
    // Casting
    
    operator sockaddr_in & ();
    operator const sockaddr_in & () const;
    
    // Static methods
    
    static address local();
    static address external();
	};
  
  // Ostream integration
  
  std :: ostream & operator << (std :: ostream &, const class address :: ip &);
  std :: ostream & operator << (std :: ostream &, const class address :: port &);
  std :: ostream & operator << (std :: ostream &, const address &);
};

#endif
