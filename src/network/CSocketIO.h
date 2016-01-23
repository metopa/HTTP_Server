//
// Created by metopa on 4/18/15.
//

#ifndef HTTP_SERVER_CSOCKETSENDER_H
#define HTTP_SERVER_CSOCKETSENDER_H

#include <string>
using namespace std;

/**
 * This class wraps low-level system IO calls into high-level interface and performs error-checking.
 * \warning The socket is closed with object's destructor.
 * \see CPortObtainer
 * \author Viacheslav Kroilov
 */

class CSocketIO {
	const int sockfd_m;
	/**< A Socket descriptor. */
	const int port_m; /**< A port number. */

public:
	/**
	 * Constructs socketIO object.
	 * \param sockfd - A connection socket descriptor.
	 * \param port - A port number (for debugging and prettier logging only).
	 */
	CSocketIO( int sockfd, int port );

	/**
	 * Destructs object and close socket.
	 */
	~CSocketIO();

	/**
	 * Sends raw data on socket.
	 * If fails, method throws SocketSenderException.
	 * \param data - A std::string object containing data to be sent.
	 */
	void sendData( const string& data ) const;

	/**
	 * Sends raw data on socket.
	 * If fails, method throws SocketSenderException.
	 * \param data - A raw char array containing data to be sent.
	 * \param size - A size of data.
	 */
	void sendData( const char * data, size_t size ) const;

	/**
	 * Receives data from the socket.
	 * Receiving stops when double CRLF bytes are received.
	 * If fails, method throws SocketReceiverException.
	 *
	 * \return The std::string object, that contains received data.
	 */
	string recvData() const;

	/**
	 * \return The port, associated with socketIO object.
	 */
	int getPort() const;
};


#endif //HTTP_SERVER_CSOCKETSENDER_H
