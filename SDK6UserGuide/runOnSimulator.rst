.. _sdk_6_run_on_simulator:

Run on Simulator
================

In order to execute an Application on the Simulator, the SDK provides the Gradle ``runOnSimulator`` task.
The prerequisites of this task are:

- The Application EntryPoint must be configured, as described in :ref:`sdk_6_create_project_configure_project`.

- The target VEE must be defined:

  - If your VEE is a VEE Port, refer to the :ref:`sdk_6_select_veeport` page to know the different ways to provide a VEE Port for a module project.
  - If your VEE is a Kernel, refer to the :ref:`sdk_6_select_kernel` page to know the different ways to provide a Kernel for a module project.

Once these prerequisites are fulfilled, the Application can be started with the Simulator:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      By double-clicking on the ``runOnSimulator`` task in the Gradle tasks view:

      .. image:: images/intellij-run-gradle-project.png
         :width: 30%
         :align: center

   .. tab:: Eclipse

      By double-clicking on the ``runOnSimulator`` task in the Gradle tasks view:

      .. image:: images/eclipse-run-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Command Line Interface

      From the command line interface::
      
          $ ./gradlew runOnSimulator

With a simple Hello World Application, the output should be::

   =============== [ Initialization Stage ] ===============
   =============== [ Converting fonts ] ===============
   =============== [ Converting images ] ===============
   =============== [ Launching on Simulator ] ===============
   Hello World!
   =============== [ Completed Successfully ] ===============
   
   SUCCESS

.. warning::
   The execution of the ``runOnSimulator`` task can fail if the SDK EULA has not been accepted.
   In that case, you can set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1B`` environment variable to ``YES`` and
   restart your IDE or you can define the ``accept-microej-sdk-eula-v3-1b`` System property 
   by creating a :ref:`custom configuration <sdk_6_howto_create_custom_configuration_in_ide>`. 
   For more information about SDK EULA, refer to the :ref:`sdk_6_licenses` chapter.

Verbose Mode
------------

If you need more information about the execution of the Application with the Simulator, 
the verbose mode can be enabled by using the ``--info`` Gradle option::

   ./gradlew runOnSimulator --info

.. _sdk_6_debug_on_simulator:

Debug on Simulator
------------------

The SDK allows to run an Application with the Simulator in debug mode by setting the System property ``debug.mode`` to ``true`` 
when executing the runOnSimulator task::

   ./gradlew runOnSimulator -P"debug.mode"=true

The debug mode is activated on the port ``12000`` by default. 
The port can be changed by using the System Property ``debug.port``::

   ./gradlew runOnSimulator -P"debug.mode"=true -P"debug.port"=8000


Once started, the Simulator waits for the connection of a debugger.

If you want to connect the IDE debugger:

.. tabs::

   .. tab:: Android Studio / IntelliJ IDEA

      .. warning::
         Android Studio and IntelliJ IDEA need an Architecture 8.1 or higher for debug mode.

      - Add a breakpoint in your Application code.
      - Click on ``Run > Edit Configurations...``.
      - Click on ``+`` button (``Add New Configuration``).
      - Select ``Remote JVM Debug``.
      - Click on the ``New launch configuration`` button.
      - Give a name to the launcher in the ``Name`` field.
      - Set the debug host and port.
      - Click on the ``Debug`` button.

   .. tab:: Eclipse

      - Add a breakpoint in your Application code.
      - Click on ``Run > Debug Configurations...``.
      - Select ``Remote Java Application``.
      - Click on the ``New launch configuration`` button.
      - Give a name to the launcher in the ``Name`` field.
      - Set the debug host and port.
      - Click on the ``Debug`` button.

The debugger should connect to the Simulator and you should be able to debug your Application.

.. _sdk_6_generate_code_coverage:

Generate Code Coverage
----------------------

To generate the Code Coverage files (``.cc``), invoke the ``:runOnSimulator`` task as follow:

::

   gradle :runOnSimulator -D"s3.cc.thread.period=15" -D"s3.cc.activated=true"

*Option Name*: ``s3.cc.thread.period``

*Description*:

It specifies the period between the generation of .cc files.

.. note:: If the application is abruptly ended (for example with ``Ctrl-C``) before the the first period, no ``.cc`` files are generated.

*Option Name*: ``s3.cc.activated``

*Description*

Set to ``true`` to enable the generation of Code Coverage files, don't define the property to disable the generation.

.. _sdk_6_generate_heap_dump:

Generate Heap Dump
------------------

*Option Name*: ``s3.inspect.heap``

*Description*:

Set to ``true`` to enable a dump of the heap each time the ``System.gc()`` method is called by the MicroEJ Application.
The ``.heap`` files are generated in ``build/output/application/heapDump/``.

Use the :ref:`Heap Viewer<heapviewer>` to visualize the ``.heap`` files.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
