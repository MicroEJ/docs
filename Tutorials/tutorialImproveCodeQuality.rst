.. _improve_code_quality:

Improve the Quality of Java Code
================================

This tutorial describes some rules and tools aimed at improving the quality of a Java code to simplify its maintenance.
It makes up a minimum consistent set of rules which can be applied in any situation, especially on embedded systems where performance and low memory footprint matter.

Intended Audience
-----------------

The audience for this document is engineers who are developing any kind of Java code (application or library).

Readable Code
-------------

This section describes rules to get a readable code, in order to facilitate:

- the maintenance of an existing code with multiple developers contributions (e.g. merge conflicts, reviews). 
- the landing to a new code base when the same rules are applied across different modules and components.

Naming Convention
^^^^^^^^^^^^^^^^^

Naming of Java elements (package, class, method, field and local) follows the `Camel Case <https://en.wikipedia.org/wiki/Camel_case>`_ convention.

- Package names are written fully in lower case (no underscore).
- Package names are singular (e.g. ``ej.animal`` instead of ``ej.animals``).
- Class names are written in upper camel case.
- Method and instance field names are written in lower camel case.
- Static field names are written in lower camel case.
- Constant names are written in fully upper case with underscore as word separator.
- Enum constant names are written in fully upper case with underscores as word separators.
- Local (and parameter) names are written in lower camel case.
- When a name contains an acronym, capitalize only the first letter of the acronym (e.g. for a local with the ``HTTP`` acronym, use ``myHttpContext`` instead of ``myHTTPContext``).

It is also recommended to use full words instead of abbreviations (e.g. ``MyProxyReference`` instead of ``MyProxyRef``).

.. _visibility:

Visibility
^^^^^^^^^^

Here is a list of the usage of each Java element visibility:

- ``public``: API.
- ``protected``: API for subclasses.
- ``package``: component intern API (collaboration inside a package).
- ``private``: internal structure, cache, lazy, etc.

By default, all instance fields must be private.

Package visibility can be used by writing the comment ``/*default*/`` in place of
the modifier.

Javadoc
^^^^^^^

Javadoc comments convention is based on the `official documentation <https://www.oracle.com/technetwork/java/javase/documentation/index-137868.html>`_.

.. note::

   Javadoc is written in HTML format and doesn't accept XHTML format: tags must not be closed. 
   For example, use only a ``<p>`` between two paragraphs.

Here is a list of the rules to follow when writing Javadoc:

- All APIs (see :ref:`visibility`) must have a full Javadoc
  (classes, methods, and fields).
- Add a dot at the end of all phrases.
- Add ``@since`` tag when introducing a new API.
- Do not hesitate to use links to help the user to navigate in the API
  (``@see``, ``@link``).
- Use the ``@code`` tag in the following cases:

  - For keywords (e.g. ``{@code null}`` or ``{@code true}``).
  - For names and types (e.g. ``{@code x}`` or ``{@code Integer}``).
  - For code example (e.g. ``{@code new Integer(Integer.parseInt(s))}``).

Here is a list of additional rules for methods:

- The first sentence starts with the third person (as if there is *This method* before).
- All parameters and returned values must be described.
- Put as much as possible information in the description, keep
  ``@param`` and ``@return`` minimal.
- Start ``@param`` with a lower case and usually with *the* or *a*.
- Start ``@return`` with a lower case as if the sentence starts with
  *Returns*.
- Avoid naming parameters anywhere other than in ``@param``. If the
  parameter is renamed afterward, the comment is not changed
  automatically. Prefer using *the given xxx*.

Code Style and Formatting
^^^^^^^^^^^^^^^^^^^^^^^^^

MicroEJ defines a formatting profile for ``.java`` files, which is automatically set up when creating a new :ref:`mmm_module_skeleton`.

.. note::

   MicroEJ SDK automatically applies formatting when a ``.java`` file is saved. It is also possible to manually apply formatting on specific files:
   
   - In ``Package Explorer``, select the desired files, folders or projects,
   - then go to :guilabel:`Source` > :guilabel:`Format`. The processed files must not have any warning or error.
   
Here is the list of formatting rules included in this profile:

- Indentation is done with 1 tab.
- Braces are mandatory with ``if``, ``else``, ``for``, ``do``, and
  ``while`` statements, even when the body is empty or contains only a
  single statement.
- Braces follow the Kernighan and Ritchie style (Egyptian brackets) described below:

  - No line break before the opening brace.
  - Line break after the opening brace.
  - Line break before the closing brace.
  - Line break after the closing brace, only if that brace terminates
    a statement or terminates the body of a method, constructor, or
    named class. For example, there is no line break after the brace
    if it is followed by else or a comma.

- One statement per line.
- Let the formatter automatically wraps your code when a statement
  needs to be wrapped.

Here is a list of additional formatting rules that are not automatically applied:

- Class and member modifiers, when present, must appear in the order
  recommended by the Java Language Specification:
  ``public protected private abstract default static final transient volatile synchronized native strictfp``.
- Avoid committing commented code (other than to explain an
  optimization).
- All methods of an interface are public. There is no need to specify
  the visibility (easier to read).
