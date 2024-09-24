.. _bon_specification:

Beyond Profile (BON)
====================

Introduction
------------

This document defines the BON profile, aimed to define an enhanced and simple
architecture to enable an open, third-party, application development
environment for controlling both its startup sequence and its memory
resource in the best possible way.

Although this specification spans a potentially wide set of devices, it
focus on embedded devices that have non-volatile memories and volatile ones
(eeprom, flash, ram, …). At the application level, it focuses on
applications that have some sort of initialization phase before entering
into a mission phase that then exists forever until the device gets
shutdown or reboots.

Specification Summary
~~~~~~~~~~~~~~~~~~~~~

.. include:: bon_spec_summary.rst

Comments
~~~~~~~~

Your comments about this specification are welcome. Please contact :ref:`our support team <get_support>` with "KF" as subject.


Why BON ?
---------

Many languages let software engineers define the memory management of
their applications. One reason is that most embedded devices have scarce
physical memory, while being cost driven. On the other hand, it is well
known that memory allocation is one of the most difficult tasks to
achieve efficiently as soon as the application uses more than a few
objects.

In order to cope with these two contradictory issues, there are two main
approaches, each one at the extremity of the possibility spectrum:

-  Pre-allocate all of what is needed for the program to run, either
   statically (at compile time) or dynamically once and for all at
   system startup. While running, no extra allocation is done. This
   approach is often used for Hard Real-Time systems when the memory
   consumption cannot be defined at compile-time through formal
   analysis.
-  Let the runtime system manage the memory, fully freeing the engineers
   from that task. This is done through the use of garbage
   collectors. A huge number of different garbage collection policies
   are available and each have their own benefits and drawbacks.

The Java virtual machine specification [JVM2] defines a heap where Java
objects reside. This heap is automatically managed by a garbage
collector. Every Java virtual machine is free to implement the memory
management that best fits the application domain it is designed for.

[JVM2] defines a semantically immortal set of objects: a pool of
``java.lang.String``, which are references in classfile constant
pools [1]_. [JVM2] also defines the way applications get initialized,
even though it is quite a loose process where lazy initialization is
permitted. Intuitively, classes must be initialized before any instance
creation or access to its static variables (see :ref:`bon-startup`).

One of the newer trends in software involves designing simple solutions
that are easy to understand and most importantly easy to manipulate and
control. Developers must be able to minimize development time, often
dealing with small memory budgets for their application. On typical
microcontrollers, the ratio between read-only memory and volatile memory
is four, meaning that there is 4 times more read-only memory (eeprom,
flash, …) than volatile memory (ram). For really cost sensitive devices,
the ratio may drop to 8 (ram is what costs the most), while for rather
more expensive ones it may reach 2.

BON defines a suitable and flexible way to fully control both memory
usage and start-up sequences on devices with limited memory resources.
It does so within the boundaries of the Java semantic. More precisely,
it allows:

-  Controlling the initialization sequence in a deterministic way.
-  Defining persistent immutable read-only objects (that may be placed
   into non-volatile memory areas), and do not require copies to be
   made in ram to be manipulated.
-  Defining immortal read-write objects that are always alive.

BON serves as a very robust foundation for implementing Java software,
in particular embedded Java Software.

BON also add a small set of useful utilities:

-  A Timer facilities that allows to schedule small activities
   repeatedly (or not). Such activities are Runnable objects that are
   automatically scheduled by the timer.
-  Platform time which cannot be changed: the time from the very last
   boot of the device.
-  Read-write ``ByteArray`` support according to the underlying processor
   endianness.
-  A set of useful math operators.

Basic Concepts
--------------

BON experts agreed to limit the set of APIs specified to only those
required to achieve a high level of portability and successful
deployments. Their main concern was to stay within the boundaries of the
Java semantics [JLS].

BON defines two phases for the execution stream:

-  The initialization phase: the initialization sequence executes all
   the static initializer methods (known as the ``<clinit>`` methods).
-  The mission phase: the ``main(String[])`` method of the main class is
   called. The application runs until the device is switched off.

There is a kind of objects, named immutable objects, that are alive at
system startup. They are read-only objects that most probably reside in
non-volatile memory. All together they form a pre-existing world that
exists on its own, just like the hardware does.

First Example
-------------

The simple next example illustrates the use of big buffers. They are
made immortal in order to recycle them manually while they represent the
most critical ram consumption. This example also makes use of an
immutable object, an array of values that never changes during the
lifetime of the device.

