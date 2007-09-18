%{
/*
 * Copyright (C) 1999-2007 Lorenzo Bettini <http://www.lorenzobettini.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>

#include "messages.h"
#include "stringdef.h"
#include "statelangelem.h"
#include "statestartlangelem.h"
#include "stringlistlangelem.h"
#include "delimitedlangelem.h"
#include "langelems.h"
#include "langdefparserfun.h"
#include "langdefscanner.h"
#include "vardefinitions.h"
#include "namedsubexpslangelem.h"

using std::cerr;
using std::string;

static void yyerror( const char *s ) ;
static void yyerror( const string &s ) ;

LangElems *current_lang_elems = 0;
VarDefinitions *vardefinitions = 0;

#define UPDATE_REDEF(el, r) if (r == 1) { el->setRedef(); } else if (r == 2) { el->setSubst(); }
#define ADD_ELEMENT(elems, elem) \
  if (elem) { \
    if (elem->isRedef()) \
      elems->redef(elem); \
    else if (elem->isSubst()) \
      elems->subst(elem); \
    else \
      elems->add(elem); \
  }

struct Key : public ParserInfo
{
  const string *key;

  ~Key() { delete key; }
};

// this is a trick since ElementNames is a typedef and cannot
// be used in the union below
struct ElementNamesList : ElementNames {
};

%}

%union {
  int tok ; /* command */
  bool booloption ;
  const std::string * string ; /* string : id, ... */
  class StringDef *stringdef;
  class StringDefs *stringdefs;
  class LangElem *langelem;
  class StateLangElem *statelangelem;
  class StateStartLangElem *statestartlangelem;
  class LangElems *langelems;
  class NamedSubExpsLangElem *namedsubexpslangelem;
  struct Key *key;
  class ElementNamesList *keys;
  int flag ;
};

%token <tok> BEGIN_T END_T ENVIRONMENT_T STATE_T MULTILINE_T DELIM_T START_T ESCAPE_T NESTED_T EXIT_ALL EXIT_T VARDEF_T REDEF_T SUBST_T NONSENSITIVE_T
%token <string> KEY STRINGDEF REGEXPNOPREPROC VARUSE BACKREFVAR
%token <stringdef> REGEXPDEF

%type <stringdef> stringdef escapedef stringdefwreferences
%type <stringdefs> stringdefs
%type <langelem> elemdef
%type <langelems> elemdefs
%type <statestartlangelem> complexelem
%type <booloption> multiline startnewenv nested nonsensitive
%type <tok> exitall redefsubst
%type <key> key;
%type <keys> keys;

%%

allelements :
        {
          /* no definitions (i.e., empty a .lang file with no definition) */
          /* such as, default.lang */
          /* synthetize a normal elem that catches everything */
          current_lang_elems = new LangElems;
          StringDefs *defs = new StringDefs;
          defs->push_back (new StringDef("(?:.*)"));
          current_lang_elems->add(new StringListLangElem("normal", defs, false));
        }
        | elemdefs { current_lang_elems = $1; }
;

elemdefs : elemdefs elemdef {
              $$ = $1;
              ADD_ELEMENT($$, $2);
           }
          | elemdef {
              $$ = new LangElems;
              ADD_ELEMENT($$, $1);
          }
         ;

elemdef : redefsubst complexelem exitall
          {
            $$ = $2;
            if ($3 > 1)
              $2->set_exitall();
            if ($3 > 0)
              $2->set_exit();
            UPDATE_REDEF($2, $1);
          }
        | redefsubst startnewenv complexelem BEGIN_T elemdefs END_T
          {
            StateLangElem *statelangelem = new StateLangElem($3->getName(), $3, $5, !$2);
            $$ = statelangelem;
            $3->setStateLangElem(statelangelem);
            UPDATE_REDEF($$, $1);
          }
        | VARDEF_T KEY '=' stringdefs {
            vardefinitions->add(*$2, $4);
            $$ = 0;
            delete $2;
          }
        ;

