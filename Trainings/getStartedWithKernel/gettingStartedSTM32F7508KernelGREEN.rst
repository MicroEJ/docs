.. _sdk_6_getting_started_stm32f7508_kernel_green:

Build your own Multi-Sandbox Executable on STM32F7508-DK
========================================================

This Getting Started is a step-by-step guide explaining
how to build a Multi-Sandbox Executable for the STM32F7508-DK Discovery kit.

This Executable will be built from 
`Kernel GREEN <https://github.com/MicroEJ/Kernel-GREEN>`__ sources.

The Multi-Sandbox Executable built in this Getting Started can then be used to
complete the :ref:`sdk_6_getting_started_stm32f7508_multisandbox` Getting Started.

During this Getting Started, you will learn how to:

* Get the Kernel GREEN,
* Configure it,
* Build the project and get the modules: Virtual Device, Executable, Javadoc, ...
* Run a Sandboxed Application project on this Multi-Sandbox Executable.

In case you are not familiar with MicroEJ, please visit `Discover MicroEJ <https://developer.microej.com/discover-microej/>`__ to understand the principles of our technology.

Prerequisites
-------------

.. note::
  
   This Getting Started has been tested on Windows 10. 
   Also note that examples used in this Getting Started could depend on older tools and libraries. 
   Most notably our dependency manager plugin (using `Gradle <https://gradle.org/>`__) could be an older version.

For this Getting Started, all you need is:

* An Internet connection to access Github repositories & :ref:`Module Repositories <module_repositories>`.
* MICROEJ SDK 6 (installed during :ref:`Environment Setup <sdk_6_getting_started_stm32f7508dk_multisandbox_environment_setup>`).
* STM32F7508-DK Discovery kit, available `here <https://www.st.com/en/evaluation-tools/stm32f7508-dk.html>`__.
* A FAT32-formatted microSD card.
* An RS232 Terminal (e.g. `Termite <https://www.compuphase.com/software_termite.htm>`__).
* `STM32CubeProgrammer <https://www.st.com/en/development-tools/stm32cubeprog.html>`__ installed to flash a Executable on your board.

.. _sdk_6_getting_started_stm32f7508dk_kernel_green_environment_setup:

Environment Setup
-----------------

To follow this Getting Started, you need to:

* Follow :ref:`MICROEJ SDK 6 installation Guide <sdk_6_install>`
  Android Studio Koala is used on this Getting Started but feel free to use your favorite IDE,
* Install the STM32CubeIDE **version 1.9.0** for STM32F7508-DK, available `here <https://www.st.com/en/development-tools/stm32cubeide.html>`__,
* Install the STM32CubeProgrammer utility program, available `here <https://www.st.com/en/development-tools/stm32cubeprog.html>`__,
* Download or clone the `Kernel GREEN <https://github.com/MicroEJ/Kernel-GREEN>`__ sources.

Be aware that we need the **1.9.0 version** of the STM32CubeIDE, 
also please install the IDE and programmer to the default installation folders,
it will simplify future steps.

Hardware Setup
~~~~~~~~~~~~~~

Set up your STM32F7508-DK Discovery kit:

- Insert a microSD card (FAT32-formatted) in the board connector,
- Connect the Ethernet connector to the internet,
- Check the jumpers configuration on JP1, you only want the :guilabel:`5V link` jumper to be bridged,
- Connect the mini-USB cable to CN14 to power the board, see
  `Board Configuration <https://github.com/MicroEJ/VEEPort-STMicroelectronics-STM32F7508-DK/blob/2.3.1/stm32f7508_freertos-bsp/projects/microej/README.rst>`__
  for more information.

The USB connection is used as a serial link, a ST-Link probe, and a power input for the board all at once.

The COM port uses the following parameters:

.. list-table::
   :header-rows: 1
   :widths: 10 10 10 10 10

   * - Baudrate
     - Data bits
     - Parity bits
     - Stop bits
     - Flow control
   * - 115200
     - 8
     - None
     - 1
     - None

You can have a look at your application logs with an RS232 Terminal (e.g. `Termite <https://www.compuphase.com/software_termite.htm>`__).

Congratulations! You have finished the setup of your environment.
You are now ready to discover how to build and flash the Kernel GREEN.

Set up the Kernel GREEN on your IDE
-----------------------------------

Import the Project
~~~~~~~~~~~~~~~~~~

The first step is to import the :guilabel:`Kernel-GREEN` into your IDE: 

.. note::
  
   If you are using an IDE other than Android Studio, please have a look at :ref:`sdk_6_import_project` section.

* If you are in the Welcome Screen, click on the :guilabel:`Open` button. Otherwise click either on :guilabel:`File` > :guilabel:`Open...`,
* Select the :guilabel:`Kernel-GREEN` directory located where you downloaded it and click on the :guilabel:`OK` button.

The Gradle project should now be imported in Android Studio,
your workspace contains the following project in the :guilabel:`Projects` view: 

   .. figure:: images/getting-started-import-kernel-green.png
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

By default, the Kernel GREEN project uses the `NXP i.MXRT1170 VEE Port <https://github.com/MicroEJ/nxp-vee-imxrt1170-evk>`__.

A pre-built version of the `STM32F7508-DK VEE Port with Multi-Sandbox capability <https://forge.microej.com/ui/repos/tree/General/microej-developer-repository-release/com/microej/veeport/st/stm32f7508-dk/R0OUY_eval/2.2.0>`__
is available on the Developer Repository.
Update the Kernel project to use this VEE Port:

