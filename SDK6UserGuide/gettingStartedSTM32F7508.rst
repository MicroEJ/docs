.. _sdk_6_getting_started_stm32f7508:

STM32F7508-DK Evaluation Kit
============================

During this Getting Started, you will learn to:

* run an Application on the STM32F7508-DK Evaluation Kit Virtual Device,
* run the same Application on your STM32F7508-DK Evaluation Kit.

In case you are not familiar with MicroEJ, please visit `Discover MicroEJ <https://developer.microej.com/discover-microej/>`__ to understand the principles of our technology.

Prerequisites
-------------

.. note::
  
   This Getting Started has been tested on macOS Sonoma 14.3.1.

This Getting Started is separated in two main parts.

The first part consists of running an MVC demo application on the Virtual Device. All you need is:

* An Internet connection to access Github repositories & :ref:`Module Repositories <module_repositories>`.
* MICROEJ SDK 6 (installed during :ref:`Environment Setup <sdk_6_getting_started_stm32f7508dk_environment_setup>`).
* The Example-Foundation-Libraries samples at GitHub. Download or clone the project `here <https://github.com/MicroEJ/Example-Foundation-Libraries>`__.

The second part consists of running the same demo application on your device. For that you will need:

* STM32F7508-DK Evaluation Kit, available `here <https://www.st.com/en/evaluation-tools/stm32f7508-dk.html>`__.
* A GNU ARM Embedded Toolchain, Cmake and Make are needed to build the BSP. You will be guided on how to install toolchain later.

.. _sdk_6_getting_started_stm32f7508dk_environment_setup:

Environment Setup
-----------------

To follow this Getting Started, you need to install: 

* MICROEJ SDK 6.

Install MICROEJ SDK 6
^^^^^^^^^^^^^^^^^^^^^

Install MICROEJ SDK 6 by following :ref:`sdk_6_install` instructions. 
Android Studio Hedgehog is used on this Getting Started but feel free to use your favorite IDE.

Set up the Application on your IDE
----------------------------------

Import the Project
^^^^^^^^^^^^^^^^^^

The first step is to import the Application into your IDE: 

.. note::
  
   If you are using another IDE than Android Studio, please have a look at :ref:`sdk_6_import_project` section.

* If you are in the Welcome Screen, click on the :guilabel:`Open` button. Otherwise click either on :guilabel:`File` > :guilabel:`Open...`.
* Select the ``Example-Foundation-Libraries`` directory located where you downloaded it and click on the :guilabel:`OK` button.

      .. figure:: images/gettingStarted/STM32F7508DK/getting-started-import-mvc-application.png
         :alt: Import demo application
         :align: center
         :scale: 70%

1The Gradle project should now be imported in Android Studio, your workspace contains the following project in the :guilabel:`Projects` view: 

      .. figure:: images/gettingStarted/STM32F7508DK/getting-started-workspace-view.png
         :alt: Workspace view
         :align: center
         :scale: 70%

.. _sdk_6_getting_started_stm32f7508dk_eula:

Accept the MICROEJ SDK EULA
---------------------------

You may have to accept the SDK EULA if didn't already do, please have a look at :ref:`sdk_6_eula_acceptation`.

.. _sdk_6_getting_started_stm32f7508dk_run_virtual_device:

Run an Application on the Virtual Device
----------------------------------------

We will be using the :guilabel:`microui.mvc` Application as the sample to test the VEE port simulation execution (you can choose another example it'll work similarly). In order to execute the :guilabel:`microui.mvc` Application on the Virtual Device, the SDK provides the Gradle :guilabel:`runOnSimulator` task. 

.. note::
  
   If you are using another IDE than Android Studio, please have a look at :ref:`sdk_6_run_on_simulator` section.

* Double-click on the :guilabel:`runOnSimulator` task in the Gradle tasks view. It may takes few seconds.

      .. figure:: images/gettingStarted/STM32F7508DK/getting-started-runOnSimulator.png
         :alt: runOnSimulator task
         :align: center
         :scale: 70%

The Virtual Device starts and executes the :guilabel:`microui.mvc` application.

      .. figure:: images/gettingStarted/STM32F7508DK/getting-started-virtual-device.png
         :alt: Virtual Device
         :align: center
         :scale: 70%

.. figure:: images/gettingStarted/well-done-mascot.png
   :alt: Well Done
   :align: center
   :scale: 70%

Well done !
-----------

Now you know how to run an application on a Virtual Device.

If you want to learn how to run an application on your STM32F7508-DK Evaluation Kit, you can continue this Getting Started: :ref:`Run an Application on STM32F7508-DK Evaluation Kit <sdk_6_getting_started_stm32f7508dk_run_on_device>`.

Otherwise, learn how to :ref:`Modify the Java Application <sdk_6_getting_started_stm32f7508dk_modify_java_application>`.

.. _sdk_6_getting_started_stm32f7508dk_run_on_device:

Run an Application on STM32F7508-DK Evaluation Kit
--------------------------------------------------

* TODO

.. _sdk_6_getting_started_stm32f7508dk_modify_java_application:

Modify the Java Application
---------------------------

With MicroEJ, it is easy to modify and test your Java application on the Virtual Device.

For example, we could modify the color used in the pie chart.

* Open :guilabel:`PieView` file located in the :guilabel:`src/main/java/com/microej/example/foundation/microui/mvc` folder.
* The pie char color is set at line 12, replace the following line:

.. code:: 

   public static final int COLOR_CONTENT = 0x2fc19c;	// green

by

.. code:: 

   public static final int COLOR_CONTENT = 0x800080;	// purple

* Follow :ref:`sdk_6_getting_started_stm32f7508dk_run_virtual_device` instructions to launch the modified application on the Virtual Device.

Here is the modified application running in simulation: 

      .. figure:: images/gettingStarted/STM32F7508DK/getting-started-virtual-device-modified.png
         :alt: Virtual Device
         :align: center
         :scale: 70%

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.