#include <stdio.h>
#include <stdlib.h>

#include "object.h"

void assert(int condition, const char* message) {
    if (!condition) {
        printf("%s\n", message);
        exit(1);
    }
}

// isMarked checks whether the object is marked.
bool isMarked(Object* object) {
    if (object->marked) {
        return true;
    }
    return false;
}

// mark marks the object.
void mark(Object* object) {
    // If the object is already marked, we're done. This avoids recursing on
    // cycles in the object graph.
    if (isMarked(object)) return;

    object->marked = 1;

    // Handle references in objects.
    if (object->type == OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}
