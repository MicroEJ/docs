.. _sdk_6_howto_pass_jvm_args_to_launch_script:

How To Pass JVM Arguments to the VEE Launch Scripts
===================================================

Some tasks (e.g., ``runOnSimulator``, ``buildExecutable``) start a new JVM process to run the VEE launch scripts.
The arguments for this JVM can be configured to customize the execution environment, for example for adjusting memory settings or enabling remote debugging.

The JVM arguments have to be set in a system property named ``microej.launch.jvmargs``. 
This property accepts a whitespace-separated list of options.

The following example shows how to control the maximum and initial heap of the JVM used to launch the simulator::

   $ ./gradlew runOnSimulator -Dmicroej.launch.jvmargs="-Xmx1024m -Xms512m"

.. note::

   The options passed with the property ``microej.launch.jvmargs`` only apply to the JVM forked during the project build.
   They do not affect the JVM configuration of the Gradle Daemon.
   To configure the options of the Gradle Daemon, you can use the property ``org.gradle.jvmargs``, as described in the `Gradle Properties Reference <https://docs.gradle.org/current/userguide/build_environment.html#gradle_properties_reference>`__.


.. _sdk_6_howto_debug_vee_launch:

Debugging Options
-----------------

To debug the JVM used to launch the VEE scripts, set the ``microej.launch.jvmargs`` system property like the following::

   -Dmicroej.launch.jvmargs="-agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=*:5005"

Then, connect the IDE's debugger to host ``localhost`` on specified port (``5005`` in this example).

This can be used for advanced use cases that require to debug the SDK tools, like the SOAR for example.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
