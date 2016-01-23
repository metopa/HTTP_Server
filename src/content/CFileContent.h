//
// Created by metopa on 5.5.15.
//

#ifndef HTTP_SERVER_CFILECONTENT_H
#define HTTP_SERVER_CFILECONTENT_H

#include "CAbstractContent.h"

using namespace std;

/**
 * This class represents a content generator entity.
 * It loads an HTML page stored on a disk.
 */
class CFileContent : public CAbstractContent {

public:
	/**
	 * Constructs a content object.
	 * Initializes some private attributes.
	 *
	 * \param userPath - A resource path as requested by user.
	 * \param realPath - A resource path that refers to the real resource location on a local machine.
	 */
	CFileContent( string const& userPath, string const& realPath );

	virtual ~CFileContent();

	/**
	 * This method loads the requested resource from disk.
	 */
	virtual void load();

private:
	void modificationTime();
};


#endif //HTTP_SERVER_CFILECONTENT_H
