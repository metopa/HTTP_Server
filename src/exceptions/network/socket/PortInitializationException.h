//
// Created by metopa on 4/22/15.
//

#ifndef HTTP_SERVER_INITIALIZATIONEXCEPTION_H
#define HTTP_SERVER_INITIALIZATIONEXCEPTION_H

#include <string.h>
#include <netdb.h>
#include "../NetworkException.h"

/**
 * This exception is being thrown by CPortObtainer class.
 */

class PortInitializationException : public NetworkException {
public:
	PortInitializationException( const string& func, const string& err, char const * port, int sock = -2 ) :
			NetworkException( func, err, port, sock ) { }


	PortInitializationException( const string& func, const string& err, int port, int sock ) :
			NetworkException( func, err, port, sock ) { }

protected:
	virtual const char * selfName() const noexcept override {
		return "Port initialization error";
	}
};


#endif //HTTP_SERVER_INITIALIZATIONEXCEPTION_H
