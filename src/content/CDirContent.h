//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CDIRCONTENT_H
#define HTTP_SERVER_CDIRCONTENT_H

#include "CAbstractContent.h"
#include <string>

/**
 * This class represents a content generator entity.
 * It generates an HTML page that contains the structure of the requested directory.
 */
class CDirContent : public CAbstractContent {
public:
	/**
	 * Constructs content object.
	 * Initializes some private attributes.
	 *
	 * \param userPath - A resource path as requested by user.
	 * \param realPath - A resource path that refers to the real resource location on a local machine.
	 */
	CDirContent( string const& userPath, string const& realPath );

	virtual ~CDirContent();

	/**
	 * This method generates an HTML table that represents requested directory content.
	 */
	virtual void load();

private:
	void modificationTime();

	/**
	 * This method normalizes a path representation.
	 * It removes multiple path delimiters.
	 * \param path - A path to normalize.
	 * \return The normalized path.
	 */
	string makeLink( const string& path );
};


#endif //HTTP_SERVER_CDIRCONTENT_H
