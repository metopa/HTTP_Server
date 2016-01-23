//
// Created by metopa on 4/22/15.
//

#include "../NetworkException.h"

#ifndef HTTP_SERVER_SOCKETRECEIVEREXCEPTION_H
#define HTTP_SERVER_SOCKETRECEIVEREXCEPTION_H

/**
 * This exception is thrown by the CSocketIO class.
 */
class SocketReceiverException : public NetworkException {

public:

	SocketReceiverException( const string& func, const string& err, int port, int sock ) :
			NetworkException( func, err, port, sock ) { }

protected:
	virtual const char * selfName() const noexcept override {
		return "Error while receiving data";
	}
};

#endif //HTTP_SERVER_SOCKETRECEIVEREXCEPTION_H

