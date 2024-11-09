#ifndef Pipe_h
#define Pipe_h

#include <stdint.h>


struct Pipe {
    uint8_t column;         // Column in which the pipe is currently in. 
    uint8_t holeHeight;     // The lowest pixel of the pipe's hole.
};


#endif