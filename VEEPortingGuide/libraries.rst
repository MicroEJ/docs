.. _foundation_libraries:

====================
Foundation Libraries
====================

Foundation Libraries are MicroEJ Core libraries that provide core runtime APIs or hardware-dependent functionalities.
They allow Managed code to call native code.

.. figure:: ./images/libraries-structure.png
   :alt: MicroEJ Foundation Libraries and Add-On Libraries
   :align: center
   :scale: 67%

   MicroEJ Foundation Libraries and Add-On Libraries

.. note::

    In SDK 5, A Foundation library is divided into 2 JARs: an API and an implementation. 
    A Foundation library API is composed of a name and a 2 digits version (e.g. ``EDC-1.3``) 
    and follows the semantic versioning (`<http://semver.org>`_) specification. 
    A Foundation Library API only contains prototypes without code. 
    Foundation Library implementations are provided by VEE Ports.
    From a MicroEJ Classpath, Foundation Library APIs dependencies are automatically mapped 
    to the associated implementations provided by the VEE Port or the Virtual Device on which 
    the application is being executed.

    In SDK 6, a Foundation Library is a single JAR, containing the implementation.
    The API is composed of all the public classes and methods of the Library.

Foundation Libraries can be consumed by Applications and other Libraries.
They are :ref:`automatically mapped to the capabilities <foundation_library_mapping>` provided by the VEE Port or the Virtual Device used to run the Application.

MicroEJ provides a large set of :ref:`Foundation Libraries <libraries>`, such as UI, Network, Audio, ... 
You can also create your own Foundation Library by going through the following steps described in the next sections:

#. Create the Library project
#. Create a Java class
#. Define C Header Files
#. Implement native code
#. Create the mock
#. Install the Library in the VEE Port

Create the Library Project
==========================

To create a Foundation Library, follow the instructions of the :ref:`sdk_6_create_project` page. 
Choose the ``Library`` type in the Project Wizards or the ``Library Project Template`` with the Command Line.

Create a Java Class
===================

Once the Library project is created, you can now create a Java class which calls native code.
Create the Java class ``Sensor`` in the ``src/main/java/com/mycompany`` folder of the Library project, with the following content:

.. code-block:: java

    package com.mycompany;

    import java.io.IOException;

    /**
     * Class providing a native method to access sensor value.
     * This method will be executed out of the Core Engine.
     */
    public class Sensor {

        public static final int ERROR = -1;

        public static int getValue() throws IOException {
            int value = getSensorValue();
            if (value == ERROR) {
                throw new IOException("Unsupported sensor");
            }
            return value;
        }

        public static native int getSensorValue();
    }

This class contains a native method ``getSensorValue`` which will be implemented by native code.

Define C Header Files
=====================

The header files define the prototype of the C functions. 
They must be added in the ``src/main/include`` folder of the Library project.

The C function name must respect the following pattern to be mapped to the Java method: ``Java_<FQN>_<methodName>``, 
where ``<FQN>`` is the fully qualified name of the Java class with all ``.`` are replaced by ``_``, and ``methodName`` is name of the Java method.
Therefore, for the ``getSensorValue`` Java method of the ``com.mycompany.Sensor`` class, the C function must be called ``Java_com_mycompany_Sensor_getSensorValue``.

Here is the content of the header file ``LLMYLIB_impl.h`` to create in the ``src/main/include`` folder of the Library project:

.. code-block:: c

    #ifndef LLMYLIB_IMPL
    #define LLMYLIB_IMPL

    /**
    * @file
    * @brief MicroEJ Sensor Low Level API
    * @author My Company
    * @version 1.0.0
    */

    #include <stdint.h>

    #ifdef __cplusplus
    extern "C" {
    #endif

    #define LLMYLIB_IMPL_getSensorValue Java_com_mycompany_Sensor_getSensorValue

    /*
    * Returns the Sensor value
    */
    uint32_t LLMYLIB_IMPL_getSensorValue();

    #ifdef __cplusplus
    }
    #endif
    #endif

The ``#define`` statement allows to separate the Java part and the C part. 
This is called the Low Level API of the Foundation Library. 
If the fully qualified name of the Java native method is updated, the C implementation code do not need to be updated.
Refer to the :ref:`low_level_api` section for more information on Low Level APIs.

At this stage, the Library project structure should look like::

   |- src/
   |    |- main/
   |    |    |- java/
   |    |    |    |- com/
   |    |    |    |    |- mycompany/
   |    |    |    |    |    |- Sensor.java
   |    |    |- include/
   |    |    |    |- LLMYLIB_impl.h
   |- build.gradle.kts

Implement Native Code
=====================

- In the C project, create a new File called ``LLMYLIB_impl.c``.
- Add the C file to the compilation objects by adding it to the C Project configuration.
- Copy and paste the following code to the file:

