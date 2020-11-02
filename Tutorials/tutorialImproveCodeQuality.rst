.. _improvecodequality:

Improve the Quality of the Code of an Application
=================================================

This tutorial explains how to analyze the quality of the code of an application and how to improve this quality in order to simplify the maintenance of the code.

Naming Convention
-----------------

Use full words instead of abbreviations (for classes, methods, fields, or
locals).

Here is a list of the casing rules for each type:

- Package names are written fully in lower case (no underscore).
- Package names are singular (for example ``ej.animal`` rather than
  ``ej.animals``).
- Class names are written in upper camel case.
- Method and instance field names are written in lower camel case.
- Static field names are written in lower camel case.
- Constant names are written in fully upper case with underscore as word separator.
- Enum names are written in fully upper case with underscores as word separators.
- Local (and parameter) names are written in lower camel case.
- For acronyms in camel case, capitalize only the first letter, not the
  others (for example, ``xmlHttpContext`` for a local).

Visibility
----------

Here is a list of the usage of each visibility:

- ``public``: API.
- ``protected``: API for subclasses.
- ``package``: component intern API (collaboration inside a package).
- ``private``: internal structure, cache, lazy, etc.

By default, all instance fields must be private.

Package visibility can be used by writing the comment ``/*default*/`` in place of
the modifier.

Javadoc
-------

Official documentation:
https://www.oracle.com/technetwork/java/javase/documentation/index-137868.html

The Javadoc is written in HTML. Do not use XHTML: all tags must not be
closed. For example, use only a ``<p>`` between two paragraphs.
Here is a list of the rules to follow when writing Javadoc:

- All APIs (see ``Visibility`` chapter) must have a full Javadoc
  (classes, methods, and fields).
- Add a dot at the end of all phrases.
- Add @since when introducing a new API.
- Do not hesitate to use links to help the user to navigate in the API
  (``@see``, ``@link``).
- Use the code tag in the following cases:

  - For keywords.
  - For names.
  - For code example.
  - ``{@code null}``, ``{@code true}``, ``{@code false}``,
    ``{@code my code}``.

For the methods, follow the rules below:

- The first sentence starts with the third person (as if there is “This
  method” before).
- All parameters and returned values must be described.
- Put as much as possible information in the description, keep
  ``@param`` and ``@return`` minimal.
- Start ``@param`` with a lower case and usually with “the” or “a.”
- Start ``@return`` with a lower case as if the sentence starts with
  “Returns."
- Avoid naming parameters anywhere other than in ``@param``. If the
  parameter is renamed afterward, the comment is not changed
  automatically. Prefer using “the given xxx.”

Code Style
----------

The formatting rules for Eclipse recommended by MicroEJ can be found here: `Eclipse Java
settings <https://repository.microej.com/packages/formatter/>`__.

These rules must be set (and committed) for each project (in ``.settings``
directory). Then, the committed files must not have any warning or
error.

- Indentation is done with 1 tab. (Why? Because it is simply more
  versatile, you can represent it as you wish!).
- Braces are mandatory with ``if``, ``else``, ``for``, ``do``, and
  ``while`` statements, even when the body is empty or contains only a
  single statement.
- Braces follow the Kernighan and Ritchie style (“Egyptian brackets”) described below:

  - No line break before the opening brace.
  - Line break after the opening brace.
  - Line break before the closing brace.
  - Line break after the closing brace, only if that brace terminates
    a statement or terminates the body of a method, constructor, or
    named class. For example, there is no line break after the brace
    if it is followed by else or a comma.

- One statement per line.
- Let the formatter automagically wraps your code when a statement
  needs to be wrapped.
- Class and member modifiers, when present, appear in the order
  recommended by the Java Language Specification:
  ``public protected private abstract default static final transient volatile synchronized native strictfp``.
- Avoid committing commented code (other than to explain an
  optimization).
- All methods of an interface are public. There is no need to specify
  the visibility (easier to read).
