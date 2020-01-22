Expressions
===========

An attribute expression is a value resulting from the computation of an
arithmetical and logical expression. Supported operators are the same
operators supported in the Java language, and follow Java semantics:

-  Unary operators: ``+ , - , ~ , !``

-  Binary operators: ``+ , - , * , / , % , << , >>> , >> , < , 
   > , <= , >= , == , != , &, | , ^ , && , ||``

-  Ternary operator: ``cond ? ifTrue : ifFalse``

-  Built-in macros:

   -  ``START(name)``: Get the start address of a section or a group of
      sections

   -  ``END(name)``: Get the end address of a section or a group of
      sections

   -  ``SIZE(name)``: Get the size of a section or a group of sections.
      Equivalent to ``END(name)-START(name)``

   -  ``TSTAMPH()``, ``TSTAMPL()``: Get 32 bits linker time stamp
      (high/low part of system time in milliseconds)

   -  ``SUM(name,tag)``: Get the sum of an auto-generated section
      (`??? <#linker-autosections>`__) column. The column is specified
      by its tag name.

An operand is either a sub expression, a constant, or a symbol name.
Constants may be written in decimal (``127``) or hexadecimal form
(``0x7F``). There are no boolean constants. Constant value ``0`` means
``false``, and other constants' values mean ``true``. Examples of use:

::

   value="symbol+3" 
   value="((symbol1*4)-(symbol2*3)"

Note: Ternary expressions can be used to define selective linking
because they are the only expressions that may remain partially
unresolved without generating an error. Example:

::

   <defSymbol name="myFunction" value="condition ? symb1 : symb2"/>

No error will be thrown if the condition is ``true`` and ``symb1`` is
defined, or the condition is ``false`` and ``symb2`` is defined, even if
the other symbol is undefined.
