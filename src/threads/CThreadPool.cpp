//
// Created by metopa on 4/17/15.
//

#include "CThreadPool.h"

void CThreadPool::join() {
	for ( auto i : threads_m )
		joinThread( i );
}

void CThreadPool::cancel() {
	for ( auto i : threads_m )
		cancelThread( i );
}

void CThreadPool::signal( int sigNum ) {
	for ( auto i : threads_m )
		signalThread( i, sigNum );
}

void CThreadPool::stop( int sigNum ) {
	for ( auto i : threads_m )
		stopThread( i, sigNum );
}

void CThreadPool::joinThread( pthread_t thread ) {
	pthread_join( thread, NULL );
}

bool CThreadPool::timedJoinThread( pthread_t thread, uint64_t msec ) {
	struct timespec ts;
	ts.tv_sec = (int) ( msec / 1000 );
	ts.tv_nsec = ( msec % 1000 ) * 1000000;
	return pthread_timedjoin_np( thread, NULL, &ts ) == 0;
}

void CThreadPool::cancelThread( pthread_t thread ) {
	pthread_cancel( thread );
}

void CThreadPool::signalThread( pthread_t thread, int sigNum ) {
	pthread_kill( thread, sigNum );
}

void CThreadPool::stopThread( pthread_t thread, int sigNum ) {
	do {
		signalThread( thread, sigNum );
	} while ( !timedJoinThread( thread ) );
}
