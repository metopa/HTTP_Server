//
// Created by metopa on 4/18/15.
//

#ifndef HTTP_SERVER_CPORTTHREAD_H
#define HTTP_SERVER_CPORTTHREAD_H

#include "CThreadSafeQueue.h"
#include "CRunnable.h"
#include "../network/CPortObtainer.h"

/**
 * This class represents a listener thread entity.
 * The thread listens for incoming connections on a port socket.
 * Once a new connection received, the thread pushes it into the request queue
 * and starts to listen again.
 *
 * \see CRunnable
 */
class CPortThread : public CRunnable {
	int id_m;
	/**< The thread ID. */
	CPortObtainer socket_m;
	/** The socket to be listened. */
	const char * port_m;
	/** The port to be listened. */
	CThreadSafeQueue<CRequest *, nullptr> * queue_m; /** A request queue. */

public:
	CPortThread( int id, char const * port, int connsPerPort, CThreadSafeQueue<CRequest *, nullptr> * queue );

	virtual void run() override;
};


#endif
