//
// Created by metopa on 4/25/15.
//

#ifndef HTTP_SERVER_STARTUPEXCEPTION_H
#define HTTP_SERVER_STARTUPEXCEPTION_H

#include "../GeneralException.h"

/**
 * This abstract class is a base class for all INI file parser exceptions defined in this code.
 *
 */
class StartupException : public GeneralException {
protected:
	string msg1_m;
	string msg2_m;
public:

	StartupException( const string& msg1, const string& msg2 ) : msg1_m( msg1 ), msg2_m( msg2 ) { }

	StartupException( const string& msg1, char c ) : msg1_m( msg1 ) {
		msg2_m += c;
	}

	StartupException( const string& msg1 ) : msg1_m( msg1 ) { }

	virtual ~StartupException() { }

	virtual ostream& print( ostream& out ) const {
		return out << msg1_m << msg2_m;
	}
};

#endif //HTTP_SERVER_STARTUPEXCEPTION_H
