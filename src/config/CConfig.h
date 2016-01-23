//
// Created by metopa on 4/22/15.
//

#ifndef HTTP_SERVER_CCONFIG_H
#define HTTP_SERVER_CCONFIG_H

#include "../globals.h"
#include <vector>
#include <string>
#include <set>
#include "../logger/ELogFlags.h"
#include "../requests/EMethodType.h"


using namespace std;

/**
 * This class represents global object that stores configured settings
 * and provides them at a global scope.
 */

class CConfig {
	bool logFlags_m[E_LOG_FLAGS_MAX];
	/**< A boolean array that contains allowed logger flags*/
	bool allowedMethods_m[RT_MAXENUM];
	/**< A boolean array that contains allowed HTTP methods*/
	vector<string> ports_m;
	string workDir_m;
	string logFile_m;
	int workerCount_m;
	vector<pair<string, string>> fileMapping_m;
	set<string> regExeExt_m;
	set<string> scriptExeExt_m;
public:
	/**
	 * Default constructor.
	 * Does nothing because real initialization is taking place i load() method.
	 */
	CConfig();

	/**
	 * Loads configuration file, parses it and sets up parameters.
	 */
	void load( int argc, char * argv[] );

	/**
	 * \return A boolean array that contains allowed logger flags.
	 * \see CLogger
	 */
	bool * getLogFlags();

	/**
	 * Checks if logger flag is allowed.
	 */
	bool checkLogFlag( ELogFlags e );

	/**
	 * Checks if HTTP method is allowed.
	 */
	bool checkMethod( EMethodType e );

	/**
	 * Checks if file with provided extension should be threatened as a regular executable program.
	 */
	bool checkRegExt( const string& ext );

	/**
	 * Checks if file with provided extension should be threatened as a bash script.
	 */
	bool checkScriptExt( const string& ext );

	/**
	 * \return The ports that should be listened.
	 */
	vector<string>& getPorts();

	/**
	 * \return The total count of ports that should be listened.
	 */
	unsigned long getPortCount() const;

	/**
	 * \return The server root directory.
	 */
	string const& getWorkDir();

	/**
	 * \return The path to the file in which the log information will be writen.
	 */
	string const& getLogFile();

	/**
	 * \return The total count of worker threads to be created.
	 */
	unsigned long getWorkerCount() const;

	/**
	 * \return The list of the path substitutions settings.
	 * \see CPathResolver
	 */
	const vector<pair<string, string>>& getFileMappings();

	friend ostream& operator <<( ostream& out, CConfig& c );

private:
	/**
	 * This method parses INI structure and initializes internal attributes.
	 */
	void parse( ini_struct_t data );

	/**
	 * This method parses the [options] block of the INI structure and initializes internal attributes.
	 */
	void parseOptions( ini_struct_t::iterator& data );

	/**
	 * This method parses the [logger] block of the INI structure and initializes internal attributes.
	 */
	void parseLogger( ini_struct_t::iterator& data );

	/**
	 * This method parses the [path_mapping] block of the INI structure and initializes internal attributes.
	 */
	void parseMapper( ini_struct_t::iterator& data );

	/**
	 * This method parses the [executables] block of the INI structure and initializes internal attributes.
	 */
	void parseExec( ini_struct_t::iterator& data );

	/**
	 * This method initializes an INI structure with the default values.
	 */
	void loadDefVals( ini_struct_t& defVals );
};

extern CConfig config;

#endif //HTTP_SERVER_CCONFIG_H
