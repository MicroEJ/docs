..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

================
Built-in objects
================

All standard built-in objects from ECMAScript 5.1 are available in MicroJS.
For the complete reference about these built-in objects, consult the `ECMA 5.1 specification <https://www.ecma-international.org/ecma-262/5.1/#sec-15>`_.

For a description and example usage and of each method or property, consult a JavaScript documentation such as `Mozilla Developer Reference <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects>`_.

Excluded methods
----------------

MicroJS supports every method and property in the ECMAScript built-in objects library (a total of **194** properties or methods) except **2** methods are excluded:

-  ``eval ( x )`` function
- ``Function ( p1, p2, … , pn, body )`` constructor

The reason is that the JavaScript compiler is not embedded in MicroJS.

Built-in complete list
----------------------
- ✔️ = implemented
- 🕗 = in progress
- ❌ = excluded

Array
*****
- ✔️ Array (len)
- ✔️ isArray ( arg )
- ✔️ join (separator)
- ✔️ concat ( [ item1 [ , item2 [ , … ] ] ] )
- 🕗 toLocaleString ( )
- ✔️ toString ( )
- ✔️ pop ( )
- ✔️ push ( [ item1 [ , item2 [ , … ] ] ] )
- ✔️ reverse ( )
- ✔️ shift ( )
- ✔️ slice (start, end)
- ✔️ sort (comparefn)
- 🕗 splice (start, deleteCount [ , item1 [ , item2 [ , … ] ] ] )
- 🕗 unshift ( [ item1 [ , item2 [ , … ] ] ] )
- ✔️ indexOf ( searchElement [ , fromIndex ] )
- ✔️ lastIndexOf ( searchElement [ , fromIndex ] )
- ✔️ every ( callbackfn [ , thisArg ] )
- ✔️ some ( callbackfn [ , thisArg ] )
- ✔️ forEach ( callbackfn [ , thisArg ] )
- ✔️ map ( callbackfn [ , thisArg ] )
- ✔️ filter ( callbackfn [ , thisArg ] )
- 🕗 reduce ( callbackfn [ , initialValue ] )
- 🕗 reduceRight ( callbackfn [ , initialValue ] )
- ✔️ length
- 🕗 [[DefineOwnProperty]] ( P, Desc, Throw )

Boolean
*******
- ✔️ Boolean (value)
- ✔️ Boolean.prototype.toString ( )
- ✔️ Boolean.prototype.valueOf ( )

Date
****
- 🕗 Date ( [ year [, month [, date [, hours [, minutes [, seconds [, ms ] ] ] ] ] ] ] )
- 🕗 Date (value)
- 🕗 Date ( )
- 🕗 parse (string)
- 🕗 UTC (year, month [, date [, hours [, minutes [, seconds [, ms ] ] ] ] ] )
- 🕗 now ( )
- 🕗 toString ( )
- 🕗 toDateString ( )
- 🕗 toTimeString ( )
- 🕗 toLocaleString ( )
- 🕗 toLocaleDateString ( )
- 🕗 toLocaleTimeString ( )
- 🕗 valueOf ( )
- 🕗 getTime ( )
- 🕗 getFullYear ( )
- 🕗 getUTCFullYear ( )
- 🕗 getMonth ( )
- 🕗 getUTCMonth ( )
- 🕗 getDate ( )
- 🕗 getUTCDate ( )
- 🕗 getDay ( )
- 🕗 getUTCDay ( )
- 🕗 getHours ( )
- 🕗 getUTCHours ( )
- 🕗 getMinutes ( )
- 🕗 getUTCMinutes ( )
- 🕗 getSeconds ( )
- 🕗 getUTCSeconds ( )
- 🕗 getMilliseconds ( )
- 🕗 getUTCMilliseconds ( )
- 🕗 getTimezoneOffset ( )
- 🕗 setTime (time)
- 🕗 setMilliseconds (ms)
- 🕗 setUTCMilliseconds (ms)
- 🕗 setSeconds (sec [, ms ] )
- 🕗 setUTCSeconds (sec [, ms ] )
- 🕗 setMinutes (min [, sec [, ms ] ] )
- 🕗 setUTCMinutes (min [, sec [, ms ] ] )
- 🕗 setHours (hour [, min [, sec [, ms ] ] ] )
- 🕗 setUTCHours (hour [, min [, sec [, ms ] ] ] )
- 🕗 setDate (date)
- 🕗 setUTCDate (date)
- 🕗 setMonth (month [, date ] )
- 🕗 setUTCMonth (month [, date ] )
- 🕗 setFullYear (year [, month [, date ] ] )
- 🕗 setUTCFullYear (year [, month [, date ] ] )
- 🕗 toUTCString ( )
- 🕗 toISOString ( )
- 🕗 toJSON ( key )

