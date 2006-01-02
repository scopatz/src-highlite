#! /usr/bin/python

"""
This is a test for the handling of
comments and string literals in Python
"""

'''
This is a test for the handling of
comments and string literals in Python
'''

"And this is a string meant as comment"

def test():		# The test routine
  '''
  It does nothing but printing different strings
  '''

  """
  It does nothing but printing different strings
  """

  print "This is the first test",
  print 'and this the second'

  'Here start the multi-lined outputs'

  print '''
Here we have
a multi-line
string.
'''

  print """
Here we have
a multi-line
string.
"""
  print '''
And this is a
second one
'''
  # End of printing
  pass			# A NOP at last

"""
"""
'And here the fun starts'
test()

table = { 'S'  : ['5'],
 'a'  : ['4','a','@'],
 'b'  : ['8','B'],
 "ps" : ["Pz"],
 'ss' : ['5S','S5'],
 'es' : ['3Z','3z'],
 'ou' : ['00'] }
