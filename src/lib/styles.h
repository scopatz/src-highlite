#ifndef STYLES_H
#define STYLES_H

#include "my_set.h"

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

typedef enum { ISBOLD=1, ISITALIC, ISUNDERLINE, ISFIXED, ISNOTFIXED, ISNOREF } StyleConstant;
typedef std::list<StyleConstant> StyleConstants;
typedef boost::shared_ptr<StyleConstants> StyleConstantsPtr;
typedef StyleConstants::const_iterator StyleConstantsIterator;

using std::string;

class Style
{
 protected:
  string StyleName ;
  string color ;
  StyleConstantsPtr styles;

 public:
  Style( const string &n ) : StyleName( n ) {}
  Style( const string &n, const string &c );

  void setStyles( StyleConstantsPtr t ) { styles = t; }
  const StyleConstantsPtr getStyleConstants() const { return styles; }

  string GetName() const { return StyleName ; }
  string GetColor() const { return color ; }
  void SetColor( const string &col ) { color = col ; }
  void Print() ;
} ;

struct StyleLess
{
  typedef std::less<string> value_compare;

  value_compare value_comp;

 public:
  bool operator() (const Style *t1, const Style *t2) const
  { return value_comp(t1->GetName(),t2->GetName()); }
};

class Styles : protected set<Style *, StyleLess>
{
  typedef set<Style *, StyleLess> container_type;

 public:
  using container_type::begin;
  using container_type::end;
  using container_type::const_iterator;

  Styles() {}
  ~Styles();
  bool AddStyle( Style *t ) { return insert( t ).second ;  }
  Style *GetStyle( const string &name ) ;
} ;

inline Style *
Styles::GetStyle( const string &name )
{
  Style *temp = new Style (name);
  const_iterator p = find (temp);
  delete temp;
  if (p != end ())
    return *p;

  return 0;
}

#endif
