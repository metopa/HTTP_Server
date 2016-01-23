//
// Created by metopa on 4/17/15.
//

#ifndef HTTP_SERVER_CTHREADSAFESTACK_H
#define HTTP_SERVER_CTHREADSAFESTACK_H

#include "primitives/CSem.h"
#include "primitives/CMutex.h"
#include "../requests.h"

/**
 * This class represents a template concurrent queue abstract data type.
 * It provides an easy and clear thread-safe communication interface between producing and consuming threads.
 * It can transfer data and commands (quit-command only) between threads.
 * The queue turns into disabled state as soon as there are no more producers left or it is manually disabled.
 * When it is disabled, no more pushes can be made (it results in fail).
 * If in addition the queue is empty, every pop() call fails as well and defVal template value is returned.
 * This queue has limited capacity.
 *
 */

template<class T, T defVal = T(), unsigned int TArraySize = 100>
class CThreadSafeQueue {
	T array_m[TArraySize];
	/**< A queue storage.*/
	unsigned int writeIndex_m;
	/**< The next push position in a storage.*/
	unsigned int readIndex_m;
	/**< The next pop position in a storage.*/

	CMutex mutex_m;
	/**< A global mutex*/
	CSem semEmpty_m;
	/**< A semaphore that blocks consumers.*/
	CSem semFull_m;
	/**< A semaphore that blocks producers.*/

	unsigned long activeProducers_m;
	/**< A producers' counter. The queue will be disabled as soon as this counter reaches zero.*/
	bool isDisabled_m; /**< Indicates that queue is disabled and thus no new data can be pushed.*/

public:
	/**
	 * Constructs queue
	 * \param activeProducers - the total count of producers for this queue.
	 */
	CThreadSafeQueue( unsigned long activeProducers );

	/**
	 * Pushes new element into queue.
	 * This method blocks thread if queue is full.
	 * \return true, if push succeeded.
	 * \return false, if queue has been disabled and thus push failed.
	 */
	bool push( const T& e );

	/**
	 * Pops and returns the next element in the queue.
	 * This method blocks thread, if queue is empty.
	 * \return defVal, if queue was disabled.
	 */
	T pop();

	/**
	 * Manually disables queue.
	 */
	void disable();

	/**
	 * Decrements producers' count.
	 */
	void notifyProducerStopped();
};

template<class T, T defVal, unsigned int TArraySize>
CThreadSafeQueue<T, defVal, TArraySize>::CThreadSafeQueue( unsigned long activeProducers ) :
		writeIndex_m( 0 ), readIndex_m( 0 ),
		semEmpty_m( 0 ), semFull_m( TArraySize ),
		activeProducers_m( activeProducers ), isDisabled_m( false ) { }

template<class T, T defVal, unsigned int TArraySize>
bool CThreadSafeQueue<T, defVal, TArraySize>::push( T const& e ) {
	semFull_m.wait();
	mutex_m.lock();
	if ( isDisabled_m ) {
		semFull_m.post();
		mutex_m.unlock();
		return false;
	}
	else {
		array_m[writeIndex_m] = e;
		writeIndex_m = ( writeIndex_m + 1 ) % TArraySize;
		mutex_m.unlock();
		semEmpty_m.post();
		return true;
	}
}

template<class T, T defVal, unsigned int TArraySize>
T CThreadSafeQueue<T, defVal, TArraySize>::pop() {
	semEmpty_m.wait();
	mutex_m.lock();
	if ( !isDisabled_m || readIndex_m != writeIndex_m ) {
		T e = array_m[readIndex_m];
		readIndex_m = ( readIndex_m + 1 ) % TArraySize;
		mutex_m.unlock();
		semFull_m.post();
		return e;
	}
	else {
		mutex_m.unlock();
		semEmpty_m.post();
		return defVal;
	}
}

template<class T, T defVal, unsigned int TArraySize>
void CThreadSafeQueue<T, defVal, TArraySize>::disable() {
	isDisabled_m = true;
	semEmpty_m.post();
	semFull_m.post();
}

template<class T, T defVal, unsigned int TArraySize>
void CThreadSafeQueue<T, defVal, TArraySize>::notifyProducerStopped() {
	mutex_m.lock();
	activeProducers_m--;
	mutex_m.unlock();
	if ( activeProducers_m == 0 )
		disable();
}

#endif //HTTP_SERVER_CTHREADSAFESTACK_H
