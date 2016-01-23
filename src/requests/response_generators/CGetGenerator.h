//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CGETGENERATOR_H
#define HTTP_SERVER_CGETGENERATOR_H

#include "CAbstractGenerator.h"

/**
 * This class represents a response generator entity.
 * It generates the response that contains meta information about a requested resource and it's data.
 */
class CGetGenerator : public CAbstractGenerator {

public:
	/**
	 * Constructs a response generator object.
	 * \param resource - The requested resource.
	 */
	CGetGenerator( const string& resource ) : CAbstractGenerator( resource, RT_GET ) {
		code_m = 200;
	}

	virtual string generate();
};


#endif //HTTP_SERVER_CGETGENERATOR_H
