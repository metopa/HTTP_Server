//
// Created by metopa on 07/06/15.
//

#ifndef HTTP_SERVER_EMPTYDATAEXCEPTION_H
#define HTTP_SERVER_EMPTYDATAEXCEPTION_H

#include "../GeneralException.h"

/**
 * This exception is thrown by the CSocketIO class.
 */
class EmptyDataException : public GeneralException {
	virtual ostream& print( ostream& out ) const override {
		return out << "Request accepted, but no data received.";
	}
};

#endif //HTTP_SERVER_EMPTYDATAEXCEPTION_H
