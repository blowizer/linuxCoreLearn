#ifndef __IPC_H__
#define __IPC_H__

#define ERR_EXIT(m) \
    do { \
        fprintf(stderr, "[%s][%d]:%s %s\n", __FILE__, __LINE__, m, strerror(errno)); \
        exit(EXIT_FAILURE); \
    } while ( 0 )

union semun {
	int val;                  /* value for SETVAL */
	struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
	unsigned short *array;    /* array for GETALL, SETALL */
				  /* Linux specific part: */
	struct seminfo *__buf;    /* buffer for IPC_INFO */
};

int sem_create(key_t key);

int sem_open(key_t key);

int sem_p(int semid);

int sem_v(int semid);

int sem_d(int semid);

int sem_setval(int semid, int val);

int sem_getval(int semid);

#endif //__IPC_H__

