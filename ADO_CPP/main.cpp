#include <iostream>
#include <cstdio>
#include <tchar.h>

using namespace std;

#import "msado15.dll" no_namespace rename("EOF", "EndOfFile")

class SqlConn
{
private:
    _ConnectionPtr cn = NULL;
    _RecordsetPtr rs = NULL;

public:
    SqlConn(
        const char *provider,
        const char *server,
        const char *user,
        const char *pass)
    {
        CoInitialize(NULL);
        _ConnectionPtr cn("ADODB.Connection");
        _RecordsetPtr rs("ADODB.Recordset");
        this->cn = cn;
        this->rs = rs;
        cn->Provider = provider;
        cn->ConnectionString = "Pool=True";
        cn->Open(server, user, pass, adConnectUnspecified);
    }

    ~SqlConn()
    {
        rs->Close();
        cn->Close();
        rs = NULL;
        cn = NULL;
        CoUninitialize();
    }

    void execute(const char *query)
    {

        rs = cn->Execute(query, NULL, adCmdText);

        for (size_t count = 0; count < 10 || !rs->EndOfFile; ++count)
        {
            for (long i = 0; i < rs->Fields->Count; ++i)
            {
                _variant_t var = rs->Fields->GetItem(i)->Value;
                if (var.vt == VT_NULL)
                    cout << "null"
                         << "|";
                else
                    cout << (LPCSTR)(_bstr_t)rs->Fields->GetItem(i)->Value << "|";
            }
            cout << endl;
            rs->MoveNext();
        }
    }
};

int main()
{
    try
    {
        SqlConn *conn = new SqlConn("OraOLEDB.Oracle", "localhost:1521/xe", "SYSTEM", "123");
        conn->execute("SELECT * FROM customers");
        delete conn;
    }
    catch (_com_error &e)
    {
        printf("Error:\n");
        printf("Code = %08lx\n", e.Error());
        printf("Code meaning = %s\n", (char *)e.ErrorMessage());
        printf("Source = %s\n", (char *)e.Source());
        printf("Description = %s\n", (char *)e.Description());
    }
    return 0;
}