.. _ack-vee-port_:

VEE Port
========

This section explains how to configure a VEE Port so that it provides the capability to build a MicroEJ Application for Android.

Once it is configured, the VEE Port can thus be used to build a MicroEJ Application for Android,
in addition to standard features such as building a MicroEJ Application for an Embedded Device and running it on the Simulator.

VEE Port Configuration
----------------------

The configuration steps ensure that the VEE Port provides build scripts and implementations of Foundation Libraries which are specific to Android.

These files are gathered in Android Packs. Each Android Pack provides support for one or multiple Foundation Libraries.
The Core Android Pack is absolutely necessary to be able to build any MicroEJ Application for Android. Additional Android Packs should be included depending on the Foundation Libraries provided by the VEE Port.

To declare an Android Pack dependency, edit the ``module.ivy`` file of the VEE Port and add the following line within the ``<dependencies>`` element:

	.. code-block:: xml

		<dependency org="com.microej.android.pack" name="[NAME]-android-pack" rev="[VERSION]"/>

MicroEJ Android Packs
---------------------

MicroEJ provides Android Packs for some Foundation Libraries:

.. list-table::
   :widths: 2 4 2
   :header-rows: 1

   * - Name
     - Module
     - Implemented Libraries
   * - Core Android Pack
     - `com.microej.android.pack#core-android-pack <https://repository.microej.com/modules/com/microej/android/pack/core-android-pack/>`_
     - `EDC`_, `BON`_, `SNI`_, `Trace`_
   * - UI Android Pack
     - `com.microej.android.pack#ui-android-pack <https://repository.microej.com/modules/com/microej/android/pack/ui-android-pack/>`_
     - `MicroUI`_, `Drawing`_
   * - VG Android Pack
     - `com.microej.android.pack#vg-android-pack <https://repository.microej.com/modules/com/microej/android/pack/vg-android-pack/>`_
     - `MicroVG`_

.. note::

   Some Foundation Libraries such as FS and NET do not require an Android Pack as their APIs are already implemented by the Android SDK.

For more information on the usage and limitations of each Android Pack, refer to its README.

.. _EDC: https://repository.microej.com/javadoc/microej_5.x/libraries/edc-1.3-api/
.. _BON: https://repository.microej.com/javadoc/microej_5.x/libraries/bon-1.4-api/
.. _SNI: https://repository.microej.com/javadoc/microej_5.x/libraries/sni-1.4-api/
.. _Trace: https://repository.microej.com/javadoc/microej_5.x/libraries/trace-1.1-api/
.. _MicroUI: https://repository.microej.com/javadoc/microej_5.x/libraries/microui-3.3-api/
.. _Drawing: https://repository.microej.com/javadoc/microej_5.x/libraries/drawing-1.0-api/
.. _MicroVG: https://repository.microej.com/javadoc/microej_5.x/libraries/microvg-1.4-api/

Custom Android Packs
--------------------

A MicroEJ Application may call native methods, which require a different implementation on each execution target (embedded device, Simulator or Android).
Therefore if an Application is executed on Android, the VEE Port should provide an implementation of these native methods for Android.
This dedicated implementation is called an Android mock, and it is usually packaged in an Android Pack.
This section explains how to develop a custom Android Pack including an Android mock.

.. note::

	Currently, VEE Ports and their components can not be developed in :ref:`MicroEJ SDK 6 <sdk_6_limitations>`.
	This means that Android Packs must be developed with :ref:`SDK 5 <sdk_user_guide>` and MMM, and cannot be developed with Android Studio and Gradle.

Setting Android SDK Environment Variable
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Since the Android mock will be compiled using Android SDK, you should have `Android Studio and Android SDK installed <https://developer.android.com/studio/install>`_.
If it is not set already on your system, you should set the `ANDROID_HOME <https://developer.android.com/tools/variables#android_home>`_ environment variable.

You can follow these steps to find the Android SDK location on your system:

- In Android Studio, select :guilabel:`File` > :guilabel:`Settings...`.
- In the settings dialog, find :guilabel:`Android SDK` and copy the path set as :guilabel:`Android SDK Location`.