* Open the ``build.gradle.kts`` file located at the root of the project,
* Edit the following variables as follows:
  
   .. code-block:: kotlin
      
      val defaultVeePortGroup: String = "com.microej.veeport.st.stm32f7508-dk"
      val defaultVeePortModule: String = "R0OUY_eval"
      val defaultVeePortVersion: String = "2.3.0"

Kernel Configuration
^^^^^^^^^^^^^^^^^^^^

The ``configuration/common.properties`` file provides a default configuration
for the Kernel (runtime heap size, maximum number of threads, images heap size, etc.).

This configuration will also impact Sandboxed Applications running on top of the Kernel
(e.g. max number of threads per application). 

Check the `Kernel GREEN README <https://github.com/MicroEJ/Kernel-GREEN/blob/master/README.md>`__
for more information about the Kernel configuration.

Accept the MICROEJ SDK EULA
---------------------------

You may have to accept the SDK EULA if you haven't already done it, please have a look at :ref:`sdk_6_eula_acceptation`.

Run the Kernel GREEN on STM32F7508-DK Discovery kit
----------------------------------------------------

Make sure to have completed all the :ref:`sdk_6_getting_started_stm32f7508dk_kernel_green_environment_setup`
steps before going further. 

To deploy :guilabel:`Kernel-GREEN` on your board, you will have to:

* Request a 30 days :ref:`Evaluation License <sdk_eula>` and install an activation key,
* Build the Executable,
* Flash the board.

Build the Executable for the STM32F7508-DK Discovery kit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to build the Executable of the :guilabel:`Kernel-GREEN`,
the SDK provides the :guilabel:`buildExecutable` Gradle task.

.. note::
  
   If you are using an IDE other than Android Studio, please have a look at :ref:`sdk_6_build_executable` section.
   Come back on this page if you need to activate an Evaluation License.

* Double-click on the :guilabel:`buildExecutable` task in the Gradle tasks view.
* The build stops with a failure.
* Go to the top project in the console view and scroll up to get the following error message:

   .. figure:: images/getting-started-console-output-license-uid.png
      :alt: Console Output License UID
      :align: center
      :scale: 70%

* Copy the UID. It will be required to activate your Evaluation license.

Request your Evaluation License:

* Request your Evaluation license by following the :ref:`evaluation_license_request_activation_key` instructions. You will be asked to fill the machine UID field with the UID you copied before.

* When you have received your activation key by email, drop it in the license directory by following the :ref:`evaluation_license_install_license_key` instructions (drop the license key zip file to the ``~/.microej/licenses/`` directory).

Now your Evaluation license is installed, you can relaunch your Kernel build by double-clicking on the :guilabel:`buildExecutable` task in the Gradle tasks view. It may take some time.

The gradle task deploys the Kernel in the BSP and then builds the BSP using Make.

The :guilabel:`Kernel-GREEN` is built and ready to be flashed on a STM32F7508-DK Discovery kit once the hardware setup is completed.

Flash the Kernel GREEN on the STM32F7508-DK Discovery kit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to flash the :guilabel:`Kernel-GREEN` on the STM32F7508-DK Discovery kit,
the application provides the Gradle :guilabel:`runOnDevice` task.

.. note::
  
   If you are using an IDE other than Android Studio, please have a look at :ref:`sdk_6_run_on_device` section.

* Double-click on the :guilabel:`runOnDevice` task in the Gradle tasks view. It may take some time:

   .. figure:: images/getting-started-runOnDevice.png
      :alt: runOnDevice task
      :align: center
      :scale: 70%

Once the Executable is flashed, you should see the :guilabel:`Kernel-GREEN` traces in your console:

   .. figure:: images/getting-started-stm32f7508dk-termite-green-fw-output.png
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

Follow the :ref:`sdk_6_getting_started_stm32f7508_multisandbox_run_application`
Getting Started to create and run a Sandboxed Application project on your 
Multi-Sandbox Executable and Virtual Device.

.. note::

   When it comes to selecting the Multi-Sandbox Executable and Virtual Device
   (section :ref:`sdk_6_getting_started_stm32f7508_multisandbox_run_virtual_device`),
   follow this procedure:

   - Open the ``settings.gradle.kts`` files located at the root of your :guilabel:`MyApplication` project,
   - Include the :guilabel:`Kernel-GREEN` project as a dependency of the :guilabel:`MyApplication` project,
      
      .. code-block:: kotlin

         rootProject.name = "MyApplication"
         include(":app")
         includeBuild("C:\\YOUR_PATH\\Kernel-GREEN")

   - Reload the Gradle project:

      .. figure:: images/getting-started-reload-gradle-project.png
         :alt: Virtual Device
         :align: center
         :scale: 70%

   - The :guilabel:`Kernel-GREEN` project should now appear in the Gradle tasks view:

      .. figure:: images/getting-started-gradle-tasks-kernel-green.png
         :alt: Kernel GREEN and MyApplication Gradle tasks
         :align: center
         :scale: 90%

   - Open the ``app/build.gradle.kts`` file of the :guilabel:`MyApplication` project,
   - Declare the dependency to the :guilabel:`Kernel-GREEN` project as follows:

      .. code-block:: kotlin

         dependencies {
            ...
            //Uncomment the microejVee dependency to set the VEE Port or Kernel to use
            microejVee("com.microej.kernel:GREEN:2.0.0")
         }
   - Come back to the :ref:`sdk_6_getting_started_stm32f7508_multisandbox_run_virtual_device` Getting Started.

Going Further
-------------

You have now successfully executed Sandboxed Applications on an embedded device so what's next?

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