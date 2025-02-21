.. _training_kernel_green_imxrt1170:

=======================
Get Started with Kernel
=======================

Description
===========

This Getting Started is a step-by-step guide explaining
how to build a Multi-Sandbox Executable for the NXP i.MXRT1170 Evaluation Kit.

This Executable will be built from the
`Kernel GREEN <https://github.com/MicroEJ/Kernel-GREEN>`__ sources.

The Multi-Sandbox Executable built in this Getting Started can then be used to
complete the :ref:`training_multisandbox_applications_imxrt1170` Getting Started.

During this Getting Started, you will learn how to:

* Get the Kernel GREEN,
* Configure it,
* Build the project and get the modules: Virtual Device, Executable, Javadoc, ...
* Run a Sandboxed Application project on this Multi-Sandbox Executable.

In case you are not familiar with MicroEJ, please visit `Discover MicroEJ <https://developer.microej.com/discover-microej/>`__ to understand the principles of our technology.


Intended Audience
=================

This training is designed for developers who want to gain a first understanding 
of the Kernel development flow.

Prerequisites
=============

To get the most out of this training, participants should have:

- A good understanding of the :ref:`overview` section.
- A basic knowledge of the :ref:`chapter-glossary`.
- Access to the `NXP i.MX RT1170 Evaluation Kit EVKB <https://www.nxp.com/design/design-center/development-boards-and-designs/i-mx-evaluation-and-development-boards/i-mx-rt1170-evaluation-kit:MIMXRT1170-EVKB>`__.
- Access to the `RK055HDMIPI4MA0 display panel <https://www.nxp.com/part/RK055HDMIPI4MA0>`__.
- A FAT32-formatted microSD card.
- An available Ethernet network connection.

.. note::
  
   This training has been tested on Windows 10. 
   Also note that examples used in this training could depend on older tools and libraries. 
   Most notably our dependency manager plugin (using `Gradle <https://gradle.org/>`__) could be an older version.

Environment Setup
-----------------

Before starting, make sure to follow the :ref:`Getting Started for NXP i.MX RT1170 Evaluation Kit <sdk_6_getting_started_imxrt1170>`
to setup your environment and be able to run a demo application on the Virtual Device and on the i.MX RT1170 Evaluation Kit.

Additionally, make sure to:

* Insert a micro-SD card (FAT32-formatted) in the board connector.
* Connect the ``1GB`` Ethernet connector to the internet.

Congratulations! You have finished the setup of your environment.
You are now ready to discover how to build and flash the :guilabel:`Kernel-GREEN`.

Set up the Kernel GREEN Project in your IDE
-------------------------------------------

Import the Project
~~~~~~~~~~~~~~~~~~

Clone or download the `Kernel GREEN <https://github.com/MicroEJ/Kernel-GREEN>`__ sources,

The first step is to import the :guilabel:`Kernel-GREEN` into your IDE: 

.. note::
  
   If you are using an IDE other than IntelliJ IDEA, please have a look at :ref:`sdk_6_import_project` section.

* If you are in the Welcome Screen, click on the :guilabel:`Open` button. Otherwise click either on :guilabel:`File` > :guilabel:`Open...`,
* Select the :guilabel:`Kernel-GREEN` directory located where you downloaded it and click on the :guilabel:`OK` button.

The Gradle project should now be imported in IntelliJ IDEA,
your workspace contains the following project in the :guilabel:`Projects` view: 

   .. figure:: images/multiSandbox/getting-started-import-kernel-green.png
      :alt: Import demo application
      :align: center
      :scale: 70%

Configure the Project
~~~~~~~~~~~~~~~~~~~~~

Select a VEE Port
^^^^^^^^^^^^^^^^^

As Applications need to depend on a VEE Port in order to be built, so does a Kernel project.
Refer to the ``Prerequisites`` section of the
`Kernel GREEN README <https://github.com/MicroEJ/Kernel-GREEN/blob/master/README.md>`__
to learn more about the VEE Port requirements.

By default, the :guilabel:`Kernel-GREEN` project already uses the
`NXP i.MXRT1170 VEE Port <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk>`__.

Kernel Configuration
^^^^^^^^^^^^^^^^^^^^

The ``configuration/common.properties`` file provides a default configuration
for the Kernel (runtime heap size, maximum number of threads, images heap size, etc.).

This configuration will also impact Sandboxed Applications running on top of the Kernel
(e.g. max number of threads per application). 

Check the `Kernel GREEN README <https://github.com/MicroEJ/Kernel-GREEN/blob/master/README.md>`__
for more information about the Kernel configuration.

Run the Kernel GREEN on NXP i.MXRT1170 Evaluation Kit
-----------------------------------------------------

To deploy :guilabel:`Kernel-GREEN` on your board, you will have to:

* Build the :guilabel:`Kernel-GREEN` Executable,
* Flash it on the board.

