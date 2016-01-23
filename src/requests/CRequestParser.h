//
// Created by metopa on 6.5.15.
//

#ifndef HTTP_SERVER_CREQUESTPARSER_H
#define HTTP_SERVER_CREQUESTPARSER_H

#include <string>

#include "EMethodType.h"

using namespace std;

/**
 * This helper class represents a request parser object.
 * It extracts a method type and a requested resource from the received data.
 */
class CRequestParser {
	EMethodType type_m;
	/**< A request method type. */
	string resource_m;
	/**< The requested resource. */
	string lastToken_m; /**< An internal attribute. */
public:
	/** Constructs a parser object. */
	CRequestParser();

	/**
	 * Parses request.
	 * \param body - Input data.
	 */
	void parse( const string& body );

	/**
	 * \return A request method type.
	 */
	EMethodType const& getType() const;

	/**
	 * The requested resource.
	 */
	const string& getResource() const;

private:
	/**
	 * This method extract the next token that is separated by delimiter.
	 * \param str - A string to be parsed.
	 * \param pos - The current position in a parsed string. Will be altered in this method.
	 * \param delim - A token separator.
	 * \return - The extracted token.
	 */
	string getNextToken( const string& str, unsigned int& pos, char delim = ' ' );
};


#endif //HTTP_SERVER_CREQUESTPARSER_H
