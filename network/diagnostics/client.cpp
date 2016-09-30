#include "client.hpp"

namespace network :: diagnostics
{
  // Constructors
  
  client :: client(const address & remote) : _remote(remote.ip(), (class address :: port)(0))
  {
    this->_socket.receive_timeout(settings :: network :: diagnostics :: client :: timeout);
  }
  
  // Getters
  
  bool client :: udp()
  {
    return this->_udp;
  }
  
  bool client :: cone()
  {
    return this->_cone;
  }
  
  bool client :: public_ip()
  {
    return this->_public_ip;
  }
  
  // Methods
  
  void client :: refresh()
  {
    try
    {
      this->_public_ip = (address :: local() == address :: external());
      this->_online = true;
    }
    catch(exception <enetwork, esocket, etcp>)
    {
      this->_online = false;
      return;
    }
    
    address alpha(this->_remote.ip(), (class address :: port)(settings :: network :: diagnostics :: server :: ports :: alpha));
    
    address beta(this->_remote.ip(), (class address :: port)(settings :: network :: diagnostics :: server :: ports :: beta));
    
    address alpha_response;
    address beta_response;
    
    try
    {
      alpha_response = this->__request(alpha);
    }
    catch(exception <enetwork, ediagnostics, eclient, eoffline>)
    {
      this->_udp = false;
    }
    
    if(this->_udp)
    {
      beta_response = this->__request(beta);
      this->_cone = (alpha_response == beta_response);
    }
  }
  
  // Private methods
  
  address client :: __request(const address & remote)
  {
    for(unsigned int i = 0; i < settings :: network :: diagnostics :: client :: retries;)
    {
      this->_socket.send(remote, "");
      
      try
      {
        auto response = this->_socket.receive();
        
        if(response.remote == remote)
          return response.message.read <address> (0);
      }
      catch(exception <enetwork, esocket, eudp, etimeout>)
      {
        i++;
      }
    }
    
    throw exception <enetwork, ediagnostics, eclient, eoffline> {};
  }
};