.. _improve_code_quality:

MicroEJ Java Programming Practices
==================================

Description
-----------

This training describes some rules and tools aimed at improving the quality of a Java code to simplify its maintenance.
It makes up a minimum consistent set of rules which can be applied in any situation, especially on embedded systems where performance and low memory footprint matter.
Also be aware of MicroEJ runtime specificities by reading the :ref:`java_language` page.

Intended Audience
-----------------

This training is designed for Application developers who want to enhance the quality of their Java code.

Prerequisites
-------------

To get the most out of this training, participants should have a good knowledge of Java programming language.

Readable Code
-------------

This section describes rules to get a readable code, in order to facilitate:

- the maintenance of an existing code with multiple developers contributions (e.g., merge conflicts, reviews).
- the landing to a new code base when the same rules are applied across different modules and components.

Naming Convention
^^^^^^^^^^^^^^^^^

Naming of Java elements (package, class, method, field and local) follows the `Camel Case <https://en.wikipedia.org/wiki/Camel_case>`_ convention.

- Package names are written fully in lower case (no underscore).
- Package names are singular (e.g. ``ej.animal`` instead of ``ej.animals``).
- Class names are written in upper camel case.
- Interfaces are named in the same way as classes (see below).
- Method and instance field names are written in lower camel case.
- Static field names are written in lower camel case.
- Constant names are written in fully upper case with underscore as word separator.
- Enum constant names are written in fully upper case with underscores as word separators.
- Local (and parameter) names are written in lower camel case.
- When a name contains an acronym, capitalize only the first letter of the acronym (e.g. for a local with the ``HTTP`` acronym, use ``myHttpContext`` instead of ``myHTTPContext``).

It is also recommended to use full words instead of abbreviations (e.g. ``MyProxyReference`` instead of ``MyProxyRef``).

Interfaces and Subclasses Naming Convention
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

An Interface is named after the feature it exposes.
It does not have a ``I`` prefix because it hurts readability and may cause naming issues when potentially converted to/from an abstract class.

The classes implementing an interface are named after the interface and how they implement it.
Using ``Impl`` suffix is not recommended because it does not express the implementation specificity. If there is no specificity, maybe there is no need to have an interface.

Example: an interface ``Storage`` (that allows to load/store data) may have several implementations, such as ``StorageFs`` (on a file system), ``StorageDb`` (on a database), ``StorageRam`` (volatile storage in RAM).

.. _visibility:

Visibility
^^^^^^^^^^

Here is a list of the usage of each Java element visibility:

- ``public``: API.
- ``protected``: API for subclasses.
- ``package``: component intern API (collaboration inside a package).
- ``private``: internal structure, cache, lazy, etc.

By default, all instance fields must be private.

Package visibility can be used by writing the comment ``/* package */`` in place of
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

Code Convention
^^^^^^^^^^^^^^^

Official documentation:
https://www.oracle.com/java/technologies/javase/codeconventions-introduction.html

Class Declaration
~~~~~~~~~~~~~~~~~

The parts of a class or interface declaration must appear in the order suggested by the Code Convention for the Java Programming Language:

- Constants.
- Class (static) fields.
- Instance fields.
- Constructors
- Methods

Fields Order
~~~~~~~~~~~~

For a better readability, the fields (class and instance) must be ordered by scope:

#. ``public``
#. ``protected``
#. ``package``
#. ``private``

Methods Order
~~~~~~~~~~~~~

It is recommended to group related methods together.
It helps for maintenance:

- when searching for a bug on a specific feature,
- when refactoring a class into several ones.

Modifiers Order
~~~~~~~~~~~~~~~

Class and member modifiers, when present, appear in the order recommended by the Java Language Specification:

``public protected private abstract default static final transient volatile synchronized native strictfp``

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

- Avoid committing commented code (other than to explain an
  optimization).
- All methods of an interface are public. There is no need to specify
  the visibility (easier to read).

.. note::

   Most of these rules are checked by :ref:`sonar_code_analysis`.

