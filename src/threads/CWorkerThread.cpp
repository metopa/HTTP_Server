//
// Created by metopa on 4/18/15.
//

#include "CWorkerThread.h"
#include "../exceptions.h"
#include "../logger.h"

CWorkerThread::CWorkerThread( int id, const char * wd, CThreadSafeQueue<CRequest *, nullptr, 100> * queue )
		: id_m( id ), wd_m( wd ), queue_m( queue ) { }

void CWorkerThread::run() {
	int processedCount = 0;
	Log.ger<>( THREADS, "Worker thread", id_m, "successfully started" );
	while ( 1 ) {
		try {
			unique_ptr<CRequest> current( queue_m->pop() );
			if ( !current )
				break;

			Log.ger<>( THREADS, "Worker thread", id_m, "has new job" );
			current->receive();
			current->parse();
			current->generate();
			current->sendBack();

			processedCount++;
		}
		catch ( EmptyDataException& e ) {
			Log.ger( DEBUG_NETWORK, e );
		}
		catch ( NetworkException& e ) {
			Log.ger( NETWORK, e );
		}
		catch ( bad_alloc& e ) { }
	}

	Log.ger<>( INFO, "Thread_id:requests_processed\t", id_m, CLogger::NoSpace(), ":", CLogger::NoSpace(),
			   processedCount );
	Log.ger<>( THREADS, "Worker thread", id_m, "shuts down" );
}
