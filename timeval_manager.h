#ifndef TIMEVAL_MANAGER
#define TIMEVAL_MANAGER

void timeval_actual(struct timeval *tv);
void timeval_set(struct timeval *tv, long sec, long usec);
void timeval_sleep(struct timeval *tv);
void min_sleep(void);
void nanosecs_sleep(int nanosecs);
void timeval_subtract(struct timeval *result, struct timeval *t1, struct timeval *t2);
void timeval_sum(struct timeval *result, struct timeval *t1, struct timeval *t2);
void timeval_div(struct timeval *t1, int n);
int timeval_mayor(struct timeval *t1, struct timeval *t2); /*return 1 si es mayor el primero o son iguales, 2 si es mayor el segundo*/
void timeval_copy(struct timeval *t1, struct timeval *t2);
void timeval_print(struct timeval *tv);
char* timeval_getStr(struct timeval *tv);

#endif
