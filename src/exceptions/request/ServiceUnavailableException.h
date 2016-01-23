//
// Created by metopa on 14.5.15.
//

#include "../GeneralException.h"

#ifndef HTTP_SERVER_SERVICEUNAVALIABLEEXCEPTION_H
#define HTTP_SERVER_SERVICEUNAVALIABLEEXCEPTION_H

/**
 * This exception is thrown by the CExternalContent class.
 */
class ServiceUnavailableException : public GeneralException {
public:
	ServiceUnavailableException( const string& path ) : path_m( path ) { }


	virtual ostream& print( ostream& out ) const {
		return out << "Service " << path_m << "is unavailable.";
	}

private:
	string path_m;
};

#endif //HTTP_SERVER_SERVICEUNAVALIABLEEXCEPTION_H

