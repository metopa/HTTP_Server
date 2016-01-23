//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CERRORGENERATOR_H
#define HTTP_SERVER_CERRORGENERATOR_H

#include "CAbstractGenerator.h"

/**
 * This class represents a response generator entity.
 * It generates the page that contains error code message of the response.
 * \see CStringContent
 */
class CErrorGenerator : public CAbstractGenerator {
public:
	/**
	 * Constructs an error response generator object.
	 * \param code - An error code of the response.
	 */
	CErrorGenerator( int code );

	virtual string generate();
};


#endif //HTTP_SERVER_CERRORGENERATOR_H
