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
#include "../platform/endianess.h"

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
    
    const size_t & size() const;
    
    // Methods
    
    template <typename type> void write(const size_t &, const type &);
    template <typename type, typename... types> void write(const size_t &, const type &, const types & ...);
    
    template <typename type> type read(const size_t &);
    template <typename type> void read(const size_t &, type &);
    template <typename type, typename... types> void read(const size_t &, type &, types & ...);
    
    ssize_t find(const string &);
    
  private:
    
    // Private methods
    
    template <typename type> size_t __read_size(const size_t &, const type &);
    template <typename type, typename... types> size_t __read_size(const size_t &, const type &, const types & ...);
    
  public:
    
    // Static methods
    
    template <typename ... types> static string forge(const types & ...);
    
  private:
    
    // Private static methods
    
    template <typename type> static size_t __write_size(const type &);
    template <typename type, typename... types> static size_t __write_size(const type &, const types & ...);
    
  public:
    
    // Operators
    
    char & operator [] (const size_t &);
    const char & operator [] (const size_t &) const;
    
    string operator () (const size_t &, const size_t &) const;
    
    void operator = (const string &);
    
    // Casting
    
    operator char * ();
    operator const char * () const;
	};
};

#endif
