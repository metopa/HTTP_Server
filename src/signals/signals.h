//
// Created by metopa on 30.4.15.
//

#ifndef HTTP_SERVER_CSIGNALWRAPPER_H
#define HTTP_SERVER_CSIGNALWRAPPER_H

#include <csignal>

/**
 * This namespace contains functions, that wraps low-level system calls
 * related to the system signals maintaining.
 */
namespace signalNS {
	/**
	 * An internal function.
	 * Initializes a sigset_t variable with an appropriate values.
	 * \param sig - A sigset_t variable to be initialized.
	 */
	void initSignalMask( sigset_t& sig );

	/**
	 * This function blocks signals that will not be handled in a caller thread. \see initSignalMask
	 */
	void blockSignals();

	/**
	 * An internal function.
	 * Is used as an empty handler for a signal.
	 */
	void emptyHandler( int sigNum );

	/**
	 * This function sets an empty handler that will be invoked on a signal sigNum delivery.
	 * \param sigNum - a signal to be handled.
	 */
	void setEmptyHandler( int sigNum );

	/**
	 * This function wraps a system sigwait() function.
	 * It blocks caller thread until one of the signals would be caught.
	 * \see initSignalMask
	 * \return A number of the signal that has been caught.
	 */
	int sigWait();
}
#endif //HTTP_SERVER_CSIGNALWRAPPER_H
