//
// Created by metopa on 6.5.15.
//

#ifndef HTTP_SERVER_EREQUESTTYPE_H
#define HTTP_SERVER_EREQUESTTYPE_H

#include <string>

/**
 * This is an enumeration type that identifies different types of HTTP methods.
 */
enum EMethodType {
	RT_GET, RT_HEAD, RT_OPTIONS, RT_UNSUPPORTED, RT_ALL, RT_MAXENUM
};

/**
 * This namespace contains functions, that works with EMethodType enums.
 *
 */
namespace methodTypeNS {
	/**
	 * \return The string, that contains the name of the method.
	 */
	const char * methodToString( EMethodType e );

	/**
	 * \return The method enum that equals to the str argument.
	 */
	EMethodType methodFromString( const std::string& str );
}


#endif //HTTP_SERVER_EREQUESTTYPE_H
