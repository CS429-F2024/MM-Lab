#include "umalloc.h"
int check_heap();

typedef enum {
    HEAP_ERR_OOO,       // Out of Order
    HEAP_ERR_IMPLICIT,  // Allocated block in free list (implicit free list)
    HEAP_ERR_UNALIGNED, // Unaligned payload
    HEAP_ERR_OVERLAP,   // Overlapping blocks
    HEAP_ERR_OTHER      // Non-standard errors (segfault, etc)
} heap_err;

typedef enum {
    ORD_SIZE,       // Size-ordered free list
    ORD_MEM,        // Memory-ordered free list
    ORD_RAND,       // Random-ordered free list
    ORD_OTHER=-1    // Unconventional free list ordering
} heap_order;

extern heap_order ord;