//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CHEADGENERATOR_H
#define HTTP_SERVER_CHEADGENERATOR_H

#include "CAbstractGenerator.h"

/**
 * This class represents a response generator entity.
 * It generates the response that contains only meta information about a requested resource excluding it's data.
 */
class CHeadGenerator : public CAbstractGenerator {

public:
	/**
 * Constructs a response generator object.
 * \param resource - The requested resource.
 */
	CHeadGenerator( const string& resource );

	virtual string generate();
};


#endif //HTTP_SERVER_CHEADGENERATOR_H
