//
// Created by metopa on 4/16/15.
//

#ifndef HTTP_SERVER_TSOCKETREMOTECONNECTION_H
#define HTTP_SERVER_TSOCKETREMOTECONNECTION_H


#include <sys/socket.h>

/**
 * This is helper class that stores information about connection socket and primary is used by CPortObtainer::accept() method.
 * \see CPortObtainer
 * \author Viacheslav Kroilov
 */

struct TSocketRemoteConnection {
	int sockfd_m;
	sockaddr_storage remoteaddr_m;
	socklen_t addrlen_m;

	TSocketRemoteConnection( int sockfd = 0 ) :
			sockfd_m( sockfd ), addrlen_m( sizeof( remoteaddr_m ) ) { }

	TSocketRemoteConnection( int sockfd, sockaddr_storage const& remoteaddr ) :
			sockfd_m( sockfd ),
			remoteaddr_m( remoteaddr ),
			addrlen_m( sizeof( remoteaddr_m ) ) { }

	operator int() const {
		return sockfd_m;
	}
};

#endif //HTTP_SERVER_TSOCKETREMOTECONNECTION_H


