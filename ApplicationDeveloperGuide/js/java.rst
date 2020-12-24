..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

===================================
 Communication between Java and JS
===================================

---------
 Closure
---------

Java can create JS functions and make them accessible to the JS runtime.

It is achieved by creating a JsClosure and sharing it in the JS global object.

This example shares a function named `javaPrint`::

    JsRuntime.JS_GLOBAL_OBJECT.put("javaPrint", JsRuntime.createFunction(new JsClosure() {
		@Override
		public Object invoke(Object thisBinding, Object... arguments) {
			System.out.println(arguments[0]);
			return null;
		}
	}), false);

This function can then be used in JS::

    javaPrint("foo")

This technique can also be used to share Java objects to JS. It is achieved by returning any Java object in the `invoke` method.

----------------------------
 Foreign Function Interface
----------------------------

As said above, JS can manipulate Java objects and call methods on Java objects.

Let `getValue()` a Java method called from JS on a Java object.
As long as the type of the object is not known at compile-time in the JS, all the types containing a method with the same signature are searched. Then the JS pre-processor generates a `JsFfi` class and a method that dynamically tries to find the type of the receiver object. So, when the `getValue()` method is called from JS, this generated method is called.

.. Warning::
    Calling a method whose name is very common could result in a delay while calling it, and some useless methods embedded.

This example shares the a Java Date of the current time::

	JsRuntime.JS_GLOBAL_OBJECT.put("getCurrentDate", JsRuntime.createFunction(new JsClosure() {
		@Override
		public Object invoke(Object thisBinding, Object... arguments) {
			return Calendar.getInstance().getTime();
		}
	}), false);

The JS can then use this Date to print the current time::

	var date = getCurrentDate()
	var time = date.getTime()
	print("Current time: ", time)

In this case, the generated method in `JsFfi` looks like::

	public static Object ffi_getTime_0(Object function, Object this_) {
		try {
			if(this_ instanceof NativeObject) {
				return JsRuntime.functionCall(((Reference)function).getValue(), this_);
			}
			if(this_ instanceof Calendar) {
				return ((Calendar)this_).getTime();
			}
			if(this_ instanceof Date) {
				return new Double( ((Date)this_).getTime());
			}
		} catch(JsErrorWrapper e){
			throw e;
		} catch(Throwable t){
			throw new JsErrorWrapper( new TypeError( "A Java exception has been thrown in generated FFI code of getTime"), t);
		}
		throw new JsErrorWrapper( new TypeError( "getTime"));
	}
