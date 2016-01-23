//
// Created by metopa on 4/17/15.
//

#include "CMutex.h"

CMutex::CMutex() {
	pthread_mutex_init( &mutex_m, NULL );
}

CMutex::~CMutex() {
	pthread_mutex_destroy( &mutex_m );
}

void CMutex::lock() {
	pthread_mutex_lock( &mutex_m );
}

bool CMutex::trylock() {
	return pthread_mutex_trylock( &mutex_m ) == 0;
}

void CMutex::unlock() {
	pthread_mutex_unlock( &mutex_m );
}