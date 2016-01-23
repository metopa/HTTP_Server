#include "CSocketIO.h"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

#include "../exceptions.h"
#include "../logger.h"

CSocketIO::CSocketIO( int sockfd, int port ) :
		sockfd_m( sockfd ), port_m( port ) { }

CSocketIO::~CSocketIO() {
	close( sockfd_m );
}


void CSocketIO::sendData( const std::string& data ) const {
	sendData( data.c_str(), data.size() );
}


void CSocketIO::sendData( const char * data, size_t size ) const {
	size_t sent = 0;
	ssize_t bytesSent;
	int errNo;

	while ( sent < size ) {
		bytesSent = send( sockfd_m, data + sent, size - sent, 0 );

		errNo = errno;
		if ( bytesSent < 0 ) {
			if ( errNo == EINTR )
				continue;
			else {
				close( sockfd_m );
				throw SocketSenderException( "send()", strerror( errNo ), port_m, sockfd_m );
			}
		}

		sent += bytesSent;
	}
	Log.ger<>( DEBUG_NETWORK, "New document has been sent on the port", port_m );
}

string CSocketIO::recvData() const {
	char buf[1024];
	ssize_t bytesRecvd;
	int errNo;
	string data;

	while ( 1 ) {
		bytesRecvd = recv( sockfd_m, buf, sizeof( buf ), 0 );

		errNo = errno;
		if ( bytesRecvd == 0 )
			break;
		else if ( bytesRecvd < 0 ) {
			if ( errNo == EINTR )
				continue;
			else
				throw SocketReceiverException( "recv()", strerror( errNo ), port_m, sockfd_m );
		}

		data.insert( data.end(), buf, buf + bytesRecvd );

		if ( data.size() >= 4 &&
			 data[data.size() - 4] == 13 &&
			 data[data.size() - 3] == 10 &&
			 data[data.size() - 2] == 13 &&
			 data[data.size() - 1] == 10 )
			break;

		/** An RFC2616 recommendation since someone may want to break the standard.*/
		if ( data.size() >= 2 &&
			 data[data.size() - 2] == 10 &&
			 data[data.size() - 1] == 10 )
			break;


	}

	if ( data.size() == 0 )
		throw EmptyDataException();

	return data;
}

int CSocketIO::getPort() const {
	return port_m;
}