.. code-block:: java

    package example;
    public class Filter {
        public static final int BufferSize = 4096;// 16k (an int is 32-bit)
        public static int[][] Buffers;
        public static int[] ValidValues;
        static {
            ValidValues =(int[])ej.bon.Immutables.get("filter");
        }

        static {
            // Allocate the immortal pool of buffers. Only two Filters may
            // be alive at the same time: ==> 32k of ram for two Filters
            Buffers = new int[2][];
            Buffers[0] = (int[])Immortals.setImmortal(new int[BufferSize]);
            Buffers[1] = (int[])Immortals.setImmortal(new int[BufferSize]);
        }

        public int ptr;
        public int[] buffer;

        public Filter(){
            // grab a buffer from the pool, or throw an exception
            synchronized (Buffers){
                for (int i = Buffers.length; --i >= 0; ){
                    if (Buffers[i] != null ){
                        buffer = Buffers[i];
                        ptr=-1;
                        Buffers[i] = null ;
                        break ;
                    } 
                } 
            } 
            if (buffer == null ){
                throw new OutOfMemoryError();
            }
        }
        
        public void close(){
            // recycle manually the immortal buffer: store it in
        // global Buffers array pool
            synchronized (Buffers){
                for (int i = Buffers.length; --i >= 0; ){
                    if (Buffers[i] == null ){
                        Buffers[i] = buffer;
                        break;
                    }
                }
            }
        }

        public synchronized void insert( int value){
            // only insert permitted values

            if (ptr >= BufferSize) return; // full

            for (int j = ValidValues.length; --j >= 0; ){
                if (value == ValidValues[j]){
                    buffer[++ptr] = value;
                }
            }
        }
    }


Object Natures
==============

The BON specification defines three natures for objects: persistent
immutable objects (:ref:`immutable`), immortal objects
(:ref:`immortal`), and reclaimable objects (:ref:`reclaimable`).
Immutable [2]_ objects are also referred to as read-only objects,
whereas reclaimable objects are regular objects.

Although objects get a liveness nature, this is fully transparent at the
Java semantic level. A semantically correct software assuming BON will
behave exactly the same on a Java virtual machine that does not
implement the three BON object natures [3]_.

.. _immutable:

Persistent Immutable Objects
----------------------------

Immutable objects are read-only objects. They are instances of any
concrete class. Although they are immutable, they obey all the Java
object's semantics. In particular, they hold a hash code, have a class
and have a monitor that a thread may enter into.

There is no way for an immutable object to directly refer to a
non-immutable object. References from immutable objects always refer to
other immutable objects. Writing into an immutable object (field write
access) results in an unspecified behavior. The BON experts group
strongly encourages implementations of the BON specification to raise
an uncatchable exception when there is an attempt to write into an
immutable object, although a no-op operation may be sufficient [4]_.

Immutable objects may be created in two ways:

-  At run-time, if the implementation allows this, as described in
   section :ref:`runtimeimmutables`,
-  At system/application configuration time by specifying objects in an
   XML configuration file, as described in the sections immediately below.

In the second case the way the immutable object's descriptions are given
to the Java virtual machine at startup is implementation-dependent. Most
implementations will assume the immutable objects to be at some
particular location in (read-only) memory: the implementation-dependent
way to give the immutable objects at startup would therefore be trivial
(nothing to do, but know the memory address). Note that immutable
objects do not need to be copied in (scarce) ram memory to be
manipulated [5]_.

Software is made up of several parts, often called libraries, that may
come with their own immutable object descriptions. Therefore more than
one immutable description may be given to the Java virtual machine.

Object ID and Immutable Object Querying
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Immutable objects are semantically organized into one global pool, just
like the Java interned ``java.lang.String`` objects.

An immutable object may be attached to a ``java.lang.String`` key, known
as its ID. This ID allows an immutable object to be retrieved out of the
global pool of immutable objects, thanks to the method
``Immutables.get(String)``. The ID of an object is globally unique: the ID
``"ANONYMOUS"`` is a reserved ID (see :ref:`runtimeimmutables`) and cannot be
used to qualify an immutable object.

Immutable Objects Descriptions and Creation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Descriptions are based on the structure of objects, that is, they embed
structural information such as fully qualified class names and field
names. Fields [6]_ that need to get initialized with some value
(base-type or another immutable object) are described using a pair:
field-name, value.

