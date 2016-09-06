// Keywords enum

#ifndef __cdncore__exception__h__ekeyword
#define __cdncore__exception__h__ekeyword

enum ekeyword {enetwork, eaddress, ehost_not_found};

#endif

// Forward declaration

template <ekeyword...> class exception;

#if !defined(__forward__) && !defined(__cdncore__exception__h)
#define __cdncore__exception__h

namespace __exception__
{
  template <typename, typename> struct concatenate;
  
  template <ekeyword... head, ekeyword... tail> struct concatenate <exception <head...>, exception <tail...>>
  {
    typedef exception <head..., tail...> type;
  };
  
  template <ekeyword... keywords> struct inheritance;
  
  template <ekeyword keyword> struct inheritance <keyword>
  {
    typedef exception <> type;
  };
  
  template <ekeyword keyword, ekeyword... keywords> struct inheritance <keyword, keywords...>
  {
    typedef typename concatenate <exception <keyword>, typename inheritance <keywords...> :: type> :: type type;
  };
};

template <> class exception <>
{
};

template <ekeyword... keywords> class exception : public __exception__ :: inheritance <keywords...> :: type
{
};

#endif
