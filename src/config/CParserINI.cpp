//
// Created by root on 4/13/15.
//
#include "CParserINI.h"
#include <istream>

#include "../exceptions.h"
#include "../logger/CLogger.h"

CParserINI::CParserINI( istream& input, ini_struct_t& predefined ) : body_m( predefined ) {
	string buffer;
	int lineNr = 1;
	while ( !input.fail() ) {
		try {
			getline( input, buffer );
			parseLine( buffer );
		}

		catch ( INIParserException& e ) {
			Log.ger( INFO, "INI File: error at the line", lineNr, "What:", e );
		}
		lineNr++;
	}
}

void CParserINI::addParam( string id, vector<string> list ) {
	if ( currentBlock.empty() )
		throw INIParserException( "Empty block" );
	body_m[currentBlock][id] = list;
}

void CParserINI::parseLine( string& line ) {
	unsigned int pos = 0;
	skipWS( line, pos );
	if ( pos == line.size() )
		return;

	switch ( line[pos] ) {
		case ';':
		case '#':
			return;
		case '[':
			parseNewBlock( line, pos );
			return;
		default:
			string id = getID( line, pos );
			vector<string> args = getArgs( line, pos );
			addParam( id, args );
			return;
	}
}

void CParserINI::parseNewBlock( string& line, unsigned int& pos ) {
	string newBlock( "" );
	pos++;
	for ( ; pos < line.size() && isValidArgChar( line[pos] ); pos++ )
		newBlock.insert( newBlock.end(), line[pos] );
	if ( pos == line.size() )
		throw INIParserException( "End of line reached (']' expected)" );
	if ( line[pos] != ']' )
		throw INIParserException( "Unrecognized symbol (']' expected): ", line[pos] );

	currentBlock = newBlock;
}

string CParserINI::getID( string& line, unsigned int& pos ) {
	string id = getIdentifier( line, pos );
	skipWS( line, pos );
	if ( pos == line.size() )
		throw INIParserException( "End of line reached ('=' expected)" );
	if ( line[pos++] != '=' )
		throw INIParserException( "Unrecognized symbol ('=' expected): ", line[pos] );
	return id;
}

vector<string> CParserINI::getArgs( string& line, unsigned int& pos ) {
	vector<string> args;
	while ( 1 ) {
		args.push_back( getIdentifier( line, pos ) );
		if ( !getComma( line, pos ) )
			break;
	}

	return args;
}

string CParserINI::getIdentifier( string& line, unsigned int& pos ) {
	string currentArg( "" );
	int delim;

	skipWS( line, pos );
	if ( pos == line.size() )
		throw INIParserException( "End of line reached (identifier expected)" );

	if ( line[pos] == '\'' || line[pos] == '"' ) {
		delim = line[pos++];
		while ( pos < line.size() ) {
			if ( line[pos] == delim ) {
				delim = -1;
				break;
			}
			currentArg.insert( currentArg.end(), line[pos] );
			pos++;
		}

		if ( delim != -1 )
			throw INIParserException( "End of line reached (quotation mark expected)" );
		pos++;
		return currentArg;
	}

	while ( pos < line.size() ) {
		if ( isValidArgChar( line[pos] ) )
			currentArg.insert( currentArg.end(), line[pos++] );
		else
			break;
	}

	if ( currentArg.empty() )
		throw INIParserException( "Empty identifier" );

	return currentArg;
}

bool CParserINI::getComma( string& line, unsigned int& pos ) {
	skipWS( line, pos );
	if ( pos == line.size() || line[pos] == ';' || line[pos] == '#' )
		return false;
	if ( line[pos] != ',' )
		throw INIParserException( "Unrecognized symbol (',' expected): ", line[pos] );
	pos++;
	return true;
}

bool CParserINI::isValidArgChar( char c ) {
	return ( inRange( c, 'a', 'z' ) || inRange( c, 'A', 'Z' ) ||
			 inRange( c, '0', '9' ) || c == '_' );
}

void CParserINI::skipWS( string& line, unsigned int& pos ) {
	for ( ; pos < line.size() && isWS( line[pos] ); pos++ );
}

bool CParserINI::isWS( char c ) {
	return c == ' ' || c == '\t';
}

bool CParserINI::inRange( int x, int a, int b ) {
	return ( x >= a ) && ( x <= b );
}
