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
  
  const size_t & string :: size() const
  {
    return this->_size;
  }
  
  // Methods
  
  template <> void string :: write(const size_t & index, const network :: address & that)
  {
    this->write(index, that.ip());
    this->write(index + sizeof(class network :: address :: ip), that.port());
  }
  
  template <> void string :: write(const size_t & index, const string & that)
  {
    this->write(index, (uint16_t) that.size());
    memcpy(this->_bytes + index + sizeof(uint16_t), that._bytes, that.size());
  }
  
  template <> network :: address string :: read <network :: address> (const size_t & index)
  {
    class network :: address :: ip ip = this->read <class network :: address :: ip> (index);
    class network :: address :: port port = this->read <class network :: address :: port> (index + sizeof(class network :: address :: ip));
    
    return network :: address(ip, port);
  }
  
  template <> string string :: read <string> (const size_t & index)
  {
    size_t size = this->read <uint16_t> (index);
    string that(this->_bytes + index + sizeof(uint16_t), size);
    return that;
  }
  
  ssize_t string :: find(const string & needle, const size_t & beg) const
  {
    for(ssize_t i = beg; i <= (ssize_t) this->_size - (ssize_t) needle._size; i++)
      if(!memcmp(this->_bytes + i, needle._bytes, needle._size))
        return i;
    
    return -1;
  }
  
  // Private methods
  
  template <> size_t string :: __read_size(const size_t & index, const network :: address & that)
  {
    return sizeof(class network :: address :: ip) + sizeof(class network :: address :: port);
  }
  
  template <> size_t string :: __read_size(const size_t & index, const string & that)
  {
    return sizeof(uint16_t) + this->read <uint16_t> (index);
  }
  
  // Static methods
  
  template <> size_t string :: __write_size(const network :: address & that)
  {
    return sizeof(class network :: address :: ip) + sizeof(class network :: address :: port);
  }
  
  template <> size_t string :: __write_size(const string & that)
  {
    return sizeof(uint16_t) + that.size();
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
  
  string string :: operator () (const size_t & beg, const size_t & size) const
  {
    return string(this->_bytes + beg, size);
  }
  
  void string :: operator = (const string & that)
  {
    if(this->_size)
      delete [] this->_bytes;
    
    this->_bytes = new char[that._size + 1];
    this->_bytes[that._size] = '\0';
    
    memcpy(this->_bytes, that._bytes, that._size);
    this->_size = that._size;
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