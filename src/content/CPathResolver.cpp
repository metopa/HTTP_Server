//
// Created by metopa on 7.5.15.
//

#include "CPathResolver.h"

#include <sys/stat.h>
#include <unistd.h>

#include "../config.h"
#include "../logger.h"
#include "../exceptions.h"

CPathResolver pathResolver;

void CPathResolver::unwindPath( const string& path ) {
	int depth = 0;
	int state = 0;
	for ( unsigned long int i = 0; i < path.length() && depth >= 0; i++ ) {
		switch ( state ) {
			case 0:
				if ( path[i] == '.' )
					state = 2;
				else if ( path[i] == '/' )
					state = 0;
				else state = 1;
				break;
			case 1:
				if ( path[i] == '/' ) {
					state = 0;
					depth++;
				}
				break;
			case 2:
				if ( path[i] == '.' )
					state = 3;
				else if ( path[i] == '/' )
					state = 0;
				else state = 1;
				break;
			case 3:
				if ( path[i] == '.' ) {
					state = 0;
					depth--;
				}
				else state = 1;
				break;
			default:
				break;
		}
	}
	if ( depth < 0 )
		throw PermissionDeniedException( path );
}

string CPathResolver::substitutePath( string& path ) {
	for ( auto it = config.getFileMappings().begin(); it != config.getFileMappings().end(); it++ )
		if ( partialCompare( path, it->first ) ) {
			if ( it->second == "-" )
				throw PermissionDeniedException( path );
			else
				return it->second + path.substr( it->first.length() );
		}
	return config.getWorkDir() + path;
}


bool CPathResolver::partialCompare( const string& a, const string& b ) {
	if ( a.length() < b.length() )
		return false;
	for ( unsigned long int i = 0; i < b.length(); i++ )
		if ( a[i] != b[i] )
			return false;
	return true;
}


string CPathResolver::getExt( const string& path ) {
	unsigned long int slash = path.find_last_of( '/' );
	unsigned long int dot = path.find_last_of( '.' );
	if ( dot > slash )
		return path.substr( dot + 1 );
	else
		return string();
}

string CPathResolver::resolve( string& path, EFileType& ft ) {
	unwindPath( path );
	string realPath = substitutePath( path );
	struct stat info;

	if ( stat( realPath.c_str(), &info ) != 0 ) {
		int errNo = errno;
		switch ( errNo ) {
			case EFAULT:
			case ENAMETOOLONG:
			case ENOENT:
			case ENOTDIR:
				throw FileNotFoundException( path );
			case EACCES:
				throw PermissionDeniedException( path );
			default:
				throw FileErrorException( path );
		}
	}

	if ( access( realPath.c_str(), R_OK ) )
		throw PermissionDeniedException( path );

	if ( S_ISDIR( info.st_mode ) ) {
		if ( path.back() != '/' ) {
			path += '/';
			realPath += '/';
		}
		ft = FT_DIRECTORY;
		return realPath;
	}

	if ( S_ISREG( info.st_mode ) ) {
		string ext = getExt( realPath );
		if ( config.checkRegExt( ext ) )
			ft = FT_EXECUTABLE;
		else if ( config.checkScriptExt( ext ) )
			ft = FT_SCRIPT;
		else
			ft = FT_REGULAR;
		return realPath;
	}

	throw FileNotFoundException( path, "Is not file or directory. Error code 401 will be send." );
}
