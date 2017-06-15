#include <pthread.h>

#include "condition.h"

int condition_init(condition_t *cond)
{
	int stat;
	if ( (stat=pthread_mutex_init(&cond->mutex, NULL)) != 0 )
		return stat;
	if ( (stat=pthread_cond_init(&cond->cond, NULL)) != 0 )
		return stat;
	return 0;
}

int condition_lock(condition_t *cond)
{
	return pthread_mutex_lock(&cond->mutex);
}

int condition_unlock(condition_t *cond)
{
	return pthread_mutex_unlock(&cond->mutex);
}

int condition_wait(condition_t *cond)
{
	return pthread_cond_wait(&cond->cond,&cond->mutex);
}

int condition_timedwait(condition_t *cond, struct timespec*tm)
{
	return pthread_cond_timedwait(&cond->cond, &cond->mutex, tm);
}

int condition_signal(condition_t *cond)
{
	return pthread_cond_signal(&cond->cond);
}

int condition_broadcast(condition_t *cond)
{
	return pthread_cond_broadcast(&cond->cond);
}

int condition_destroy(condition_t *cond)
{
	int stat;
	if ( (stat=pthread_mutex_destroy(&cond->mutex)) != 0 )
		return stat;
	if ( (stat=pthread_cond_destroy(&cond->cond)) != 0 )
		return stat;
	return 0;
}

