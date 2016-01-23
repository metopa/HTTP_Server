//
// Created by metopa on 6.5.15.
//

#include "EMethodType.h"

const char * methodTypeNS::methodToString( EMethodType e ) {
	switch ( e ) {
		case RT_GET:
			return "GET";
		case RT_HEAD:
			return "HEAD";
		case RT_OPTIONS:
			return "OPTIONS";
		case RT_ALL:
			return "ALL";
		default:
			return "UNSUPPORTED";
	}
}

EMethodType methodTypeNS::methodFromString( const std::string& str ) {
	for ( int i = 0; i < RT_MAXENUM; i++ ) {
		if ( str == methodToString( (EMethodType) i ) )
			return (EMethodType) i;
	}
	return RT_UNSUPPORTED;
}