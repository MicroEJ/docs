
Create a JavaScript API from Java
=================================

.. note::

    Before trying this example, make sure you have the :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>` installed.

    It is also recommended to follow the :ref:`js.getting_started` page and/or the :ref:`js.examples.simple_app` example before.

In this example a JavaScript API is exposed from Java.
This can be useful when a specific API must be defined in JavaScript or when adapting an existing Java API to a JavaScript API.

Create a class ``MyApiHostObject`` (``src/main/java/com/mycompany/MyApiHostObject.java``):

.. code-block:: java

	public class MyApiHostObject extends JsObject {

		public MyApiHostObject(Object thisBinding) {

			this.put("count", new DataPropertyDescriptor(JsRuntime.createFunction(new JsClosure() {
				@Override
				@Nullable
				public Object invoke(@Nullable Object thisBinding, int argsLength, Object... arguments) {
					String data = (String) arguments[0];
					return Integer.valueOf(data.length());
				}
			})));

		}
	}

This class defines a JavaScript object using the MicroEJ JavaScript API by extending the class ``JsObject``.
It also defines a ``count`` method which accepts a String parameter and returns its length.

Then in the Java Main class of the application, add the glue to expose the `MyApi` object to the JavaScript code and init the JavaScript engine:

.. code-block:: java

	public static void main(String[] args) throws Exception {
		// Add the "MyApi" function in the JavaScript global object
		JsRuntime.JS_GLOBAL_OBJECT.put("MyApi", JsRuntime.createFunction(new JsClosure() {
			@Override
			@Nullable
			public Object invoke(Object thisBinding, int argsLength, Object... arguments) {
				return new MyApiHostObject(thisBinding);
			}
		}), false);

		// Init the JavaScript code
		JsCode.initJs();
		// Start the JavaScript engine
		JsRuntime.ENGINE.run();
	}

You can now call the new API from the JavaScript code:

.. code-block:: javascript

	var myApi = new MyApi();
	print(myApi.count("Hello World!"));

Finally, build and execute the application with the :ref:`MMM CLI <mmm_build_kit>`:

.. code-block:: console

    $ mmm build
    $ mmm run

The length of the string ``Hello World!`` (12) should be displayed.

For more information about communication between Java and JavaScript please refer to the :ref:`js.java` page.

..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
