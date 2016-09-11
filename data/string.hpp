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
    this->write(index + size(that), those...);
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
    this->read(index + size(that), those...);
  }
  
  // Static methods
  
  template <typename type> size_t string :: size(const type & that)
  {
    return sizeof(that);
  }
  
  template <typename type, typename... types> size_t string :: size(const type & that, const types & ... those)
  {
    return size(that) + size(those...);
  }
  
  template <typename... types> string string :: forge(const types & ... those)
  {
    string forged(size(those...));
    forged.write(0, those...);
    return forged;
  }
};

#endif
