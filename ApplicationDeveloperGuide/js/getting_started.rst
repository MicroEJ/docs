..
.. ReStructuredText
..
.. Copyright 2020-2021 MicroEJ Corp. All rights reserved.
.. MicroEJ Corp. PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
..

===============
Getting started
===============

Let's walk through the steps required to use Javascript in your MicroEJ application:

- install the :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>`
- create your Standalone Application project with the ``init`` command:

.. code:: console

    mmm init -Dskeleton.org=com.is2t.easyant.skeletons -Dskeleton.module=firmware-singleapp -Dskeleton.rev=1.1.12  -Dproject.org=com.mycompany -Dproject.module=myproject -Dproject.rev=1.0.0 -Dskeleton.target.dir=myproject 

Adapt the properties values to your need.
See the :ref:`MMM CLI init command documentation <mmm.cli.commands.init>` for more details.

Javascript is supported in the following project types: ``microej-javalib``, ``application`` and ``firmware-singleapp``.
You can have more information on the project types in the :ref:`Module Natures page <module_natures>`.

- add the js dependency in the ``module.ivy`` file:

.. code:: xml

    <dependency org="com.microej.library.runtime" name="js" rev="0.5.0"/>

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

<<<<<<< HEAD:ApplicationDeveloperGuide/microjs/getting_started.rst
You can now go further by exploring the :ref:`capabilities of the MicroEJ Javascript engine <microjs.builtin>` and discovering the :ref:`commands available in the CLI <mmm_cli>`.
=======
You can now go further by exploring the :ref:`capabilities of the MicroEJ Javascript engine <js.builtin>` and discovering the :ref:`commands available in the CLI <mmm.cli>`.
>>>>>>> M0228J-57 Rename MicroJS to JS.:ApplicationDeveloperGuide/js/getting_started.rst
