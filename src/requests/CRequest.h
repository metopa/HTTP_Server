//
// Created by metopa on 4/18/15.
//

#ifndef HTTP_SERVER_CABSTRACTREQUEST_H
#define HTTP_SERVER_CABSTRACTREQUEST_H

#include <string>
#include <chrono>

#include "../network/CSocketIO.h"
#include "CRequestParser.h"
#include "response_generators/CAbstractGenerator.h"

using namespace std;
using namespace chrono;

/**
 * This class represents a request handler.
 * It performs the whole request processor cycle. That is:
 * - Receive a request
 * - Parse it
 * - Look up for a resource
 * - Load the resource
 * - Generate a response
 * - Send the response back
 */

class CRequest {
private:
	CSocketIO socketIO_m; /**< A connection socket. */
	string inputMsg_m; /**< Received data. */
	string outputMsg_m; /**< Generated response. */
	high_resolution_clock::time_point clock_m; /**< The start of the command processing. */

	CRequestParser parser_m; /**< A request parser object. */
	CAbstractGenerator * generator_m; /**< A pointer to the response generator object. */

public:
	/**
	 * Constructs a request handler object.
	 * \param sockfd - A socket to communicate with a client.
	 * \param port - A port on which the sockfd refers to.
	 */
	CRequest( int sockfd, int port );

	/**
	 * Destructs the object.
	 */
	~CRequest();

	/**
	 * This method determines the type of the requested resource and it's availability.
	 * It initializes a generator_m variable.
	 */
	void parse();

	/**
	 * This method generates an HTTP response.
	 */
	void generate();

	/**
	 * This method receives a request.
	 */
	void receive();


	/**
	 * This method sends the response.
	 */
	void sendBack();

private:
	/**
	 * This method sends information about processed request into a log stream.
	 * \see CLogger
	 */
	void logStatistic();
};


#endif //HTTP_SERVER_CABSTRACTREQUEST_H
