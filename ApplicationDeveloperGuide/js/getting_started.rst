.. _js.getting_started:

===============
Getting Started
===============

Let's walk through the steps required to use Javascript in your MicroEJ application:

- install the :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>`
- create your Standalone Application project with the ``init`` command:

.. code:: console

    mmm init -Dskeleton.org=com.is2t.easyant.skeletons -Dskeleton.module=firmware-singleapp -Dskeleton.rev=1.1.12 -Dproject.org=com.mycompany -Dproject.module=myproject -Dproject.rev=1.0.0 -Dskeleton.target.dir=myproject 

Adapt the properties values to your need.
See the :ref:`MMM CLI init command documentation <mmm_cli.commands.init>` for more details.

Javascript is supported in the following :ref:`Module Natures page <module_natures>`: 
- :ref:`module_natures.addon_lib`, 
- :ref:`module_natures.standalone_application`,
- :ref:`module_natures.sandboxed_application`.

- add the js dependency in the ``module.ivy`` file:

.. code:: xml

    <dependency org="com.microej.library.runtime" name="js" rev="0.13.0"/>

- add the following lines in your application main class:

.. code:: java

    import com.microej.js.JsErrorWrapper;
    import com.microej.js.JsCode;
    import com.microej.js.JsRuntime;

    ...

    JsCode.initJs();
    JsRuntime.ENGINE.runOneJob();
    JsRuntime.stop();

- create a file named ``hello.js`` in the folder ``src/main/js`` with the following content:

.. code:: javascript

    function hello() {
        var message = "MicroEJ Javascript application!";
        print("My first", message);
    }

    hello()

- follow the steps described in the :ref:`run command documentation <mmm_cli.commands.run>`
- in a terminal, go to the folder containing the ``module.ivy`` file and build the project with the command:

.. code:: console

    mmm build

You should see the following message at the end of the build:

.. code:: console

    BUILD SUCCESSFUL

    Total time: 20 seconds

- now that your application is built, you can run it in the simulator with the command:

.. code:: console

    mmm run

You should see the following output:

.. code:: console

    My first  MicroEJ Javascript application!

You can now go further by exploring the :ref:`capabilities of the MicroEJ Javascript engine <js.api>` and discovering the :ref:`commands available in the CLI <mmm_cli>`.

..
   | Copyright 2020-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
