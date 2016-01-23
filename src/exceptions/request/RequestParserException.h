//
// Created by metopa on 6.5.15.
//

#ifndef HTTP_SERVER_REQUESTPARSEREXCEPTION_H
#define HTTP_SERVER_REQUESTPARSEREXCEPTION_H

#include "../GeneralException.h"

/**
 * This exception is thrown by the CRequestParser class.
 */
class RequestParserException : public GeneralException {

protected:
	string token_m;
	string expected_m;

public:

	RequestParserException( const string& token, const string& expected ) :
			token_m( token ), expected_m( expected ) { }

	virtual ostream& print( ostream& out ) const override {
		return out << "Corrupted HTTP request: expected \"" << expected_m << "\", reached \"" << token_m << '"' << '.';
	}
};

#endif //HTTP_SERVER_REQUESTPARSEREXCEPTION_H
