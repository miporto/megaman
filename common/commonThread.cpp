#include <pthread.h>

#include "commonThread.h"

Thread::Thread() {}

void* Thread::runner(void *data) {
	Thread *self = (Thread*)data;
	self->run();
	
	return NULL;
}

int Thread::start() {
	return pthread_create(&thread, NULL, Thread::runner, this);
}

void Thread::join() {
	pthread_join(thread, NULL);
}

Thread::~Thread() {}

Mutex::Mutex() {
	pthread_mutex_init(&this->mutex, NULL);	
}

void Mutex::lock() {
	pthread_mutex_lock(&this->mutex);
}

void Mutex::unlock() {
	pthread_mutex_unlock(&this->mutex);
}
        
Mutex::~Mutex() {
	pthread_mutex_destroy(&this->mutex);
}

Lock::Lock(Mutex &m) : m(m) {
	m.lock();
}

Lock::~Lock() {
	m.unlock();
}
