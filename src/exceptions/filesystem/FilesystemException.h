//
// Created by metopa on 5.5.15.
//

#ifndef HTTP_SERVER_FILESYSTEMEXCEPTION_H
#define HTTP_SERVER_FILESYSTEMEXCEPTION_H

#include "../GeneralException.h"

/**
 * This abstract class is a base class for all filesystem exceptions defined in this code.
 *
 */
class FilesystemException : public GeneralException {
protected:
	string file_m;
	string action_m;
public:

	FilesystemException( string const& file, string const& action ) :
			file_m( file ), action_m( action ) { }

	FilesystemException( const string& file ) :
			file_m( file ) { }

};

#endif //HTTP_SERVER_FILESYSTEMEXCEPTION_H
