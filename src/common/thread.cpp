/*
 * Implemetation of class Thread
 */

#include"thread.h"

void* Thread::thr_run(void *r) {

	int ret = ((Thread *) r)->run();
	pthread_exit(0);
}
