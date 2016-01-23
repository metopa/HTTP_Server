//
// Created by metopa on 4/18/15.
//

#ifndef HTTP_SERVER_CPROCESSORTHREAD_H
#define HTTP_SERVER_CPROCESSORTHREAD_H

#include <memory>

#include "CThreadSafeQueue.h"
#include "CRunnable.h"
#include "../requests.h"

/**
 * This class represents a worker thread entity.
 * The thread waits for the available requests in the request queue.
 * Once request received, the thread starts the whole request process cycle,
 * which includes these steps:
 *  - receive data
 *  - parse the request
 *  - load the requested resource
 *  - generate the response
 *  - send the data back
 * \see CRunnable
 */
class CWorkerThread : public CRunnable {
	int id_m;
	const char * wd_m;
	CThreadSafeQueue<CRequest *, nullptr> * queue_m;

public:
	/**
	 * Constructs a thread object.
	 * \param id - A thread ID.
	 * \param wd - NULL-terminated string, that contains configured working directory.
	 * \param queue - A pointer to the shared request queue.
	 */
	CWorkerThread( int id, const char * wd, CThreadSafeQueue<CRequest *, nullptr, 100> * queue );

	virtual void run() override;
};


#endif //HTTP_SERVER_CPROCESSORTHREAD_H
