' The script can be called via

<%@LANGUAGE="VBSCRIPT" CODEPAGE="1252"%>

if AQresponse <> "" then
  response.write(AQresponse)
else
  response.write("ERROR")
end if

%>

' Actual script follows. This could be placed in a separate file, 
' such as the smslib.asp file described above

<%
Dim method, secured, error_on_length, username, password, AQresponse
  ' User Editable Variables
  secured = 0                       ' Set to either 1 for SSL connection 
                                    ' or 0 for normal connection.
  error_on_length = 1               ' Whether to give and error on messages over 160 chracters. 
                                    ' 1 for true, 0 for false.
  username = "testusername"         ' Your aql username, can either be set here 
                                    ' or done on a per call basis from the function.
  password = "testpassword"         ' Your aql password, can either be set here
                                    ' or done on a per call basis from the function.

Dim objXMLHTTP, xml
  message = replace(message," ","+")
  Set xml = Server.CreateObject("Microsoft.XMLHTTP") 
  if secured = null or secured = 0 then
    xml.Open "POST", "http://gw1.aql.com/sms/sms_gw.php", False
    xml.setRequestHeader "Content-Type", "application/x-www-form-urlencoded"
    xml.Send "username=" & username & "&password=" & password & "&destination=" & destination & 
             "&message=" & message & "&originator=" & originator & "&flash=" & flash
  else if secured = 1 then
    xml.Open "POST", "https://gw1.aql.com/sms/sms_gw.php", False
    xml.setRequestHeader "Content-Type", "application/x-www-form-urlencoded"
    xml.Send "username=" & username & "&password=" & password & "&destination=" & destination & 
             "&message=" & message & "&originator=" & originator & "&flash=" & flash
  else
    call senderror(7)
    end if
   end if

AQresponse = xml.responseText
Set xml = nothing

End Function 


%>
