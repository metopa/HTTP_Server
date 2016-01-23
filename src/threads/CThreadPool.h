//
// Created by metopa on 4/17/15.
//

#ifndef HTTP_SERVER_CTHREADSTARTER_H
#define HTTP_SERVER_CTHREADSTARTER_H

#include <pthread.h>
#include <signal.h>
#include <vector>

#include "../logger.h"
#include "CRunnable.h"

/**
 * This class represents a thread pool object.
 * It is primary designed to maintain a pool of threads of the same group
 * (although, there is no real restrictions on the thread type).
 * In addition, it provides some base batch operations on threads.
 * - Join all threads in a pool
 * - Send a signal to all threads
 * - Gently stop all threads \see stop()
 * - Cancel all threads
 */
class CThreadPool {
	vector<pthread_t> threads_m;
public:
	/**
	 * Constructs a pool from a collection that consists pointers on thread objects and
	 * attempts to start these threads with an appropriate function.
	 * \param beginIter - A begin iterator of a collection.
	 * \param andIter - An end iterator of a collection.
	 * \param func - A pointer to the void*(*)(void*) function, that is in charge of the thread start.
	 */
	template<class InputIterator>
	CThreadPool( const InputIterator& beginIter, const InputIterator& endIter,
				 void * (* func)( void * ) = CRunnable::threadRunner ) {
		pthread_attr_t attr;
		pthread_attr_init( &attr );
		pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
		int retCode;

		for ( auto it = beginIter; it != endIter; it++ ) {
			threads_m.push_back( pthread_t() );
			if ( ( retCode = pthread_create( &threads_m.back(), &attr, func, (void *) &( **it ) ) ) != 0 ) {
				threads_m.pop_back();
				Log.ger<>( CRITICAL, "pthread_create: failed to create thread. Error #", CLogger::NoSpace(), retCode );
			}
		}

		pthread_attr_destroy( &attr );
	}


	/**
	 * Constructs a pool from a single thread objects and
	 * attempts to start this thread with an appropriate function.
	 * \param e - A pointer to the thread object.
	 * \param func - A pointer to the void*(*)(void*) function, that is in charge of the thread start.
	 */
	template<class T>
	CThreadPool( const T& e, void * (* func)( void * ) = CRunnable::threadRunner ) {
		pthread_attr_t attr;
		pthread_attr_init( &attr );
		pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
		int retCode;

		threads_m.push_back( pthread_t() );
		if ( ( retCode = pthread_create( &threads_m.back(), &attr, func, (void *) &( *e ) ) ) != 0 ) {
			threads_m.pop_back();
			Log.ger<>( CRITICAL, "pthread_create: failed to create thread. Error #", CLogger::NoSpace(), retCode );
		}

		pthread_attr_destroy( &attr );
	}

	/**
	 * A batch pool join.
	 */
	void join();

	/**
	 * A batch pool stop.
	 * It repeatedly sends a given signal until every thread stops.
	 * \param sigNum - A signal to send.
	 */
	void stop( int sigNum = SIGUSR1 );

	/**
	 * A batch pool cancel.
	 * \warning The cancellation of the thread can result in a resource leak.
	 */
	void cancel();

	/**
	 * Send a signal to all threads in a pool.
	 * \param sigNum - A signal to send.
	 */
	void signal( int sigNum = SIGUSR1 );

private:
	/**
	 * \param thread - A thread to be joined.
	 */
	void joinThread( pthread_t thread );

	/**
	 * \param thread - A thread to be joined.
	 * \param msec - A timeout.
	 * \return true, if thread has been joined.
	 * \return false, otherwise.
	 */
	bool timedJoinThread( pthread_t thread, uint64_t msec = 10 );

	/**
	 * \param thread - A thread to be canceled.
	 */
	void cancelThread( pthread_t thread );

	/**
	 * \param thread - A thread to which a signal will be sent
	 * \param sigNum - A signal to be sent.
	 */
	void signalThread( pthread_t thread, int sigNum = SIGUSR1 );

	/**
	 * This method stops a thread by repeatedly sending a given signal until the thread stops.
	 * \param thread - A thread t be stopped.
	 * \param sigNum -  A signal to be sent.
	 */
	void stopThread( pthread_t thread, int sigNum );
};


#endif //HTTP_SERVER_CTHREADSTARTER_H
