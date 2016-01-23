//
// Created by metopa on 4/17/15.
//

#ifndef HTTP_SERVER_CSEMAPHORE_H
#define HTTP_SERVER_CSEMAPHORE_H

#include <semaphore.h>

/**
 * This class represents a semaphore object.
 * It provides easy and clear high-level interface to the pthread library functions and prevents resource leaks.
 * For further information, see pthread man pages.
 */

class CSem {
	sem_t sem_m;

	CSem( const CSem& other ) { };

public:
	/**
	 * Constructs a semaphore object.
	 * \param value - A semaphore counter initial value.
	 */
	CSem( unsigned int value );

	CSem( CSem& other ) = delete;

	CSem& operator =( CSem& other ) = delete;

	/**
	 * Destructs a semaphore object.
	 */
	~CSem();

	/**
	 * Decrements semaphore counter. The calling thread is blocked if counter value is zero.
	 */
	void wait();

	/**
	 * Increments semaphore counter. This method is non blocking.
	 */
	void post();
};

#endif //HTTP_SERVER_CSEMAPHORE_H
