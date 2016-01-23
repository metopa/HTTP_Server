//
// Created by metopa on 7.5.15.
//

#include "FilesystemException.h"

#ifndef HTTP_SERVER_PERMISSIONDENIEDEXCEPTION_H
#define HTTP_SERVER_PERMISSIONDENIEDEXCEPTION_H

/**
 * This exception is being thrown by CDirContent, CExternalContent and CPathResolver classes.
 */
class PermissionDeniedException : public FilesystemException {
public:
	PermissionDeniedException( const string& file ) : FilesystemException( file ) { }

	virtual ostream& print( ostream& out ) const noexcept override {
		return out << "Can't access " << file_m << ". Permission denied.";
	}
};

#endif //HTTP_SERVER_PERMISSIONDENIEDEXCEPTION_H
