.. _sdk_6_howto_gradle_system_property:

How To Pass a Property to Project Build Script
==============================================

It is sometimes needed to use properties to pass values to a project build script.
This avoids to have hardcoded values in the project sources.

Gradle allows to define System Properties with the command line thanks to the ``-D`` prefix:

.. code:: console
   
   $ ./gradlew build -DmyPropertyName="myPropertyValue"

and use them with the API ``providers.systemProperty("myPropertyName").get()``.

For example to define a local VEE Port directory, the project can be configured with::

   dependencies {
      microejVee(files(providers.systemProperty("myVeePortPath").get()))
   }

and built with:

.. code:: console

   $ ./gradlew build -DmyVeePortPath="C:\\path\\to\\my\\veePort\\directory"

The ``providers.systemProperty("myPropertyName")`` API returns a ``org.gradle.api.provider.Provider`` object, which provides other capabilities like:

- defining a default value if the System Property does not exist: ``providers.systemProperty("myPropertyName").getOrElse("myDefaultValue")``
- returning ``null`` if the value does not exist: ``providers.systemProperty("myPropertyName").getOrNull()``.

.. warning::
   If the property to pass is an :ref:`Application option <application_options>`, it must be prefixed by ``microej.option.*``.

.. note::
   If the property is an argument for the JVM used by the VEE launch scripts, it must be set in a system property named ``microej.launch.jvmargs``. 
   This property accepts a whitespace-separated list of JVM options, which will be passed to the underlying Java process executed during the project build.
   
   For example, to control the JVM maximum and initial heap of the JVM running the simulator, the command line would be:

   .. code::
      
      $ ./gradlew runOnSimulator -Dmicroej.launch.jvmargs="-Xmx1024m -Xms512m"

   Note that these options only apply to the JVM forked during the project build, they do not affect the JVM configuration for the Gradle Daemon.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
