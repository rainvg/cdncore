#ifndef __cdncore__data__string__hpp
#define __cdncore__data__string__hpp

#include "string.h"

namespace data
{
  // Methods
  
  template <typename type> void string :: write(const size_t & index, const type & that)
  {
    memcpy(this->_bytes + index, (char *) &that, sizeof(that));
  }
  
  template <typename type, typename... types> void string :: write(const size_t & index, const type & that, const types & ... those)
  {
    this->write(index, that);
    this->write(index + __write_size(that), those...);
  }
  
  template <typename type> type string :: read(const size_t & index)
  {
    type that;
    memcpy((char *) &that, this->_bytes + index, sizeof(that));
    return that;
  }
  
  template <typename type> void string :: read(const size_t & index, type & that)
  {
    that = this->read <type> (index);
  }
  
  template <typename type, typename... types> void string :: read(const size_t & index, type & that, types & ... those)
  {
    that = this->read <type> (index);
    this->read(index + this->__read_size(index, that), those...);
  }
  
  // Private methods
  
  template <typename type> size_t string :: __read_size(const size_t & index, const type & that)
  {
    return sizeof(type);
  }
  
  template <typename type, typename... types> size_t string :: __read_size(const size_t & index, const type & that, const types & ... those)
  {
    size_t tsize = this->__read_size(index, that);
    return tsize + this->__read_size(index + tsize, those...);
  }
  
  // Static methods
  
  template <typename... types> string string :: forge(const types & ... those)
  {
    string forged(__write_size(those...));
    forged.write(0, those...);
    return forged;
  }
  
  // Private static methods
  
  template <typename type> size_t string :: __write_size(const type & that)
  {
    return sizeof(that);
  }
  
  template <typename type, typename... types> size_t string :: __write_size(const type & that, const types & ... those)
  {
    return __write_size(that) + __write_size(those...);
  }
};

#endif
