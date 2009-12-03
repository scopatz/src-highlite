$6 !~ /^ack/ && $5 !~ /[SFR]/   {
        # given a tcpdump ftp trace, output one line for each send
        # in the form
        #   <send time> <seq no>
        # where <send time> is the time packet was sent (in seconds with
        # zero at time of first packet) and <seq no> is the tcp sequence
        # number of the packet divided by 1024 (i.e., Kbytes sent).
        #
        # convert time to seconds
        n = split ($1,t,":")
        tim = t[1]*3600 + t[2]*60 + t[3]
        if (! tzero) {
                tzero = tim
                OFS = "\t"
        }
        # get packet sequence number
        i = index($6,":")
        printf "%7.2f\t%g\n", tim-tzero, substr($6,1,i-1)/1024
        }

BEGIN{
  buffer = "";
}

/\015*$/ {
  gsub(/\015*$/, "");
}

/^%%S NL/ {
  print "";
  next;
}

/^%%S/ {
  gsub (/^%%S/, "%%" );
  print;
  next;
}

/^\\Syntax/ {
  printing = 1;
  indentation = 0;
  next;
}

// {
  if (buffer != "") {
    gsub(/^ */, "");
    $0 = buffer $0;
  }
  buffer = "";
}

/\|\|/ {
  gsub(/\|\|/, "-");
}

/^  */{
  gsub(/^  */, indspaces);
}

/\\Something/ {
  $0 = gensub(/\\Something *{([^}]*)}/, "<\\1>", "g");
}

/\\Literal/ {
  $0 = gensub(/\\Literal *{([^}]*)}/, "\\1", "g");
}

/\\Tex/ {
  $0 = gensub(/\\Tex *{([^}]*)}/, "\\1", "g");
}

/\\Optional/ {
  $0 = gensub(/\\Optional *{([^}]*)}/, "[\\1]", "g");
}

/\\Means/ {
  gsub(/\\Means/, "-->");
  indentation = match($0, /-->/);
  indspaces = " ";
  for(i=0; i < indentation; i++)
    indspaces = indspaces " ";
}

/\\Lbrace/ {
  gsub(/\\Lbrace/, "{");
}

/\\Rbrace/ {
  gsub(/\\Rbrace/, "}");
}

/\\Or/ {
  gsub(/\\Or/, "|");
}

/\\Next/ {
  gsub(/\\Next /, "");
}

/\\Whatever/ {
  whatind = 57;
  whatpos = match($0, /\\Whatever/);
  b = substr($0, 0, whatpos - 1)
  c = substr($0, whatpos)
  c = gensub(/\\Whatever *{([^}]*)}/, "(\\1)", "g", c);
  $0 = b;
  for(i = whatpos; i < whatind; i++)
    $0 = $0 " ";
  $0 = $0 c;
}

/^}/ {printing = 0;}

/% *$/ {
  gsub(/% *$/, "");
  buffer = $0;
  next;
}

/^ *$/ {
  $0 = "================= ERROR";
}

/  *$/ {
  gsub(/  *$/, "");
}

{ if (printing) print; }
