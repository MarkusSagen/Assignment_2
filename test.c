
#include "common.h"
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"
#include "iterator.h"
#include "business_logic.h"
#include <CUnit/CUnit.h> //install via brew install cunit
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>





//// Asserting initial

// Test for entries
int init_entries(void)
{
  return 0;
}

int clear_entries(void)
{
  return 0;
}



void test_table()
{
    int a = 5;
    CU_ASSERT(5 == a);
}






int main()
{
    
    //// Initialize initials
    CU_pSuite pSuiteEntries     = NULL;
    
    
    
    //// Initialize and print error messages if errors
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    
    //// Here we start to assert tests
    pSuiteEntries   = CU_add_suite("Test all functions with insertion and removal: ", init_entries, clear_entries);
   
    
    
    
    
    
    if (NULL == pSuiteEntries)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
   
    
    
    //// Test Hash table
    // Testing hashtable create and destroy
    if (
        (NULL == CU_add_test( pSuiteEntries, "Test lookup_table()", test_table))

        )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    
    
    
    
    //// Final state:
    // Run test, display errors and clear registry
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
