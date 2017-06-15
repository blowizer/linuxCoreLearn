#include <unistd.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

pthread_key_t key;
pthread_once_t once_control = PTHREAD_ONCE_INIT;

void destructor(void* value)
{
	printf("destructor...!\n");
	free(value);
}

typedef struct stu {
	int id;
	char *str;
}stu_t;

void init_routine(void)
{
	pthread_key_create(&key, destructor);
}

void *run(void *arg)
{
	pthread_once(&once_control, init_routine);
	stu_t *p = (stu_t*)malloc(sizeof(stu_t));
	p->id = pthread_self();
	p->str = (char*)arg;
	pthread_setspecific(key, p);
	
	p = NULL;
	p = (stu_t*)pthread_getspecific(key);
	printf("id=%#X, %s\n", p->id, p->str);
	sleep(2);
	p = NULL;
	p = (stu_t*)pthread_getspecific(key);
	printf("id=%#X, %s\n", p->id, p->str);
}

int main ( void )
{
	//pthread_key_create(&key, destructor);
	
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, run, "thread1");
	pthread_create(&tid2, NULL, run, "thread2");
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	pthread_key_delete(key);
}

