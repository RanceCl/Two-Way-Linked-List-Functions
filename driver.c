/* driver.c

Writing and debugging MP2 is challenging, and it is particularly hard if you
try and write all the code before you do any testing. It is much easier to
break the problem into small pieces and test each piece.

For MP2, one approach is to write llist_insert first, since it might be the
easiest algorithm and it depends only on llist_construct.

   For testing, we use a simple main function in this file.  This file is for
   testing only, and you will NOT submit it as it is for your personal testing
   during development.

Below are a few simple examples that allocates a few structures and inserts 
them into a list.

With this file, you can compile and run llist.c on its own using 

   gcc -Wall -g driver.c llist.c ids_support.c -o driver

The compiling command is also in the makefile. Do
   make driver 

Do this testing before you make ANY changes to ids_support.c.  The only 
reason we need to compile ids_support.c is for the ids_compare function.
The linker needs to find the compare_fun function and it is found in the template
   ids_support.c file (with no changes) 
*/

#include <stdlib.h>
#include <stdio.h>
#include "llist.h"
#include "ids_support.h"

/* prototype for list debug print */
void llist_debug_print(llist_t *list_ptr);

int main(void)
{
    data_t *datap = NULL;
    llist_t *Lptr = NULL;

    Lptr = llist_construct(ids_compare_genid);

    // create one item to test llist_insert
    datap = (data_t *) calloc(1, sizeof(data_t));
    datap->generator_id = 555;
    llist_insert(Lptr, datap, 0);
    datap = NULL;

    // test llist_access with one item in list
    datap = llist_access(Lptr, LLPOSITION_FRONT);
    if (datap != NULL) {
        printf("should find 555 and found (%d)\n", datap->generator_id);
    } else {
        printf("ERROR: list access is broken?\n");
    }
    datap = NULL;

    // add a second item 
    datap = (data_t *) calloc(1, sizeof(data_t));
    datap->generator_id = 333;
    llist_insert(Lptr, datap, LLPOSITION_BACK);
    datap = NULL;

    // add a third item
    datap = (data_t *) calloc(1, sizeof(data_t));
    datap->generator_id = 444;
    llist_insert(Lptr, datap, LLPOSITION_BACK);
    datap = NULL;

    // find all three and print 
    datap = llist_access(Lptr, 0);   /* same as LLPOSITION_FRONT */
    if (datap != NULL) {
        printf("Position 0 should find 555 and found (%d)\n", datap->generator_id);
        datap = llist_access(Lptr, 1);
        printf("Position 1 should find 333 and found (%d)\n", datap->generator_id);
        datap = llist_access(Lptr, LLPOSITION_BACK);
        printf("Position 2 should find 444 and found (%d)\n", datap->generator_id);
    } else {
        printf("ERROR: list access is broken?\n");
    }

    //Next try to use llist_debug_print 
    printf("\nTest of list debug print function\n\n");
    llist_debug_print(Lptr);

    // you should repeat the above tests with differents insertion orders

    // next you may want to work on llist_insert_sorted, so replace the above
    // llist_insert commands with llist_insert_sorted
 
    // after the insertion functions work, you can try the find command
 
    // Uncomment this section to test llist_elem_find 
    //*********************************************************************
    int position = -9876;
    data_t my_template;
    my_template.generator_id = 444;
    data_t *foundp = llist_elem_find(Lptr, &my_template, &position, ids_compare_genid);
    printf("\nTest of list elem find\n");
    if (foundp != NULL) {
        printf("looked for %d and found %d in position %d\n",
            my_template.generator_id, foundp->generator_id, position);
        if (my_template.generator_id != foundp->generator_id) {
            printf("ERROR: returned pointer to wrong record\n");
        }
        if (position < -1) {
            printf("ERROR: did not set position\n");
        }
    } else {
        printf("looked for %d and did not find. Is this an error? \n", 
            my_template.generator_id);
    }
    

    llist_destruct(Lptr);
    // End of tests with unsorted list
 
    // Uncomment this section to try some tests on a sorted list 
    //*********************************************************************
    llist_t *Lsortptr = llist_construct(ids_compare_genid);

    datap = (data_t *) calloc(1,sizeof(data_t));
    datap->generator_id = 23;
    llist_insert_sorted(Lsortptr, datap);

    // add a second item
    datap = (data_t *) calloc(1,sizeof(data_t));
    datap->generator_id = 7;
    llist_insert_sorted(Lsortptr, datap);

    // add a third item
    datap = (data_t *) calloc(1,sizeof(data_t));
    datap->generator_id = 15;
    llist_insert_sorted(Lsortptr, datap);

    printf("\nHere is the sorted list\n\n");
    llist_debug_print(Lsortptr);

    llist_destruct(Lsortptr);
   
    return 0;
}

/*

   Next you will want to write your own llist_debug_print function to print a
   list. Then you can do "before and after" testing. That is, print the list
   before a change, and print the list after the change to verify that the change
   worked.

   Something like
*/

void llist_debug_print(llist_t *list_ptr) {
    llist_elem_t *rover;
    int count;

    printf("list size: %d\n", list_ptr->ll_entry_count);
    rover = list_ptr->ll_front;
    count = 0;
    while(rover != NULL) {
        printf("Pos: %d contains ID: %d\n", count, rover->data_ptr->generator_id);
        rover = rover->ll_next;
        count++;
    }
    if (count != list_ptr->ll_entry_count)
        printf("\nERROR: the list size is wrong! count is %d\n", count);
}

