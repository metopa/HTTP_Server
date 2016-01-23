//
// Created by metopa on 4/18/15.
//
#include "CRequest.h"

#include "../exceptions.h"
#include "../logger.h"
#include "response_generators/CErrorGenerator.h"
#include "response_generators/CGetGenerator.h"
#include "response_generators/COptionsGenerator.h"
#include "response_generators/CHeadGenerator.h"

CRequest::CRequest( int sockfd, int port ) : socketIO_m( sockfd, port ) {
	generator_m = nullptr;
}

CRequest::~CRequest() {
	delete generator_m;
}

void CRequest::parse() {
	clock_m = high_resolution_clock::now();
	try {
		parser_m.parse( inputMsg_m );
		switch ( parser_m.getType() ) {
			case RT_GET:
				generator_m = new CGetGenerator( parser_m.getResource() );
				break;
			case RT_HEAD:
				generator_m = new CHeadGenerator( parser_m.getResource() );
				break;
			case RT_OPTIONS:
				generator_m = new COptionsGenerator( parser_m.getResource() );
				break;
			default:
				generator_m = new CErrorGenerator( 501 ); //Not Implemented
		}
	}
	catch ( RequestParserException& e ) {
		Log.ger<>( DEBUG_REQUEST, e );
		if ( parser_m.getType() == RT_UNSUPPORTED )
			generator_m = new CErrorGenerator( 501 ); //Not Implemented
		else
			generator_m = new CErrorGenerator( 400 ); //Bad Request
	}

	catch ( MethodProhibitedException& e ) {
		Log.ger<>( DEBUG_REQUEST, e );
		generator_m = new CErrorGenerator( 405 ); //Method Not Allowed
	}

	catch ( FileNotFoundException& e ) {
		Log.ger<>( DEBUG_REQUEST, e );
		generator_m = new CErrorGenerator( 404 ); //Not Found
	}

	catch ( FileErrorException& e ) {
		Log.ger<>( DEBUG_REQUEST, e );
		generator_m = new CErrorGenerator( 409 ); //Conflict
	}

	catch ( PermissionDeniedException& e ) {
		Log.ger<>( DEBUG_REQUEST, e );
		generator_m = new CErrorGenerator( 403 ); //Forbidden
	}

	catch ( ServiceUnavailableException& e ) {
		Log.ger<>( DEBUG_REQUEST, e );
		generator_m = new CErrorGenerator( 503 ); //Service unavailable
	}

	catch ( InternalErrorException& e ) {
		Log.ger<>( DEBUG_REQUEST, e );
		generator_m = new CErrorGenerator( 500 ); //Internal Server Error
	}

	catch ( GeneralException& e ) {
		Log.ger<GeneralException&>( CRITICAL, e );
		generator_m = new CErrorGenerator( 500 ); //Internal Server Error
	}
}


void CRequest::generate() {
	outputMsg_m = generator_m->generate();
}

void CRequest::sendBack() {
	socketIO_m.sendData( outputMsg_m );
	logStatistic();
}

void CRequest::receive() {
	inputMsg_m = socketIO_m.recvData();
	Log.ger<>( DEBUG_REQUEST, "Received data from port", socketIO_m.getPort(), "size =", inputMsg_m.size() );
}

void CRequest::logStatistic() {
	Log.printStatistic( socketIO_m.getPort(), clock_m, inputMsg_m, outputMsg_m );
}
