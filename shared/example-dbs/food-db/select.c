#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main(int argc, char **argv)
{
    sqlite3 *db;

    int rc = sqlite3_open("foods.sqlite3", &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_stmt *stmt;
    char const*tail;
    char *sql = "select * from episodes;";

    rc = sqlite3_prepare(db, sql, (int)strlen(sql), &stmt, &tail);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    rc = sqlite3_step(stmt);
    int ncols = sqlite3_column_count(stmt);

    while(rc == SQLITE_ROW) {

        for(int i = 0; i < ncols; i++) {
            fprintf(stdout, "'%s' ", sqlite3_column_text(stmt, i));
        }

        fprintf(stdout, "\n");

        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return 0;
}
