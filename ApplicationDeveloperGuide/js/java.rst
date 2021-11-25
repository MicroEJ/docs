..
.. ReStructuredText
..
.. Copyright 2020-2021 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _js.java:

Communication Between Java and JS
=================================

The MicroEJ engine allows to communicate between Java and JavaScript: Java API can be used from JavaScript code and vice-versa.

.. _js.java.engine:

JavaScript Engine
-----------------

The JavaScript code is executed in a single-threaded engine, which means only one JavaScript statement is executed at a given time.
Each piece of JavaScript code that must be executed is pushed in a job queue.
It is up to the engine to manage the job queue and execute the jobs.

One consequence of this design is that Java code called from a JavaScript code must not be blocker.
When calling a Java API from a Javascript code, in order to avoid blocking the JavaScript engine, the Java code must return as quick as possible.
Otherwise the JavaScript engine is stuck and cannot execute other JavaScript jobs.
It is especially harmfull when the Java operation takes time, for example for network or IO operations.
In such a case, it is therefore recommended to execute it in a new thread and return immediately.

Another consequence of the JavaScript engine design is that JavaScript code must always be executed by the engine, by the single thread.
Therefore, any call to a JavaScript code from a Java code must create a job and add it to the job queue.  

.. _js.java.java_to_js:

Calling Java from JavaScript
----------------------------

The MicroEJ engine allows to expose Java objects or methods to the JavaScript code by using the engine API and creating the adequate JavaScript object.

Java objects can be exposed to JavaScript using the ``JavaImport`` mechanism: 
it takes a Java fully qualified name as argument and returns an objects that 
gives access to the constructors, static methoods and static fields.

For instance, the following code imports ``java.lang.System`` and prints a 
string calling ``System.out.println()``:

.. code-block:: javascript

	var System = JavaImport("java.lang.System")
	System.out.println("foo");

Here we instantiate a Java ``File`` object and checks that it exists:

.. code-block:: javascript

	var File = JavaImport("java.io.File")
	var myFile = new File("myFile.txt")

	if (myFile.exists()) {
		print("myFile.txt exists")
	} else {
		print("myFile.txt does not exist")
	}

We can also implement JavaScript functions in Java by adding their 
implementation to the global object from Java. For example, here is the code to 
create a JavaScript function named `javaPrint` in the global scope:

.. code-block:: java

    JsRuntime.JS_GLOBAL_OBJECT.put("javaPrint", JsRuntime.createFunction(new JsClosure() {
		@Override
		public Object invoke(Object thisBinding, Object... arguments) {
			System.out.println("Print from Java: " + arguments[0]);
			return null;
		}
	}), false);

The function is created with a ``com.microej.js.objects.JsObjectFunction`` object created with the API ``JsRuntime.createFunction(JsClosure jsClosure)``,
and injected in the object ``JsRuntime.JS_GLOBAL_OBJECT`` which maps to the JavaScript global scope.

The function ``javaPrint`` can then be used in JS:

.. code-block:: javascript

    javaPrint("foo")

This technique can also be used to share any Java object to JavaScript.
It is achieved by returning the Java object in the `invoke` method of the ``JsClosure`` object.
For example, a Java ``Date`` object can be exposed as follows:

.. code-block:: java

	JsRuntime.JS_GLOBAL_OBJECT.put("getCurrentDate", JsRuntime.createFunction(new JsClosure() {
		@Override
		public Object invoke(Object thisBinding, Object... arguments) {
			return Calendar.getInstance().getTime();
		}
	}), false);

When a Java object is exposed in JavaScript, all its public methods can be called, therefore the JavaScript code can then use this ``Date`` object and get the time:

.. code-block:: javascript

	var date = getCurrentDate()
	var time = date.getTime()
	print("Current time: ", time)

for more information on how these called are managed by the MicroEJ JavaScript engine, please go to the :ref:`js.java.ffi` section.

Java objects can also be shared using one of the other Java JS adapter objects.
With this solution, the code of the Java object is executed at engine initialisation, contrary to the previous solution where it is executed only when the JavaScript code is called.
For example, here is the code to expose a Java string named `javaString` in the JavaScript global scope:

.. code-block:: java

    JsRuntime.JS_GLOBAL_OBJECT.put("javaString", "Hello World!", false);

The string ``javaString`` can then be used in JS:

.. code-block:: javascript

    var myString = javaString;

The available Java JS adapter objects are:

