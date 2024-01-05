.. _ack_installation_:

Installation
============

To develop applications compatible with both Android and MicroEJ VEE, it is required to use :ref:`MicroEJ SDK 6 <sdk_6_user_guide>`.
The MicroEJ SDK provides Gradle plugins that allow for seamless integration in Android Studio.

For comprehensive installation instructions, read the :ref:`SDK 6 Installation Guide <sdk_6_install>` (follow the steps related to Android Studio when relevant).

In addition to installing MicroEJ SDK 6, make sure to comply with the requirements listed below.

JDK Version
-----------

The Android Compatibility Kit, like MicroEJ SDK 6, is compatible with a JDK 11 or higher LTS version.
The JDK version to use will depend on the Android Gradle Plugin (AGP) being used by your Android project. 
Starting from version 8, AGP requires a minimum JDK 17.
If you intend to use JDK 11, you will need to specify a compatible version of AGP (e.g., 7.4.2).
Refer to the `Android Gradle plugin release notes <https://developer.android.com/build/releases/gradle-plugin>`_ for more information. 

Configure Repositories
----------------------

The :ref:`SDK 6 repositories configuration <sdk_6_configure_repositories>` references the MicroEJ module repositories which are required for resolving the SDK Gradle plugins and modules.
Working with Android plugins and modules involves extending this configuration to include additional repositories that are essential for Android development.

- download and copy :download:`this file <resources/microej.wear.init.gradle.kts>` in ``<user.home>/.gradle/init.d/``.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.