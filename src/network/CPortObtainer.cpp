//
// Created by metopa on 4/15/15.
//

#include "CPortObtainer.h"

#include <cstring>
#include <unistd.h>

#include "../logger.h"
#include "../exceptions.h"

CPortObtainer::CPortObtainer( const char * port, int connsPerPort ) :
		addrinfo_m( port ), socket_m( addrinfo_m, port ) {
	if ( listen( socket_m, connsPerPort ) == -1 )
		throw PortInitializationException( "listen()", strerror( errno ), port );

	Log.ger<>( DEBUG_NETWORK, port, "is binded to socket", (int) socket_m );
	if ( sscanf( port, "%d", &port_m ) != 1 )
		port_m = -1;
}

CPortObtainer::operator int() const {
	return (int) socket_m;
}

TSocketRemoteConnection CPortObtainer::acceptConnection() {
	TSocketRemoteConnection rConn;
	rConn.sockfd_m = accept( socket_m, (sockaddr *) &( rConn.remoteaddr_m ), &( rConn.addrlen_m ) );
	if ( rConn.sockfd_m == -1 ) {
		throw PortInitializationException( "accept()", strerror( errno ), port_m, socket_m );
	}

	Log.ger<>( DEBUG_NETWORK, port_m, "has new connection. Session socket", rConn.sockfd_m );
	return rConn;
}

CPortObtainer::CAddrInfoWrapper::CAddrInfoWrapper( const char * port ) {
	addrinfo hints;

	memset( &hints, 0, sizeof( hints ) );

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int status;
	if ( ( status = getaddrinfo( NULL, port, &hints, &servinfo_m ) ) != 0 ) {
		servinfo_m = nullptr;
		throw PortInitializationException( "getaddrinfo()", gai_strerror( status ), port );
	}
}

CPortObtainer::CAddrInfoWrapper::~CAddrInfoWrapper() {
	if ( servinfo_m )
		freeaddrinfo( servinfo_m );
}

CPortObtainer::CAddrInfoWrapper::operator addrinfo *() const {
	return servinfo_m;
}

CPortObtainer::CSocketWrapper::CSocketWrapper( addrinfo * servinfo, const char * port ) {
	int yes = 1;

	for ( addrinfo * it = servinfo; it != nullptr; it = it->ai_next ) {
		if ( ( sockfd_m = socket( it->ai_family, it->ai_socktype, it->ai_protocol ) ) == -1 ) {
			Log.ger<>( DEBUG_NETWORK, port, "socket() returned error:", strerror( errno ) );
			continue;
		}

		if ( setsockopt( sockfd_m, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof( int ) ) == -1 ) {
			throw PortInitializationException( "setsockopt()", strerror( errno ), port, sockfd_m );
		}

		if ( bind( sockfd_m, it->ai_addr, it->ai_addrlen ) == -1 ) {
			close( sockfd_m );
			sockfd_m = -1;
			Log.ger<>( DEBUG_NETWORK, "Function bind() returned error on port", port, strerror( errno ) );
			continue;
		}
		break;
	}

	if ( sockfd_m == -1 )
		throw PortInitializationException( "socket()", "Function failed on all addrinfo structures", port );
}

CPortObtainer::CSocketWrapper::~CSocketWrapper() {
	if ( sockfd_m != -1 )
		close( sockfd_m );
}

CPortObtainer::CSocketWrapper::operator int() const {
	return sockfd_m;
}

int CPortObtainer::port() {
	return port_m;
}
