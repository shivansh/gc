#ifndef VM_H_
#define VM_H_

#include "object.h"

typedef struct {
    int numObjects;            // total number of currently allocated objects
    int maxObjects;            // number of objects required to trigger a GC
    Object* firstObject;       // the first object in the list of all objects
    Object* stack[STACK_MAX];  // stack stores the variables currently in scope
    int stackSize;
} VM;

VM* newVM();
Object* newObject(VM*, ObjectType);
void push(VM*, Object*);
Object* pop(VM*);
void pushInt(VM*, int);
Object* pushPair(VM*);
void markAll(VM*);
void freeVM(VM*);

#endif  // VM_H_
