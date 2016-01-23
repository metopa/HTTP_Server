//
// Created by metopa on 14.5.15.
//

#ifndef HTTP_SERVER_INTERNALERROREXCEPTION_H
#define HTTP_SERVER_INTERNALERROREXCEPTION_H

#include "FilesystemException.h"

/**
 * This exception is being thrown by CExternalContent class.
 */
class InternalErrorException : public FilesystemException {

public:
	InternalErrorException( const string& file ) : FilesystemException( file ) { }

	virtual ostream& print( ostream& out ) const noexcept override {
		return out << "Internal error while executing " << file_m << ".";
	}
};

#endif //HTTP_SERVER_INTERNALERROREXCEPTION_H
