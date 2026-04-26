#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <mpi/mpi.h>
#include <pthread.h>
#include <string.h>

#define ZBITS 30
#define INSIZE 16

struct globals {
    int my_rank;
    int num_procs;
} globals;

/*********************  Job Manager  ************************/

#define JOB_SIZE 0x100000
#define JOB_SZ_BYTES 3

unsigned char next_start[INSIZE];
pthread_mutex_t start_mutex = PTHREAD_MUTEX_INITIALIZER;

volatile int global_success = 0;

unsigned char winner[INSIZE];

/**************************************************************************
 * Initialize starting input to all zeros.
 */
void next_init(void) {
    memset(next_start, 0, INSIZE);
    global_success = 0;
}


/**************************************************************************
 * Increment starting job value by "JOB_SIZE"
 */
void next_job(unsigned char *fillin) {
    pthread_mutex_lock(&start_mutex);
    memcpy(fillin, next_start, INSIZE);
    if ((next_start[JOB_SZ_BYTES-1] += (JOB_SIZE>>(JOB_SZ_BYTES-1))) == 0) {
        for (int j=JOB_SZ_BYTES; j<INSIZE; j++) {
            if (++next_start[j] != 0) break;
        }
    }
    pthread_mutex_unlock(&start_mutex);
}

/**************************************************************************
 * The job manager thread. Repeatedly receives a status result from
 * each processor, and checks to see if the processor reported
 * "success" (first byte being 1). If so, it sets a flag saying that
 * all other processes should get a "stop" message when they ask for
 * another job. If no success, then increment to the next job start
 * and send that back to the processor for its next batch.
 */
void *jobmanager(void *arg) {
    unsigned char job_start[INSIZE+1];
    unsigned char recv_buffer[INSIZE+1];
    MPI_Status status;
    int stops_sent = 0;

    for (int i=0; i<INSIZE+1; i++) {
        job_start[i] = 0;
    }

    while (1) {
        MPI_Recv(recv_buffer, sizeof(recv_buffer), MPI_UNSIGNED_CHAR,
                 MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

        if (recv_buffer[0] == 1) {
//            printf("Success indication from rank %d\n", status.MPI_SOURCE);
            memcpy(winner, recv_buffer+1, INSIZE);
            global_success = 1;
            if (++stops_sent == (globals.num_procs-1))
                break;
        } else {
//            printf("Received request from rank %d\n", status.MPI_SOURCE);
            next_job(&job_start[1]);
            job_start[0] = global_success;
            MPI_Send(job_start, sizeof(job_start), MPI_UNSIGNED_CHAR,
                     status.MPI_SOURCE, 0, MPI_COMM_WORLD);
            if (global_success && (++stops_sent == (globals.num_procs-1)))
                break;
        }
    }

    return NULL;
}

/***********************  End of Job Manager  ************************/

/**************************************************************************
 * Try a batch of inputs (itercount of them), starting from "tohash"
 */
int dosearch(unsigned char *tohash, int len, int itercount) {
    unsigned char md[SHA256_DIGEST_LENGTH];
    for (int i=0; i<itercount; i++) {
        SHA256(tohash, INSIZE, md);
        int bitsclear = 0;
        int j;
        for (j=0; j<SHA256_DIGEST_LENGTH && md[j]==0; j++) {
            bitsclear += 8;
        }
        if (j < SHA256_DIGEST_LENGTH) {
            for (int m=0x80; (md[j]&m) == 0; m >>= 1)
                bitsclear++;
        }

        if (bitsclear >= ZBITS) {
            return 1;
        } else {
            for (int j=0; j<INSIZE; j++) {
                if (++tohash[j] != 0) break;
            }
        }
    }

    return 0;
}

/**************************************************************************
 * Get the next job from the rank 0 processor (job manager)
 */
int get_job(unsigned char *fillin) {
    if (globals.my_rank == 0) {
        next_job(&fillin[1]);
        fillin[0] = global_success;
    } else {
        fillin[0] = 0;
        MPI_Send(fillin, INSIZE+1, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(fillin, INSIZE+1, MPI_UNSIGNED_CHAR, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    return 1;
}

/**************************************************************************
 * Send a success notice to the rank 0 processor (job manager)
 */
void signal_success(unsigned char *fillin) {
    if (globals.my_rank == 0) {
        global_success = 1;
        memcpy(winner, fillin+1, INSIZE);
    } else {
        fillin[0] = 1;
        MPI_Send(fillin, INSIZE+1, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }
}

/**************************************************************************
 */
int main(int argc, char *argv[]) {
    // Job start counter -- initialize
    next_init();

    // Initialize the infrastructure necessary for communication
    MPI_Init(&argc, &argv);

    // Identify this process
    MPI_Comm_rank(MPI_COMM_WORLD, &globals.my_rank);

    // Find out how many total processes are active
    MPI_Comm_size(MPI_COMM_WORLD, &globals.num_procs);

    if (globals.my_rank == 0)
        printf("Number of active processes: %d\n", globals.num_procs);

    // Start up the job manager thread on processor 0
    pthread_t pthread;
    if (globals.my_rank == 0) {
        pthread_create(&pthread, NULL, jobmanager, NULL);
    }

    unsigned char my_start[INSIZE+1];
    memset(my_start, 0, INSIZE+1);

    while (1) {
        get_job(my_start);
        if (my_start[0] == 1) break;  // This is the "done" flag.
        int success = dosearch(my_start+1, INSIZE, JOB_SIZE);
        if (success) {
            signal_success(my_start);
            my_start[0] = 1;
            break;
        }
    }

    // Only print result from rank 0 processor (since job manager runs there)
    if (globals.my_rank == 0) {
        printf("Input: ");
        for (int i=0; i<INSIZE; i++)
            printf(" %02x", winner[i]);
        printf("\n");

        pthread_join(pthread, NULL);
    }

    // Tear down the communication infrastructure
    MPI_Finalize();
    return 0;
}
