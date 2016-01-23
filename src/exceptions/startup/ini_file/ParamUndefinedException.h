//
// Created by metopa on 4/27/15.
//

#include "../StartupException.h"

#ifndef HTTP_SERVER_PARAMUNDEFINEDEXCEPTION_H
#define HTTP_SERVER_PARAMUNDEFINEDEXCEPTION_H

/**
 * This exception is thrown by the CConfig class.
 */
class ParamUndefinedException : public StartupException {
public:
	ParamUndefinedException( char const * param, char const * action ) : StartupException( param, action ) { }

	virtual ~ParamUndefinedException() { };

	virtual ostream& print( ostream& out ) const noexcept override {
		return out << "Missing \"" << msg1_m << "\" parameter definition. " << msg2_m;
	}
};


#endif //HTTP_SERVER_PARAMUNDEFINEDEXCEPTION_H
