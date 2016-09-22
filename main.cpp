#include <iostream>
#include <thread>

#include <miniupnpc/miniupnpc.h>

int main()
{
  const char * multicastif = nullptr;
  const char * minissdpdpath = nullptr;
  int localport = UPNP_LOCAL_PORT_ANY;
  int ipv6 = 0;
  unsigned char ttl = 2;
  char lanaddr[64] = "unset";
  
  int error = 0;
  
  struct UPNPDev * devlist = upnpDiscover(2000, multicastif, minissdpdpath, localport, ipv6, ttl, &error);
  
  if(devlist)
  {
    std :: cout << "Something found." << std :: endl;
    
    struct UPNPUrls urls;
    struct IGDdatas data;

    int status = UPNP_GetValidIGD(devlist, &urls, &data, lanaddr, sizeof(lanaddr));
    
    std :: cout << "Status: " << status << std :: endl;
  }
}