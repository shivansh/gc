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
