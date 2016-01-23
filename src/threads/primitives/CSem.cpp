//
// Created by metopa on 4/17/15.
//

#include "CSem.h"

CSem::CSem( unsigned int value ) {
	sem_init( &sem_m, 0, value );
}

CSem::~CSem() {
	sem_destroy( &sem_m );
}

void CSem::wait() {
	sem_wait( &sem_m );
}

void CSem::post() {
	sem_post( &sem_m );
}





