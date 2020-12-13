program Project1;

{$APPTYPE CONSOLE}

{$R *.res}

uses
    System.SysUtils,
    System.DateUtils,
    FireDAC.Comp.Client,
    FireDAC.Stan.Async,
    FireDAC.Stan.Def,
    FireDAC.Phys.Intf,
    FireDAC.Phys.SQLite,
    FireDAC.DApt;

var
    fConn: TFDConnection;
    fQry: TFDQuery;
    fDrv: TFDPhysSQLiteDriverLink;
    today : TDateTime;
    sum: Double;
    i: Integer;
    count: Integer;

begin
    count := 1;
    sum := 0;
    for i := 0 to count-1 do begin
        fConn := TFDConnection.Create(Nil);
        fDrv := TFDPhysSQLiteDriverLink.Create(Nil);
        fQry := TFDQuery.Create(Nil);
        try
          today := Now;
          fConn.Connected := false;
          with fConn.Params do begin
            Clear;
            Add('DriverID=SQLite');
            Add('Database=../../db.db');
            //Add('Pooled=True');
          end;
          fQry.Connection := fConn;
          fQry.SQL.Text := 'SELECT * FROM CUSTOMERS';
          fConn.Connected := true;
          fQry.Open;
          while Not fQry.Eof do begin
            //WriteLn(fQry.FieldByName('CUSTOMERID').AsString, '    ', fQry.FieldByName('COMPANYNAME').AsString);
            fQry.Next;
          end;
          fConn.Close;
        finally
          fConn.Free;
          fDrv.Free;
          fQry.Free;
        end;
        WriteLn('Conn ',i+1,' Time:',(Now - today), ' seconds');
        sum := sum + Now - today;
    end;
    WriteLn('Avg: ', sum/(count));
    ReadLn;
end.
