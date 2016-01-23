//
// Created by metopa on 7.5.15.
//

#include "CStringContent.h"
#include "CHTMLGenerator.h"

void CStringContent::load() {
	string rawHtml = CHTMLGenerator( msg_m ).enlarge( 2 ).wrap( msg_m );
	size_m = rawHtml.size();
	data_m.insert( data_m.begin(), rawHtml.begin(), rawHtml.end() );
	creationTime();
}

const char * CStringContent::getModTime() const {
	return getCreateTime();
}
