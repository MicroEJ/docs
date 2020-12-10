..
.. ReStructuredText
..
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

===============
Getting started
===============

Let's walk through the steps required to use Javascript in your MicroEJ application:

- create your application project in the MicroEJ SDK, see :ref:`standalone_application`. 
  Once done, you can continue with the MicroEJ SDK or with your favorite IDE.
- install the :ref:`MMM CLI (Command Line Interface) <mmm.cli.installation>`
- add the microjs dependency in the ``module.ivy`` file:

.. code:: xml

    <dependency org="com.microej.library.runtime" name="microjs" rev="0.2.1"/>

- add the following lines in your application main class:

.. code:: java

    import com.microej.microjs.JsErrorWrapper;
    import com.microej.microjs.MicroJsCode;
    import com.microej.microjs.MicroJsRuntime;

    ...

    MicroJsCode.initJs();
    MicroJsRuntime.ENGINE.runOneJob();
    MicroJsRuntime.stop();

- create a file named ``hello.js`` in the folder ``src/main/resources`` with the following content:

.. code:: javascript

    function hello() {
        var message = "MicroEJ Javascript application!";
        print("My first", message);
    }

    hello()

- follow the steps described in the :ref:`run command documentation <mmm.cli.commands.run>`
- in a terminal, go to the folder containing the ``module.ivy`` file and build the project with the command:

.. code:: shell

    mmm build

You should see the following message at the end of the build:

.. code:: shell

    BUILD SUCCESSFUL

    Total time: 20 seconds

- now that your application is built, you can run it in the simulator with the command:

.. code:: shell

    mmm run

You should see the following output:

.. code:: shell

    My first  MicroEJ Javascript application!

You can now go further by exploring the :ref:`capabilities of the MicroEJ Javascript engine <microjs.builtin>` and discovering the :ref:`commands available in the CLI <mmm.cli>`.