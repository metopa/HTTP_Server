//
// Created by metopa on 7.5.15.
//

#include "CHTMLGenerator.h"

CHTMLGenerator::CHTMLGenerator( const string& data, int sortPriority )
		: data_m( data ), sortPriority_m( sortPriority ) { }

CHTMLGenerator& CHTMLGenerator::applyAttr( const string& attr ) {
	data_m = '<' + attr + '>' + data_m + '<' + '/' + attr + '>';
	return *this;
}

CHTMLGenerator& CHTMLGenerator::applyAttr( const string& attr, const string& param ) {
	data_m = '<' + attr + ' ' + param + '>' + data_m + '<' + '/' + attr + '>';
	return *this;
}

CHTMLGenerator& CHTMLGenerator::append( const CHTMLGenerator& other ) {
	data_m += other.data_m;
	return *this;
}

CHTMLGenerator& CHTMLGenerator::append( const string& str ) {
	data_m += str;
	return *this;
}

CHTMLGenerator& CHTMLGenerator::append( char c ) {
	data_m += c;
	return *this;
}

CHTMLGenerator& CHTMLGenerator::makeHyperlink( const string& path ) {
	data_m = "<a href=\"" + path + "\">" + data_m + "</a>";
	return *this;
}

CHTMLGenerator& CHTMLGenerator::makeTable( vector<CHTMLGenerator>& entries ) {
	CHTMLGenerator current;
	for ( auto it : entries ) {
		current = it;
		current.applyAttr( "td" ).applyAttr( "tr" ).append( '\n' );
		append( current );
	}
	applyAttr( "table" );

	return *this;
}

CHTMLGenerator& CHTMLGenerator::enlarge( int sizeDelta ) {
	char buf[10];
	sprintf( buf, "%d", 6 + sizeDelta * 2 );
	applyAttr( "font", "size=" + string( buf ) );
	return *this;
}


CHTMLGenerator& CHTMLGenerator::substituteNL() {
	unsigned long int n = 0;
	string htmlNL = "<br>";
	while ( ( n = data_m.find( '\n', n ) ) != data_m.npos ) {
		data_m.insert( n, htmlNL );
		n += htmlNL.size() + 1;
	}
	return *this;
}

string CHTMLGenerator::wrap( const string& title ) {
	return "<html>\n"
				   "  <head>\n"
				   "    <title>" + title + "</title>\n"
				   "  </head>\n"
				   "  <body>\n      " +
		   data_m + "\n"
				   "  </body>\n"
				   "</html>";
}


void CHTMLGenerator::setPriority( int newPriority ) {
	sortPriority_m = newPriority;
}

bool CHTMLGenerator::operator <( const CHTMLGenerator& other ) const {
	if ( sortPriority_m != other.sortPriority_m )
		return sortPriority_m < other.sortPriority_m;
	return data_m.compare( other.data_m ) < 0;
}
