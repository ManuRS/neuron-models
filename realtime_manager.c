#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>

#include <rtai_lxrt.h>
#include <rtai_sem.h>
#include <rtai_msg.h>

static RT_TASK *task;
static RTIME task_period_ns = 100000;/*ns*/
static RTIME task_period_count;/* requested timer period, in counts */
static RTIME timer_period_count;/* actual timer period, in counts */

int realtime_on(void){
    int retval;

    /*RT_TASK * rt_task_init_schmod(unsigned long name, int priority, int stack_size, int max_msg_size, int policy, int cpus_allowed)*/
    if(!(task = rt_task_init_schmod(nam2num("TAREA11"), 1, 0, 0, SCHED_FIFO, 0xF))){
        printf("rt_task_init_schmod error\n");
        return -1;
    }

    mlockall( MCL_CURRENT | MCL_FUTURE );
    printf("TAREAL EN TIEMPO REAL (name = %lu, address = %p)\n", nam2num("TAREA1"), task);

    rt_set_oneshot_mode();
    task_period_count = nano2count(task_period_ns);
    timer_period_count = start_rt_timer(task_period_count);/*Inicia temporizador*/

    printf("\tRequested %d counts, got %d counts\n",(int) task_period_count, (int) timer_period_count);
    retval = rt_task_make_periodic(task, rt_get_time() + task_period_count, task_period_count); /* recurring period */
    if (0 != retval) {
      printf("rt_task_make_periodic error\n");
      return -1;
    }

    rt_make_hard_real_time(); 

    printf("\tPeriodo=%f\n\n",(double)task_period_ns/1e9);

    return 1;
}

void realtime_wait(void){
  rt_task_wait_period();
}

void realtime_off(void){
    rt_make_soft_real_time();
}


