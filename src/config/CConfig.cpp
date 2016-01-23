//
// Created by metopa on 28.4.15.
//
#include "CConfig.h"

#include <list>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "CParserINI.h"
#include "../exceptions.h"

CConfig config;

CConfig::CConfig() { }

void CConfig::load( int argc, char * argv[] ) {
	const char * iniFile;
	if ( argc > 1 )
		iniFile = argv[1];
	else
		iniFile = DEFAULT_INIFILE;

	ifstream ifile( iniFile );
	if ( !ifile.is_open() )
		throw FileNotFoundException( iniFile, MSG_CRIT_ERR );

	ini_struct_t defVals;
	loadDefVals( defVals );
	parse( CParserINI( ifile, defVals ) );
}

bool * CConfig::getLogFlags() {
	return logFlags_m;
}

bool CConfig::checkLogFlag( ELogFlags e ) {
	return logFlags_m[e];
}


bool CConfig::checkMethod( EMethodType e ) {
	if ( e == RT_OPTIONS )
		return false;  //nobody cares
	return allowedMethods_m[e];
}


bool CConfig::checkRegExt( const string& ext ) {
	return regExeExt_m.find( ext ) != regExeExt_m.end();
}

bool CConfig::checkScriptExt( const string& ext ) {
	return scriptExeExt_m.find( ext ) != scriptExeExt_m.end();
}

vector<string>& CConfig::getPorts() {
	return ports_m;
}

unsigned long CConfig::getPortCount() const {
	return ports_m.size();
}

string const& CConfig::getWorkDir() {
	return workDir_m;
}

string const& CConfig::getLogFile() {
	return logFile_m;
}

unsigned long CConfig::getWorkerCount() const {
	return workerCount_m;
}

const vector<pair<string, string>>& CConfig::getFileMappings() {
	return fileMapping_m;
}

ostream& operator <<( ostream& out, CConfig& c ) {
	out << "Ports:";
	for ( auto it = c.getPorts().begin(); it != c.getPorts().end(); it++ ) {
		out << ' ' << *it;
	}
	out << endl;

	out << "Working directory: " << c.getWorkDir() << endl;

	out << "Logger flags:";
	for ( int i = 0; i < E_LOG_FLAGS_MAX; i++ )
		if ( c.logFlags_m[i] )
			out << ' ' << logflagsNS::logFlagsToString( (ELogFlags) i );

	out << endl;
	return out;
}

void CConfig::parse( ini_struct_t data ) {
	auto section = data.find( "options" );
	if ( section == data.end() )
		throw BlockUndefinedException( "options", MSG_CRIT_ERR );

	parseOptions( section );

	section = data.find( "logger" );
	if ( section == data.end() ) {
		cout << BlockUndefinedException( "logger", "Default value: \"CRITICAL\"" ) << endl;
		logFlags_m[CRITICAL] = true;
	}
	else {
		try {
			logFile_m = section->second.at( "logfile" ).front();
		}
		catch ( out_of_range& e ) {
			logFile_m = "stdout";
		}
		try {
			parseLogger( section );
		}
		catch ( ParamUndefinedException& e ) {
			logFlags_m[CRITICAL] = true;
		}
	}

	section = data.find( "path_mapping" );
	if ( section != data.end() )
		parseMapper( section );

	section = data.find( "executables" );
	if ( section != data.end() )
		parseExec( section );
}

void CConfig::parseOptions( map<string, map<string, vector<string>>>::iterator& data ) {
	try {
		ports_m = data->second.at( "ports" );
	}
	catch ( out_of_range& e ) {
		throw ParamUndefinedException( "ports", MSG_CRIT_ERR );
	}

	try {
		workDir_m = *( data->second.at( "wd" ).begin() );
	}
	catch ( out_of_range& e ) {
		throw ParamUndefinedException( "wd", MSG_CRIT_ERR );
	}

	try {
		string p = *( data->second.at( "workers" ).begin() );
		if ( sscanf( p.c_str(), "%d", &workerCount_m ) != 1 || workerCount_m < 1 ) {
			workerCount_m = 1;
			throw ParamUndefinedException( "workers", "default: 1" );
		}
	}
	catch ( out_of_range& e ) {
		workerCount_m = 1;
		throw ParamUndefinedException( "workers", "default: 1" );
	}

	try {
		vector<string> req = data->second.at( "accepted_methods" );
		for ( int i = 0; i < RT_MAXENUM; i++ )
			allowedMethods_m[i] = false;

		for ( auto it = req.begin(); it != req.end(); it++ ) {
			EMethodType current = methodTypeNS::methodFromString( *it );
			if ( current == RT_ALL ) {
				for ( int i = 0; i < RT_MAXENUM; i++ )
					allowedMethods_m[i] = true;
				break;
			}
			else
				allowedMethods_m[methodTypeNS::methodFromString( *it )] = true;
		}
	}
	catch ( out_of_range& e ) {
		throw ParamUndefinedException( "accepted_methods", "default: \"ALL\"" );
	}
}

void CConfig::parseLogger( map<string, map<string, vector<string>>>::iterator& data ) {
	try {
		vector<string> flags = data->second.at( "flags" );
		for ( int i = 0; i < E_LOG_FLAGS_MAX; i++ )
			logFlags_m[i] = false;

		for ( auto it = flags.begin(); it != flags.end(); it++ ) {
			ELogFlags eLogFlags = logflagsNS::logFlagsFromString( *it );

			switch ( eLogFlags ) {
				case SILENT:
					for ( int i = 0; i < E_LOG_FLAGS_MAX; i++ )
						logFlags_m[i] = false;
					break;

				case DEBUG_ALL:
					for ( int i = SILENT + 1; i < UNDEFINED; i++ )
						logFlags_m[i] = true;
					break;

				case UNDEFINED:
					break;

				default:
					logFlags_m[eLogFlags] = true;
					break;
			}
		}
	}
	catch ( out_of_range& e ) {
		throw ParamUndefinedException( "flags", "default: \"CRITICAL\"" );
	}
}

void CConfig::parseMapper( map<string, map<string, vector<string>>>::iterator& data ) {
	for ( auto it = data->second.begin(); it != data->second.end(); it++ )
		fileMapping_m.push_back( make_pair( it->first, it->second.front() ) );

	auto comp = []( const pair<string, string>& a, const pair<string, string>& b ) -> bool {
		return a.first.length() > b.first.length();
	};

	sort( fileMapping_m.begin(), fileMapping_m.end(), comp );
}

void CConfig::parseExec( map<string, map<string, vector<string>>>::iterator& data ) {
	auto it = data->second.find( "regular_exe_ext" );
	if ( it != data->second.end() ) {
		regExeExt_m.insert( it->second.begin(), it->second.end() );
	}
	it = data->second.find( "script_exe_ext" );
	if ( it != data->second.end() ) {
		scriptExeExt_m.insert( it->second.begin(), it->second.end() );
	}

}

void CConfig::loadDefVals( ini_struct_t& defVals ) {
	defVals = {{"options", {
								   {"workers", {"1"}},
								   {"accepted_methods", {"ALL"}}
						   }
			   },
			   {"logger",  {
								   {"logfile", {DEFAULT_LOGFILE}},
								   {"flags",            {"CRITICAL", "INFO"}}
						   }
			   }
	};
}

