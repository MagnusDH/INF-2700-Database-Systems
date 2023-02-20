/** @file interpreter.h
 * @brief Interpreter of database commands
 * @author Weihai Yu
 *
 * Reading and running SQL-like commands.
 *
 * For simplicity, we restrict the syntax of the commands.
 * Please read the source code to see the restrictions.
 */

#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

/*
-Read and run commands. 
-Goes through tokens in the input stream
-Calls different functions based in the user input
-functions: quit, skip_line, show_help_info, show_database, print_str, create_tbl, drop_tbl, insert_row, select_rows, error_near
-DONE*/
extern void interpret (int argc, char* argv[]);

#endif