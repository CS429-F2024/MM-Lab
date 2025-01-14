/**************************************************************************
 * C S 429 MM-lab
 * 
 * runner.c - Runs the traces and evaluates the umalloc package for correctness
 * and utilization.
 * 
 * Copyright (c) 2021 M. Hinton. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/

#include "csbrk.h"
#include "support.h"
#include "check_heap.h"
#include <sys/mman.h>

int verbose = 0;
extern char msg[MAXLINE];      /* for whenever we need to compose an error message */
extern size_t sbrk_bytes;
extern const char author[];
extern heap_order ord;
extern mem_block_header_t *free_head;

mem_block_header_t* pass_blocks = NULL;          // should pass
mem_block_header_t* fail_blocks_alloc = NULL;    // has allocated blocks in list
mem_block_header_t* fail_blocks_misalign = NULL; // misaligned blocks
mem_block_header_t* fail_blocks_overlap = NULL;  // overlapping blocks
mem_block_header_t* fail_blocks_order = NULL;    // out of order


void free_list_builder() {

    // pass_blocks
    curr_blk = pass_blocks;
    for (int i = 0; i < 10; i++) {
        mem_block_header_t* test_blk = (mem_block_header_t*) malloc(sizeof(mem_block_header_t));
        test_blk->block_metadata = (i * 20) << 4;
        if (curr_blk == NULL) {
            curr_blk = test_blk;
            pass_blocks = test_blk;
        } else {
            curr_blk->next = test_blk;
            curr_blk = curr_blk->next;
        }
    }

    // fail blocks: allocated block in free list
    curr_blk = pass_blocks;
    for (int i = 0; i < 10; i++) {
        mem_block_header_t* test_blk = (mem_block_header_t*) malloc(sizeof(mem_block_header_t));
        test_blk->block_metadata = (i * 20) << 4;
        if (curr_blk == NULL) {
            curr_blk = test_blk;
            pass_blocks = test_blk;
        } else {
            if (i == 8) {
                test_blk->block_metadata |= 1; 
            }
            curr_blk->next = test_blk;
            curr_blk = curr_blk->next;
        }
    }
    
    // fail blocks: allocated block in free list
    curr_blk = pass_blocks;
    for (int i = 0; i < 10; i++) {
        mem_block_header_t* test_blk = (mem_block_header_t*) malloc(sizeof(mem_block_header_t));
        test_blk->block_metadata = (i * 20) << 4;
        if (curr_blk == NULL) {
            curr_blk = test_blk;
            pass_blocks = test_blk;
        } else {
            if (i == 8) {
                test_blk->block_metadata |= 1; 
            }
            curr_blk->next = test_blk;
            curr_blk = curr_blk->next;
        }
    }


    switch(ord) {
        case ORD_MEM:
            // blocks
            break;
        case ORD_SIZE:
            // sort(blocks)
            break;
        case ORD_RAND:
            // random.shuffle(blocks)
            break; 
        case OTHER:
            // please god no
            break;
    }
}
int main(int argc, char **argv)
{

    printf("Welcome to the MM lab check_heap runner\n\n");
    printf("Author: %s\n", author);

    // TODO: Insert custom free list tests
    // set free_head = test


    int res = check_heap();
    

}