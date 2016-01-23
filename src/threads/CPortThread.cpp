//
// Created by metopa on 4/18/15.
//

#include "CPortThread.h"
#include "../exceptions.h"
#include "../logger.h"

CPortThread::CPortThread( int id, char const * port, int connsPerPort, CThreadSafeQueue<CRequest *, nullptr> * queue )
		: id_m( id ), socket_m( port, connsPerPort ), port_m( port ), queue_m( queue ) { }

void CPortThread::run() {
	Log.ger<>( THREADS, "Listener thread", id_m, "successfully started" );
	int processedCount = 0;

	while ( 1 ) {
		try {
			if ( !queue_m->push( new CRequest( socket_m.acceptConnection(), socket_m.port() ) ) )
				break;
			processedCount++;
		}
		catch ( NetworkException& e ) {
			break;
		}
	}

	queue_m->notifyProducerStopped();

	Log.ger<>( INFO, "Port_number:requests_processed\t", port_m, CLogger::NoSpace(), ":", CLogger::NoSpace(),
			   processedCount );
	Log.ger<>( THREADS, "Listener thread", id_m, "shuts down" );

}


