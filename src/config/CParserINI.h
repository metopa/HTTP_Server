//
// Created by root on 4/13/15.
//

#ifndef HTTP_SERVER_INI_PARSER_H
#define HTTP_SERVER_INI_PARSER_H

#include <string>
#include <vector>
#include "../globals.h"

using namespace std;


/**
 * This class represents a parser that processes INI format structure and
 * returns parsed data in ini_struct_t data type.
 */
class CParserINI {
	ini_struct_t body_m;
	string currentBlock;

public:
	/**
	 * Constructor that parses data.
	 */
	CParserINI( istream& input, ini_struct_t& predefined );

	operator ini_struct_t() {
		return body_m;
	}

private:
	/**
	 * This method saves a new parameter.
	 * \param id - The name of the parameter.
	 * \param list - The arguments of th parameter.
	 */
	void addParam( string id, vector<string> list );

	/**
	 * This method parses a single line.
	 * \param A string to be parsed.
	 */
	void parseLine( string& line );

	/**
	 * This method parses the line that was recognized as a new block name.
	 * \param line - A line to be parses.
	 * \param pos - The current position in the line, that will be altered in this method.
	 */
	void parseNewBlock( string& line, unsigned int& pos );

	/**
	 * This method parses the line that was recognized as a new parameter and returns the parameter's name.
	 * \param line - A line to be parses.
	 * \param pos - The current position in the line, that will be altered in this method.
	 * \return The string that contains a name of the parameter.
	 */
	string getID( string& line, unsigned int& pos );

	/**
	 * This method parses the line that was recognized as a new parameter and returns the parameter's arguments.
	 * \param line - A line to be parses.
	 * \param pos - The current position in the line, that will be altered in this method.
	 * \return THe vector of string that contains arguments of the parameter.
	 */
	vector<string> getArgs( string& line, unsigned int& pos );

	/**
	 * This method extracts a single identifier from the line.
	 * As an identifier is considered any sequence that consists from [A-Z][a-z][0-9] and underscore symbol or
	 * any char sequence (excluding newline symbol) in quotes.
	 * \param line - A line to be parses.
	 * \param pos - The current position in the line, that will be altered in this method.
	 * \return The extracted identifier.
	 */
	string getIdentifier( string& line, unsigned int& pos );

	/**
	 * This method parses the line that was recognized as a new block name.
	 * \param line - A line to be parses.
	 * \param pos - THe current position in the line, that will be altered in this method.
	 */
	bool getComma( string& line, unsigned int& pos );

	/**
	 * This method tests if the character is a valid character for an unquoted identifier.
	 * \param c - A char to be tested.
	 * \return true, if char is in one of those ranges: [A-Z][a-z][0-9].
	 * \return false, otherwise.
	 */
	bool isValidArgChar( char c );

	/**
	 * This method tests if the character is a whitespace character.
	 * \param c - A char to be tested.
	 * \return true, if char is a space or a tabulator.
	 * \return false, otherwise.
	 */
	bool isWS( char c );

	/**
	 * This method skips whitespace characters in the line.
	 * \param line - A line to be parses.
	 * \param pos - The current position in the line, that will be altered in this method.
	 */
	void skipWS( string& line, unsigned int& pos );

	/**
	 * \return true, if a <= x <= b.
	 * \return false, otherwise.
	 */
	bool inRange( int x, int a, int b );
};


#endif //HTTP_SERVER_INI_PARSER_H
