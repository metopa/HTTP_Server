//
// Created by metopa on 4/25/15.
//

#ifndef HTTP_SERVER_INIPARSEREXCEPTION_H
#define HTTP_SERVER_INIPARSEREXCEPTION_H

#include "../StartupException.h"

/**
 * This exception is thrown by the CParserINI class.
 */
class INIParserException : public StartupException {
public:
	INIParserException( const char * msg ) : StartupException( msg ) { }

	INIParserException( char const * msg1, char msg2 ) : StartupException( msg1, msg2 ) { }

	INIParserException( char const * msg1, char const * msg2 ) : StartupException( msg1, msg2 ) { }

	virtual ~INIParserException() { };
};

#endif //HTTP_SERVER_INIPARSEREXCEPTION_H

