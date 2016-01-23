//
// Created by metopa on 7.5.15.
//

#include "CAbstractGenerator.h"

#include "../../content/CPathResolver.h"
#include "../../content/CFileContent.h"
#include "../../content/CDirContent.h"
#include "../../content/CExternalContent.h"
#include "../../exceptions/request/MethodProhibitedException.h"
#include "../../config.h"

const char * CAbstractGenerator::getCodeMsg( int code ) {
	switch ( code ) {
		case 200:
			return "OK";
		case 400:
			return "Bad Request";
		case 403:
			return "Forbidden";
		case 404:
			return "Not Found";
		case 405:
			return "Method Not Allowed";
		case 409:
			return "Conflict";
		case 501:
			return "Not Implemented";
		case 503:
			return "Service Unavailable";
		default:
			return "Other Code";
	}
}

CAbstractGenerator::CAbstractGenerator( const string& resource, EMethodType method ) {
	if ( !config.checkMethod( method ) )
		throw MethodProhibitedException( method );
	code_m = 0;
	content_m = nullptr;
	resource_m = resource;
	EFileType ft;
	realPath_m = pathResolver.resolve( resource_m, ft );
	switch ( ft ) {
		case FT_REGULAR:
			content_m = new CFileContent( resource_m, realPath_m );
			break;
		case FT_DIRECTORY:
			content_m = new CDirContent( resource_m, realPath_m );
			break;
		case FT_EXECUTABLE:
			content_m = new CExternalContent( resource_m, realPath_m, false );
			break;
		case FT_SCRIPT:
			content_m = new CExternalContent( resource_m, realPath_m, true );
			break;
	}

	content_m->load();
}

CAbstractGenerator::CAbstractGenerator() {
	code_m = 0;
	content_m = nullptr;
}

CAbstractGenerator::~CAbstractGenerator() {
	delete content_m;
}
