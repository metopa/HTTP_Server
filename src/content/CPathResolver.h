//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CPATHRESOLVER_H
#define HTTP_SERVER_CPATHRESOLVER_H

#include <string>

using namespace std;

/**
 * This is an enumeration type that identifies a resource type.
 */
enum EFileType {
	FT_REGULAR, FT_DIRECTORY, FT_EXECUTABLE, FT_SCRIPT
};

/**
 * This class looks up for a resource in a filesystem.
 * In addition it checks possible errors (file not found, permission denied) and determines a resource type.
 *
 */
class CPathResolver {
	/**
	 * This method unwinds requested path and prevents attempts to escape out from the server working directory.
	 * A protection from attacks like './../../'.
	 */
	void unwindPath( const string& path );

	/**
	 * This method implements a virtual filesystem feature.
	 * It searches a requested resource in a list of paths that should be mapped to other paths specified by user.
	 */
	string substitutePath( string& path );

	/**
	 * An internal function.
	 * It compares two string.
	 * \param a - The first string.
	 * \param b - The second string.
	 * \return true, if the first string starts with the second string.
	 * \return false, otherwise
	 */
	bool partialCompare( const string& a, const string& b );

	/**
	 * The method extracts an extension of the resource.
	 * \return The string that contains a file extension.
	 */
	string getExt( const string& path );

public:
	/**
	 * This method determines the real resource location in a filesystem and the resource type.
	 * \param path - An input parameter that contains a path relatively to the server root directory.
	 * \param ft - An output parameter that will contain information about resource type.
	 * \return - The string that contains real resource path.
	 */
	string resolve( string& path, EFileType& ft );
};

extern CPathResolver pathResolver;


#endif //HTTP_SERVER_CPATHRESOLVER_H
