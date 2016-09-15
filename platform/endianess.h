#ifndef __cdncore__platform__endianess__h__enums
#define __cdncore__platform__endianess__h__enums

namespace platform
{
  namespace endianess
  {
    enum type {big, little};
  }
};

#endif

#ifndef __cdncore__platform__endianess__h__settings
#define __cdncore__platform__endianess__h__settings

namespace settings
{
  namespace platform
  {
    namespace endianess
    {
      static constexpr :: platform :: endianess :: type network = :: platform :: endianess :: little;
    };
  };
};

#endif

#if !defined(__forward__) && !defined(__cdncore__platform__endianess__h)
#define __cdncore__platform__endianess__h

// Libraries

#include <stddef.h>
#include <type_traits>

namespace platform
{
	namespace endianess
	{
    #ifdef __BYTE_ORDER
    #if __BYTE_ORDER == __BIG_ENDIAN
    #define __core__platform__endianess__endianess big
    #endif
        
    #if __BYTE_ORDER == __LITTLE_ENDIAN
    #define __core__platform__endianess__endianess little
    #endif
    #endif
        
    #ifdef __BIG_ENDIAN__
    #define __core__platform__endianess__endianess big
    #endif
        
    #ifdef __LITTLE_ENDIAN__
    #define __core__platform__endianess__endianess little
    #endif
        
    #ifdef __ARMEB__
    #define __core__platform__endianess__endianess big
    #endif
        
    #ifdef __ARMEL__
    #define __core__platform__endianess__endianess little
    #endif
        
    #ifdef __THUMBEB__
    #define __core__platform__endianess__endianess big
    #endif
        
    #ifdef __THUMBEL__
    #define __core__platform__endianess__endianess little
    #endif
        
    #ifdef __AARCH64EB__
    #define __core__platform__endianess__endianess big
    #endif
        
    #ifdef __AARCH64EL__
    #define __core__platform__endianess__endianess little
    #endif
        
    #ifdef _MIPSEB
    #define __core__platform__endianess__endianess big
    #endif
        
    #ifdef _MIPSEL
    #define __core__platform__endianess__endianess little
    #endif
        
    #ifdef __MIPSEB
    #define __core__platform__endianess__endianess big
    #endif
        
    #ifdef __MIPSEL
    #define __core__platform__endianess__endianess little
    #endif
        
    #ifdef __MIPSEB__
    #define __core__platform__endianess__endianess big
    #endif
        
    #ifdef __MIPSEL__
    #define __core__platform__endianess__endianess little
    #endif
        
    #ifdef __BYTE_ORDER__
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define __core__platform__endianess__endianess big
    #endif
        
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define __core__platform__endianess__endianess little
    #endif
    #endif
        
    #ifdef __FLOAT_WORD_ORDER__
    #if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
    #define __core__platform__endianess__endianess big
    #endif
        
    #if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define __core__platform__endianess__endianess little
    #endif
    #endif
    
    // Properties
    
    static constexpr type local = __core__platform__endianess__endianess;
    static constexpr type network = settings :: platform :: endianess :: network;
    
    // Functions
    
    void translate(char *, const size_t &);
	};
};

#endif
