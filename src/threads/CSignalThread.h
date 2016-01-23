//
// Created by metopa on 3.5.15.
//

#ifndef HTTP_SERVER_CSIGNALTHREAD_H
#define HTTP_SERVER_CSIGNALTHREAD_H


#include "CThreadSafeQueue.h"
#include "CRunnable.h"


/**
 * This class represents a helper thread entity.
 * The thread waits for system signals (SIGHUP, SIGINT, SIGTERM, SIGPIPE).
 * Once a signal received, the thread sets the request queue in the disabled state,
 * thereby forcing other threads to quit.
 * \see CRunnable
 */

class CSignalThread : public CRunnable {
	CThreadSafeQueue<CRequest *, nullptr> * queue_m; /** A request queue. */

public:
	CSignalThread( CThreadSafeQueue<CRequest *, nullptr> * queue );

	virtual void run() override;
};


#endif //HTTP_SERVER_CSIGNALTHREAD_H
