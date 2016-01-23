//
// Created by metopa on 4/17/15.
//

#ifndef HTTP_SERVER_CMUTEX_H
#define HTTP_SERVER_CMUTEX_H

#include <pthread.h>

/**
 * This class represents a mutex object.
 * It provides easy and clear high-level interface to the pthread library functions and prevents resource leaks.
 * For further information, see pthread man pages.
 */
class CMutex {
	pthread_mutex_t mutex_m;
public:
	/**
	 * Constructs a mutex object.
	 */
	CMutex();

	CMutex( const CMutex& other ) = delete;

	void operator =( const CMutex& other ) = delete;

	/**
	 * Destructs a mutex object.
	 */
	~CMutex();

	/**
	 * Locks mutex. This method is blocking.
	 *
	 */
	void lock();

	/**
	 * Tries to lock mutex. This method is non blocking.
	 *
	 * \return true, if mutex has been locked successfully.
	 */
	bool trylock();

	/**
	 * Releases locked mutex. This method is non blocking.
	 */
	void unlock();
};


#endif //HTTP_SERVER_CMUTEX_H
