#!/bin/sh

  #.*$         - comment

echo ${variable##*i} # prints "s bob"

  #.*$         - comment

echo ${variable#*n}  # prints "ame is bob"


echo ${#variable}    # prints 17

echo ${#array[*]} # prints 4


echo $# + 1 # prints 0

# Incidentally, all of the $ variables should be variable markup 
# (i.e. $#, $@, $?, $!, $*, $-, $$, $[0-9] and ${[0-9][0-9]*})

echo $#  
echo $@ $?  $! $*  $-  $$  $8 ${12}

echo "comment" ### this is a comment
