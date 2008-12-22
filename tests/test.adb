--
--  This is a classical Hello world example written in Ada
--  to test source-highlight with Ada programs.
--
--  to perform a html translation type:
--
--  source-highlight -s ada -f html --input test.ada --output test.ada.html
--
--  or type source-highlight --help for the list of options
--
--
--  written by Reto Buerki <reet@codelabs.ch>
--

with Ada.Text_IO;

procedure Test is
   Test_Int     : Integer := 10;
   --  This is an example test integer
   Test_Float   : constant Float := 10.2;
   --  This is an example test float
   Test_Boolean : Boolean := False;
   --  This is an example test boolean
   Test_Char    : Character := 'C';
   --  This is an example test character
   Test_String  : String := "Some test string";
   --  This is an example test string

   type Test_Person_Type is tagged record
      Name : String (1 .. 8);
      --  Name
      Age  : Positive := 18;
      --  Age
   end record;
   --  This is an example type

   type Test_Profession_Type is (Unknown, Medic, Fireman, Construction_Worker);
   --  Enumeration test type : All possible professions

   type Test_Employee_Type is new Test_Person_Type with record
      Profession : Test_Profession_Type := Unknown;
      --  Initial profession is not known
   end record;
   --  This is an example extension of Test_Person_Type

   subtype Test_Int_Subtype is Integer range 1 .. 9;
   --  This is an example subtype

   task Test_Greeter_Task is
      entry Run;
      --  Entry to start example task
   end Test_Greeter_Task;
   --  An example task

   task body Test_Greeter_Task is

      ------------------
      -- Get_Greeting --
      ------------------

      function Get_Greeting (Num : in Integer) return String is
      begin
         return Integer'Image (Num) & " : Hello world from an Ada task";
      end Get_Greeting;

   begin
      accept Run;
      for Index in Test_Int_Subtype'Range loop
         Ada.Text_IO.Put_Line (Get_Greeting (Num => Index));
      end loop;
   end Test_Greeter_Task;

   use Ada.Text_IO;

begin

   --  Just display some greeting

   Put_Line ("Hello world in Ada for GNU Source-highlight");
   Put_Line ("written by Reto Buerki <reet@codelabs.ch>");
   Test_Greeter_Task.Run;

end Test;
