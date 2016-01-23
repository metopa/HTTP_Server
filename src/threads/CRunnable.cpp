//
// Created by metopa on 4/18/15.
//

#include "CRunnable.h"

void * CRunnable::threadRunner( void * ptr ) {
	( (CRunnable *) ptr )->run();
	return nullptr;
}