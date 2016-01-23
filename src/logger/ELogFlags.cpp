//
// Created by metopa on 4.5.15.
//

#include "ELogFlags.h"

const char * logflagsNS::logFlagsToString( ELogFlags f ) {
	switch ( f ) {
		case SILENT:
			return "SILENT";
		case CRITICAL:
			return "CRITICAL";
		case INFO:
			return "INFO";
		case DEBUG_ALL:
			return "DBG_ALL";
		case NETWORK:
			return "NETWORK";
		case DEBUG_NETWORK:
			return "DBG_NETWORK";
		case DEBUG_REQUEST:
			return "DBG_REQUEST";
		case REQUEST:
			return "REQUEST";
		case DEBUG_PARSER:
			return "DBG_PARSER";
		case THREADS:
			return "THREADS";
		case STATISTICS:
			return "STATISTICS";
		default:
			return "UNDEFINED";
	}
}

const char * logflagsNS::logFlagsToStringPrintable( ELogFlags f ) {
	switch ( f ) {
		case SILENT:
			return "SILENT     ";
		case CRITICAL:
			return "CRITICAL   ";
		case INFO:
			return "INFO       ";
		case DEBUG_ALL:
			return "DBG_ALL    ";
		case NETWORK:
			return "NETWORK    ";
		case DEBUG_NETWORK:
			return "DBG_NETWORK";
		case DEBUG_REQUEST:
			return "DBG_REQUEST";
		case REQUEST:
			return "REQUEST    ";
		case DEBUG_PARSER:
			return "DBG_PARSER ";
		case THREADS:
			return "THREADS    ";
		case STATISTICS:
			return "STATISTICS ";
		default:
			return "UNDEFINED  ";
	}
}

ELogFlags logflagsNS::logFlagsFromString( std::string& str ) {
	for ( int i = 0; i < E_LOG_FLAGS_MAX; i++ )
		if ( str.compare( logFlagsToString( (ELogFlags) i ) ) == 0 )
			return (ELogFlags) i;
	return UNDEFINED;
}