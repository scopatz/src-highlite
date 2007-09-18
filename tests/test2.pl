#! /usr/bin/env perl

use strict;
use warnings;

"I'm happy because of $x!"
qq~I'm happy because of $x!~
qq{I'm happy because of $x!}
qq|I'm happy because of $x!|
qq#I'm happy because of $x!#
qq!I'm happy because of $x\!!

'The variable is called $var.'
q~The variable is called $var.~
q|The variable is called $var.|
q{The variable is called $var.}
q[The variable is called $var.]
q#The variable is called $var.#
q!The variable is called $var.! 

my $port = $ARGV[0];

# prepare freqently used regexes
my $trailing_comment      = qr#;\s*\#.*#;
my $leading_comment       = qr|(?:^\|\n)\s*#.*|;
my $leading_comment       = qr<(?:^\|\n)\s*#.*>;
my $leading_comment       = qr[(?:^\|\n)\]\s*#.*];
my $connecting_backslash  = qr@\s*\\\n\s*@;

my $quick_check = qr{:$port}i;

my $dependency  = qr{depends_(?=[brl])(?:build|run|lib)(?:-(?:append|delete))?
                  .*
                  (?=[plb])(?:port|(?:path|lib|bin):[^:]+):(?i:${port}|$port)(\{\})(?:\s|$)}x;

my $dependency  = qr{
                      (?=[plb])(?:port|(?:path|lib|bin):[^:]+)  # kind
                      :                                         # separator
                      (?i:${port})(?:\s|$)                      # name
                    }x; 

$/ = ".\n";

while (defined(my $portfile = <*/*/Portfile>)) { 
  @ARGV = $portfile;

  while (<>) {
    # make a quick and dirty check if the port has a remote chance of
    # depending on $port
    if ($_ =~ m\$quick_check|foo(.*)\i) {

      s#$connecting_backslash|a\#b#\# #g;      # merge backslash-connected lines
      s#$connecting_backslash|a\#b#\# #;      # merge backslash-connected lines
      s#$connecting_backslash|a\###;      # merge backslash-connected lines
      s/$leading_comment|a\/b/a\/b/g;            # remove leading comments
      s{$trailing_comment|\}}{\}}g;          # remove trailing comments
      s($trailing_comment|\))(\))g;          # remove trailing comments
      s<$trailing_comment|\>><\>>g;          # remove trailing comments
      s[$trailing_comment|\]][a\]b]g;          # remove trailing comments
      s|$trailing_comment\||a\|b|g;          # remove trailing comments
      s@$trailing_comment|(a\@b)@(bar\@)@g;          # just for test
      s_$connectingbackslash|a\_b_\_ _g;      # merge backslash-connected lines
      s\$trailing_comment|(a\\b)\(bar\\)\g;          # just for test

    s-[a\-z]{3}-fu- ;   # just for test
    s^\^foo^fu^ ;   # just for test
    s$foo(\w{3})\$$fu\$1$ ;   # just for test
    s!foo(\w{3})\!!fu\$1! ;   # just for test
    s?foo(\w{3})\??fu\$1? ;   # just for test
    s*foo(\w{3})\**fu\$1* ;   # just for test

    # let's some more exotic syntaxes ;-)
    s?foo(\w{3})\?\$?!fu\!1! ;   # just for test
    s$foo(\w{3})\$$^fu\^\$1^ ;   # just for test
    s$foo(\w{3})\$$ ^fu\^\$1^ ;   # just for test
    s$foo(\w{3})\$$ ^fu\^\$1^g ;   # just for test
    s#foo(\w{3})\## ^fu\^\$1^g ;   # just for test
    s$foo(\w{3})\$$ #fu\#\$1#g ;   # just for test

      if ($_ =~ m{$dependency}) {
        $portfile =~ s{/Portfile$}{};   # remove trailing '/Portfile'
        print "$portfile\n";
      }
    }
  }
}
