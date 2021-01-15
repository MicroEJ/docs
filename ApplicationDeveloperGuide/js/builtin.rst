..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _js.builtin:

================
Built-in objects
================

All standard built-in objects from ECMAScript 5.1 are supported.
For the complete reference about these built-in objects, consult the `ECMA 5.1 specification <https://www.ecma-international.org/ecma-262/5.1/#sec-15>`_.

For a description and usage examples of each method or property, consult a JavaScript documentation such as `Mozilla Developer Reference <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects>`_.

Excluded methods
----------------

Every method and property in the ECMAScript built-in objects library (a total of **194** properties or methods) are supported except **2** methods:

-  ``eval ( x )`` function
- ``Function ( p1, p2, … , pn, body )`` constructor

The reason is that the JavaScript compiler is not embedded in the runtime.

Built-in complete list
----------------------

Array
*****
- Array (len)
- isArray ( arg )
- join (separator)
- concat ( [ item1 [ , item2 [ , … ] ] ] )
- toString ( )
- pop ( )
- push ( [ item1 [ , item2 [ , … ] ] ] )
- reverse ( )
- shift ( )
- slice (start, end)
- sort (comparefn)
- indexOf ( searchElement [ , fromIndex ] )
- lastIndexOf ( searchElement [ , fromIndex ] )
- every ( callbackfn [ , thisArg ] )
- some ( callbackfn [ , thisArg ] )
- forEach ( callbackfn [ , thisArg ] )
- map ( callbackfn [ , thisArg ] )
- filter ( callbackfn [ , thisArg ] )
- length

Boolean
*******
- Boolean (value)
- Boolean.prototype.toString ( )
- Boolean.prototype.valueOf ( )

Error
*****
- toString ( )

Function
********
- **[excluded]** Function (p1, p2, … , pn, body)
- length
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

JSON
****
- parse ( text [ , reviver ] )
- stringify ( value [ , replacer [ , space ] ] )

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
- toString ( [ radix ] )
- valueOf ( )

Object
******
- Object ( [ value ] )
- Object.getPrototypeOf ( O )
- Object.getOwnPropertyDescriptor ( O, P )
- Object.getOwnPropertyNames ( O )
- Object.create ( O [, Properties] )
- Object.defineProperty ( O, P, Attributes )
- Object.defineProperties ( O, Properties )
- Object.seal ( O )
- Object.freeze ( O )
- Object.preventExtensions ( O )
- Object.isSealed ( O )
- Object.isFrozen ( O )
- Object.isExtensible ( O )
- Object.keys ( O )
- toString ( )
- valueOf ( )
- hasOwnProperty (V)
- isPrototypeOf (V)
- propertyIsEnumerable (V)

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
- slice (start, end)
- substring (start, end)
- toLowerCase ( )
- toUpperCase ( )
- trim ( )
- length
- [[GetOwnProperty]] ( P )

Limitations
-----------

The following methods are not supported by the MicroEJ JavaScript engine:

- Date
- Regex
- methods using locales.