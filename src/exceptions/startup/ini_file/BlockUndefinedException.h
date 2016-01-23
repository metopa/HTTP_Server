//
// Created by metopa on 4/27/15.
//

#ifndef HTTP_SERVER_BLOCKUNDEFINEDEXCEPTION_H
#define HTTP_SERVER_BLOCKUNDEFINEDEXCEPTION_H

#include "../StartupException.h"

/**
 * This exception is thrown by the CConfig class.
 */
class BlockUndefinedException : public StartupException {
public:
	BlockUndefinedException( char const * block, char const * action ) : StartupException( block, action ) { }

	virtual ~BlockUndefinedException() { };

	virtual ostream& print( ostream& out ) const noexcept override {
		return out << "Missing \"" << msg1_m << "\" block definition. " << msg2_m;
	}
};

#endif //HTTP_SERVER_BLOCKUNDEFINEDEXCEPTION_H
