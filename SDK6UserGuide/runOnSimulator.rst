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

      |

      .. warning::
         Android Studio does not allow to run multiple Gradle tasks in parallel.
         If you still want to execute several Gradle tasks simultaneously, 
         you can launch them from a terminal with the Gradle Command Line Interface (CLI).

   .. tab:: Eclipse

      By double-clicking on the ``runOnSimulator`` task in the Gradle tasks view:

      .. image:: images/eclipse-run-gradle-project.png
         :width: 50%
         :align: center

   .. tab:: Visual Studio Code

      By double-clicking on the ``runOnSimulator`` task in the Gradle tasks view:

      .. image:: images/vscode-run-gradle-project.png
         :width: 25%
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
      - Click on :guilabel:`Run` > :guilabel:`Edit Configurations...`.
      - Click on :guilabel:`+` button (:guilabel:`Add New Configuration`).
      - Select :guilabel:`Remote JVM Debug`.
      - Click on the :guilabel:`New launch configuration` button.
      - Give a name to the launcher in the :guilabel:`Name` field.
      - Set the debug host and port.
      - Click on the :guilabel:`Debug` button.

   .. tab:: Eclipse

      - Add a breakpoint in your Application code.
      - Click on :guilabel:`Run` > :guilabel:`Debug Configurations...`.
      - Select :guilabel:`Remote Java Application`.
      - Click on the :guilabel:`New launch configuration` button.
      - Give a name to the launcher in the :guilabel:`Name` field.
      - Set the debug host and port.
      - Click on the :guilabel:`Debug` button.

   .. tab:: Visual Studio Code

      .. warning::
         VS Code needs an Architecture 8.1 or higher for debug mode.

      - Add a breakpoint in your Application code.

         .. figure:: images/vscode-add-breakpoint.png
            :alt: VS Code add a breakpoint
            :align: center
            :scale: 70%

      - Click on the :guilabel:`Run and Debug (Ctrl+Shift+D)` icon on the right panel.
      - Click on ``create a launch.json file`` in the opened panel.
      
         .. figure:: images/vscode-open-debug-launcher.png
            :alt: VS Code open debug launchers
            :align: center
            :scale: 70%

      - Click on the ``Java`` entry proposed in the search field.

         .. figure:: images/vscode-select-java-debug.png
            :alt: VS Code select Java debug
            :align: center
            :scale: 70%

      - Click on :guilabel:`Add Configuration` button
      - Select ``{} Java: Attach to Remote Program`` entry in the popup list.

         .. figure:: images/vscode-add-attach-remote-configuration.png
            :alt: VS Code add attach remote debug configuration
            :align: center
            :scale: 70%

      - Set ``localhost`` as ``hostName`` and  the ``port`` (default is ``1200``) in the generated json.

         .. figure:: images/vscode-configure-remote-debug.png
            :alt: VS Code configure remote debug in json
            :align: center
            :scale: 70%

      - Select ``Attach to Remote Program`` in the selection box of the launcher.

         .. figure:: images/vscode-attach-remote-program.png
            :alt: VS Code run debug
            :align: center
            :scale: 70%

      - Click on the ``Start`` button

         .. figure:: images/vscode-stopped-on-breakpoint.png
            :alt: VS Code stopped on breakpoint
            :align: center
            :scale: 70%

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
