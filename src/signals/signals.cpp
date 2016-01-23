//
// Created by metopa on 30.4.15.
//

#include "signals.h"

#include <cstring>

void signalNS::initSignalMask( sigset_t& sig ) {
	sigemptyset( &sig );
	sigaddset( &sig, SIGHUP );
	sigaddset( &sig, SIGINT );
	sigaddset( &sig, SIGTERM );
	sigaddset( &sig, SIGPIPE );
}

void signalNS::blockSignals() {
	sigset_t signalMask;
	initSignalMask( signalMask );
	pthread_sigmask( SIG_BLOCK, &signalMask, nullptr );
}

int signalNS::sigWait() {
	int signal = -1;
	sigset_t signalMask;
	initSignalMask( signalMask );
	sigaddset( &signalMask, SIGUSR1 );

	sigwait( &signalMask, &signal );
	return signal;
}

void ::signalNS::emptyHandler( int sigNum ) {
}

void ::signalNS::setEmptyHandler( int sigNum ) {
	struct sigaction sa;
	memset( (void *) &sa, 0, sizeof( sa ) );

	sa.sa_handler = emptyHandler;

	sigaction( sigNum, &sa, nullptr );
}
