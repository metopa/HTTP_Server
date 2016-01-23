//
// Created by metopa on 4/22/15.
//

#ifndef HTTP_SERVER_SOCKETSENDEREXCEPTION_H
#define HTTP_SERVER_SOCKETSENDEREXCEPTION_H

#include "../NetworkException.h"

/**
 * This exception is thrown by the CSocketIO class.
 */
class SocketSenderException : public NetworkException {

public:
	SocketSenderException( const string& func, const string& err, int port, int sock ) :
			NetworkException( func, err, port, sock ) { }

protected:
	virtual const char * selfName() const noexcept override {
		return "Error while sending data";
	}
};

#endif //HTTP_SERVER_SOCKETSENDEREXCEPTION_H
