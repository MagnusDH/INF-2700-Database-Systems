#include <string.h>
#include "testschema.h"
#include "test_data_gen.h"
#include "pmsg.h"


#define NUM_RECORDS 1000

/* The records generated in test_tbl_write().
   Will be used in test_tbl_read() to check for correctness. */
record in_recs[NUM_RECORDS];

/*
  -Puts msg in message line: "test_tbl_write ... table_name"
  -Release memory pages in memory, write dirty blocks back to memory, close files, Initiate new pager, and read table description?
  -Creates new test schema and adds info to it
  -Resets the test data generator
  -Appends 1000 records to the new created schema
  -Adds some information about each table in the system to the message line(s)?
  -Puts "test_tbl_write() done" into message line
-DONE*/
void test_tbl_write(char const* tbl_name) {
  put_msg(INFO, "test_tbl_write (\"%s\") ...\n", tbl_name);

  open_db();
  /* put_pager_info(DEBUG, "After open_db"); */

  char id_attr[11] = "Id", str_attr[11] = "Str";
  char *attrs[] = {strcat(id_attr, tbl_name), strcat(str_attr,tbl_name), "Int"};
  int attr_types[] = {INT_TYPE, STR_TYPE, INT_TYPE};
  schema_p sch = create_test_schema(tbl_name, 3, attrs, attr_types);

  test_data_gen(sch, in_recs, NUM_RECORDS);

  for (size_t rec_n = 0; rec_n < NUM_RECORDS; rec_n++) {
    /* put_msg(DEBUG, "rec_n %d  ", rec_n); */
    append_record(in_recs[rec_n], sch);
    /* put_pager_info(DEBUG, "After writing a record"); */
  }

  /* put_pager_info(DEBUG, "Before page_terminate"); */
  put_db_info(DEBUG);
  close_db();
  /* put_pager_info(DEBUG, "After close_db"); */

  put_pager_profiler_info(INFO);
  put_msg(INFO,  "test_tbl_write() done.\n\n");
}

/*
  -Opens database
  -Fetches tbl_name->schema
  -fetches table named tbl_name
  -Creates a new record
  -Set current position pointer to start of table
  -While not at the end of the table:
    ..Retrieve record value at current position and move position pointer
    ..if new created record does NOT have an equal value as the beforehand created record(in_recs):
      ....add to message line: "test_tbl_read"
      ....put info from record into message line and schema
      ....Exit, cleanup, temrinate program with STATUS 
    -If record has equal value as beforehand created record:
    ...Release memory allocated to the record and its fields. 
    -Print error if not every record can be read
    -Release memory allocated to the record and its fields. 
    -puts info about pager profiler into message line: Number of disk seeks/reads/writes/IOs
    -Close database
    -Put into message line: test_tbl_read() success"
-DONE*/
void test_tbl_read(char const* tbl_name) {
  put_msg(INFO,  "test_tbl_read (\"%s\") ...\n", tbl_name);

  open_db();
  /* put_pager_info(DEBUG, "After open_db"); */

  schema_p sch = get_schema(tbl_name);
  tbl_p tbl = get_table(tbl_name);
  record out_rec = new_record(sch);
  set_tbl_position(tbl, TBL_BEG);
  int rec_n = 0;

  while (!eot(tbl)) {
    get_record(out_rec, sch);
    if (!equal_record(out_rec, in_recs[rec_n], sch)) {
      put_msg(FATAL, "test_tbl_read:\n");
      put_record_info(FATAL, out_rec, sch);
      put_msg(FATAL, "should be:\n");
      put_record_info(FATAL, in_recs[rec_n], sch);
      exit(EXIT_FAILURE);
    }
    release_record(in_recs[rec_n++], sch);
    /* put_pager_info(DEBUG, "After reading a record"); */
  }

  if (rec_n != NUM_RECORDS)
    put_msg(ERROR, "only %d of %d records read", rec_n, NUM_RECORDS);

  release_record(out_rec, sch);

  /* put_pager_info(DEBUG, "Before page_terminate"); */
  put_pager_profiler_info(INFO);
  close_db();
  /* put_pager_info(DEBUG, "After close_db"); */

  put_msg(INFO,  "test_tbl_read() succeeds.\n");

}

/*
  -Put into message line: "test_tbl_natural_join 'my_tbl', 'yr_tabl'"
  -Call test_tbl_write() to create schema and add records to it
  -Open database
  -Return two existing tables
  -Join the two tables
  -put info in the message line about every table in the system?
  -Close database
  -Put info about pager profiler into message line: "Number of disk seeks/reads/writes/IOs
  -Put into message line: 'test_tbl_natural_join() done:' 
-DONE*/
void test_tbl_natural_join(char const* my_tbl, char const* yr_tbl) {
  put_msg(INFO, "test_tbl_natural_join (\"%s\", \"%s\") ...\n", my_tbl, yr_tbl);

  test_tbl_write(yr_tbl);

  open_db();

  tbl_p tbl_m = get_table(my_tbl);
  tbl_p tbl_y = get_table(yr_tbl);
  
  table_natural_join(tbl_m, tbl_y);

  put_db_info(DEBUG);
  close_db();
  /* put_pager_info(DEBUG, "After close_db"); */

  put_pager_profiler_info(INFO);
  put_msg(INFO,  "test_tbl_natural_join() done.\n\n");
}

/*
-Creates a simple test table with two int fields.
-The ID field is filled with an integer ranging from 0 to num_records
-The second field is filled with integers ranging from 0 to num_records, and is filled either only with even numbers or odd numbers depending on the "odd" argument
-table_name = name of table
-num_records = number of records to be appended
-fields1 = string name of first field
-field2 = string name of second field
-odd = 1 if odd numbers are to be included*/
void create_test_tbl(char const* tbl_name, int num_records, char *field1, char *field2, int odd)
{
  open_db();

  char *attrs[] = {field1, field2};


  int attr_types[] = {INT_TYPE, INT_TYPE};
  schema_p sch = create_test_schema(tbl_name, 2, attrs, attr_types);

  record record;

  //Fill table with odd AND even numbers
  if(odd == 1){
    for (int i = 0; i < num_records; i++){
      record = new_record(sch);
      fill_record(record, sch, i, i);
      append_record(record, sch);
    }
  }
  //Fill table only with even numbers
  else if(odd == 0){
    for (int i = 0; i < num_records; i++){
      record = new_record(sch);
      fill_record(record, sch, i, i*2);
      append_record(record, sch);
    }
  }
  
  close_db();
}


void MY_test_tbl_natural_join(tbl_p left, tbl_p right)
{
  table_natural_join(left, right);

  put_db_info(DEBUG);

  put_pager_profiler_info(INFO);
  put_msg(INFO,  "test_tbl_natural_join() done.\n\n");
}