Fields that are not described get initialized with the default Java
value (``0`` for numeric types, ``null`` for objects, ``false`` for booleans,
``0.0`` for floating-point numbers [JLS]). No visibility rule applies,
that is, any kind of field may be listed, even private ones. Final
fields must be initialized.

There is no particular order for the creation of the immutable objects.
The BON experts recommend the use of tools for the creation of large
graphs of immutable objects.

XML Grammar
~~~~~~~~~~~

Immutable objects are described according to the following XML syntax
(Annex :ref:`DTD` gives the DTD).

-  ``<immutables>``: the root element of one immutable objects description.

   -  attributes:
  
      -  ``name``: an optional attribute that defines the content of the XML description.
  
   -  child elements: ``<object>`` , ``<objectAlias>``, ``<array>`` , ``<string>``, ``<class>``, ``<null>``, ``<importObject>``.

-   ``<object>``: element that defines a new object.

   -  attributes:
  
      -  ``id``: the ID string that allows the object to be retrieved
         through the use of ``Immutables.get(String)``
      -  ``type``: the name of the class of the object. An alias may be
         used instead of the fully-qualified class name.
      -  ``private``: a boolean that indicates whether the object will be
         accessible using the ``Immutables.get(String)`` method. If
         false, the objects can only be referenced within the XML
         immutable objects descriptions.

   -  child elements: ``<field>`` , ``<refField>``
  
-  ``<objectAlias>``: element that defines a new key for an existing object.

   -  attributes:

      -  ``id``: the ID string that allows the object to be retrieved
         through the use of ``Immutables.get(String)``.
      -  ``object``: the existing object ID or alias ID.
      -  ``private`` : a boolean that indicates whether the object will be
         accessible using the Immutables.get(String) method. If
         false, the objects can only be referenced within the XML
         immutable objects descriptions.

   -  child elements: none
  
-  ``<string>``: element that defines an interned string.

   -  attributes:
  
      -  ``id``: the ID that allows the object to be retrieved through the
         use of ``Immutables.get(String)``
      -  ``value``: the string literal
      -  ``private`` : a boolean that indicates whether the object will be
         accessible using the ``Immutables.get(String)`` method. If
         false, the objects can only be referenced within the XML
         immutable objects descriptions.

   -  child elements: none

-  ``<class>``: element that defines an instance of a ``java.lang.Class``.
   The ID of this object can be used for type attributes.

   -  attributes:
  
      -  ``id``: the ID that allows the object to be retrieved through the
         use of ``Immutables.get(String)``
      -  ``type``: the class fully qualified name like ``java.lang.Object``.
      -  ``private`` : a boolean that indicates whether the object will be
         accessible using the ``Immutables.get(String)`` method. If
         false, the objects can only be referenced within the XML
         immutable objects descriptions.

   -  child elements: none
  
-  ``<field>``: elements that state a field with its associated literal value.
  
   -  attributes:
 
      -  ``name``: the name of the field as defined in the class that
         defines it.
      -  ``value``: the value of the field. The value is a primitive type
         (numeric or boolean) or a literal string (see ).
      -  ``type``: this attribute is optional. It represents the class
         where the field is defined. A field without its ``type``
         attribute refers to the first field found while scanning the
         class hierarchy from the bottom to the top (following the
         superclass link).

   -  child elements: none

-  ``<refField>``: elements that state a field that references an immutable object.

   -  attributes:

      -  ``name``: the name of the field as defined in the class that
         defines it.
      -  ``ref``: the ID of the referenced immutable object.
      -  ``type``: this attribute is optional. It represents the class
         where the field is defined. A field without its type
         attribute refers to the first field found while scanning the
         class hierarchy from the bottom to the top (following the
         superclass link).

   -  child elements: none

-  ``<array>``: element that defines a new array.

   -  attributes:

      -  ``id``: the ID that allows the object to be retrieved through the
         use of ``Immutables.get(String)``
      -  ``type``: the array type. An alias may be used instead of the
         fully qualified class name. Dimensions are given using the
         Java notation ``[]``.
      -  ``length``: this attribute is optional. It represents the number
         of elements the array has.
      -  ``private`` : a boolean that indicates whether the object will be
         accessible using the ``Immutables.get(String)`` method. If
         false, the objects can only be referenced within the XML
         immutable objects descriptions.

   -  child elements: ``<elem>`` , ``<refElem>``

-  ``<elem>``: element that defines an array element with its literal value.
  
   -  attributes:
 
      -  ``value``: the value of the element. The value is a primitive type
         (numeric or boolean) or a literal string (see ).
 
   -  child elements: none

