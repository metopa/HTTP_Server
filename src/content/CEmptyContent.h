//
// Created by metopa on 7.5.15.
//

#ifndef HTTP_SERVER_CEMPTYCONTENT_H
#define HTTP_SERVER_CEMPTYCONTENT_H


#include "CAbstractContent.h"

/**
 * This class represents a content generator entity.
 * It generates an empty HTML page.
 */
class CEmptyContent : public CAbstractContent {

public:
	virtual void load() override;

	virtual const char * getModTime() const override;
};


#endif //HTTP_SERVER_CEMPTYCONTENT_H
