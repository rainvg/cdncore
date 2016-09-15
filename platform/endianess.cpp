#include "endianess.hpp"

namespace platform
{
  void endianess :: translate(char * bytes, const size_t & size)
  {
    struct translator
    {
      static inline void run(char * bytes, const size_t & size)
      {
        if(size > 1)
        {
          char swap = bytes[0];
          bytes[0] = bytes[size - 1];
          bytes[size - 1] = swap;
          
          translate(bytes + 1, size - 2);
        }
      }
    };
    
    struct idler
    {
      static inline void run(char * bytes, const size_t & size)
      {
      }
    };
    
    std :: conditional <local != network, translator, idler> :: type :: run(bytes, size);
  }
};