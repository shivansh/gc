#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdbool.h>

typedef enum {
    OBJ_INT,
    OBJ_PAIR,
} ObjectType;

typedef struct sObject {
    // Since the mark can only take values {0, 1}, we are good with allocating
    // a single byte char type instead of a 4 byte int type.
    unsigned char marked;

    ObjectType type;

    // next determines the next object in the list of all the objects.
    struct sObject* next;

    union {
        // OBJ_INT
        int value;

        // OBJ_PAIR: denotes references, where the head references the tail.
        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 32

void assert(int, const char*);
bool isMarked(Object*);
void mark(Object*);

#endif  // OBJECT_H_
