//
// Created by metopa on 4/22/15.
//

#ifndef HTTP_SERVER_NETWORKEXCEPTION_H
#define HTTP_SERVER_NETWORKEXCEPTION_H

#include <exception>
#include "../GeneralException.h"

/**
 * This abstract class is a base class for all network exceptions defined in this code.
 *
 */
class NetworkException : public GeneralException {
protected:
	string func_m;
	string err_m;
	int port_m;
	int sock_m;

	virtual const char * selfName() const = 0;

public:
	NetworkException( const string& func, const string& err, int port, int sock = -2 ) :
			func_m( func ), err_m( err ), port_m( port ), sock_m( sock ) { }

	NetworkException( const string& func, const string& err, const char * port, int sock = -2 ) :
			func_m( func ), err_m( err ), sock_m( sock ) {
		if ( sscanf( port, "%d", &port_m ) != 1 )
			port_m = -1;
	}

	virtual ostream& print( ostream& out ) const noexcept override {
		if ( sock_m == -2 )
			return out << selfName() << ' ' << func_m << " on port " << port_m << '(' << sock_m << "): " << err_m;
		else
			return out << selfName() << ' ' << func_m << " on port " << port_m << ": " << err_m;
	}
};


#endif //HTTP_SERVER_NETWORKEXCEPTION_H
