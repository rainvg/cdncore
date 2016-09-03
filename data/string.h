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
    string(const char *, const size_t &);
    string(const char *);
    string(const string &);
    
    // Destructor
    
    ~string();
    
    // Getters
    
    const size_t & size();
    
    // Operators
    
    char & operator [] (const size_t &);
    const char & operator [] (const size_t &) const;
    
    // Casting
    
    operator char * ();
    operator const char * () const;
	};
};

#endif
