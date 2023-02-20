/** @file test_data_gen.h
 * @brief Test data generator
 * @author Weihai Yu
 */

#ifndef _TEST_DATA_GEN_H_
#define _TEST_DATA_GEN_H_

#include "schema.h"

/*
-Create the test schema
    -my_schema (MyIdField: int, MyStrField:str[TEST_STR_LEN], myIntField:int)
    
    -Returns a new schema:
        -Removes the current schema (if it exists)
        -Creates a new schema of a given name
        -Adds fields(columns) to the new schema (could be INT's of STR's)
        -Prints name of schema, its number of fileds and total bytes
-DONE*/
extern schema_p create_test_schema(char const* name, int n_attrs,
                                   char* attrs[], int attr_types[]);

/*
*prepare the test data generator.
*For each run, the same series of random numbers are generated
*DONE
*/
extern void prepare_test_data_gen();

/*
 * resets the test data generator.
 * next_test_record_id is set to 0
 * DONE*/
extern void test_data_gen(schema_p sch, record* r, int n);

/** fill a record with some generated data. 
 * DONE*/
extern void fill_gen_record(schema_p s, record r, int id);

#endif
