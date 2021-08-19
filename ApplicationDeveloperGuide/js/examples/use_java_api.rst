..
.. ReStructuredText
..
.. Copyright 2021 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

Use a Java API in JavaScript
============================

.. note::

    Before trying this example, make sure you have the :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>` installed.

    It is also recommended to follow the :ref:`js.getting_started` page and/or the :ref:`js.examples.simple_app` example before.

In this example the JavaScript code calls a Java API.
The Java API can come from the application or from any library used by the application.
Let's create it in the project for this example, in a class ``Calculator`` (``src/main/java/com/mycompany/Calculator.java``):

.. code-block:: java

    public class Calculator {
        public int sum(int x, int y) {
            return x + y;
        }

        public int mul(int x, int y) {
            return x * y;
        }
    }

Then in the Java Main class of the application, add the glue to expose the `Calculator` Java API to the JavaScript code and init the JavaScript engine:

.. code-block:: java

    public static void main(String[] args) throws Exception {
        // Add the "getCalculator" function in the JavaScript global object
        JsRuntime.JS_GLOBAL_OBJECT.put("getCalculator", JsRuntime.createFunction(new JsClosure() {
            @Override
            @Nullable
            public Object invoke(Object thisBinding, int argsLength, Object... arguments) {
                return new Calculator();
            }
        }), false);

        // Init the JavaScript code
        JsCode.initJs();
        // Start the JavaScript engine
        JsRuntime.ENGINE.run();
    }

You can now call the API from the JavaScript code:

.. code-block:: javascript

    var calc = getCalculator();
    print(calc.sum(1, 2));
    print(calc.mul(5, 3));

As you can see, the methods of the Java API `Calculator` can be used directly from the JavaScript code.

Finally, build and execute the application with the :ref:`MMM CLI <mmm_build_kit>`:

.. code-block:: console

    $ mmm build
    $ mmm run

The sum and multiply results should be displayed.

For more information about communication between Java and JavaScript please refer to the :ref:`js.java` page.