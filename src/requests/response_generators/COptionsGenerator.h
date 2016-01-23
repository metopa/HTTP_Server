//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_COPTIONSGENERATOR_H
#define HTTP_SERVER_COPTIONSGENERATOR_H

#include "CAbstractGenerator.h"

/**
 * This class represents a response generator entity.
 * It generates the response that contains a list of allowed HTTP methods related to a requested resource.
 */
class COptionsGenerator : public CAbstractGenerator {
public:

	/**
 	* Constructs a response generator object.
 	* \param resource - The requested resource.
 	*/
	COptionsGenerator( const string& resource );

	virtual string generate();
};


#endif //HTTP_SERVER_COPTIONSGENERATOR_H
