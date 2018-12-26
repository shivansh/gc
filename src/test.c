#include "test.h"
#include "gc.h"
#include "object.h"

void test1() {
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    gc(vm);
    assert(vm->numObjects == 2, "Should have preserved all the objects.");
    freeVM(vm);
}

void test2() {
    VM* vm = newVM();
    pushInt(vm, 1);
    // Mark the previously pushed objected as dead.
    pop(vm);
    gc(vm);
    assert(vm->numObjects == 0, "Should have collected all the objects.");
    freeVM(vm);
}

void test3() {
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    Object* a = pushPair(vm);
    pushInt(vm, 3);
    pushInt(vm, 4);
    Object* b = pushPair(vm);

    // NOTE: we have 6 objects in heap at this point.
    // Setup a cycle, while making 2 and 4 unreachable which will be collected.
    a->tail = b;
    b->tail = a;

    gc(vm);
    assert(vm->numObjects == 4, "Should have collected all the objects.");
    freeVM(vm);
}
