#ifndef GC_H_
#define GC_H_

#include "vm.h"

void sweep(VM*);
void gc(VM*);

#endif  // GC_H_
