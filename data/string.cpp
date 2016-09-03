#include "string.hpp"

namespace data
{
  // Constructors
  
  string :: string()
  {
    this->_size = 0;
  }
  
  string :: string(const char * bytes, const size_t & size)
  {
    this->_bytes = new char[size];
    memcpy(this->_bytes, bytes, size);
    this->_size = size;
  }
  
  string :: string(const char * bytes) : string(bytes, strlen(bytes))
  {
  }
  
  string :: string(const string & that) : string(that._bytes, that._size)
  {
  }
  
  // Destructor
  
  string :: ~string()
  {
    if(this->_size)
      delete [] this->_bytes;
  }
  
  // Getters
  
  const size_t & string :: size()
  {
    return this->_size;
  }
  
  // Operators
  
  char & string :: operator [] (const size_t & index)
  {
    return this->_bytes[index];
  }
  
  const char & string :: operator [] (const size_t & index) const
  {
    return this->_bytes[index];
  }
  
  // Casting
  
  string :: operator char * ()
  {
    return this->_bytes;
  }
  
  string :: operator const char * () const
  {
    return this->_bytes;
  }
};