//
// Created by metopa on 5.5.15.
//

#include "CFileContent.h"

#include <fstream>
#include <sys/stat.h>

#include "../exceptions.h"

CFileContent::CFileContent( string const& userPath, string const& realPath ) :
		CAbstractContent( userPath, realPath ) { }

CFileContent::~CFileContent() { }

void CFileContent::load() {
	ifstream is( realPath_m, ifstream::binary );
	if ( !is )
		throw FileNotFoundException( userPath_m.c_str(), "" );

	is.seekg( 0, is.end );
	size_m = (size_t) is.tellg();
	is.seekg( 0, is.beg );

	char * buf = new char[size_m];
	is.read( buf, size_m );

	size_m = (size_t) is.tellg();

	data_m.insert( data_m.begin(), buf, buf + size_m );
	delete[] buf;

	if ( !is.good() )
		throw FileErrorException( userPath_m.c_str() );

	is.close();

	modificationTime();
	creationTime();
}

void CFileContent::modificationTime() {
	struct stat attr;
	stat( realPath_m.c_str(), &attr );
	ctime_r( &attr.st_mtime, modTime_m );

	for ( int i = 1; i < 32; i++ )
		if ( !modTime_m[i] ) {
			modTime_m[i - 1] = 0;
			break;
		}
}
