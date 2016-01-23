//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CABSTRACTGENERATOR_H
#define HTTP_SERVER_CABSTRACTGENERATOR_H

#include <string>

#include "../../content/CAbstractContent.h"
#include "../EMethodType.h"

using namespace std;

/**
 * This is a base class for a response generator entity.
 * It constructs a content generator object and creates an HTTP response using data provided by a content generator.
 */
class CAbstractGenerator {
public:
	virtual ~CAbstractGenerator();

	/**
	 * This method generates an HTTP response.
	 * \return The generated response.
	 */
	virtual string generate() = 0;
protected:
	string resource_m; /**< A requested resource. */
	string realPath_m; /**< A path to the requested resource. */
	CAbstractContent * content_m; /**< A pointer to a content generator. */
	int code_m; /**< An HTTP response code to be send. */

	/**
	 * This function maps HTTP response code numbers to theirs names.
	 * \param code  - A code number.
	 * \return The string that contains a code name.
	 */
	const char * getCodeMsg( int code );

	/**
	 * This constructor initializes internal attributes, determines a resource type and construct a content generator based on this type.
	 */
	CAbstractGenerator( const string& resource, EMethodType method );

	/**
	 * This constructor initializes internal attributes.
	 */
	CAbstractGenerator();
};


#endif //HTTP_SERVER_CABSTRACTGENERATOR_H