Build and Flash the Kernel GREEN on the NXP i.MXRT1170 Evaluation Kit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to build and flash the :guilabel:`Kernel-GREEN` on the NXP i.MXRT1170 Evaluation Kit,
the application provides the Gradle :guilabel:`runOnDevice` task.

.. note::
  
   If you are using an IDE other than IntelliJ IDEA, please have a look at :ref:`sdk_6_run_on_device` section.

* Double-click on the :guilabel:`runOnDevice` task in the Gradle tasks view. It may take some time:

   .. figure:: images/multiSandbox/getting-started-runOnDevice.png
      :alt: runOnDevice task
      :align: center
      :scale: 70%

Once the Executable is flashed, you should see the :guilabel:`Kernel-GREEN` traces in your console:

   .. figure:: images/multiSandbox/iMXRT1170/getting-started-imxrt1170-termite-green-fw-output.png
      :alt: Logs Output on Termite Serial Terminal
      :align: center
      :scale: 60%

.. figure:: images/well-done-mascot.png
   :alt: Well Done
   :align: center
   :scale: 70%

Well Done!
-----------

Now you know how to build and run a Multi-Sandbox Executable!

If you want to learn how to run a Sandboxed Application on your Multi-Sandbox Executable, you can continue this Getting Started.

.. _sdk_6_getting_started_stm32f7508_kernel_green_run_application:

Run a Sandboxed Application on your Multi-Sandbox Executable and Virtual Device
-------------------------------------------------------------------------------

Follow the :ref:`training_multisandbox_applications_imxrt1170_create_app`
Getting Started to create and run a Sandboxed Application project on your 
Multi-Sandbox Executable and Virtual Device.

.. note::

   When it comes to selecting the Multi-Sandbox Executable and Virtual Device
   (section :ref:`training_multisandbox_applications_imxrt1170_run_virtual_device`),
   follow this procedure:

   - Open the ``settings.gradle.kts`` files located at the root of your :guilabel:`MyApplication` project,
   - Include the :guilabel:`Kernel-GREEN` project as a dependency of the :guilabel:`MyApplication` project,
      
      .. code-block:: kotlin

         rootProject.name = "MyApplication"
         include(":app")
         includeBuild("C:\\YOUR_PATH\\Kernel-GREEN")

   - Reload the Gradle project:

      .. figure:: images/multiSandbox/getting-started-reload-gradle-project.png
         :alt: Virtual Device
         :align: center
         :scale: 70%

   - The :guilabel:`Kernel-GREEN` project should now appear in the Gradle tasks view:

      .. figure:: images/multiSandbox/getting-started-gradle-tasks-kernel-green.png
         :alt: Kernel GREEN and MyApplication Gradle tasks
         :align: center
         :scale: 90%

   - Open the ``app/build.gradle.kts`` file of the :guilabel:`MyApplication` project,
   - Declare the dependency to the :guilabel:`Kernel-GREEN` project as follows:

      .. code-block:: kotlin

         dependencies {
            ...
            //Uncomment the microejVee dependency to set the VEE Port or Kernel to use
            microejVee("com.microej.kernel:GREEN:2.1.0")
         }
   
   
      .. note::
            
            Make sure that the version corresponds to the version defined in your
            `Kernel-GREEN build.gradle.kts <https://github.com/MicroEJ/Kernel-GREEN/blob/master/build.gradle.kts>`_ file.

   - Come back to the :ref:`training_multisandbox_applications_imxrt1170_run_virtual_device` Getting Started.

Going Further
-------------

You have now successfully executed a Sandboxed Application on an embedded device so what's next?

If you are an application developer you can continue to explore MicroEJ's APIs and functionalities by running and studying our samples at GitHub:

.. list-table::
   :widths: 33 33 33

   * - Foundation Libraries
     - Eclasspath
     - IoT
   * - This project gathers all the basic examples of the foundation libraries. 
     - This project gather all the examples of eclasspath. 
     - This project gathers simple applications using net libraries. 
   * - https://github.com/MicroEJ/Example-Foundation-Libraries
     - https://github.com/MicroEJ/Example-Eclasspath
     - https://github.com/MicroEJ/Example-IOT

You can also learn how to build bigger and better applications by reading our :ref:`Application Developer Guide <application-developer-guide>`.

If you are an embedded engineer you could look at our VEE port examples at `GitHub <https://github.com/microej?q=vee&type=all&language=&sort=>`_. And to learn how create custom VEE ports you can read our :ref:`VEE Porting Guide <vee-porting-guide>`.

You can also follow the :ref:`Kernel Developer Guide <kernel-developer-guide>` for more information on our multi-application framework or read about our powerful wearable solution called :ref:`VEE Wear <vee-wear>`.

Last but not least you can choose to learn about specific topics by following one of our many :ref:`trainings` ranging from how to easily debug application to setting up a Continuous Integration process and a lot of things in between.

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.