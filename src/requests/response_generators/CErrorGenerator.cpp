//
// Created by metopa on 7.5.15.
//

#include "CErrorGenerator.h"

#include <sstream>

#include "../../content/CStringContent.h"
#include "../../globals.h"

CErrorGenerator::CErrorGenerator( int code ) {
	code_m = code;
	content_m = new CStringContent( getCodeMsg( code_m ) );
	content_m->load();
}

string CErrorGenerator::generate() {
	ostringstream response;

	response << "HTTP/1.1 " << code_m << ' ' << getCodeMsg( code_m ) << http_endl;
	response << "Date: " << content_m->getCreateTime() << http_endl;
	response << "Last-Modified: " << content_m->getModTime() << http_endl;
	response << "Content-Length: " << content_m->getSize() << http_endl;
	response << http_endl;
	for ( auto it : content_m->getData() )
		response.put( it );

	return response.str();
}