Best Practices
--------------

This section describes rules made of best practices, well-known restrictions of the Java Programming Language, and more generally Object Oriented paradigm.
Due to the resource constraints related to CPU, RAM, or FLASH usage, some
Java best practices can be counterproductive when used in an embedded
software development context. This section also exists to discuss such limitations.
Be also aware that there is no absolute truth when talking about these limitations,
you should keep in mind that depending on your hardware some may apply some may not.

Common Pitfalls
^^^^^^^^^^^^^^^

- `Object.equals(Object)`_ and `Object.hashCode()`_ methods must be overridden in
  pairs. See :ref:`equals_hashcode`.
- Do not assign fields in field declaration but in the constructor.
- Do not use non-final method inside the constructor.
- Do not overburden the constructor with logic.
- Do not directly store an array given by parameter.
- Save object reference from a field to a local before using it (see :ref:`local_extraction`).

.. _Object.equals(Object): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#equals-java.lang.Object-
.. _Object.hashCode(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Object.html#hashCode--

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
- Use ``+`` operator only for single-line string concatenation. Use an explicit `StringBuilder`_ otherwise.
- Use component-oriented architecture to separate concerns. If a class is intended to be instantiated using `Class.newInstance()`_, add a default constructor (without parameters).

.. _StringBuilder: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/StringBuilder.html
.. _Class.newInstance(): https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#newInstance--

Basic Optimizations
^^^^^^^^^^^^^^^^^^^

- Avoid explicitly initializing fields to ``0`` or ``null``, because they are zero-initialized by the runtime. A ``//VM_DONE`` comment
  can be written to understand the optimization.
- Avoid using built-in thread safe types (`Vector`_, `Hashtable`_, `StringBuffer`_, etc.).
  Usually synchronization has to be done at a higher level.
- Avoid serializing/deserializing data from byte arrays using manual
  bitwise operations, use `ByteArray`_ utility methods instead.

.. _Vector: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Vector.html
.. _Hashtable: https://repository.microej.com/javadoc/microej_5.x/apis/java/util/Hashtable.html
.. _StringBuffer: https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/StringBuffer.html
.. _ByteArray: https://repository.microej.com/javadoc/microej_5.x/apis/ej/bon/ByteArray.html

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

The `Object.equals(Object)`_ method implements an equivalence relation (defined in
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
  optional and may be removed if the object has few fields.
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

The goal of the `Object.hashCode()`_ is to produce different values for unequal objects.
A good hashcode is uniformly distributed among hash buckets (for instance in HashMap, HashSet, etc.)

The ``hashCode()`` method is written that way:

- Choose any prime number such as ``31`` (that is large enough so that the number of buckets is unlikely to be divisible by it) or a bigger one.
- Create a result local intialized with the hashcode of the most significant field.
- For each remaining field, multiply the previous result with the prime plus the hash code of the field and store it as the result.
- Return the result.
- Only the fields used in ``equals()`` must be used.
- Derivative fields, that are computed from fields already included in computing of ``hashCode()`` can be ignored.
- Precomputing the hashcode may be convenient for performance purpose (especially when fields are final).
- The hashcode can also be lazy initialized the first time it is requested.

Depending on its type, the hash code of a field is:

- Boolean: ``(f ? 1231 : 1237)``.
- Byte, char, short, int: ``(int) f``.
- Long: ``(int)(f ^ (f >>> 32))``.
- Float: ``Float.floatToIntBits(f)``.
- Double: ``Double.doubleToLongBits(f)`` and the same as for a long.
- Object: ``(f == null ? 0 : f.hashCode())``.
- Array: add the hash codes of all its elements (depending on their type).
- The hashcode of a null field is 0.

.. code:: java

  private static final int PRIME = 31;

  @Override
  public int hashCode() {
    int result = field0;
    result = PRIME * result + (field1 ? -1 : 1);
    result = PRIME * result + (field2 == null ? 0 : field2.hashCode());
    return result;
  }

- Prefer using "foo".equals(string) to avoid potential null accesses.

.. code:: java

  String s = null;
  // Null safe
  "foo".equals(s);
  // NullPointerException
  s.equals("foo");

Autoboxing and Numbers
^^^^^^^^^^^^^^^^^^^^^^

- Avoid using boxed primitives (such as Integer, Byte, Float classes) if not needed. Most of
  the time using boxed primitives leads to autoboxing (the process of converting
  primitives to boxed primitives and the other way around), which can be CPU intensive due to casting.

.. code:: java

  // Boxed primitive type example
  Integer boxedInteger = Integer.valueOf(5);
  // Primitive basetype
  int unboxedInteger = boxedInteger.intValue();
  // Autoboxing example
  List<Integer> integerList = new ArrayList<>();
  // Here you "autobox" the basetype into its corresponding primitive type
  list.add(5);

- Prefer 32-bit floats for embedded performance. Double operations are more CPU intensive.

Generic Types
^^^^^^^^^^^^^

- Do not use parameterized types as raw types such as using the Collection without specifying the type parameter, prefer using a parameterized type as designed (it ensures type safety, avoid explicit type casting, and improve code readability).
  Generic and parameterized types are a compile time feature, it won't impact runtime performances and memory footprint.

.. code:: java

  // Prefer
  ArrayList<Foo> paramList = new ArrayList<>();
  paramList.add(new Foo("I'm foo!"));

  // Compiler will trigger an error if you try to add a wrong type here
  paramList.add(new Bar("I'm bar!"));

  // Over
  ArrayList list = new ArrayList();
  list.add(new Foo("I'm another foo!"));

Memory Use of Objects
^^^^^^^^^^^^^^^^^^^^^

- The Java bytecode specification defines a 32-bit operand stack model. Declaring local variables with types that require fewer bits (byte, short, char) results in additional conversion and casting instructions during execution. However this is not applicable when declaring Java instance fields, which are optimized for size in the internal Java object structure. The organization of fields in memory is left to the runtime implementation.

- Operations on local variables in Java are happening using the thread's own stack (by loading and storing values onto the stack).
  Local variables are tied to their scope/context usually their associated method.
  Objects are stored in Managed Heap.

- :ref:`memory-considerations` and :ref:`limitations` are also documentation pages that describe
  the memory use of Objects and the limitations of the MicroEJ runtime.

- You rarely need to trigger a Garbage Collection (GC) manually through `System.gc() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#gc-->`_.
  A use case example that would require a manual GC trigger is when you need an accurate memory usage of the Managed Heap (before a call to `Runtime.getRuntime().freeMemory() <https://repository.microej.com/javadoc/microej_5.x/apis/index.html?java/lang/System.html>`_).

- Prefer using an array for fixed memory usage against dynamic data structure. If you do not need
  the convenience of dynamically allocated types, it is most of the time more efficient (CPU wise) to
  use arrays. Dynamical allocated types such as collection types tend to check for size and have mechanisms to enlarge on-the-fly
  the data structure. Using an array prevent that but obviously you keep the runtime checks.

.. code:: java

  // Prefer
  int[] array = new int[size];

  // Over (when applicable)
  ArrayList<Integer> arrayList = new ArrayList<>();

- Try calibrating data structure by giving it a size at initialization (avoid automatically enlarging them when needed).

.. code:: java

  // Try initializing the ArrayList with a known size
  Collection<String> colors = new ArrayList<String>(500);

- To use the cloning mechanism provided by Java, here are the rules to respect:

  - Always implement ``Cloneable``.
  - ``bar.clone() != bar`` is ``True``.
  - ``bar.clone().getClass() == bar.getClass()`` is ``True``.
  - ``bar.clone().equals(bar)`` is ``True``.
  - Use deep copies for your implementation of ``.clone()`` over shallow copies. Shallow copies
    mean clones are tied to their original instance.

.. code:: java

  // Prefer
  @Override
  protected Object clone() throws CloneNotSupportedException {
	Bar newClone = (Bar) super.clone();
	newClone.setField(newClone.getField().clone());
	return newClone;
  }

  // Over
  @Override
  protected Object clone() throws CloneNotSupportedException {
	return super.clone();
  }

- For specific memory size optimizations, see :ref:`tutorial_optimize_memory_footprint`.

Reflection
^^^^^^^^^^

- MicroEJ does not embed the fully qualified name of all classes in the final binary. As such
  you need to explicitly specify which type names to embed using ``*.types.list`` files (see
  :ref:`section.classpath.elements.types`).

- Java reflection forces to embed the fully qualified name of Java elements. As such
  it can be costly in persistent memory. MicroEJ has made the choice to only allow
  `Class.forName() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#forName-java.lang.String->`_, `Class.getName() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getName-->`_, `Class.getSimpleName() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Class.html#getSimpleName-->`_, and `Class.newInstance()`_
  methods from the reflection framework.

BON Constants
^^^^^^^^^^^^^

- Consider using BON constants, they allow for sections of code to not be embedded in the final binary depending
  on the constant value.
  Constants are resolved at binary level without having to recompile the sources. More information can be
  found at this :ref:`section.classpath.elements.constants` section of the documentation.

- BON constants are preferred to System properties for the following reasons:

  - BON constants are compile time checked whereas System properties are often used with runtime checks.
  - System properties allow only String values (meaning String comparison most of the time).
  - System properties checks do not allow to completely remove the code from the binary (so they are more costly in code memory space).

Enums
^^^^^

- Avoid Enum types in your code, use int constants when possible. Enum types are costly
  at runtime.

Concurrency
^^^^^^^^^^^

- Do not implement applications that expect a behavior of the underlying task scheduler.
  Make your synchronization between threads explicit.

- Best pratices for synchronization:

  - Small exclusion zones, large exclusion zones usually means thread wait longer.
  - Use `Executors <https://repository.microej.com/javadoc/microej_5.x/apis/java/util/concurrent/Executor.html>`_.
  - For the use of explicit synchronization and use of monitors, you can consult this
    `article <https://www.baeldung.com/java-wait-notify>`_.

- There is no explicit way to kill a Java thread. A well designed thread that is long running checks for
  interrupts at regular intervals and acts on interrupt signals. More information can be found `here <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.html#interrupt-->`_.

Serialization
^^^^^^^^^^^^^

- The “native” serialization of the standard JVM is not implemented by MicroEJ. This mechanism has historically introduced numerous compatibility issues and has since been officially deprecated. Synchronization and serialization should be handled at the application level.
  See data formats commonly used with MICROEJ VEE: :ref:`chapter.data_serialization`.

Annotations
^^^^^^^^^^^

- MicroEJ supports only compile-time annotations. The usual annotations we encourage to use are
  ``@Override``, the Null Analysis annotations, and ``@Deprecated``.

- Another typical use case of annotations is for declaring JUnit tests. See :ref:`sdk_6_test_project` for more information.

- You can also define your custom annotations in conjonction with add-on processors.

Polymorphism, Inheritance, and Interfaces
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Prefer interfaces to abstract classes for the following reasons:

  - it easily integrates with existing classes, add the ``implements`` to existing classes, it is harder to do with abstract classes,
  - interfaces allow the easy notion of `mixin <https://en.wikipedia.org/wiki/Mixin>`_,
  - interfaces allow for the creation nonhierarchical types.

- The SOAR tries to make method calls direct as much as it can, see :ref:`soar_method_devirtualization` for more information.

Exceptions
^^^^^^^^^^
Here are in no particular order best pratices around managing exceptions in Java:

- Use existing exceptions for your API, e.g., there is no need to create a ``MyModelOptionException`` when `IllegalArgumentException <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/IllegalArgumentException.html>`_ exists.
- Use checked exceptions for recoverable errors, use unchecked exceptions for programming errors or code violations.

  - Checked exceptions allows to complete your API with its exceptional conditions.
  - Unchecked exceptions are throwables such as errors and runtime exceptions, they usually indicate a violation of some fundamental rules of
    Java (such as `ArrayIndexOutOfBoundsException <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/ArrayIndexOutOfBoundsException.html>`_).
  - It is a good pratice to have your custom unchecked exceptions to extend `RuntimeException <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/RuntimeException.html>`_.
  - Do not use unchecked exceptions to not be bothered using ``throws`` in your methods.

- If you want an "undying" thread, you should catch all `Throwable <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Throwable.html>`_.

- Avoid exception masking (e.g., doing nothing in a catch clause).

.. code:: java

  // Do not do this
  try{
    // Some code causing an Exception
  } catch (Exception e){
    //  You should do something here
  }

  //Prefer
  try{
    // Some code causing an Exception
  } catch (Exception e){
    // You could do log it
    logger.log(Level.SEVERE, "Severe error message");
    // or you could rethrow it, by tweaking the exceptional type
    throw new MyException(e);
  }

- It is a good practice to set your custom `Thread.UncaughtExceptionHandler <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/Thread.UncaughtExceptionHandler.html>`_ to improve the robustness of your application. It could set per thread or at application level.

.. code:: java

  public class MyHandler implements Thread.UncaughtExceptionHandler {

    public void uncaughtException(Thread thread, Throwable e) {
      // Process what to do
      logger.log(Level.SEVERE, "Uncaught exception: " + e.getMessage());
      e.printStackTrace();
    }

  }

- Automatically close resources using try-with-resources.

- For more information on Exception as well as a hierarchy of common exceptions please read `this article <https://rollbar.com/blog/java-exceptions-hierarchy-explained/#>`_.

Data Encapsulation and Fields
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Keep your fields private by default.
- Provide field getters and setters when needed.
  - Do not directly return an internal array or an internal non-immutable Object. Once returned the caller could modify "your" instance without warning or synchronization.
- Use ``final`` for public basetype fields because:

  - By default it forces fields to be read-only.
  - It ensures thread safety.
  - It forces you to consider if the field should have right access and communicate intent to other developers.

Native Interfaces
^^^^^^^^^^^^^^^^^

- Several mechanisms exist to communicate between managed and native worlds. Find more information at :ref:`native_mechanisms`.

Usage of Inner Classes
^^^^^^^^^^^^^^^^^^^^^^

- Prefer static inner classes when needed because there is a performance impact on accessing the outer class instance.
- Non static inner classes keep a reference to an instance of the outer class.

.. code:: java

  public class OuterClass {

      // Avoid non-static inner class (an instance of this class is stored in the outer class)
      private class InnerClass1 {
          public void message() {
              System.out.println("This is a non-static inner class.");
          }
      }

      // Prefer static inner class (the instances are shared among all instances of OuterClass)
      public static class InnerClass2 {
          public void message() {
              System.out.println("This is a static inner class.");
          }
      }
  }

- Prefer short inner classes for readability (if your inner class gets too complex it surely deserves its own file).

Usage of Clinits
^^^^^^^^^^^^^^^^

- The clinit order is done statically by the SOAR before the execution, as such clinits shall be limited to class internal constant initialization, with as less as possible dependency. :ref:`soar_clinit` describes how MicroEJ deals with class initialization.

About Limitations
^^^^^^^^^^^^^^^^^

- For a deeper look at what is allowed in terms of number of fields or methods in a class, maximum number of threads and more: please consult :ref:`limitations`.

Inlining
^^^^^^^^

- For better CPU performance at runtime, the SOAR implements some inlining techniques more information at :ref:`soar_method_inlining`.

Binary creation from classpath
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Not all files found in the classpath are embedded in a MicroEJ Application, to manage embedded resources consult :ref:`chapter.microej.applicationResources`.

- In the same philosophy the SOAR does not embed every unused types from the classpath in the final binary. More information at :ref:`chapter.microej.classpath`.

- The SOAR also strips the unused methods from the code.

Immutables and Immortals
^^^^^^^^^^^^^^^^^^^^^^^^

- MICROEJ VEE defines two additional categories of objects: Immutables (objects that cannot change) and Immortals (objects that cannot be garbage-collected). More information below.

  - :ref:`immutable`
  - :ref:`immortal`

Loop Invariants
^^^^^^^^^^^^^^^

- Avoid unnecessary operations in loop (e.g., accessing a Collection size if not changing, accessing fields, etc.), consider using primitive types for loop variables, and minimize object creation.

.. code:: java

   // Prefer "caching" class fields in a local variable when it does not depend on the loop operations
   int localNumberToUse = this.numberToUse;
   for (int i = 0; i < 10000; i++) {
      result = thingsToMultiply * localNumberToUse
   }

   // Prefer accessing Collection size outside of a loop
   Collection<String> colors = new ArrayList<>();
   colors.add("Red");
   colors.add("Green");
   colors.add("Blue");

   // Retrieve the size only once
   int size = colors.size();
   for (String color : colors) {
      // Cheaper access for each loop
      System.out.println(color + " is a color in an ArrayList of " + size + " colors.");
   }

- A `foreach` loop is a shorter way to write a loop over collections or arrays. It eliminates the need for explicit indexing and provides better readability.

.. code:: java

   int[] scores = {90, 85, 95, 88};

   for (int score : scores) {
      System.out.println("Score: " + score);
   }

Use of I/O Classes
^^^^^^^^^^^^^^^^^^

- Be mindful of the use of IO classes and their buffered version. While buffered types such as `BufferedInputStream <https://repository.microej.com/javadoc/microej_5.x/apis/java/io/BufferedInputStream.html>`_ are classes that improve the performance of input/output operations by reducing the number of I/O calls, these types do it by consuming more memory.

Logging
^^^^^^^

- Use BON constants to enable and disable logging traces in your code to conserve ROM space, see :ref:`section.classpath.elements.constants`.
- Use Logger over System.out.println.

Array Copy
^^^^^^^^^^

- When doing memory transfers on arrays use `System.arraycopy() <https://repository.microej.com/javadoc/microej_5.x/apis/java/lang/System.html#arraycopy-java.lang.Object-int-java.lang.Object-int-int->`_ when possible as it is optimized to run nearly as fast as a native ``memmove``.

Switch Statements
^^^^^^^^^^^^^^^^^

- Try to optimize your switch statement with contiguous case values resulting in a faster implementation.

- The switch/case statements are generated by the Java compiler in two ways depending on the
  cases density. Prefer declaring consecutive cases (`table_switch`) for performance (``O(1)``) and slightly
  smaller code memory footprint instead of `lookup_switch` (``O(log N)``).

Related Tools
-------------

This section points to tools aimed at helping to improve code quality.

Unit Testing
^^^^^^^^^^^^

Here is a list of rules when writing tests (see :ref:`training_application_testing`):

- Prefer black-box tests (with a maximum coverage).
- Here is the test packages naming convention:

  - Suffix package with .test for black-box tests.
  - Use the same package for white-box tests (allow to use classes with
    package visibility).


.. _sonar_code_analysis:

Code Analysis with SonarQube™
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

SonarQube is an open source platform for continuous inspection of code quality.
SonarQube offers reports on duplicated code, coding standards, unit tests, code coverage, code complexity, potential bugs, comments, and architecture.

To set it up on your MicroEJ application project, please refer to `this documentation <https://github.com/MicroEJ/ExampleTool-Sonar>`_.
It describes the following steps:

- How to run a SonarQube server locally.
- How to run an analysis using a dedicated script.
- How to run an analysis during a module build.

Code Instrumentation
^^^^^^^^^^^^^^^^^^^^

We have tools allow the profiling and logging of Java code behavior, please refer to :ref:`codeInstrumentationForLogging`.

..
   | Copyright 2020-2025, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.

