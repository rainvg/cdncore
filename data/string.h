// Forward declaration

namespace data
{
	class string;
};

#if !defined(__forward__) && !defined(__cdncore__data__string__h)
#define __cdncore__data__string__h

// Libraries

#include <stddef.h>
#include <string.h>

// Includes

#include "../network/address.h"

namespace data
{
	class string
	{
    // Members
    
    char * _bytes;
    size_t _size;
    
  public:
    
    // Constructors
    
    string();
    string(const size_t &);
    string(const char *, const size_t &);
    string(const char *);
    string(const string &);
    
    // Destructor
    
    ~string();
    
    // Getters
    
    const size_t & size();
    
    // Methods
    
    template <typename type> void write(const size_t &, const type &);
    template <typename type, typename... types> void write(const size_t &, const type &, const types & ...);
    
    template <typename type> type read(const size_t &);
    template <typename type> void read(const size_t &, type &);
    template <typename type, typename... types> void read(const size_t &, type &, types & ...);
    
    // Static methods
    
    template <typename type> static size_t size(const type &);
    template <typename type, typename... types> static size_t size(const type &, const types & ...);
    
    template <typename ... types> static string forge(const types & ...);
    
    // Operators
    
    char & operator [] (const size_t &);
    const char & operator [] (const size_t &) const;
    
    // Casting
    
    operator char * ();
    operator const char * () const;
	};
};

#endif
