//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CHTMLWRAPPER_H
#define HTTP_SERVER_CHTMLWRAPPER_H

#include <string>
#include <vector>

using namespace std;


/**
 * This helper class provides an easy and clear interface for wrapping data into HTML page.
 * In addition it provides methods for encapsulating data into HTML tags and for generating HTML tables.
 */

class CHTMLGenerator {
	string data_m;
	/**< An input data that is encapsulated.*/
	int sortPriority_m; /** An internal helper parameter. Is used for generating table rows in defined order. */
public:
	/**
	 * Constructs an HTML generator object.
	 * \param data - A string that contains data to be encapsulated.
	 * \param sortPriority - Defines order in which rows will appear in an HTML table.
	 */
	CHTMLGenerator( const string& data = "", int sortPriority = 0 );

	/**
	 * This method encapsulates the data into an HTML attribute.
	 * \param attr - An attribute name.
	 */
	CHTMLGenerator& applyAttr( const string& attr );

	/**
	 * This method encapsulates the data into an HTML attribute.
	 * \param attr - An attribute name.
	 * \param param - An attribute parameter.
	 */
	CHTMLGenerator& applyAttr( const string& attr, const string& param );

	/**
	 * This method appends data from the other HTML generator object.
	 * \param other - An object to be appended.
	 */
	CHTMLGenerator& append( const CHTMLGenerator& other );

	/**
	 * This method appends data from string.
	 * \param str - A string to be appended.
	 */
	CHTMLGenerator& append( const string& str );

	/**
	 * This method appends a single char.
	 * \param c - A char to be appended.
	 */
	CHTMLGenerator& append( char c );

	/**
	 * This method wraps the object's data into a hyperlink.
	 * \param path - A string that contains a path of the link.
	 */
	CHTMLGenerator& makeHyperlink( const string& path );

	/**
	 * This method creates an HTML table from a vector of the HTML generator objects.
	 * \param entries - A vector that contains entries of the table.
	 */
	CHTMLGenerator& makeTable( vector<CHTMLGenerator>& entries );

	/**
	 *	This method applies a size HTML attribute.
	 *	\param size - A relative size parameter. Default is 6 pt. Can be negative.
	 */
	CHTMLGenerator& enlarge( int size = 0 );

	/**
	 * This method substitutes all newline symbols with an HTML <br> tag.
	 */
	CHTMLGenerator& substituteNL();

	/**
	 * This method wraps data into an HTML page.
	 * \param title - A title of the page.
	 * \return The generated page.
	 */
	string wrap( const string& title );

	/**
	 * This method changes a sortPriority_m attribute value.
	 */
	void setPriority( int newPriority );

	bool operator <( const CHTMLGenerator& other ) const;
};


#endif //HTTP_SERVER_CHTMLWRAPPER_H
