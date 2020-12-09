program Project1;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils,
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

begin
  fConn := TFDConnection.Create(Nil);
  fDrv := TFDPhysSQLiteDriverLink.Create(Nil);
  fQry := TFDQuery.Create(Nil);
  try
    fConn.Connected := false;
    with fConn.Params do
    begin
      Clear;
      Add('DriverID=SQLite');
      Add('Database=C:\Users\zoglam\Desktop\TEST\delphi\db.db');
      //Add('Pooled=True');
    end;
    fQry.Connection := fConn;
    fQry.SQL.Text := 'SELECT * FROM lol';
    fConn.Connected := true;
    fQry.Open;
    while Not fQry.Eof do begin
      WriteLn(fQry.FieldByName('id').AsString, '    ', fQry.FieldByName('name').AsString);
      fQry.Next;
    end;
    fConn.Close;
  finally
    fConn.Free;
    fDrv.Free;
    fQry.Free;
  end;
  ReadLn;
end.

