//
// Created by metopa on 5.5.15.
//

#ifndef HTTP_SERVER_FILEERROREXCEPTION_H
#define HTTP_SERVER_FILEERROREXCEPTION_H

#include "FilesystemException.h"

/**
 * This exception is thrown by the CDirContent, the CFileContent and the CPathResolver classes.
 */
class FileErrorException : public FilesystemException {
public:
	FileErrorException( const string& file ) : FilesystemException( file ) { }

	virtual ostream& print( ostream& out ) const noexcept override {
		return out << "File " << file_m << " is unavaliable.";
	}
};

#endif //HTTP_SERVER_FILEERROREXCEPTION_H
