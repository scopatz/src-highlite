-- A test snippet based on
-- http://google-code-prettify.googlecode.com/svn/trunk/tests/prettify_test.html
--
-- A comment
These --> are --| not |-- comments
--but this is a comment again

module Foo(bar) where
import Blah
import BlahBlah(blah)
import Monads(Exception(..), FIO(..),unFIO,handle,runFIO,fixFIO,fio,
              write,writeln,HasNext(..),HasOutput(..))

{- nested comments
 - should {- just -}  work -}
instance Thingy Foo where
  a = b

data Foo :: (* -> * -> *) -> * > * -> * where
  Nil :: Foo a b c
  Cons :: a b c -> Foo abc -> Foo a b c

str = "Foo\\Bar"
chars = [ 'x', '\'', '\\', '\"', '\120', '\o100', '\xbeef' ] -- Escapes too
Not.A.Char = 'too long'  -- Don't barf.  Show that 't is a lexical error.

(ident, ident', Fo''o.b'ar)

(0, 12, 0x45, 0xA7, 0o177, 0O377, 0.1, 1.0, 1e3, 0.5E-3, 1.0E+45)

[1,2..10]

(#) = \x y -> s x y
  where s x y = (x+y) `mod` 13

bar (x:_) = putStrLn x

main = do
  let foo x = do { spam $ eggs x }
  foo >>= bar
