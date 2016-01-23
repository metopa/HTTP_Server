//
// Created by metopa on 3.5.15.
//

#include "CSignalThread.h"

#include "../signals/signals.h"
#include "../logger.h"

CSignalThread::CSignalThread( CThreadSafeQueue<CRequest *, nullptr> * queue ) {
	queue_m = queue;
}

void CSignalThread::run() {
	Log.ger<>( THREADS, "Signal thread successfully started" );
	int sig = signalNS::sigWait();
	Log.ger<>( CRITICAL, "Signal", sig, "caught. Request queue is disabled." );
	queue_m->disable();
}
