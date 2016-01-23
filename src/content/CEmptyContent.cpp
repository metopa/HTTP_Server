//
// Created by metopa on 7.5.15.
//

#include "CEmptyContent.h"


void CEmptyContent::load() {
	creationTime();
}

const char * CEmptyContent::getModTime() const {
	return getCreateTime();
}
