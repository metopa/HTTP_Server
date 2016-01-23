//
// Created by metopa on 11.5.15.
//

#include "../GeneralException.h"
#include "../../requests/EMethodType.h"

#ifndef HTTP_SERVER_REQUESTUNSUPPORTEDEXCEPTION_H
#define HTTP_SERVER_REQUESTUNSUPPORTEDEXCEPTION_H

/**
 * This exception is thrown by the CAbstractGenerator class.
 */
class MethodProhibitedException : public GeneralException {
protected:
public:
	MethodProhibitedException( EMethodType const& type ) : type_m( type ) { }

	virtual ostream& print( ostream& out ) const override {
		return out << "HTTP method " << methodTypeNS::methodToString( type_m ) << " prohibited.";
	}

protected:
	EMethodType type_m;

};

#endif //HTTP_SERVER_REQUESTUNSUPPORTEDEXCEPTION_H
