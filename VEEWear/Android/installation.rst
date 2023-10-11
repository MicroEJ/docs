.. _ack_installation_:

Installation
============

To develop applications compatible with both Android and MicroEJ VEE, it is required to use :ref:`MicroEJ SDK 6 <sdk_6_user_guide>`.
The MicroEJ SDK provides Gradle plugins that allow for seamless integration in Android Studio.

For comprehensive installation instructions, read the :ref:`SDK 6 Installation Guide <sdk_6_install>`.
Simply follow the steps related to Android Studio when relevant.

In addition to installing MicroEJ SDK 6, make sure to comply with the requirements listed in the next sections.

JDK Version
-----------

Not all features of MicroEJ SDK 6 are compatible with JDK 15 and higher.
As a consequence, using the Android Compatibility Kit requires the use of JDK 11.

As stated in the :ref:`SDK 6 Installation Guide <sdk_6_check_jdk>`, make sure to set either the ``JAVA_HOME`` or ``PATH`` variables to reference a JDK 11 installation.

.. note:: 
   The latest versions of Android Studio bundle and use a JDK version higher than 11 by default.
   Make sure that Gradle uses a JDK 11 in the Android Studio settings.

   - Go to :guilabel:`File` > :guilabel:`Settings...` > :guilabel:`Build, Execution, Deployment` > :guilabel:`Build Tools` > :guilabel:`Gradle`.
   - For :guilabel:`Gradle SDK`, select a JDK 11 installation in the list.

The primary implication of using a JDK 11 is that the maximum version of the Android Gradle Plugin that can be used is ``7.4.2``.


Configure Repositories
----------------------

The :ref:`SDK 6 repositories configuration <sdk_6_configure_repositories>` references the MicroEJ module repositories which are required for resolving the SDK Gradle plugins and modules.
Working with Android plugins and modules involves extending this configuration to include additional repositories that are essential for Android development.

- download and copy :download:`this file <resources/microej.android.init.gradle.kts>` in ``<user.home>/.gradle/init.d/``.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.