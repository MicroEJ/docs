..
.. ReStructuredText
..
.. Copyright 2021 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

.. _js.examples.simple_app:

Simple Application
==================

.. note::

    Before trying this example, make sure you have the :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>` installed.


This example shows the minimal code for a MicroEJ JavaScript application:

- create an :ref:`Add-On Library <libraries>` project or a :ref:`Sandboxed Application <sandboxed_application>` project
- add the MicroEJ JavaScript dependency in the build file of your project:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("com.microej.library.runtime:js:0.13.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.library.runtime" name="js" rev="0.13.0"/>


- init the JavaScript code in your Java application with:

.. code-block:: java

    import com.microej.js.JsCode;
    
    ...

    JsCode.init();

The class ``com.microej.js.JsCode`` is the Java class generated from the JavaScript sources.

- ask the MicroEJ JavaScript engine to start processing the job queue with:

.. code-block:: java

    import com.microej.js.JsRuntime;
    
    ...

    JsRuntime.ENGINE.run();

This makes the JavaScript engine process the job queue forever until the program is stopped.

- create a file with the ``js`` extension in the ``src/main/js`` folder (for example ``app.js``) with the following content:

.. code-block:: javascript

    print("My Simple Application");

- build and execute the application with the :ref:`MMM CLI <mmm_build_kit>`:

.. code-block:: console

    $ mmm build
    $ mmm run

The message ``My Simple Application`` should be displayed.