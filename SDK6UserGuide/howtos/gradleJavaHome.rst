.. _sdk_6_howto_gradle_java_home:

How To Define a Specific Java Home for Gradle
=============================================

By default, Gradle uses the JDK defined in the ``JAVA_HOME`` environment variable or in the ``PATH``.
If you want to use a different JDK without changing the default JDK of your system, 
you can define the property ``org.gradle.java.home`` in the `Gradle Properties <https://docs.gradle.org/current/userguide/build_environment.html#sec:gradle_configuration_properties>`_.
Gradle Properties can be defined in the following locations, sorted by the highest priority:

- command line, as set using ``-D``.
- ``gradle.properties`` in the ``GRADLE_USER_HOME`` directory (defaults to ``$USER_HOME/.gradle``).
- ``gradle.properties`` in the project directory, then its parent project directory up to the build root directory.
- ``gradle.properties`` in the Gradle installation directory.

If an option is configured in multiple locations, the first one found in any of these locations wins.
Therefore, if you want all your Gradle project to use a different JDK than the system default JDK, 
you can add the following property in the file ``$USER_HOME/.gradle/gradle.properties``::

   org.gradle.java.home="C:\\path\\to\\the\\jdk"

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