- The parts of a class or interface declaration must appear in the
  order suggested by the Code Convention for the Java Programming
  Language:

  - Class (static) variables. First, the public class variables, then
    the protected, then package level (no access modifier), and then
    the private.
  - Instance variables. First, the public class variables, then the
    protected, then package level (no access modifier), and then the
    private.
  - Constructors
  - Methods

Bad Practices
-------------

- Avoid redefining ``toString()`` method for debugging purposes. The method
  will always be embedded and consume some Flash.
- Do not implement ``equals(Object)`` and ``hashCode()`` if not necessary
  (if ``==`` operator is sufficient). See :ref:`equals-hashcode`.

Best Practices to Avoid Pitfalls
--------------------------------

- ``equals(Object)`` and ``hashCode()`` must be overridden in
  pairs. See :ref:`equals-hashcode`.
- Do not assign fields in field declaration but in the constructor.
- Do not use non-final method inside the constructor.
- Do not overburden the constructor with logic.
- Prefer a default constructor (without parameters) in order to use
  reflection (``Class.newInstance()``).
- Do not directly store an array given by parameter.
- Do not directly return an internal array.
- Save object reference from a field to a local before using it::

	Object myLocale = this.myField;
	if (myLocale != null) {
		myLocale.myMethod();
	}

Best Practices to Simplify Maintenance
--------------------------------------

- Extract constants instead of using magic numbers.
- Use parenthesis for complex operation series; it simplifies the understanding 
  of operator priorities.
