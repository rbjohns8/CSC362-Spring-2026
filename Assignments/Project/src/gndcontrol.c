// This is the main program for the air traffic ground control server.

// The job of this module is to set the system up and then turn over control
// to the airs_protocol module which will handle the actual communication
// protocol between clients (airplanes) and the server.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "airplane.h"
#include "airs_protocol.h"

/************************************************************************
 * Part 1 main: Only 1 airplane, doing I/O via stdin and stdout.
 */
int main(int argc, char *argv[]) {
    airplane myplane;
    airplane_init(&myplane, stdout, stdin);

    char *lineptr = NULL;
    size_t linesize = 0;

    while (myplane.state != PLANE_DONE) {
        if (getline(&lineptr, &linesize, myplane.fp_recv) < 0) {
            // Failed getline means the client disconnected
            break;
        }
        docommand(&myplane, lineptr);
    }

    return 0;
}
