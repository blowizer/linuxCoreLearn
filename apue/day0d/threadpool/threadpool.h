#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "condition.h"

typedef struct task
{
	void *(*run)(void *arg);
	void *arg;
	struct task *next;
}task_t;

typedef struct threadpool
{
	condition_t ready;  // 任务准备就绪或线程池销毁通知
	task_t *first;      // 任务队列的头指针
	task_t *last;       // 任务队列的尾指针
	int counter;        // 线程池中的当前线程数
	int idle;			// 当前线程池中空闲的线程数
	int max_threads;	// 线程池中最大的线程数
	int quit;			// 销毁线程池时置1
}threadpool_t;

// 初始化线程池
void threadpool_init(threadpool_t *pool, int threads);
// 往线程池中添加任务
void threadpool_add_task(threadpool_t *pool, void *(*run)(void *arg), void *arg);
// 销毁线程池
void threadpool_destroy(threadpool_t *pool);

#endif //__THREADPOOL_H__

