//
// Created by metopa on 6.5.15.
//

#include "CRequestParser.h"
#include "../exceptions.h"

CRequestParser::CRequestParser() { }

void CRequestParser::parse( const string& body ) {
	unsigned int pos = 0;
	type_m = methodTypeNS::methodFromString( getNextToken( body, pos ) );
	if ( type_m == RT_UNSUPPORTED )
		throw RequestParserException( lastToken_m.c_str(), "Request type" );
	resource_m = getNextToken( body, pos );
	if ( resource_m.empty() )
		throw RequestParserException( lastToken_m.c_str(), "Resource" );
}

EMethodType const& CRequestParser::getType() const {
	return type_m;
}

const string& CRequestParser::getResource() const {
	return resource_m;
}

string CRequestParser::getNextToken( const string& str, unsigned int& pos, char delim ) {
	lastToken_m.clear();

	while ( pos < str.size() && str[pos] == delim )
		pos++;

	while ( pos < str.size() ) {
		if ( str[pos] == delim )
			return lastToken_m;

		lastToken_m += str[pos++];
	}

	return lastToken_m;
}