On Windows, this path is typically ``C:\Users\[USER]\AppData\Local\Android\Sdk``.

Make sure to restart MicroEJ SDK after setting the environment variable.

Creating the Android Pack Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The first step is to create the ``custom-android-pack`` project:

- In MicroEJ SDK, select :guilabel:`File`> :guilabel:`New` > :guilabel:`Project...`.
- In the wizard dialog, select :guilabel:`MicroEJ` > :guilabel:`Module Project` and click on :guilabel:`Next >`.
- In the new module dialog, type ``custom-android-pack`` as :guilabel:`Project Name` and as :guilabel:`Module`, choose the :guilabel:`Organization` and :guilabel:`Revision` of your choice, select ``product-java`` as :guilabel:`Skeleton` and click on :guilabel:`Finish`.

By default, the library built by the module is not packaged as an Android mock. To make sure that the library is added to the list of Android mocks,
edit the ``module.ivy`` file of the project and add the following lines within the ``<ea:build>`` element:

.. code-block:: xml

	<ea:property name="target.main.artifact.rip.relativedir" value="android/mocks/dropins"/>

Compiling against Android SDK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, the library is compiled against the JRE. Both the Eclipse project and the MMM build must be configured to compile against Android SDK rather than the JRE.

First, the JRE must be replaced by Android SDK in the build path of the Eclipse project:

- Right-click on the project, select :guilabel:`Build Path` > :guilabel:`Configure Build Path...`.
- In the properties dialog, open the :guilabel:`Libraries` tab, select :guilabel:`JRE System Library`, click on :guilabel:`Remove` and click on :guilabel:`Add Variable...`.
- In the classpath entry dialog, click on :guilabel:`Configure Variables...`.
- In the variables dialog, click on :guilabel:`New...`.
- In the new variable dialog, type ``ANDROID_HOME`` as :guilabel:`Name`, type the Android SDK location as :guilabel:`Path` and click on :guilabel:`OK`.
- Back to the variables dialog, click on :guilabel:`Apply and Close`.
- Back to the classpath entry dialog, select the ``ANDROID_HOME`` variable and click on :guilabel:`Extend...`.
- In the variable extension dialog, browse the ``platforms/android-[VERSION]/android.jar`` file and click on :guilabel:`OK`.
- Back to the properties dialog, click on :guilabel:`Apply and Close`.

Finally, the JRE must be replaced by Android SDK in the build path of the MMM module:

- Edit the ``module.ivy`` file and add the following lines within the ``<ea:build>`` element:

	.. code-block:: xml

		<ea:property name="include.java.runtime" value="false"/>
		<ea:property name="no.obfuscation" value="true"/>

- Create a file named ``module.ant`` at the root of the project with the following content:

	.. code-block:: xml

		<project name="custom-android-pack" xmlns:ea="antlib:org.apache.easyant">
			<target name="-custom-android-pack:augment-classpath" extensionOf="abstract-compile:compile-ready">
				<property environment="env"/>
				<ea:path pathid="compile.main.classpath" overwrite="prepend">
					<fileset file="${env.ANDROID_HOME}/platforms/android-[VERSION]/android.jar"/>
				</ea:path>
			</target>
		</project>

- In this ``module.ant``, replace ``[VERSION]`` in the ``<fileset>`` element by the minimum Android SDK version required by your Android mock.

Implementing the Android mock
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can add the Java source code of your Android mock into the ``src/main/java`` folder of the project.
At runtime, the Android mock will be added to the classpath before the code of the Application and before its dependencies.
This allows you to replace the implementation of any Java class in an Android mock.
The recommended practice is to replace only the classes which include native methods.

Using the Android Pack in the VEE Port
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To build the Android Pack, right-click on the project and select :guilabel:`Build Module`.

The Android Pack can be included in a VEE Port by declaring a dependency in the ``module.ivy`` of the VEE Port as explained in the first subsection:

	.. code-block:: xml

		<dependency org="[ORGANIZATION]" name="custom-android-pack" rev="[VERSION]"/>

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
