//
// Created by metopa on 4/18/15.
//

#ifndef HTTP_SERVER_CRUNNABLE_H
#define HTTP_SERVER_CRUNNABLE_H

#include <memory>

/**
 * This is abstract class, that represents a single thread.
 * It provides a unified interface to start threads.
 * \see CPortThread
 * \see CWorkerThread
 * \see CSignalThread
 */
class CRunnable {
public:
	typedef std::shared_ptr<CRunnable> ptr_t;

	/**
	 * Virtual method, that is called on thread start.
	 */
	virtual void run() = 0;

	/**
	 * Static function that calls run() method.
	 */
	static void * threadRunner( void * ptr );

	/**
	 * A virtual destructor.
	 */
	virtual ~CRunnable() { };
};


#endif //HTTP_SERVER_CRUNNABLE_H
