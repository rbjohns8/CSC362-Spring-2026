// The airplane module contains the airplane data type and management functions

#include <stdlib.h>
#include <string.h>

#include "airplane.h"

/************************************************************************
 * plane_init initializes an airplane structure in the initial PLANE_UNREG
 * state, with given send and receive FILE objects.
 */
void airplane_init(airplane *plane, FILE *fp_send, FILE *fp_recv) {
    plane->state = PLANE_UNREG;
    plane->fp_send = fp_send;
    plane->fp_recv = fp_recv;
    plane->id[0] = '\0';
}

/************************************************************************
 * plane_destroy frees up any resources associated with an airplane, like
 * file handles, so that it can be free'ed.
 */
void airplane_destroy(airplane *plane) {
    fclose(plane->fp_send);
    fclose(plane->fp_recv);
}
