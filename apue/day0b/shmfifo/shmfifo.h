#ifndef __SHMFIFO_H__
#define __SHMFIFO_H__

#include <sys/types.h>

typedef struct shmhead shmhead_t;
typedef struct shmfifo shmfifo_t;

struct shmhead {
	unsigned int blksz;    // 块大小
	unsigned int blocks;   // 总块数
	unsigned int rd_index; // 读索引
	unsigned int wr_index; // 写索引
};

struct shmfifo {
	shmhead_t *p_shm; // 共享内存头部指针
	char *p_payload;  // 有效数据负载地址
	int shmid;        // 共享内存ID
	int sem_mutex;    // 用来互斥的信号量
	int sem_full;     // 判断是否满的信号量
	int sem_empty;    // 判断是否空的信号量	
};

shmfifo_t* shmfifo_init(key_t key, int blksz, int blocks);
void shmfifo_put(shmfifo_t *fifo, const void *buf);
void shmfifo_get(shmfifo_t *fifo, void *buf);
void shmfifo_destroy(shmfifo_t *fifo);

#endif //__SHMFIFO_H__

