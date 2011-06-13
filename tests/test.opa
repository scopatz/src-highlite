// single line comment
/*
/* multi line comment */
*/

ident `ident` `ident+[['`
function() `FuNcTiOn@`(1,2)

//int/float literals
1 1. 2.0 3. 5.6e-5 0x12 0b0111001 0o1234567 -5.6

//directives
@opensums @private @publish_async

//strings literals
"yeay" "with an expr: {"yeay"}" "with an expr: {String.lowercase("yeay")}"

// ids
<div id=#div/>

// bypass
`+` = %% BslPervasives.int_add %%

// bindings
x = 1
`poi` = 1
// type binding
type Queue.t = ...
// bindings in modules
Queue = {{
  pop() = ...
  empty = ...
}}
// bindings in records
{~a ~b c=2}
