#ifndef _TESTSCHEMA_H_
#define _TESTSCHEMA_H_

#include "schema.h"

extern void test_tbl_write(char const* tbl_name);
extern void test_tbl_read(char const* tbl_name);
extern void test_tbl_natural_join(char const* my_tbl, char const* yr_tbl);


extern void create_test_tbl(char const* tbl_name, int num_records, char *field1, char *field2, int odd);
void MY_test_tbl_natural_join(tbl_p left, tbl_p right);

#endif
