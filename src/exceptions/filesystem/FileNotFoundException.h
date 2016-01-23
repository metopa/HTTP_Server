//
// Created by metopa on 4/27/15.
//

#ifndef HTTP_SERVER_FILENOTFOUNDEXCEPTION_H
#define HTTP_SERVER_FILENOTFOUNDEXCEPTION_H

#include "FilesystemException.h"

/**
 * This exception is being thrown by CConfig, CLogger, CFileContent and CPathResolver classes.
 */
class FileNotFoundException : public FilesystemException {
public:
	FileNotFoundException( const string& file, const string& action ) : FilesystemException( file, action ) { }

	FileNotFoundException( const string& file ) : FilesystemException( file, "Error code 404 will be send." ) { }

	virtual ostream& print( ostream& out ) const override {
		return out << "File " << file_m << " is unavaliable. " << action_m;
	}
};

#endif //HTTP_SERVER_FILENOTFOUNDEXCEPTION_H

