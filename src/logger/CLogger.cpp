//
// Created by metopa on 28.4.15.
//

#include "CLogger.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fstream>

#include "../exceptions.h"

CLogger Log;

CLogger::CLogger() {
	logStream_m = &cerr;
	logStreamIsCOUT = true;
	pid_m = getpid();
	initialized_m = false;
}

CLogger::~CLogger() {
	logStream_m->flush();
	if ( !logStreamIsCOUT ) {
		delete logStream_m;
		logStream_m = nullptr;
	}
}

void CLogger::init( const string& logFile ) {
	if ( logFile == "stdout" ) {
		logStreamIsCOUT = true;
		logStream_m = &cout;
	}
	else {
		logStreamIsCOUT = false;
		ofstream * lfile = new ofstream( logFile.c_str() );
		if ( !lfile->is_open() ) {
			delete lfile;
			throw FileNotFoundException( logFile.c_str(), MSG_CRIT_ERR );
		}
		logStream_m = lfile;
	}
	initialized_m = true;
}

void CLogger::printTimestamp() {
	time_t ltime;
	tm result;
	char stime[32];

	*logStream_m << '(' << pid_m << ')' << ' ';

	ltime = time( NULL );
	localtime_r( &ltime, &result );
	asctime_r( &result, stime );
	for ( int i = 1; i < 32; i++ )
		if ( !stime[i] ) {
			stime[i - 1] = 0;
			break;
		}
	*logStream_m << stime;
}

void CLogger::welcome() {
	*logStream_m << "################################  HTTP  Server  ################################" << endl;
}

void CLogger::error( ELogFlags level, int errNo ) {
	if ( !initialized_m || config.checkLogFlag( level ) ) {
		mutex_m.lock();
		printTimestamp();
		*logStream_m << '\t' << logflagsNS::logFlagsToString( level ) << '\t' << strerror( errNo ) << endl;
		mutex_m.unlock();
	}
}

void CLogger::options() {
	if ( initialized_m ) {
		*logStream_m << "Log options: ";
		for ( int i = 0; i < E_LOG_FLAGS_MAX; i++ )
			if ( config.checkLogFlag( ELogFlags( i ) ) )
				*logStream_m << logflagsNS::logFlagsToString( ELogFlags( i ) ) << ' ';
		*logStream_m << endl;
	}
}

void CLogger::printStatistic( int port, const high_resolution_clock::time_point& time, const string& input,
							  const string& output ) {
	if ( !initialized_m || config.checkLogFlag( STATISTICS ) ) {
		mutex_m.lock();
		printTimestamp();
		auto us = chrono::duration_cast<chrono::microseconds>( high_resolution_clock::now() - time ).count();
		auto ms = us / 1000;
		us %= 1000;
		*logStream_m << '\t' << logflagsNS::logFlagsToStringPrintable( STATISTICS ) << ' ' <<
		"port:" << port << '\t' <<
		"processing_time(ms):" << ms << '.' << us << '\t' <<
		//"request_header:" << substractHeader( inputMsg_m ) << '\t' <<
		"request_size:" << input.size() << "\t" <<

		"response_size:" << output.size() << endl;
		mutex_m.unlock();
	}
}
