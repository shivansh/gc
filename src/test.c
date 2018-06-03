#include "test.h"
#include "gc.h"
#include "object.h"

void test1() {
    VM* vm = newVM();
    pushInt(vm, 1);
    pushInt(vm, 2);
    gc(vm);
    assert(vm->numObjects == 2, "Should preserve objects.");
    freeVM(vm);
}
