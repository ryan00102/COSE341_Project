#include <sched.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define ROW (100)
#define COL ROW
#define EPOCH_INTERVAL 100000

int count = 0;
int total_time = 0;
struct sched_attr {
    uint32_t size;
    uint32_t sched_policy;      //scheduling policy
    uint64_t sched_flags;
    int32_t sched_nice;
    uint32_t sched_priority;    //priority
    uint64_t sched_runtime;
    uint64_t sched_deadline;
    uint64_t sched_period;
};

static int sched_setattr(pid_t pid, const struct sched_attr* attr, unsigned int flags) {
    return syscall(SYS_sched_setattr, pid, attr, flags);
}

void matrix_multiply() {
    int matrixA[ROW][COL];
    int matrixB[ROW][COL];
    int matrixC[ROW][COL];

    // 행렬 초기화
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            matrixA[i][j] = rand() % 100;
            matrixB[i][j] = rand() % 100;
        }
    }

    // 행렬 곱셈 연산 수행
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            matrixC[i][j] = 0;
            for (int k = 0; k < COL; k++) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    count++;
}

void sigint_handler(int signum) {
    printf("\nSIGNAL : Process expired.\n");
    printf("totalCount = %d, time = %d\n", count, total_time);
    exit(1);
}

void child_process(int process_id, int process_time) {
    struct timespec start, end;
    int ops_count = 0;
    int elapsed_time = 0;
    printf("pid: #%ld parents: %ld \n", (long)getpid(), (long)getppid());
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (elapsed_time < process_time) {
        matrix_multiply();
        ops_count++;

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000; //ms 단위
        total_time = elapsed_time;
        if (elapsed_time % 100 == 0) {
            printf("PROCESS #%d count = %d time = %d %d\n",
                process_id, ops_count, EPOCH_INTERVAL / 1000, elapsed_time);
        }
    }

    printf("PROCESS #%d totalCount = %d, time = %d\n", process_id, ops_count, elapsed_time);
    exit(0);
}

int main(int argc, char* argv[]) {
    int num_processes = atoi(argv[1]);

    int time_to_execute = atoi(argv[2]) * 1000;

    struct sched_attr scheduler;

    memset(&scheduler, 0, sizeof(scheduler));
    scheduler.size = sizeof(struct sched_attr);

    scheduler.sched_priority = 10; //configure priority
    scheduler.sched_policy = SCHED_RR; //configure scheduling policy


    // SIGINT 신호 핸들러 등록
    signal(SIGINT, sigint_handler);
    for (int n = 0; n < num_processes; n++) {
        printf("PROCESS #%d CREATED\n", n);
    }

    pid_t pid;
    for (int i = 0; i < num_processes; i++) {
        pid = fork();
        if (pid == 0) {
            child_process(i, time_to_execute);
        }
        else if (pid < 0) {
            printf("ERROR : PROCESS %d IS NOT CREATED\n", i);
            exit(1);
        }
    }

    // 자식 프로세스의 종료를 기다림
    int status;
    for (int i = 0; i < num_processes; i++) {
        wait(&status);
    }

    return 0;
}
