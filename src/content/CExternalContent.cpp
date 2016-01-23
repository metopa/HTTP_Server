//
// Created by metopa on 7.5.15.
//

#include "CExternalContent.h"

#include <unistd.h>
#include <sys/wait.h>

#include "CHTMLGenerator.h"
#include "../logger.h"
#include "../exceptions.h"

CExternalContent::CExternalContent( string const& userPath, string const& realPath, bool isScript,
									bool wrapNeeded ) :
		CAbstractContent( userPath, realPath ), wrapNeeded_m( wrapNeeded ), isScript_m( isScript ) { }

void CExternalContent::load() {
	exec();
	if ( wrapNeeded_m )
		rawData_m = CHTMLGenerator( rawData_m ).substituteNL().wrap( userPath_m );
	data_m.insert( data_m.begin(), rawData_m.begin(), rawData_m.end() );
	size_m = data_m.size();
	creationTime();
}

const char * CExternalContent::getModTime() const {
	return getCreateTime();
}


void CExternalContent::exec() {
	int dataPipe[2];
	pipe( dataPipe );

	int chPID;
	if ( ( chPID = fork() ) == -1 ) {
		int errNo = errno;
		Log.ger<>( CRITICAL, "fork() failed, errno", errNo );
		close( dataPipe[0] );
		close( dataPipe[1] );
		throw InternalErrorException( realPath_m ); //TODO add args
	}

	if ( chPID == 0 ) {
		close( dataPipe[0] );
		dup2( dataPipe[1], STDOUT_FILENO );

		if ( isScript_m )
			exit( system( realPath_m.c_str() ) );
		else {
			execl( realPath_m.c_str(), realPath_m.c_str(), (char *) nullptr );
			exit( 127 );
		}
	}
	else {
		close( dataPipe[1] );
		readPipe( dataPipe[0] );
		close( dataPipe[0] );
		int rc;
		waitpid( chPID, &rc, 0 );
		if ( rc == 127 )
			throw PermissionDeniedException( realPath_m );
		if ( rc != 0 )
			throw ServiceUnavailableException( realPath_m );
	}
}


void CExternalContent::readPipe( int fd ) {
	uint8_t buf[1024];
	ssize_t bytesRecvd;
	int errNo;

	while ( 1 ) {
		bytesRecvd = read( fd, buf, sizeof( buf ) );
		errNo = errno;
		if ( bytesRecvd == 0 )
			break;
		else if ( bytesRecvd < 0 ) {
			if ( errNo == EINTR )
				continue;
			else
				throw InternalErrorException( realPath_m );
		}

		rawData_m.insert( rawData_m.end(), buf, buf + bytesRecvd );
	}
}
