#include <vector>
#include "network.h"
#include "threads.h"
#include "exceptions.h"
#include "signals/signals.h"

int main( int argc, char * argv[] ) {
	try {
		signalNS::blockSignals();
		signalNS::setEmptyHandler( SIGUSR1 );

		config.load( argc, argv );
		Log.init( config.getLogFile() );
		Log.welcome();
		Log.options();

		CThreadSafeQueue<CRequest *, nullptr> queue( config.getPortCount() );

		CRunnable::ptr_t signalHandler( new CSignalThread( &queue ) );

		vector<CRunnable::ptr_t> ports;
		for ( unsigned int i = 0; i < config.getPortCount(); i++ ) {
			try {
				ports.push_back( CRunnable::ptr_t( new CPortThread( i, config.getPorts()[i].c_str(), 10, &queue ) ) );
				Log.ger<>( NETWORK, "Port", config.getPorts()[i], "obtained" );
			}
			catch ( PortInitializationException& e ) {
				queue.notifyProducerStopped();
				Log.ger<>( CRITICAL, e );
			}
		}

		vector<CRunnable::ptr_t> workers;
		for ( unsigned int i = 0; i < config.getWorkerCount(); i++ )
			workers.push_back( CRunnable::ptr_t( new CWorkerThread( i, config.getWorkDir().c_str(), &queue ) ) );

		CThreadPool sigThread( signalHandler );
		CThreadPool portThreads( ports.begin(), ports.end() );
		CThreadPool workerThreads( workers.begin(), workers.end() );

		Log.ger<>( CRITICAL, "Server started" );

		workerThreads.join();
		portThreads.stop();
		sigThread.stop();
		Log.ger<>( CRITICAL, "Server stoped" );
	}
	catch ( GeneralException& e ) {
		Log.ger<>( CRITICAL, e );
	}

	return 0;
}