-  ``<refElem>``: element that defines an array element. Such element
   references an immutable object.

   -  attributes:

      -  ``ref``: the ID of the referenced immutable object.

   -  child elements: none

-  ``<null>``: element that defines a null object that can be referenced
   by an object field or an array element

   -  attributes:

      -  ``id``: the ID that allows the null object to be retrieved through
         the use of ``Immutables.get(String)``
      -  ``private`` : a boolean that indicates whether the object will be
         accessible using the ``Immutables.get(String)`` method. If false,
         the objects can only be referenced within the XML immutable
         objects descriptions.

   -  child elements: none

-  ``<importObject>``: element that import an object that is defined in
   another immutable file. The referenced object may be private or public.

   -  attributes:

      -  ``id``: the ID of the imported object

   -  child elements: none

Class names use the Java notation (using a ``'.'`` as separator):
``java.lang.Object`` is an example.

String literals are defined as in XML specification. To allow quotes in
XML string data use the apostrophe ``'’ '`` separator as XML separator
or the escape character ``&quot;``.

To define the next 9 characters String, ``my"String``, as string literal
value, use one of following syntax:

.. code-block:: xml

    <field name="f1" value=’my"String’ />
    <field name="f1" value="my&quot;String" />

Next table lists the format for the primitive values:

.. list-table:: Table 1: Immutables Primitive Type Format
   :header-rows: 1
   :widths: 2 4 3

   - 
      - Primitive Type
      - Format
      - Example
   - 
      - boolean
      - ``true`` or ``false``
      - ``<…value=”true”/>``
   - 
      - byte, short, int, long
      - Format defined in the Java method ``Long.decode(String)``
      - ``<…value=”123”/>``
        ``<…value=”0x2A”/>``
        ``<…value=”-561”/>``
   - 
      - char
      - ``Format defined in the Java method Long.decode(String)`` or a
        character value between simple quotes
      - ``<…value=”123”/>``
        ``<…value=”'z'”/>``
        ``<…value=”'&#xA9;'”/>``
   - 
      - float
      - Format defined in the Java method Float.parseFloat\ ``(String)``
      - ``<…value=”2.3”/>``
        ``<…value=”4.2e12”/>``
        ``<…value=”-5.671”/>``
   - 
      - double
      - Format defined in the Java method Double.parseDouble\ ``(String)``
      - ``<…value=”2.3”/>``
        ``<…value=”4.2e12”/>``
        ``<…value=”-5.671”/>``


IDs define one global name space [7]_: an ID only refers to only one
object. It is an error to have objects sharing ID.

Immutable XML Description Examples
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: xml

    <immutables name="MyCorp objects">

        <array id="corp.immut00" type="boolean[]" length="2">
            <elem value="true"/>
            <elem value="false"/>
        </array>
        
        <array id="corp.immut01" type="int[]">
            <elem value="3"/>
            <elem value="2"/>
            <elem value="1"/>
        </array>

        <class id="MyClass" type="myCompany.mypackage.MyClass" 
        private="true"/>

        <object id="corp.immut02" type="MyClass">
            <field name="a" value="50" />
            <field name="str" value="Hello" />
            <refField name="b" ref="corp.null" />
        </object>

        <object id="corp.immut03" type="myCompany.mypackage.A">
            <refField name="f" ref="corp.immut04" />
            <refField name="s" ref="corp.internalKey"/>
            <refField name="o" ref="corp2.immut"/>
        </object>

        <string id="corp.immut04" value='Hello World!' />

        <string id="corp.internalKey" value="one" private="true" />

        <string id="key1" value="two" />

        <string id="key2" value='thr"ee' />

        <object id="value1" type="java.lang.Object" />

        <null id="corp.null"/>

        <importObject id="corp2.immut"/>

    </immutables>

.. _runtimeimmutables:

Turning Objects Into Immutable Objects
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Some systems may define persistent memory where new immutable objects
can be stored. Such objects remain “live” through device reboots. The
number of available persistent memory is system dependent and is
described within the datasheet of the Java virtual machine that
implements the BON specification. ``Immutables.totalMemory()`` returns
this persistent immutable memory size, whereas ``Immutables.freeMemory()``
returns the left remaining persistent memory size.

If an object is persistently added with an ID that was already in use by
a previously defined immutable object, the new added object takes
precedence over the object that was referred to by that ID: the next
call to ``Immutables.get(ID)`` returns the last added object with that
ID [8]_.

Objects are (runtime) added to the persistent memory as a graph, defined
by the values held in an hash table.

