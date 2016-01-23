//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CSTRINGCONTENT_H
#define HTTP_SERVER_CSTRINGCONTENT_H

#include "CAbstractContent.h"

#include <string>

using namespace std;

/**
 * This class represents a content generator entity.
 * It generates an HTML page that shows the specified string.
 */
class CStringContent : public CAbstractContent {
private:
	string msg_m; /**< A string to be wrapped into HTML. */

public:
	/**
 	* Constructs a content object.
 	* Initializes some private attributes.
 	*
 	* \param msg - A string to be wrapped into HTML.
 	*/
	CStringContent( const string& msg ) : msg_m( msg ) { }

	/**
	 * This method generates an HTML page.
	 */
	virtual void load();

	virtual const char * getModTime() const;

};


#endif //HTTP_SERVER_CSTRINGCONTENT_H
