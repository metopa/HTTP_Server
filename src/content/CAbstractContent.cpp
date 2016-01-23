//
// Created by metopa on 5.5.15.
//

#include "CAbstractContent.h"
#include <ctime>

CAbstractContent::CAbstractContent( const string& userPath, const string& realPath )
		: userPath_m( userPath ), realPath_m( realPath ) { }

CAbstractContent::CAbstractContent() {
	size_m = 0;
}

CAbstractContent::~CAbstractContent() { }

size_t CAbstractContent::getSize() const {
	return size_m;
}

const char * CAbstractContent::getCreateTime() const {
	return createTime_m;
}

const char * CAbstractContent::getModTime() const {
	return modTime_m;
}

const vector<uint8_t>& CAbstractContent::getData() const {
	return data_m;
}

void CAbstractContent::creationTime() {
	time_t ltime;
	tm result;

	ltime = time( NULL );
	localtime_r( &ltime, &result );
	asctime_r( &result, createTime_m );

	for ( int i = 1; i < 32; i++ )
		if ( !createTime_m[i] ) {
			createTime_m[i - 1] = 0;
			break;
		}
}
