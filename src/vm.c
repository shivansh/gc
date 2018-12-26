#include <stdio.h>
#include <stdlib.h>

#include "gc.h"
#include "object.h"

// newVM creates a new VM object.
VM* newVM() {
    VM* vm = malloc(sizeof(VM));
    vm->firstObject = NULL;
    vm->stackSize = 0;
    vm->numObjects = 0;
    vm->maxObjects = INITIAL_GC_THRESHOLD;
    return vm;
}

// newObject creates a new object.
Object* newObject(VM* vm, ObjectType type) {
    Object* object = malloc(sizeof(Object));
    object->marked = 0;
    object->type = type;

    // Insert the current object into the list of allocated objects.
    object->next = vm->firstObject;
    vm->firstObject = object;
    vm->numObjects++;

    return object;
}

// push inserts a new live object into the stack.
void push(VM* vm, Object* value) {
    assert(vm->stackSize < STACK_MAX, "Stack overflow!");
    vm->stack[vm->stackSize++] = value;
}

// pop removes an object (possibly dead) from the stack.
Object* pop(VM* vm) {
    assert(vm->stackSize > 0, "Stack underflow!");
    return vm->stack[--vm->stackSize];
}

// pushInt pushes an int object into the stack.
void pushInt(VM* vm, int intValue) {
    Object* object = newObject(vm, OBJ_INT);
    object->value = intValue;
    push(vm, object);
}

// pushPair pushes a pair of objects (references) into the stack.
// NOTE that even though the pointers to objects comprising the "reference"
// object (head and tail) are being popped from the stack, they are still
// available in heap. Hence, at the end of this step we'll have one more object
// in the heap.
Object* pushPair(VM* vm) {
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

// markAll marks all the live objects.
void markAll(VM* vm) {
    for (int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

void freeVM(VM* vm) {
    // Setting stacksize to zero will avoid markall to mark all objects.
    vm->stackSize = 0;
    gc(vm);
    free(vm);
}