-  The keys of the hash table represent the IDs of the objects: these
   keys must be of the ``java.lang.String`` [9]_ class. Objects that
   are not in the hash table do not take part in the immutable
   storage action.
-  The special ID ``"ANONYMOUS"`` allows objects held by an array (from
   the type ``java.lang.Object[]``) to be added into the hash table.
   They are considered as being part of the hash table, but
   anonymously. The key ``"ANONYMOUS"`` is not added to the set of all
   available IDs [10]_.


.. _illustration-1:
.. figure:: images/bon_spec/illust1.png
  :align: center
  :width: 515px
  :height: 203px

  Illustration 1: Example of hash table passed to ``Immutables.putAll(Hashtable)``.


The hash table is added using the
``Immutables.putAll(Hashtable)`` method. It persistently writes copies of
all the values in the hash table that are not already immutable objects.
All references within those objects to non-immutable objects or to
objects that are outside the hash table are set to ``null``. References to
immutable objects remain, literal strings [11]_ are considered as
immutable (see :ref:`immutable`). Keys that refer to ``null`` are
ignored.

The ``Immutables.put(String, Object)`` method allows to store a single
object.

All operations on ``Immutables`` must be thread safe.

.. _immortal:

Immortal Objects 
----------------

Non Garbageable Objects
~~~~~~~~~~~~~~~~~~~~~~~

Immortal objects are regular objects that are not managed by the Java
virtual machine garbage collector. Immortal objects do not move around
in memory: they remain physically located in one memory location
forever.

.. _turningIntoImmortal:

Turning Objects Into Immortal Objects
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Reclaimable objects may be turned into immortal objects using the
``Immortals.setImmortal(Object)`` method. Only the object passed as
argument is turned into an immortal object, i.e. none of the objects it
refers to through its fields become immortal. This is in contrast with
``Immortals.deepImmortal(Object)`` that turns the object passed as the
argument and all objects referred to from the argument into immortal
objects. Note that weakly reachable objects are not turned into immortal
objects; in other words the ``WeakReference`` semantic is not affected by
this operation.

The total amount of free immortal memory still available is
``Immortals.freeMemory()``. It is system dependent.

The system provides the possibility to create objects directly as
immortal objects using the method ``Immortals.run(Runnable)``: while the
``run()`` method of the ``Runnable`` executes, all created objects are
allocated as immortal objects.

The system may define a property ``ej.bon.immortalAfterInit``. If the
property exists and if set to ``true``, a global memory collection is
triggered at the end of the initialization phase, reclaiming all dead
objects that were created to get the system initialized. All remaining
objects become immortal, and accessible for the mission phase.

.. _reclaimable:

Reclaimable Objects
-------------------

Death Notification
~~~~~~~~~~~~~~~~~~

Most objects are reclaimable objects. Sometimes, they interact with the
underlying system using handles. Those handles represent underlying data
that needs to be closed/freed/acknowledged/… when the object that holds
the handle dies.

The BON profile defines a sound and easy way to get notified when an
object is dead through the use of ``EnqueuedWeakReference`` objects:
``EnqueuedWeakReference`` is a subclass of ``WeakReference``. When such
objects get their weak reference set to ``null`` by the system, they are
added to a ``ReferenceQueue`` they were assigned to at their creation.

Death Notification Actions
~~~~~~~~~~~~~~~~~~~~~~~~~~

Once an object has expired, it cannot be brought to life again. It is
the responsibility of the application to make provisions for all actions
that have to be taken on an object death. Such provisions are
materialized by subclasses of the ``EnqueueWeakReference`` class.

``ReferenceQueue.poll()`` and ``ReferenceQueue.remove()`` allow the
execution of a hook at the death of the object referenced by the weak
reference. The first one returns ``null`` when queue is empty whereas the
second one blocks while the queue is empty.

The application is responsible of the execution of such hook.

Weak objects association
~~~~~~~~~~~~~~~~~~~~~~~~

``java.util.Hashtable`` allows to associate a ``value`` with a ``key`` within
a table (the key indexes the value within the table for fast searches).
It prevents both key and value from being discarded by the garbage
collector.

BON defines the ``ej.bon.WeakHashtable`` class as a subclass of
``java.util.Hashtable``. ``WeakHashtable`` allows to relax such hard
constraint on the key, which becomes a weak reference within the table.
If no other regular reference refers the key, the key can be removed
automatically by the system, which removes the associated value too.

Runtime Phases
==============

