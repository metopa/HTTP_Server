//
// Created by metopa on 4/15/15.
//

#ifndef HTTP_SERVER_CPORTOBTAINER_H
#define HTTP_SERVER_CPORTOBTAINER_H

#include <netdb.h>
#include "TSocketRemoteConnection.h"
/**
 * This class represents a network port as a high-level object.
 * It wraps related POSIX functions into easy and clear interface
 * and performs error-checking.
 * \see CSocketIO
 * \author Viacheslav Kroilov
 */
class CPortObtainer {
	/**
	 * A helper class, that is used for the RAII strategy. Attempts to retrieve an addrinfo structure.
	 * Constructor throws PortInitializationException, if some of the system calls failed.
	 */
	class CAddrInfoWrapper {
		addrinfo * servinfo_m;
	public:
		CAddrInfoWrapper( const char * port );

		~CAddrInfoWrapper();

		operator addrinfo *() const;

	};

	/**
	 * A helper class, that is used for the RAII strategy. Attempts to obtain a system socket descriptor.
	 * Constructor throws PortInitializationException, if some of the system calls failed.
	 */
	class CSocketWrapper {
		int sockfd_m;

	public:
		CSocketWrapper( addrinfo * servinfo, const char * port );

		~CSocketWrapper();

		operator int() const;
	};

	CAddrInfoWrapper addrinfo_m;
	/**< A helper object. \see CAddrInfoWrapper*/
	CSocketWrapper socket_m;
	/**< A helper object. \see CSocketWrapper*/
	int port_m; /**< The port number.*/
public:

	/**
	 * \param port - A NULL-terminated string that contains the port number.
	 * \param connsPerPort - A size of the system connection queue.
	 */
	CPortObtainer( const char * port, int connsPerPort );

	/**
	 * \return The system file descriptor referring to the opened port.
	 */
	operator int() const;

	/**
	 * A method that wraps accept() system function call.
	 * It throws PortInitializationException if the call was interrupted by the signal.
	 * \return The TSocketRemoteConnection struct that contains connection socket descriptor.
	 */
	TSocketRemoteConnection acceptConnection();

	/**
	 * \return The port number.
	 */
	int port();
};


#endif //HTTP_SERVER_CPORTOBTAINER_H
