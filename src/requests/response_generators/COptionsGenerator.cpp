//
// Created by metopa on 7.5.15.
//

#include "COptionsGenerator.h"

#include <sstream>

#include "../../globals.h"

COptionsGenerator::COptionsGenerator( const string& resource ) : CAbstractGenerator( resource, RT_OPTIONS ) {
	code_m = 200;
}

string COptionsGenerator::generate() {
	ostringstream response;

	response << "HTTP/1.1 " << code_m << ' ' << getCodeMsg( code_m ) << http_endl;
	response << "Date: " << content_m->getCreateTime() << http_endl;
	response << "Allow: GET, HEAD, OPTIONS" << http_endl;
	response << http_endl;

	return response.str();
}