.. code-block:: c

    #include "LLMYLIB_impl.h"
    #include "sni.h"

    /**
    * @file
    * @brief MicroEJ Sensor low level API
    * @author My Company
    * @version 1.0.0
    */
    uint32_t LLMYLIB_IMPL_getSensorValue()
    {
        return 42;
    }

This file defines a basic C implementation of the ``getSensorValue`` function.

Create the Mock
===============

If you need to use the Library in the Simulator, a Mock must be implemented.
A Mock is a component that implements the native method in Java to use the Library in the Simulator.
Refer to the :ref:`mock` page to create the Mock for ``Sensor`` Library.

Once the Mock is created, it must be declared as a dependency of the Library, in the ``build.gradle.kts`` file::

    dependencies {
        microejMock("com.mycompany:my-mock:1.0.0")
    }

Install the Library in the VEE Port
===================================

Once the Library project is done, it must be installed in the VEE Port by adding it as a dependency in the ``build.gradle.kts`` file of the VEE Port project::

    dependencies {
        api("com.mycompany:my-library:1.0.0")
    }

When declaring the dependency with the ``api`` configuration, if :ref:`the VEE Port transitive resolution <sdk_6_vee_port_transitivity>` is enabled, 
it is exposed transitively to the project depending on the VEE Port.
If you do not want to expose the Library transitively, use the ``implementaion`` configuration instead::

    dependencies {
        implementation("com.mycompany:my-library:1.0.0")
    }

Test in an Application
======================

In order to test the Library, it is recommended to create an Application that uses the VEE Port and calls the Sensor Library.
The Application project must declare the VEE Port and the Library as dependencies in its ``build.gradle.kts`` file::

    dependencies {
        implementation("com.mycompany:my-library:1.0.0")
        microejVee("com.mycompany:my-vee-port:1.0.0")
    }

Then the main method of the Application must call the ``Sensor`` API:

.. code-block:: java

    package com.mycompany;

    public class Main {

        public static void main(String[] args) {
            System.out.println("Sensor value: " + Sensor.getValue());
        }

    }


You can now run the Application with the Simulator thanks to the ``ruOnSimulator`` Gradle task::

    ./gradlew runOnSimulator

The following trace shall appear on the standard output::

    =============== [ Initialization Stage ] ===============
    =============== [ Launching on Simulator ] ===============
    Sensor value: 42
    =============== [ Completed Successfully ] ===============


You can also build and deploy the Application on your device.
The following trace shall appear on the standard output::

    VM START
    Sensor value: 42
    VM END (exit code = 0)

Implement a Validation Testsuite
================================

To validate the Foundation Library against the VEE Ports they will be used with, it is recommended to provide a :ref:`validation Testsuite <vee_port_testsuite>`.
It contains a bunch of Java tests that validate the Abstraction Layer implementing the Low Level APIs of the Foundation Library.

You can find examples of validation Testsuites in `the VEE Port project template <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/master/vee-port/validation>`__.

Extend the Link Process
=======================

Libraries can extend the Linking process using LSC files.
Refer to the :ref:`microej_linker` page for more information.

These files must be added in the ``src/main/lscf`` folder of the Library project::

   |- src/
   |    |- main/
   |    |    |- java/
   |    |    |    |- com/
   |    |    |    |    |- mycompany/
   |    |    |    |    |    |- Sensor.java
   |    |    |- include/
   |    |    |    |- LLMYLIB_impl.h
   |    |    |- lscf/
   |    |    |    |- mylib.lscf
   |- build.gradle.kts

Define Configurable Properties in LSC Files
-------------------------------------------

The LSC files can use properties to define configurable values.
For example, you may want to define a configurable heap size for your library:

.. code-block:: xml

    <lscFragment>
        <defSymbol name="_mylibrary_heap_size" value="${mylibrary.heap.size}" rootSymbol="true"/>
        <defSection name=".bss.mylibrary.heap" size="_mylibrary_heap_size" align="4"/>
        <defSymbol name="_mylibrary_heap_start" value="START(.bss.mylibrary.heap)" rootSymbol="true"/>
        <defSymbol name="_mylibrary_heap_end" value="END(.bss.mylibrary.heap)" rootSymbol="true"/>
    </lscFragment>

The property can be set by the Application which uses the Library, by defining the :ref:`Application Option <application_options>` ``mylibrary.heap.size``.

Set Default Values for the Configurable Properties
--------------------------------------------------

The LSC format allows to define a default value for the properties, by suffixing the property name with ``:``, followed by the default value.
For example, the following line defines the property ``mylibrary.heap.size`` with the default value ``1024``:

.. code-block:: xml

    <defSymbol name="_mylibrary_heap_size" value="${mylibrary.heap.size:1024}" rootSymbol="true"/>

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.