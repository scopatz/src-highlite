(*
TODO just a comment

foo bar
*)

displayName(choose file with prompt "Select a file:") --if double-clicked
return -- not needed, but shows that the script stops here when "run"

on open of finderObjects -- "open" handler triggered by drag'n'drop launches
  repeat with i in (finderObjects) -- in case multiple objects dropped on applet
    displayName(i) -- show file/folder's info
    if folder of (info for i) is true then -- process folder's contents too
      tell application "Finder" to set temp to (entire contents of i)
      repeat with j in (temp)
        display dialog j as string -- example of doing something with each item
      end repeat
    end if
  end repeat
end open

if CurState is 0 then
	connect configuration "pccard-serial"
end if

on GetParentPath(myPath)
  set oldDelimiters to AppleScript's text item delimiters -- always preserve original delimiters
  set AppleScript's text item delimiters to {":"}
  set pathItems to text items of (myPath as text)
  if last item of pathItems is "" then set pathItems to items 1 thru -2 of pathItems -- its a folder
  set parentPath to ((reverse of the rest of reverse of pathItems) as string) & ":"
  (* The above line works better than the more obvious set parentPath to ((items 1 thru -2 of pathItems) as string) & ":"
     because it will not return an error when passed a path for a volume, i.e., "Macintosh HD:", but rather will return ":"
     indicating the desktop is the root of the given path. Andy Bachorski <andyb@APPLE.COM> *)
  set AppleScript's text item delimiters to oldDelimiters -- always restore original delimiters
  return parentPath
end GetParentPath
