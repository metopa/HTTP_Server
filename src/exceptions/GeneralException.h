//
// Created by metopa on 4/26/15.
//

#ifndef HTTP_SERVER_GENERALEXCEPTION_H
#define HTTP_SERVER_GENERALEXCEPTION_H


#include <ostream>
#include <string>

using namespace std;

/**
 * This abstract class is a base class for all exceptions defined in this code.
 */
class GeneralException {

public:
	virtual ~GeneralException() { };

	virtual ostream& print( ostream& out ) const = 0;

	friend ostream& operator <<( ostream& out, const GeneralException& e ) {
		return e.print( out );
	}
};

#endif //HTTP_SERVER_GENERALEXCEPTION_H