- The parts of a class or interface declaration must appear in the
  order suggested by the Code Convention for the Java Programming
  Language:

  - Class (static) fields. First, the public class fields, then
    the protected, then package level (no access modifier), and then
    the private.
  - Instance fields. First, the public class fields, then the
    protected, then package level (no access modifier), and then the
    private.
  - Constructors
  - Methods

.. note::
   
   Most of these rules are checked by :ref:`sonar_code_analysis`.

Best Practices 
--------------

This section describes rules made of best practices and well-known restrictions of the Java Programming Language and more generally Object Oriented paradigm.

Common Pitfalls
^^^^^^^^^^^^^^^

- `Object.equals(Object) <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#equals-java.lang.Object->`_ and `Object.hashCode() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#hashCode-->`_ methods must be overridden in
  pairs. See :ref:`equals_hashcode`.
- Do not assign fields in field declaration but in the constructor.
- Do not use non-final method inside the constructor.
- Do not overburden the constructor with logic.
- Do not directly store an array given by parameter.
- Do not directly return an internal array.
- Save object reference from a field to a local before using it (see :ref:`local_extraction`).

Simplify Maintenance
^^^^^^^^^^^^^^^^^^^^

- Extract constants instead of using magic numbers.
- Use parenthesis for complex operation series; it simplifies the understanding 
  of operator priorities.
- Write short lines. This can be achieved by extracting locals (see :ref:`local_extraction`).
- Use a limited number of parameters in methods (or perhaps a new type
  is needed).
- Create small methods with little complexity. When a method gets too
  complex, it should be split.
- Use ``+`` operator only for single-line string concatenation. Use an explicit `StringBuilder <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/StringBuilder.html>`_ otherwise.
- Use component-oriented architecture to separate concerns. If a class is intended to be instantiated using `Class.newInstance() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#newInstance-->`_, add a default constructor (without parameters).

Basic Optimizations
^^^^^^^^^^^^^^^^^^^

- Avoid explicitly initializing fields to ``0`` or ``null``, because they are zero-initialized by the runtime. A ``//VM_DONE`` comment
  can be written to understand the optimization.
- The switch/case statements are generated by the Java compiler in two ways depending on the
  cases density. Prefer declaring consecutive cases (`table_switch`) for performance (``O(1)``) and slightly
  smaller code memory footprint instead of `lookup_switch` (``O(log N)``).
- Avoid using built-in thread safe types (`Vector <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Vector.html>`_,
  `Hashtable <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Hashtable.html>`_,
  `StringBuffer <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/StringBuffer.html>`_, etc.). 
  Usually synchronization has to be done at a higher level.
- Avoid serializing/deserializing data from byte arrays using manual
  bitwise operations, use `ByteArray <https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/ByteArray.html>`_ utility methods instead.

.. _local_extraction:

Local Extraction
^^^^^^^^^^^^^^^^

Local extraction consists of storing the result of an expression before using it, for example:

.. code:: java

   Object myLocale = this.myField;
   if (myLocale != null) {
     myLocale.myMethod();
   }

It improves the Java code in many ways:

- self documentation: gives a name to a computed result.
- performance and memory footprint: avoids repeated access to same elements and extract loop invariants.
- thread safety: helps to avoid synchronization issues or falling into unwanted race conditions.
- code pattern detection: helps automated tools such as Null Analysis.

.. _equals_hashcode:

Equals and Hashcode
^^^^^^^^^^^^^^^^^^^

The purpose of these methods is to uniquely and consistently identify
objects. The most common use of these methods is to compare instances in
collections (list or set elements, map keys, etc.).

The `Object.equals(Object) <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#equals-java.lang.Object->`_ method implements an equivalence relation (defined in
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

.. code:: java

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

The `Object.hashCode() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#hashCode-->`_ method is written that way:

- Choose a prime number.
- Create a result local, whatever the value (usually the prime number).
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

.. code:: java

  private static final int PRIME = 31;

  @Override
  public int hashCode() {
    int result = PRIME;
    result = PRIME * result + field1;
    result = PRIME * result + (field2 == null ? 0 : field2.hashCode());
    return result;
  }

Related Tools
-------------

This section points to tools aimed at helping to improve code quality.

Unit Testing
^^^^^^^^^^^^

Here is a list of rules when writing tests (see :ref:`application_testsuite`):

- Prefer black-box tests (with a maximum coverage).
- Here is the test packages naming convention:

  - Suffix package with .test for black-box tests.
  - Use the same package for white-box tests (allow to use classes with
    package visibility).


.. _sonar_code_analysis:

Code Analysis with SonarQube™
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

SonarQube is an open source platform for continuous inspection of code quality.
SonarQube offers reports on duplicated code, coding standards, unit tests, code coverage, code complexity, potential bugs, comments, and architecture.

To set it up on your MicroEJ application project, please refer to `this documentation <https://github.com/MicroEJ/ExampleTool-Sonar>`_.
It describes the following steps:

- How to run a SonarQube server locally.
- How to run an analysis using a dedicated script.
- How to run an analysis during a module build.
