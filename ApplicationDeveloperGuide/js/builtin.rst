..
.. ReStructuredText
..
.. Copyright 2020-2021 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _js.builtin:

================
Built-in Objects
================

This section lists all the JavaScript built-in objects and their support status.
For the complete reference about these built-in objects, consult the `ECMA 5.1 specification <https://www.ecma-international.org/ecma-262/5.1/#sec-15>`_.

For a description and usage examples of each method or property, consult a JavaScript documentation such as `Mozilla Developer Reference <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects>`_.

Array
*****
- Array (len)
- isArray ( arg )
- toString ( )
- **[excluded]** toLocaleString ( )
- concat ( [ item1 [ , item2 [ , … ] ] ] )
- join (separator)
- pop ( )
- push ( [ item1 [ , item2 [ , … ] ] ] )
- reverse ( )
- shift ( )
- slice (start, end)
- sort (comparefn)
- **[excluded]** splice (start, deleteCount [ , item1 [ , item2 [ , … ] ] ] )
- unshift ( [ item1 [ , item2 [ , … ] ] ] )
- indexOf ( searchElement [ , fromIndex ] )
- lastIndexOf ( searchElement [ , fromIndex ] )
- every ( callbackfn [ , thisArg ] )
- some ( callbackfn [ , thisArg ] )
- forEach ( callbackfn [ , thisArg ] )
- map ( callbackfn [ , thisArg ] )
- filter ( callbackfn [ , thisArg ] )
- **[excluded]** reduce ( callbackfn [ , initialValue ] )
- **[excluded]** reduceRight ( callbackfn [ , initialValue ] )
- length

Boolean
*******
- Boolean (value)
- Boolean.prototype.toString ( )
- Boolean.prototype.valueOf ( )

Date
****
- **[excluded]**

Error
*****
- **[excluded]**

Function
********
- **[excluded]** Function (p1, p2, … , pn, body)
- length
- **[excluded]** toString ( )
- apply (thisArg, argArray)
- call (thisArg [ , arg1 [ , arg2, … ] ] )
- **[excluded]** bind (thisArg [, arg1 [, arg2, …]])
- [[Call]]
- [[Construct]]

Global
******
- NaN
- Infinity
- undefined
- **[excluded]** eval ( x )
- parseInt (string , radix)
- parseFloat (string)
- isNaN (number)
- isFinite (number)
- **[excluded]** escape (string)
- **[excluded]** unescape (string)
- **[excluded]** decodeURI (encodedURI)
- **[excluded]** decodeURIComponent (encodedURIComponent) 
- **[excluded]** encodeURI (uri)
- **[excluded]** encodeURIComponent (uriComponent)

JSON
****
- parse ( text [ , reviver ] )
- stringify ( value , [ replacer [ , space ] ] )

Math
****
- E
- LN10
- LN2
- LOG2E
- LOG10E
- PI
- SQRT1_2
- SQRT2
- abs (x)
- acos (x)
- asin (x)
- atan (x)
- atan2 (y, x)
- ceil (x)
- cos (x)
- exp (x)
- floor (x)
- log (x)
- max ( [ value1 [ , value2 [ , … ] ] ] )
- min ( [ value1 [ , value2 [ , … ] ] ] )
- pow (x, y)
- random ( )
- round (x)
- sin (x)
- sqrt (x)
- tan (x)

Number
******
- Number (value)
- MAX_VALUE
- MIN_VALUE
- NaN
- NEGATIVE_INFINITY
- POSITIVE_INFINITY
- **[excluded]** toString ( [ radix ] )
- **[excluded]** toLocaleString()
- valueOf ( )
- **[excluded]** toFixed (fractionDigits)
- **[excluded]** toExponential (fractionDigits)
- **[excluded]** toPrecision (precision)

Object
******
- Object ( [ value ] )
- Object.getPrototypeOf ( O )
- Object.getOwnPropertyDescriptor ( O, P )
- Object.getOwnPropertyNames ( O )
- Object.create ( O [, Properties] )
- Object.defineProperty ( O, P, Attributes )
- Object.defineProperties ( O, Properties )
- **[excluded]** Object.seal ( O )
- **[excluded]** Object.freeze ( O )
- **[excluded]** Object.preventExtensions ( O )
- Object.isSealed ( O )
- Object.isFrozen ( O )
- Object.isExtensible ( O )
- Object.keys ( O )
- toString ( )
- **[excluded]** toLocaleString ( )
- valueOf ( )
- hasOwnProperty (V)
- isPrototypeOf (V)
- propertyIsEnumerable (V)

Regex
*****
- RegExp (pattern, flags)
- exec (string)
- test (string)
- toString ()

String
******
- String (value)
- fromCharCode ( [ char0 [ , char1 [ , … ] ] ] )
- toString ( )
- valueOf ( )
- charAt (pos)
- charCodeAt (pos)
- concat ( [ string1 [ , string2 [ , … ] ] ] )
- indexOf (searchString, position)
- lastIndexOf (searchString, position)
- **[excluded]** localeCompare (that)
- match (regexp)
- replace (searchValue, replaceValue)
- **[excluded]** search (regexp)
- slice (start, end)
- split (separator, limit)
- **[excluded]** substr (start [ , length ] )
- substring (start, end)
- toLowerCase ( )
- **[excluded]** toLocaleLowerCase ( )
- toUpperCase ( )
- **[excluded]** toLocaleUpperCase ( )
- trim ( )
- length
- [[GetOwnProperty]] ( P )
