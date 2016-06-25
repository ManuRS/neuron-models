#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void timeval_actual(struct timeval *tv){
    gettimeofday(tv, NULL);
}

void timeval_set(struct timeval *tv, long sec, long usec){ /*1s=1e6us*/
    tv->tv_sec=sec;
    tv->tv_usec=usec;
}

void timeval_sleep(struct timeval *tv){
    struct timespec request;
    struct timespec remain;
    request.tv_sec = tv->tv_sec;
    request.tv_nsec = tv->tv_usec*1000; /*range 0 to 999999999*/
    nanosleep(&request, &remain);
}

void min_sleep(void){
    struct timespec request;
    request.tv_sec = 0;
    request.tv_nsec = 1; /*range 0 to 999999999*/
    nanosleep(&request, NULL);
}

void nanosecs_sleep(long nanosecs){
    struct timespec request;
    struct timespec remain;
    request.tv_sec = 0;
    request.tv_nsec = nanosecs; /*range 0 to 999999999*/
    nanosleep(&request, &remain);
}

void timeval_subtract(struct timeval *result, struct timeval *t1, struct timeval *t2){
  if (t1->tv_sec >= t2->tv_sec && t1->tv_usec >= t2->tv_usec){
    result->tv_usec = t1->tv_usec - t2->tv_usec;
    result->tv_sec = t1->tv_sec - t2->tv_sec;
  }else if (t1->tv_sec > t2->tv_sec && t1->tv_usec <= t2->tv_usec){
    result->tv_usec = 1000000 - (t2->tv_usec - t1->tv_usec);
    result->tv_sec = t1->tv_sec - t2->tv_sec - 1;
  }else {
    /*Para el uso que se le esta dando da igual si es cero o menos, es lo mismo*/
    result->tv_usec = 0;
    result->tv_sec = 0;
  }
}

void timeval_sum(struct timeval *result, struct timeval *t1, struct timeval *t2){
  if (t1->tv_usec + t2->tv_usec > 1000000){
    result->tv_usec = t1->tv_usec + t2->tv_usec - 1000000;
    result->tv_sec = t1->tv_sec + t2->tv_sec + 1;
  }else{
    result->tv_usec = t1->tv_usec + t2->tv_usec;
    result->tv_sec = t1->tv_sec + t2->tv_sec;
    }
}
 
void timeval_div(struct timeval *t1, int n){
  float aux = (t1->tv_usec + (t1->tv_sec%n)*1000000);
  aux = aux/n;
  t1->tv_usec = (long int)((t1->tv_usec + (t1->tv_sec%n)*1000000 ) / n);
  t1->tv_sec = (long int)(t1->tv_sec/n);
    if( (aux-(int)aux) > 0.5){
    t1->tv_usec++;
  }
}

int timeval_mayor(struct timeval *t1, struct timeval *t2){
    /*Comparamos segundos*/
    if(t1->tv_sec>t2->tv_sec){
        return 1;
    }else if(t2->tv_sec>t1->tv_sec){
        return 2;
    }
    /*Comparamos usegundos*/
    if(t1->tv_usec>t2->tv_usec){
        return 1;
    }else if(t2->tv_usec>t1->tv_usec){
        return 2;
    }else{
        return 3;
    }
}

void timeval_copy(struct timeval *t1, struct timeval *t2){
    t1->tv_sec = t2->tv_sec;
    t1->tv_usec = t2->tv_usec;
}

void timeval_print(struct timeval *tv){
    printf("%ld.%06ld\n", tv->tv_sec, tv->tv_usec);
}

char* timeval_getStr(struct timeval *tv){
  char *str = malloc (sizeof (char) * 18);
  sprintf(str, "%ld.%06ld", tv->tv_sec, tv->tv_usec);
  return str;
}
