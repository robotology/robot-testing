with RTF; use RTF;
With RTF.Asserter;
With MyTest; use MyTest;

package body MyTest is
    
    procedure Create is 
    begin
        SetTest(new MyTest, "MyTest");
    end;

    function Setup (Self : in out MyTest;
                    Parameters : String) return Boolean is
        pragma Unreferenced (Self);
        pragma Unreferenced (Parameters);
    begin
        Asserter.TestReport("Preparing setup...");
        return True;
    end Setup;

    procedure TearDown (Self : in out MyTest) is
         pragma Unreferenced (Self);  
    begin
        Asserter.TestReport("Tearing down...");
    end;

    procedure Run (Self : in out MyTest) is
         pragma Unreferenced (Self);  
    begin
        Asserter.TestCheck(5>3, "5 is bigger than 3.");
        Asserter.TestCheck(5<3, "5 is smaller than 3.");
    end;

end MyTest;
