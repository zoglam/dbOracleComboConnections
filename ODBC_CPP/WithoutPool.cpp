#include <stdio.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#define CONNECTIONS_COUNT 3

int main()
{
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLRETURN retcode;
    LARGE_INTEGER t0, freq, t[CONNECTIONS_COUNT];

    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
    {
        printf("SQLAllocHandle success\n");
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
                                (SQLPOINTER)SQL_OV_ODBC3, 0);

        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
        {
            printf("SQLSetEnvAttr success\n\n");
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&t0);

            for (size_t i = 0; i < CONNECTIONS_COUNT; i++)
            {
                retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                {
                    printf("Conn: %d - SQLAllocHandle success\n", i + 1);
                    retcode = SQLDriverConnect(
                        hdbc,
                        NULL,
                        (SQLTCHAR *)"DRIVER={Microsoft ODBC for Oracle};SERVER=(localhost:1521/xe);UID=SYSTEM;PWD=123",
                        //(SQLTCHAR *)"Driver={Microsoft ODBC for Oracle};Server=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=localhost)(PORT=1521))(CONNECT_DATA=(SID=xe)));Uid=SYSTEM;Pwd=123;",
                        //(SQLTCHAR *)"Driver={SQL Server};DSN='';Server=MSSERVER;Database=pubs;",
                        SQL_NTS,
                        NULL,
                        0,
                        NULL,
                        SQL_DRIVER_COMPLETE);

                    printf("retcode = %d\n", retcode);
                    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
                    {
                        printf("SQLConnect success\n\n");
                        SQLDisconnect(hdbc);
                    }
                    else
                    {
                        printf("SQLConnect failed\n\n");
                    }
                    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
                    QueryPerformanceCounter(&t[i]);
                }
            }
        }
        for (size_t i = 1; i < CONNECTIONS_COUNT; i++)
        {
            printf("Conn diff between: %d-%d Time: %7.2f ms\n", i, i + 1, (double)(t[i].QuadPart - t[i - 1].QuadPart) * 1000 / freq.QuadPart);
        }
        printf("Average: %5.2f ms\n", (double)(t[CONNECTIONS_COUNT - 1].QuadPart - t[0].QuadPart) * 1000 / freq.QuadPart / (CONNECTIONS_COUNT - 1));
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
    }
}
