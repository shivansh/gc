#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
#include "object.h"

// sweep makes a single pass through the entire list of allocated objects,
// unallocated the ones which are not marked.
void sweep(VM* vm) {
    Object** object = &vm->firstObject;
    while (*object) {
        if (!isMarked(*object)) {
            // The current object was not reached, unallocate it.
            Object* unreached = *object;
            *object = unreached->next;
            free(unreached);
            vm->numObjects--;
        } else {
            // The current object was reached, unmark it for the next GC call.
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

// gc is the entry point for the garbage collector.
void gc(VM* vm) {
    int numObjects = vm->numObjects;
    markAll(vm);
    sweep(vm);
    // After every call to GC the number of live objects will be modified. We
    // update the GC threshold to be twice the size of currently live objects.
    vm->maxObjects = vm->numObjects * 2;
    printf("GC: Collected %d, remaining %d\n", numObjects - vm->numObjects,
           vm->numObjects);
}
