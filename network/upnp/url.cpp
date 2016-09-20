#include "url.hpp"

namespace network :: upnp
{
  // Constructors
  
  url :: url() : valid(false)
  {
  }
  
  url :: url(const data :: string & url)
  {
    valid = false;
    ssize_t pos;
    
    pos = url.find("://");
    
    if(pos < 0) return;
    
    size_t host_beg = pos + 3;
    
    pos = url.find(":", host_beg);
    
    size_t path_beg;
    
    if(pos < 0)
    {
      port = 80;
      pos = url.find("/", host_beg);
      
      if(pos < 0) return;
      
      host = url(host_beg, pos - host_beg);
      path_beg = pos + 1;
    }
    else
    {
      size_t host_end = pos;
      host = url(host_beg, host_end - host_beg);
      
      pos = url.find("/", host_end);
      if(pos < 0) return;
      
      port = atoi(url(host_end + 1, pos - host_end));
      path_beg = pos + 1;
    }
    
    if(path_beg == url.size())
      path = "/";
    else
      path = url(path_beg, url.size() - path_beg);
    
    valid = true;
  }
};