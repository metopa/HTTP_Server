//
// Created by metopa on 4.5.15.
//

#ifndef HTTP_SERVER_ELOGFLAGS_H
#define HTTP_SERVER_ELOGFLAGS_H

#include <string>

/**
 * This is an enumeration type that identifies different types of log messages.
 */
enum ELogFlags {
	SILENT, CRITICAL, INFO, DEBUG_ALL, NETWORK, DEBUG_NETWORK,
	REQUEST, DEBUG_REQUEST, DEBUG_PARSER, THREADS, STATISTICS, UNDEFINED, E_LOG_FLAGS_MAX
};

/**
 * This namespace contains functions, that works with ELogFlags enums.
 *
 */
namespace logflagsNS {

	/**
	 * \return The string, that contains the name of the log flag.
	 */
	const char * logFlagsToString( ELogFlags f );

	/**
	 * \return The string, that contains the aligned name of the log flag.
	 */
	const char * logFlagsToStringPrintable( ELogFlags f );

	/**
	 * \return The log flag that equals to the str argument.
	 */
	ELogFlags logFlagsFromString( std::string& str );
}


#endif //HTTP_SERVER_ELOGFLAGS_H