- Write short lines. This can be achieved by extracting variables (for
  example: (``(a == null || b == null)`` becomes
  ``(aIsNull || bIsNull)``).
- Use component-oriented architecture to separate concerns (Use
  ej.library.runtime#component).
- Use a limited number of parameters in methods (or perhaps a new type
  is needed).
- Create small methods with little complexity. When a method gets too
  complex, it should be split.
- Use ``+`` operator for single-line string concatenation. Use a
  StringBuilder otherwise.

Performance Considerations
--------------------------

- Avoid using ``Calendar.getInstance()`` for a repeated operation. It
  creates a new instance of Calendar for each call. Prefer using the
  same instance when possible.
- Avoid using the Calendar to compute fields to display a watch face
  for example. The computation of the fields of a Calendar may affect
  performance. In a watch face, prefer maintaining a watch model
  (with one field per data: second, minute, hour, etc.) that updates
  its fields every x milliseconds, then every x seconds or minutes. The
  model can be updated using a calendar. An update on an NTP can also
  be considered.

Basic Optimizations
-------------------

- Avoid initializing fields to ``0`` or ``null``. A ``//VM_DONE`` tag
  can be written to understand the optimization.
- The switch/case blocks are generated in two ways depending on the
  cases. Prefer consecutive cases for faster execution (and slightly
  smaller bytecode).
- Avoid using synchronized types (Vector, Hashtable, StringBuffer,
  etc.) when possible.
- Avoid using not packed collections as fields. Instead of ArrayList
  prefer using arrays with the right size and instead of HashSet,
  HashMap use packed maps (see ``ej.library.runtime#basictool``
  library).
- Avoid using not packed collections as fields. Prefer using arrays
  with the right size or packed maps (see
  ``ej.library.runtime#basictool`` library).
- Use locals for repeated access to fields or array elements.
- Save fields in local (for reading use cases) to avoid synchronization
  issues.
- Save results of method calls as local.
- Arrays in static fields consume a lot of flash and are initialized
  dynamically (it generates a lot of Java bytecode). It can be
  optimized by declaring it as immutables.
- All stateless objects initialized at startup could be turned
  into immutables to save RAM and execution time.

.. _equals-hashcode:

Equals and Hashcode
-------------------

The purpose of these methods is to uniquely and consistently identify
objects. The most common use of these methods is to compare instances in
collections (list or set elements, map keys, etc.).

The ``equals(Object)`` method implements an equivalence relation (defined in
the Javadoc) with the following properties:

- It is reflexive: for any reference value x, ``x.equals(x)`` must return
  ``true``.
- It is symmetric: for any reference values x and y, ``x.equals(y)`` must
  return ``true`` if and only if ``y.equals(x)`` returns ``true``.
- It is transitive: for any reference values x, y, and z, if ``x.equals(y)``
  returns ``true`` and ``y.equals(z)`` returns ``true``, then ``x.equals(z)``
  must return ``true``.
- It is consistent: for any reference values x and y, multiple invocations of
  ``x.equals(y)`` consistently return ``true`` or consistently return
  ``false``, provided no information used in equals comparisons on the object
  is modified.
- For any non-null reference value x, ``x.equals(null)`` must return ``false``.

Avoid overriding the ``equals(Object)`` method in a subclass of a class that
already overrides it; it could break the contract above. See
*Effective Java* book by *Joshua Bloch* for more information.

If the ``equals(Object)`` method is implemented, the ``hashCode()`` method
must also be implemented. The ``hashCode()`` method follows these rules
(defined in the Javadoc):

- It must consistently return the same integer when invoked several times.
- If two objects are equal according to the ``equals(Object)`` method, then
  calling the ``hashCode()`` method on each of the two objects must produce
  the same integer result.
- In the same way, it should return distinct integers for distinct objects.

The ``equals(Object)`` method is written that way:

- Compare the argument with ``this`` using the ``==`` operator. If both are
  equals, return ``true``. This test is for performance purposes, so it is
  optional and may be removed if the object has a few fields.
- Use an ``instanceof`` to check if the argument has the correct type. If not,
  return ``false``. This check also validates that the argument is not null.
- Cast the argument to the correct type.
- For each field, check if that field is equal to the same
  field in the casted argument. Return ``true`` if all fields are equal,
  ``false`` otherwise.

::

  @Override
  public boolean equals(Object o) {
    if (o == this) {
      return true;
    }
    if (!(o instanceof MyClass)) {
      return false;
    }
    MyClass other = (MyClass)o;
    return field1 == other.field1 &&
      (field2 == null ? other.field2 == null : field2.equals(other.field2));
  }

The ``hashCode()`` method is written that way:

- Choose a prime number.
- Create a result variable, whatever the value (usually the prime number).
- For each field, multiply the previous result with the prime
  plus the hash code of the field and store it as the result.
- Return the result.

Depending on its type, the hash code of a field is:

- Boolean: ``(f ? 0 : 1)``.
- Byte, char, short, int: ``(int) f)``.
- Long: ``(int)(f ^ (f >>> 32))``.
- Float: ``Float.floatToIntBits(f)``.
- Double: ``Double.doubleToLongBits(f)`` and the same as for a long.
- Object: ``(f == null ? 0 : f.hashCode())``.
- Array: add the hash codes of all its elements (depending on their type).

::

  private static final int PRIME = 31;

  @Override
  public int hashCode() {
    int result = PRIME;
    result = PRIME * result + field1;
    result = PRIME * result + (field2 == null ? 0 : field2.hashCode());
    return result;
  }

JUnit
-----

- Prefer black-box tests (with a maximum coverage).
- Here is the test packages naming convention:

  - Suffix package with .test for black-box tests.
  - Use the same package for white-box tests (allow to use classes with
    package visibility).

Code Analysis with SonarQube™
-----------------------------

SonarQube is an open source platform for continuous inspection of code quality.
SonarQube offers reports on duplicated code, coding standards, unit tests, code coverage, code complexity, potential bugs, comments, and architecture.

To set it up on your MicroEJ application project, please refer to `this documentation <https://github.com/MicroEJ/ExampleTool-Sonar>`_.
It describes the following steps:

- How to run a SonarQube server locally.
- How to run an analysis using a dedicated script.
- How to run an analysis during "Build with EasyAnt."
