..
.. ReStructuredText
..
.. Copyright 2021 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

=================
 Troubleshooting
=================

-----------------------------------------------------------------
 Compilation error ``cannot be resolved to a type`` in FFI class
-----------------------------------------------------------------

A compilation error can be raised when the classpath contains unexpected classes, for example::

	Exception in thread "main" java.lang.Error: Unresolved compilation problems: 
		ArrayComparisonFailure cannot be resolved to a type
		ArrayComparisonFailure cannot be resolved to a type

		at java.lang.Throwable.fillInStackTrace(Throwable.java:82)
		at java.lang.Throwable.<init>(Throwable.java:37)
		at java.lang.Error.<init>(Error.java:18)
		at com.microej.js.JsFfi.ffi_toString_0(JsFfi.java:54)
		at com.microej.js.JsCode$1$1.invoke(JsCode.java:50)

As described in :ref:`the FFI section <js.java.ffi>`, in order to call Java methods from JavaScript code, all the methods with the given names are searched in the classpath.
Since the classpath can contain test dependencies which are not available at compile time, the generated FFI can contain classes from these dependencies and therefore fail to compile.
The following classes are excluded by default:

- ``ej.junit.*``
- ``org.junit.*``
- ``junit.*``
- ``org.hamcrest.*``
- ``java.lang.String``
- ``java.lang.Number``

This list can be changed by setting the system property ``js.ffi.excludes.classes`` to a comma-separated list of FQN patterns. For example:

.. code-block:: properties

	js.ffi.excludes.classes=ej.junit.*,org.junit.*,junit.*,org.hamcrest.*,java.lang.String,java.lang.Number,com.mycompany.test.*

.. warning::

    Defining this property overwrites the default value, so do not forget to keep the default excluded classes (unless you know what you are doing).