complexelem : key DELIM_T stringdef stringdefwreferences escapedef multiline nested
                {
                  $$ = new DelimitedLangElem(*($1->key), $3, $4, $5, $6, $7);
                  $$->setParserInfo($1);
                  delete $1;
                }
          | key START_T stringdef {
              $$ = new DelimitedLangElem(*($1->key), $3, 0, 0, false, false);
              $$->setParserInfo($1);
              delete $1;
            }
          | key '=' stringdefs nonsensitive {
              $$ = new StringListLangElem(*($1->key), $3, $4);
              $$->setParserInfo($1);
              delete $1;
            }
          | '(' keys ')' '=' REGEXPNOPREPROC {
          		$$ = new NamedSubExpsLangElem($2, new StringDef(*$5));
                        $$->setParserInfo(parsestruct->file_name, @1.first_line);
          		delete $5;
            } 
        ;

key: KEY {
    $$ = new Key;
    $$->key = $1;
    $$->setParserInfo(parsestruct->file_name, @1.first_line);
  }
;

keys: keys ',' KEY 
    {
        $$ = $1;
        $$->push_back(*$3);
        delete $3;
    }
    | KEY
    {
    	$$ = new ElementNamesList;
    	$$->push_back(*$1);
        delete $1;
    }
;

escapedef : ESCAPE_T stringdef { $$ = $2; }
        | { $$ = 0; }
        ;

exitall: EXIT_ALL { $$ = 2; }
        | EXIT_T { $$ = 1; }
        | { $$ = 0; }
        ;

startnewenv : ENVIRONMENT_T { $$ = true; }
        | STATE_T { $$ = false; }
          ;

multiline : MULTILINE_T { $$ = true; }
            | { $$ = false; }
            ;

redefsubst : REDEF_T { $$ = 1; }
           | SUBST_T { $$ = 2; }
            | { $$ = 0; }
            ;

nested : NESTED_T { $$ = true; }
            | { $$ = false; }
            ;

nonsensitive : NONSENSITIVE_T { $$ = true; }
            | { $$ = false; }
            ;

stringdefs : stringdefs ',' stringdef { $$ = $1; $$->push_back($3); }
            | stringdef {
                $$ = new StringDefs;
                $$->push_back($1); }
           ;

stringdefwreferences : REGEXPDEF {
              $$ = $1;
            }
          | STRINGDEF {
              $$ = new StringDef(*$1, true);
              delete $1;
            }
          | REGEXPNOPREPROC {
              $$ = new StringDef(*$1);
              delete $1;
            }
          | VARUSE {
              if (! vardefinitions->contains(*$1)) {
                yyerror("undefined variable " + *$1);
              }
              $$ = new StringDef(vardefinitions->getVar(*$1));
              delete $1;
            }
          | BACKREFVAR {
              $$ = new StringDef(*$1);
              $$->setBackRef(true);
              delete $1;
            }
          | stringdefwreferences '+' stringdefwreferences {
              $$ = StringDef::concat($1, $3);
              delete $1;
              delete $3;
            }
          ;

stringdef : REGEXPDEF {
              $$ = $1;
            }
          | STRINGDEF {
              $$ = new StringDef(*$1, true);
              delete $1;
            }
          | REGEXPNOPREPROC {
              $$ = new StringDef(*$1);
              delete $1;
            }
          | VARUSE {
              if (! vardefinitions->contains(*$1)) {
                yyerror("undefined variable " + *$1);
              }
              $$ = new StringDef(vardefinitions->getVar(*$1));
              delete $1;
            }
          | stringdef '+' stringdef {
              $$ = StringDef::concat($1, $3);
              delete $1;
              delete $3;
            }
          ;

%%

extern int langdef_lex_destroy (void);

void
yyerror( const char *s )
{
  exitError(s, parsestruct);
}

void
yyerror( const string &s )
{
  yyerror(s.c_str());
}

LangElems *
parse_lang_def()
{
  vardefinitions = new VarDefinitions;
  parsestruct = new ParseStruct("", "stdin");
  langdef_parse();
  delete parsestruct;
  delete vardefinitions;
  parsestruct = 0;
  vardefinitions = 0;

  // release scanner memory
  langdef_lex_destroy ();

  return current_lang_elems;
}

LangElems *
parse_lang_def(const char *path, const char *name)
{
  vardefinitions = new VarDefinitions;
  parsestruct = new ParseStruct(path, name);
  open_file_to_scan(path, name);
  langdef_parse();
  delete parsestruct;
  delete vardefinitions;
  parsestruct = 0;
  vardefinitions = 0;

  // release scanner memory
  langdef_lex_destroy ();

  return current_lang_elems;
}

