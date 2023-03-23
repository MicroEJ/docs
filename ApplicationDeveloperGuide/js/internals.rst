.. _js.internals:

Internals
=========

JavaScript Sources Processing
-----------------------------

The JavaScript code is not executed directly, it is first translated in Java code and compiled with the Java application code.
This transpilation is done by the JavaScript Add-On Processor.
This processor uses the OpenJDK Nashorn library (extracted from `jre1.8.0_92`) to parse the Javascript files. 

The operations performed by this processor are summarized in this diagram:

.. figure:: images/js_processor_overview.png
   :alt: MicroEJ JavaScript Processor Overview
   :align: center

- **Parsing**: all JavaScript source files located in the folder ``src/main/js`` and ``src/test/js`` are parsed by the Nashorn library to provide a JavaScript AST.
- **JS Validation**: validation on the JavaScript AST to detect unsupported language features (for example ``eval``).
- **Conversion preparation**: before actually converting the JavaScript AST to a Java AST, a preparation operation is done to initialize all the lexical environments (done by ``JsIrVisitor``).
- **Conversion**: conversion of the JavaScript AST to a Java AST.
- **Java AST cleanup/optim**: post-conversion step to cleanup and optimize the Java AST. The following operations are done:
  - fix imports
  - remove dead code
  - remove literal statements
- **Java sources generation**: generation of the Java sources from the Java AST.

.. _js.java.ffi:

Foreign Function Interface
--------------------------

As said in the section :ref:`js.java.java_to_js`, a JavaScript code can manipulate Java objects and call methods on Java objects.
This chapter describes how does the call to methods on Java objets work.

Let ``getValue()`` a Java method called from JavaScript on a Java object.
As long as the type of the object is not known at compile-time in the JavaScript code, all the types containing a method with the same signature are searched in the classpath.
Then the JavaScript pre-processor generates a ``JsFfi`` class and a method that dynamically tries to find the type of the receiver object.
So, when the ``getValue()`` method is called from JavaScript, this generated method is called.

.. Warning::
    Calling a method whose name is very common could result in a delay while calling it, and some useless methods embedded.

This example shares a Java Date of the current time:

.. code-block:: java

	JsRuntime.JS_GLOBAL_OBJECT.put("getCurrentDate", JsRuntime.createFunction(new JsClosure() {
		@Override
		public Object invoke(Object thisBinding, Object... arguments) {
			return Calendar.getInstance().getTime();
		}
	}), false);

The JavaScript can then use this Date to print the current time:

.. code-block:: javascript

	var date = getCurrentDate()
	var time = date.getTime()
	print("Current time: ", time)

In this case, the generated method in `JsFfi` looks like:

.. code-block:: java

	public static Object ffi_getTime_0(Object function, @ej.annotation.Nullable Object this_) {
		try {
			if (this_ instanceof JsObject || this_ instanceof String)
				return JsRuntime.functionCall(((Reference) function).getValue(), this_);
			if (this_ instanceof Calendar) {
				return ((Calendar) this_).getTime();
			}
			if (this_ instanceof Date) {
				return new Double(((Date) this_).getTime());
			}
		} catch (JsErrorWrapper e) {
			throw e;
		} catch (Throwable t) {
			throw new JsErrorWrapper(new JsObjectError.TypeError("A Java exception has been thrown in generated FFI code of getTime"), t);
		}
		throw new JsErrorWrapper(new JsObjectError.TypeError("getTime"));
	}

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
