#include "string.hpp"

namespace data
{
  // Constructors
  
  string :: string()
  {
    this->_size = 0;
  }
  
  string :: string(const size_t & size)
  {
    this->_bytes = new char[size + 1];
    this->_bytes[size] = '\0';
    
    this->_size = size;
  }
  
  string :: string(const char * bytes, const size_t & size)
  {
    this->_bytes = new char[size + 1];
    this->_bytes[size] = '\0';
    
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
  
  // Methods
  
  template <> void string :: write(const size_t & index, const network :: address & that)
  {
    this->write(index, that.ip());
    this->write(index + sizeof(class network :: address :: ip), that.port());
  }
  
  template <> network :: address string :: read <network :: address> (const size_t & index)
  {
    class network :: address :: ip ip = this->read <class network :: address :: ip> (index);
    class network :: address :: port port = this->read <class network :: address :: port> (index + sizeof(class network :: address :: ip));
    
    return network :: address(ip, port);
  }
  
  // Static methods
  
  template <> size_t string :: size(const network :: address & that)
  {
    return sizeof(class network :: address :: ip) + sizeof(class network :: address :: port);
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