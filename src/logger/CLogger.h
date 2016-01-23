//
// Created by metopa on 28.4.15.
//

#ifndef HTTP_SERVER_CLOGGER_H
#define HTTP_SERVER_CLOGGER_H

#include <chrono>
#include <ostream>

#include "../threads/primitives/CMutex.h"
#include "ELogFlags.h"
#include "../config.h"

using namespace std;
using namespace chrono;

/**
 * This class represents a global logger object.
 * It provides unified interface for logging various events through a template method ger() (because log.ger()) which is thread-safe.
 * Event types are defined in the ELogFlags enumeration type.
 * The events that will be logged are configured through the configuration file.
 */
class CLogger {
	ostream * logStream_m;
	/**< A pointer to the output stream object, in which the log will be written out. */
	bool logStreamIsCOUT;
	/**< Defines if an output stream should be freed on object destruction. */
	CMutex mutex_m;
	/**< A global mutex for a thread safety. */
	int pid_m;
	/**< A process ID that is used for logging. */
	bool initialized_m; /**< Determines if an object is fully constructed. It is necessary because of the fact that the global object needs to be initialized with data that will be available only at a runtime (after processing a configuration file). */
public:

	/**
	 * This class is used an argument for a ger() method.
	 * It indicates that the space before the next argument will be omitted.
	 */
	class NoSpace {
	};

	/**
	 * Partially constructs a logger object.
	 * \see init()
	 */
	CLogger();

	~CLogger();

	/**
	 * This method completes the construction of the object.
	 * \param logFile - The name of the file in which the log will be writen (can be "stdout").
	 */
	void init( const string& logFile );

	/**
	 * This method prints a welcome string into a log output.
	 */
	void welcome();

	/**
	 * This method prints a standard error message into a log output.
	 * \param level - The type of the log event.
	 * \param errNo - The number of an error to be logged.
	 */
	void error( ELogFlags level, int errNo );

	/**
	 * This method prints a list of logging events into a log output.
	 */
	void options();

	/**
	 * This method prints a statistic data about a processed request into a log output.
	 * \param port - The number of the port on which the request has been accepted.
	 * \param time - The time when the request has been accepted.
	 * \param input - A reference to the received data.
	 * \param output - A reference to the generated data.
	 */
	void printStatistic( int port, const high_resolution_clock::time_point& time, const string& input,
						 const string& output );

	/**
	 * This is a variadic template method that provides an easy way to print a log message with any number of arguments.
	 * This method is thread-safe.
	 * \param level - The type of the log event.
	 * \param args - Any count of the arguments of any type that will be logged. Arguments are separated with a space (to omit a single space add NoSpace object as an argument). The only restriction on argument type is the existence of the overloaded operator << (ostream&, TYPE).
	 */
	template<class... Args>
	void ger( ELogFlags level, const Args& ... args ) {
		if ( !initialized_m || config.checkLogFlag( level ) ) {
			mutex_m.lock();
			printTimestamp();
			*logStream_m << '\t' << logflagsNS::logFlagsToStringPrintable( level ) << ' ';
			print( args... );
			*logStream_m << endl;
			mutex_m.unlock();
		}
	}

	/**
	 * This method flushes the log stream.
	 */
	void flush() {
		logStream_m->flush();
	}

private:
	/**
	 * This method prints a process id and current date and time into a log output.
	 */
	void printTimestamp();

	/**
	 * \name The following functions are used for a meta generation of a variadic template.
	*/

	//@{
	template<class T, class... Args>
	inline void print( const T& a, const Args& ... args ) {
		*logStream_m << a;
		printSpace( args... );
	}

	template<class... Args>
	inline void print( NoSpace ns, const Args& ... args ) {
		print( args... );
	}

	inline void print() { };

	template<class... Args>
	inline void printSpace( const Args& ... args ) {
		*logStream_m << ' ';
		print( args... );
	}

	template<class... Args>
	inline void printSpace( NoSpace ns, const Args& ... args ) {
		print( args... );
	}

	inline void printSpace() { };
	//@}
};

extern CLogger Log;

#endif //HTTP_SERVER_CLOGGER_H
