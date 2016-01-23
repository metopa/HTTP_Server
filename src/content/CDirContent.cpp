//
// Created by metopa on 7.5.15.
//

#include "CDirContent.h"

#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>

#include "CHTMLGenerator.h"
#include "../logger.h"
#include "../exceptions.h"

CDirContent::CDirContent( string const& userPath, string const& realPath ) :
		CAbstractContent( userPath, realPath ) { }

CDirContent::~CDirContent() { }

void CDirContent::load() {
	int rc;
	DIR * dir;
	dirent entry;
	dirent * result;
	Log.ger<>( DEBUG_REQUEST, "Directory:", realPath_m, userPath_m );
	vector<CHTMLGenerator> files_m;

	if ( !( dir = opendir( realPath_m.c_str() ) ) ) {
		int errNo = errno;

		switch ( errNo ) {
			case EACCES:
				throw PermissionDeniedException( userPath_m );
			case ENOENT:
				throw FileNotFoundException( userPath_m );
			default:
				throw FileErrorException( userPath_m );
		}
	}

	while ( !( rc = readdir_r( dir, &entry, &result ) ) ) {
		if ( result == nullptr )
			break;
		files_m.push_back( CHTMLGenerator( result->d_name ) );
		Log.ger<>( DEBUG_REQUEST, "Directory", result->d_name, (int)result->d_type );
		if ( result->d_type == DT_DIR || result->d_type == DT_REG )
			files_m.back().makeHyperlink( makeLink( result->d_name ) );
		files_m.back().enlarge();
		if ( !strcmp( result->d_name, ".." ) )
			files_m.back().setPriority( -2 );
		else if ( !strcmp( result->d_name, "." ) )
			files_m.back().setPriority( -1 );
	}

	stable_sort( files_m.begin(), files_m.end() );

	CHTMLGenerator table( string( "Index of " ) + userPath_m );
	table.enlarge( 2 ).makeTable( files_m );
	if ( rc )
		table.append( "\nAn error occured while reading directory content. Try to refresh page\n" );
	string rawHTML = table.wrap( string( "Index of " ) + userPath_m.c_str() );
	data_m.insert( data_m.begin(), rawHTML.begin(), rawHTML.end() );

	closedir( dir );

	size_m = data_m.size();

	modificationTime();
	creationTime();
}

void CDirContent::modificationTime() {
	struct stat attr;
	stat( realPath_m.c_str(), &attr );
	ctime_r( &attr.st_mtime, modTime_m );

	for ( int i = 1; i < 32; i++ )
		if ( !modTime_m[i] ) {
			modTime_m[i - 1] = 0;
			break;
		}
}

string CDirContent::makeLink( const string& path ) {
	if ( userPath_m.back() == '/' )
		return userPath_m + path;
	else if ( path == "." )
		return userPath_m;
	else
		return userPath_m + '/' + path;
}