Error
*****
- 🕗 Error (message)
- 🕗 name
- 🕗 message
- ✔️ toString ( )

Function
********
- ❌ **[excluded]** Function (p1, p2, … , pn, body)
- ✔️ length
- 🕗 toString ( )
- 🕗 apply (thisArg, argArray)
- 🕗 call (thisArg [ , arg1 [ , arg2, … ] ] )
- 🕗 bind (thisArg [, arg1 [, arg2, …]])
- ✔️ [[Call]]
- ✔️ [[Construct]]
- 🕗 [[HasInstance]] (V)

Global
******
- ✔️ NaN
- ✔️ Infinity
- ✔️ undefined
- ❌ **[excluded]** eval ( x )
- ✔️ parseInt (string , radix)
- ✔️ parseFloat (string)
- ✔️ isNaN (number)
- ✔️ isFinite (number)
- 🕗 decodeURI (encodedURI)
- 🕗 decodeURIComponent (encodedURIComponent)
- 🕗 encodeURI (uri)
- 🕗 encodeURIComponent (uriComponent)

JSON
****
- ✔️ parse ( text [ , reviver ] )
- ✔️ stringify ( value [ , replacer [ , space ] ] )

Math
****
- ✔️ E
- ✔️ LN10
- ✔️ LN2
- ✔️ LOG2E
- ✔️ LOG10E
- ✔️ PI
- ✔️ SQRT1_2
- ✔️ SQRT2
- ✔️ abs (x)
- ✔️ acos (x)
- ✔️ asin (x)
- ✔️ atan (x)
- ✔️ atan2 (y, x)
- ✔️ ceil (x)
- ✔️ cos (x)
- ✔️ exp (x)
- ✔️ floor (x)
- ✔️ log (x)
- ✔️ max ( [ value1 [ , value2 [ , … ] ] ] )
- ✔️ min ( [ value1 [ , value2 [ , … ] ] ] )
- ✔️ pow (x, y)
- ✔️ random ( )
- ✔️ round (x)
- ✔️ sin (x)
- ✔️ sqrt (x)
- ✔️ tan (x)

Number
******
- ✔️ Number (value)
- ✔️ MAX_VALUE
- ✔️ MIN_VALUE
- ✔️ NaN
- ✔️ NEGATIVE_INFINITY
- ✔️ POSITIVE_INFINITY
- ✔️ toString ( [ radix ] )
- 🕗 toLocaleString()
- ✔️ valueOf ( )
- 🕗 toFixed (fractionDigits)
- 🕗 toExponential (fractionDigits)
- 🕗 toPrecision (precision)

Object
******
- ✔️ Object ( [ value ] )
- ✔️ Object.getPrototypeOf ( O )
- ✔️ Object.getOwnPropertyDescriptor ( O, P )
- ✔️ Object.getOwnPropertyNames ( O )
- ✔️ Object.create ( O [, Properties] )
- ✔️ Object.defineProperty ( O, P, Attributes )
- ✔️ Object.defineProperties ( O, Properties )
- ✔️ Object.seal ( O )
- ✔️ Object.freeze ( O )
- ✔️ Object.preventExtensions ( O )
- ✔️ Object.isSealed ( O )
- ✔️ Object.isFrozen ( O )
- ✔️ Object.isExtensible ( O )
- ✔️ Object.keys ( O )
- ✔️ toString ( )
- 🕗 toLocaleString ( )
- ✔️ valueOf ( )
- ✔️ hasOwnProperty (V)
- ✔️ isPrototypeOf (V)
- ✔️ propertyIsEnumerable (V)

RegExp
******
- 🕗 RegExp(pattern, flags)
- 🕗 exec(string)
- 🕗 test(string)
- 🕗 toString()
- 🕗 source
- 🕗 global
- 🕗 ignoreCase
- 🕗 multiline
- 🕗 lastIndex

String
******
- ✔️ String (value)
- ✔️ fromCharCode ( [ char0 [ , char1 [ , … ] ] ] )
- ✔️ toString ( )
- ✔️ valueOf ( )
- ✔️ charAt (pos)
- ✔️ charCodeAt (pos)
- ✔️ concat ( [ string1 [ , string2 [ , … ] ] ] )
- ✔️ indexOf (searchString, position)
- ✔️ lastIndexOf (searchString, position)
- 🕗 localeCompare (that)
- 🕗 match (regexp)
- 🕗 replace (searchValue, replaceValue)
- 🕗 search (regexp)
- ✔️ slice (start, end)
- 🕗 split (separator, limit)
- ✔️ substring (start, end)
- ✔️ toLowerCase ( )
- 🕗 toLocaleLowerCase ( )
- ✔️ toUpperCase ( )
- 🕗 toLocaleUpperCase ( )
- ✔️ trim ( )
- ✔️ length
- ✔️ [[GetOwnProperty]] ( P )