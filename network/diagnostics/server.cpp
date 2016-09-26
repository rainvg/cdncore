#include "server.hpp"

namespace network :: diagnostics
{
  // Constructors
  
  server :: server() : _started(false)
  {
    this->_alpha.bind(settings :: network :: diagnostics :: server :: ports :: alpha);
    this->_beta.bind(settings :: network :: diagnostics :: server :: ports :: beta);
  }
  
  // Destructor
  
  server :: ~server()
  {
    if(this->_started)
    {
      this->_alpha.send({"127.0.0.1", settings :: network :: diagnostics :: server :: ports :: alpha}, "");
      
      this->_beta.send({"127.0.0.1", settings :: network :: diagnostics :: server :: ports :: beta}, "");
      
      this->_service_alpha.join();
      this->_service_beta.join();
    }
    
    this->_alpha.close();
    this->_beta.close();
  }
  
  // Methods
  
  void server :: start()
  {
    this->_service_alpha = std :: thread(&server :: __run, this, &(this->_alpha));
    this->_service_beta = std :: thread(&server :: __run, this, &(this->_beta));
    
    this->_started = true;
  }
  
  // Private methods
  
  void server :: __run(socket :: udp * socket)
  {
    while(true)
    {
      try
      {
        auto request = socket->receive();
        
        if(request.remote == address {"127.0.0.1", socket->port()})
          return;
        
        socket->send(request.remote, data :: string :: forge(request.remote));
      }
      catch(exception <enetwork, esocket, etcp>)
      {
      }
    }
  }
};