- ``com.microej.js.objects.JsObject`` : exposes a Java object as a JavaScript object
- ``com.microej.js.objects.JsObjectFunction`` : exposes a Java "process" as a JavaScript function (using a JsClosure object)
- ``com.microej.js.objects.JsObjectString`` : exposes a Java String as a JavaScript String
- ``com.microej.js.objects.JsObjectArray`` : exposes a Java items collection as a JavaScript Array
- ``com.microej.js.objects.JsObjectBoolean`` : exposes a Java Boolean as a JavaScript Boolean
- ``com.microej.js.objects.JsObjectNumber`` : exposes a Java Number as a JavaScript Number

.. _js.java.js_to_java:

Calling JavaScript from Java
----------------------------

The MicroEJ JavaScript engine API allows to call JavaScript code from Java code.
For example, given the following JavaScript function in a file in ``src/main/js``:

.. code-block:: javascript

    function sum(a, b) {
        print(a + " + " + b + " = " + (a+b));
    }

it can be called from a Java piece of code with:

.. code-block:: java

    JsObjectFunction functionObject = (JsObjectFunction) JsRuntime.JS_GLOBAL_OBJECT.get("sum");
    JsRuntime.ENGINE.addJob(functionObject, JsRuntime.JS_GLOBAL_OBJECT, new Integer(5), new Integer(3));

The first line gets the JavaScript function from the global scope.
The second line adds a job in the JavaScript engine queue to execute the function, in the global scope, with the arguments ``5`` and ``3``.

Passing Values Between JavaScript and Java
------------------------------------------

JavaScript base types are represented by Java objects and not Java base types. 
The following table show the correspondance between types in both languages: 

+------------+-----------------------------------------------+
| JavaScript | Java                                          |
+============+===============================================+
| Number     | ``java.lang.Integer`` or ``java.lang.Double`` |
+------------+-----------------------------------------------+
| Boolean    | ``java.lang.Boolean``                         |
+------------+-----------------------------------------------+
| String     | ``java.lang.String``                          |
+------------+-----------------------------------------------+
| Null       | ``null`` value                                |
+------------+-----------------------------------------------+
| Undefined  | ``JsRuntime.JS_UNDEFINED_OBJECT`` singleton   |
+------------+-----------------------------------------------+

In JavaScript, a ``Number`` type is a 64-bits floating-point value. 
Nevertheless, Kifaru may use integer values (``Integer`` Java type) when 
possible for performance reasons. Otherwhise, ``Double`` type will be used.

.. note::

    Prefer passing ``Integer`` values as argument to a job added to the JavaScript execution queue, or return ``Integer`` values when implementing a ``JsClosure`` instead of ``Double`` when possible.

It is not possible to retrieve the returned value of a JavaScript function from 
Java. For instance, consider the following JavaScript function:

.. code-block:: javascript

    function sum(a, b) {
        return a + b;
    }

When calling this function from Java, we have no way to get the result back:

.. code-block:: java

    JsObjectFunction functionObject = (JsObjectFunction) JsRuntime.JS_GLOBAL_OBJECT.get("sum");
    JsRuntime.ENGINE.addJob(functionObject, JsRuntime.JS_GLOBAL_OBJECT, new Integer(5), new Integer(3));

A workaround is to modify the JavaScript function so it takes a callback object 
as argument:

.. code-block:: javascript

    function sum(a, b, callback) {
        callback.returnValue(a + b);
    }

Here is a possible implementation of the callback object:

.. code-block:: java

    public class Callback<T> {

        @Nullable
        private T value;

        private boolean returned;

        /**
         * Gets the value returned by this callback function when ready.
         * <p>
         * A call to this method waits for the value to be ready.
         *
         * @return the value return by the callback
         */
	    @Nullable
        public T getValue() {
            synchronized (this) {
                while (!this.returned) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        throw new JsErrorWrapper(""); //$NON-NLS-1$
                    }
                }
            }

             return this.value;
        }

        /**
         * Sets the value to return by this callback function.
         *
         * @param value
         *            the value to return
         */
        public synchronized void returnValue(@Nullable T value) {
            this.value = value;
            this.returned = true;
            notify();
        }
    }

We can now pass the callback to the job. The Java code will wait on the 
``callback.getValue()`` untill the result is ready.

.. code-block:: java

    JsObjectFunction functionObject = (JsObjectFunction) JsRuntime.JS_GLOBAL_OBJECT.get("sum");
    Callback<Integer> callback = new Callback<>();
    JsRuntime.ENGINE.addJob(functionObject, JsRuntime.JS_GLOBAL_OBJECT, new Integer(5), new Integer(3), callback);
    Integer returnedValue = callback.getValue();
    System.out.println("Result is " + returnedValue);