BON defines two phases of execution:

-  ``initialization phase``: this is the very first Java code that
   executes. Its purpose is to let the device “boot”, that is, to
   initialize all necessary resources, like allocating buffers for
   drivers, performing default sanity checks, scanning hardware, etc.
-  ``mission phase``: once initialized, the device switches to the endless
   mission phase. The device and its software application run until
   they are switched off.

Initialization Phase
--------------------

``ej.bon.Util.isInInitialization()`` allows the phase to be tested.

.. _mono:

Mono-threaded Phase
~~~~~~~~~~~~~~~~~~~

During the initialization phase, there is only one Java thread running:
the main thread which will eventually execute the ``main(String[])``
method once the system enters the mission phase.

.. _illustration-2:
.. figure:: images/bon_spec/illust2.png
  :align: center
  :width: 686px
  :height: 263px

  Illustration 2: BON phases and thread activation.

If other threads are created while the class initializations execute
(``<clinit>`` methods), those threads will be on hold (i.e. waiting) until
the system enters the mission phase, even if those threads have received
the ``start()`` message and have a higher priority than the main thread.

If the property ``ej.bon.immortalAfterInit`` is set, all live objects
become immortal (see :ref:`turningIntoImmortal`) at the end of the
initialization phase.

.. _bon-startup:

Deterministic Initialization Order 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If a class needs to be initialized, it defines a ``<clinit>`` method [12]_
[JVM2].

During the initialization phase, all classes which are involved within
the application are initialized. It implies calling all ``<clinit>``
methods, in sequence.

Although the precise order of the sequence of calls is not known, it
MUST be defined once for all, before any code execution. This order does
not rely on runtime behavior, but only on the application code. The
constraint is: if the application code does not change, the order
remains the same.

The order must be compatible with the Java semantic [JLS]. Intuitively,
a class may depend on other classes. Those classes should be initialized
first. We list a few of these dependencies: object creation, superclass,
methods receiver, arguments and fields types, … Refer to [JVM2] for a
complete description of the initialization process and its implications
on the order of the ``<clinit>`` sequence.

Dependencies of classes upon themselves define a graph of dependencies.
This graph may depict cycles. The graph is linearized in an order which
depends only on the graph itself.

Although BON experts encourage implementors of this specification to
explain the order of the ``<clinit>`` sequence to engineers in some useful
way, this is not mandatory.

The classes dependencies MUST include all the classes of pre-configured
immutable objects.

The ``main(String[])`` method of the main class [JVM2] is an entry point
in the dependencies graph.

Mission Phase
-------------

Thread Activations
~~~~~~~~~~~~~~~~~~

At the beginning of the mission phase, all threads that have been
started during the initialization phase activated.
``ej.bon.Util.isInMission()`` allows the phase to be tested.

Thread Control
~~~~~~~~~~~~~~

In mission phase, one thread may send an exception within the context of
another thread, using the
``ej.bon.Util.throwExceptionInThread(RuntimeException,Thread)`` method.

.. _illustration-3:
.. figure:: images/bon_spec/illust3.png
  :align: center
  :width: 527px
  :height: 264px

  Illustration 3: Sending an asynchronous exception Util.throwExceptionInThread.

The exact moment at which the exception is thrown is system dependent.
However, if the thread in which the exception is to be thrown has
entered one or more critical sections (i.e. it holds some object's
monitor) the exception is not thrown until the thread has exited all the
critical sections. In such situations, the system should make its best
effort to have the thread exit all the critical sections it has entered
as fast as possible.

.. _illustration-4:
.. figure:: images/bon_spec/illust4.png
  :align: center
  :width: 520px
  :height: 253px

  Illustration 4: Exception thrown when thread has exited all critical sections.|

The ``ej.bon.Util.throwHardExceptionInThread(RuntimeException,Thread)``
just throw the exception, as if it was sent from inside the thread. It
does not wait for the critical sections to finish.

For both ``throwHardExceptionInThread`` and ``throwExceptionInThread``, if
the thread is either sleeping or waiting, the thread is unblocked (i.e.
thread is interrupted: a ``java.lang.InterruptedException`` is thrown) and
the exception is thrown as soon as possible.

Class.forName 
~~~~~~~~~~~~~~

If the system is capable of dynamic code downloading,
``Util.dynamicCodeAllowed()`` returns ``true``, and this specification
defines a consistent
and sound way for downloading code that matches the overall semantic of BON:

-  All referenced classes from the class given in
   ``Class.forName(String)`` have to be
   determined at once. They form the downloaded classes.
-  Initialization of all downloaded classes MUST be ordered as
   specified in :ref:`bon-startup`. All
   methods of the downloaded classes that are accessible from
   outside the downloaded classes
   scope are considered as entry points for the dependencies graph
   computation.
-  A new thread is created in an initialization phase, which means
   that
   ``Util.isInInitialization()`` return ``true`` if executed in the
   context of this new thread. All class initializations of the downloaded classes are
   executed in that thread. As in :ref:`mono`, all thread
   activations (i.e. ``Thread.start()``) are disabled until this initialization
   thread is done. Note that even if the property
   ``ej.bon.immortalAfterInit`` is set, objects
   created during this initialization phase do not become immortal.

BON Properties 
----------------

The BON specification defines a set of optional properties:

-  ``"ej.bon.version"``: the version holds three positive integers
   separated by ``'.'`` (e.g.: ``1.2.0``).
-  ``"ej.bon.vendor"``: the name of the BON library provider.
-  ``"ej.bon.vendor.url"``: the web site of the BON library provider.
-  ``"ej.bon.immortalAfterInit"``: if set to ``true``, turn as immortal all
   remaining live objects at the end of the initialization phase (see :ref:`turningIntoImmortal`).

Utilities
=========

Timer & TimerTask
-----------------

An ``ej.bon.Timer`` defines a single Java thread in charge of scheduling
``Runnable`` objects from the ``ej.bon.TimerTask`` class. All ``TimerTask``
are executed sequentially, according to their schedule. A ``Timer`` does
its best effort to schedule the ``TimerTask`` appropriately, which depends
on the ``TimerTask`` durations and schedules (there is no real-time
guaranties).

A ``TimerTask`` may be scheduled repeatedly. In that case, the delay for
the next schedule may depends on the end of the previous ending of the
``TimerTask``, and not on some absolute time: if the previously execution
of the ``TimerTask`` is delayed for some reason, the next executions are
delayed too by the same amount of time. It is also possible to schedule
repeatedly a ``TimerTask`` at fixed rate, which allows executions to be
independent .

In case a ``TimerTask`` execution terminates unexpectedly, the other tasks
are not impacted: the ``TimerTask`` is assumed to have terminated its
execution regularly, and is not rescheduled event if it was scheduled
repeatedly.

The main APIs are:

-  ``schedule(TimerTask, long)`` and ``schedule(TimerTask, Date)`` methods
   allow to schedule one execution after the specified delay.
-  ``schedule(TimerTask task, long, long)`` and ``schedule(TimerTask, Date,
   long)`` methods allow to schedule repeatedly executions, the first
   one after the specified delay. The waiting time between two
   executions is relative to the end of the previous execution.
-  ``scheduleAtFixedRate(TimerTask task, long, long)`` and
   ``scheduleAtFixedRate(TimerTask, Date, long)`` methods allow to
   schedule repeatedly executions, the first one after the specified
   delay. The waiting time between two executions is independent of
   the end of the previous execution.

Platform time
-------------

The application time is the user time: it depends on its localization.
``java.lang.System.currentTimeMillis`` returns the application time
expressed in milliseconds since midnight, January 1, 1970 UTC.

BON introduces a platform time that is independent from any user
considerations: it materializes the running time since the very last
start of the device. This time cannot be changed.

The ``ej.bon.Util`` class defines several methods to handle both
application time and platform time: 

-  ``platformTimeNanos`` and ``platformTimeMillis`` method return the
   platform time, a ``long``, expressed in nanoseconds and in
   milliseconds.
-  ``setCurrentTimeMillis(long)`` and ``setCurrentTimeMillis(Date)``
   methods allow to change the application time in order to match a
   user localization. This has no effect on the platform time.
   ``ej.bon.Util.currentTimeMillis()`` method is a synonym of
   ``java.lang.System.currentTimeMillis``.

Byte Array Accesses
-------------------

The addresses space is 8-bit oriented even if there are platforms that
manipulate quantities that are larger than an 8-bit: 32-bit processors
for example do so. The ordering of individual addressable sub-components
within the representation of a larger data item is called the
endianness. ``BigEndian`` describes an ordering with the most significant
byte first, whereas ``LittleEndian`` describes an ordering with the least
significant byte first.

.. _illustration-5:
.. figure:: images/bon_spec/illust5.png
  :align: center
  :width: 447px
  :height: 70px

  Illustration 5: Representation of the 32-bit quantity 0x0000100A using both BigEndian and in LittleEndian layout.

