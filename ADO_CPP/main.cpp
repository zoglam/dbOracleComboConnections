#include <iostream>
#include <cstdio>
#include <tchar.h>
#include <time.h>

using namespace std;

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "EndOfFile")

#define CONN_COUNT 50

class SqlConn
{
private:
    _ConnectionPtr cn = NULL;
    _RecordsetPtr rs = NULL;

public:
    SqlConn(
        const char* provider,
        const char* server,
        const char* user,
        const char* pass,
        const bool ispooled)
    {
        CoInitialize(NULL);
        _ConnectionPtr cn("ADODB.Connection");
        _RecordsetPtr rs("ADODB.Recordset");
        this->cn = cn;
        this->rs = rs;
        cn->Provider = provider;
        if (ispooled)
            cn->ConnectionString = "Pooling=True;Min Pool Size=100";
        cn->Open(server, user, pass, adConnectUnspecified);
        cout << (LPCSTR)(_bstr_t)cn->ConnectionString;
    }

    ~SqlConn()
    {
        rs->Close();
        cn->Close();
        rs = NULL;
        cn = NULL;
        CoUninitialize();
    }

    void execute(const char* query)
    {

        rs = cn->Execute(query, NULL, adCmdText);

        for (size_t count = 0; count < 10 || rs->EndOfFile; ++count)
        {
            for (long i = 0; i < rs->Fields->Count; ++i)
            {
                _variant_t var = rs->Fields->GetItem(i)->Value;
                /*
                if (var.vt == VT_NULL)
                    cout << "null"
                    << "|";
                else
                    cout << (LPCSTR)(_bstr_t)rs->Fields->GetItem(i)->Value << "|";
                    */
            }
            //cout << endl;
            rs->MoveNext();
        }
    }
};

void executeWithTimeTracking(SqlConn *connection, const int conn_count) {
    clock_t startTime, endTime;
    double sum = 0;

    for (size_t i = 0; i < conn_count; i++) {
        startTime = clock();
        connection->execute("SELECT * FROM customers");
        endTime = clock();
        sum += (endTime - startTime) / (double)CLOCKS_PER_SEC;
        cout << "Conn " << i + 1 << ": " << (endTime - startTime) / (double)CLOCKS_PER_SEC << " sec" << endl;
    }
    cout << "Avg: " << sum / conn_count;
}

int main()
{
    try
    {
        SqlConn* conn1 = new SqlConn("OraOLEDB.Oracle", "localhost:1521/xe", "SYSTEM", "123", true);
        SqlConn* conn2 = new SqlConn("OraOLEDB.Oracle", "localhost:1521/xe", "SYSTEM", "123", false);

        cout << "--With pool--" << endl;
        executeWithTimeTracking(conn1, 50);        
        cout << endl << endl;
        cout << "--Without pool--" << endl;
        executeWithTimeTracking(conn2, 50);

        delete conn1;
        delete conn2;
    }
    catch (_com_error& e)
    {
        printf("Error:\n");
        printf("Code = %08lx\n", e.Error());
        printf("Code meaning = %s\n", (char*)e.ErrorMessage());
        printf("Source = %s\n", (char*)e.Source());
        printf("Description = %s\n", (char*)e.Description());
    }
    return 0;
}