BON introduces methods to read and write into array of byte (byte[])
according to the platform endianness, or according to a specific
provided endianness. The ``ej.bon.ByteArray`` class provides such APIs:

-  ``getPlatformEndianness()`` returns the underlying system-dependent
   endianness, which mostly depends on the target processor(s).
-  ``readInt(byte[], int)`` and ``writeInt(byte[], int, int)`` reads and
   writes an ``int`` using the platform specific endianness.
-  ``readInt(byte[], int, int)`` and ``writeInt(byte[], int, int, int)``
   reads and writes an ``int`` using the specified endianness as last
   argument, which may be either ``LITTLE_ENDIAN`` or ``BIG_ENDIAN``.

Similar methods are provided for ``short``, ``char``, ``long`` types.

Math
----

The ``ej.bon.XMath`` complements the math operations provided by
``java.lang.Math``. The new operations are: ``limit``, ``asin``, ``acos``,
``atan``, ``log``, ``exp``, ``pow``.

.. _DTD:

Annex A: Immutables DTD
=======================

.. code-block:: dtd

    <!ELEMENT immutables ( object*, objectAlias*, array*, string*, class*, null*, importObject* ) >
    <!ATTLIST immutables 
        name     CDATA #IMPLIED
    >

    <!ELEMENT object ( field*, refField* ) >
    <!ATTLIST object 
        id    	ID    #REQUIRED
        private  	(true | false) "false"
        type	 	CDATA #REQUIRED
    >

    <!ELEMENT objectAlias EMPTY >
    <!ATTLIST objectAlias 
        id    	ID    #REQUIRED
        private  	(true | false) "false"
        object 	IDREF #REQUIRED
    >


    <!ELEMENT array ( elem*, refElem* ) >
    <!ATTLIST array 
        id    	ID    #REQUIRED
        private  	(true | false) "false"
        type  	CDATA #REQUIRED 
        length 	CDATA #IMPLIED 
    >

    <!ELEMENT elem EMPTY >
    <!ATTLIST elem 
        value CDATA #REQUIRED 
    >

    <!ELEMENT refElem EMPTY >
    <!ATTLIST refElem 
        ref IDREF #REQUIRED 
    >

    <!ELEMENT class EMPTY >
    <!ATTLIST class 
        id    	ID    #REQUIRED
        private  	(true | false) "false"
        type		CDATA #REQUIRED
    >

    <!ELEMENT string EMPTY >
    <!ATTLIST string 
        id    	ID    #REQUIRED
        private  	(true | false) "false"
        value 	CDATA #REQUIRED
    >

    <!ELEMENT field EMPTY >
    <!ATTLIST field 
        name  CDATA #REQUIRED 
        value CDATA #REQUIRED 
        type  CDATA #IMPLIED
    >

    <!ELEMENT refField EMPTY >
    <!ATTLIST refField 
        name  CDATA #REQUIRED 
        ref 	IDREF #REQUIRED 
        type  CDATA #IMPLIED
    >

    <!ELEMENT null EMPTY >
    <!ATTLIST null 
        id    	ID    #REQUIRED
        private  	(true | false) "false"
    >

    <!ELEMENT importObject EMPTY >
    <!ATTLIST importObject 
        id    	ID    #REQUIRED
    >



.. [1]
   Literal strings are turned into CONSTANT_String_info by Java
   compilers.

.. [2]
   Persistent immutable objects are named immutable objects throughout
   the specification.

.. [3]
   Writing into an immutable object is considered as a semantic error.

.. [4]
   The write access to read-only memory is often a no-op operation that
   has no cost.

.. [5]
   A specification with persistent storage that would force to copies
   the data/objects in ram would be impractical for small devices.

.. [6]
   Only instance fields of objects are involved, i.e. not static fields.

.. [7]
   As a good practice, it is recommended to define ID using a qualified
   name, such as “myCorp.myApp.MyID12”.

.. [8]
   This feature is often used to overwrite default system setting.

.. [9]
   On highly resource constrained devices, it might be important to
   define short ID.

.. [10]
   The ANONYMOUS key holds all the private immutable objects.

.. [11]
   Dynamically created interned String (using ``intern()`` method) are not
   considered as immutable objects.

.. [12]
   ``<clinit>`` methods are not visible per se at the Java source level.
   They are generated by compilers: they capture the semantic of the
   initialization of both static fields and static initializers of
   classes.


..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
