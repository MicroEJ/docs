.. _sdk_6_getting_started_imx93:

i.MX93 Evaluation Kit
==========================

During this Getting Started, you will learn to:

* Run an Application on the i.MX93 Evaluation Kit Virtual Device.
* Run the same Application on your i.MX93 Evaluation Kit.

If you need to become more familiar with MicroEJ, please visit `Discover MicroEJ <https://developer.microej.com/discover-microej/>`__ to understand the principles of our technology.

Prerequisites
-------------

.. note::
  
   This Getting Started has been tested on Windows 10 & 11 with a WSL distribution Ubuntu 22.04.

This Getting Started is separated into two main parts.

The first part consists in running a demo application on the Virtual Device. All you need is:


* An Internet connection to access Github repositories & :ref:`Module Repositories <module_repositories>`.
* MICROEJ SDK 6 (installed during :ref:`Environment Setup <sdk_6_getting_started_imx93_environment_setup>`).

The second part consists in running the same demo application on your device. For that, you will need:

* An i.MX93 Evaluation Kit, available `here <https://www.nxp.com/design/design-center/development-boards/i-mx-evaluation-and-development-boards/i-mx-93-evaluation-kit:i.MX93EVK>`__.

* An HDMI display with touchscreen connected with an `IMX-MIPI-HDMI adapter <https://www.nxp.com/part/IMX-MIPI-HDMI#/>`__.

   * This getting started has been tested with a `MageDok T080A <https://magedok.com/products/8-inch-1280-720-resolution-touch-monitor-t080a>`_.

* Yocto Linux image (TBD)

* Yocto SDK (TBD)

.. _sdk_6_getting_started_imx93_environment_setup:

Environment Setup
-----------------

To follow this Getting Started, you need to: 

* Install MICROEJ SDK 6.
* Get the Example-Java-Widget from Github.

Install MICROEJ SDK 6
^^^^^^^^^^^^^^^^^^^^^

Install MICROEJ SDK 6 by following the :ref:`sdk_6_install` instructions. 
IntelliJ IDEA is used on this Getting Started, but feel free to use your favorite IDE.

Get Example-Java-Widget
^^^^^^^^^^^^^^^^^^^^^^^

For this Getting Started, the :guilabel:`Example-Java-Widget` Application will be used. You can download it using the following command::
   
   git clone -b 8.0.0 https://github.com/MicroEJ/Example-Java-Widget.git

.. note::
  
   If you don't have Git installed, you can download the source code directly from our `GitHub repository <https://github.com/MicroEJ/Example-Java-Widget/tree/1.0.0>`__. 
   Then you can click on::guilabel:` Code > Download ZIP`.

Set up the Application on your IDE
----------------------------------

Import the Project
^^^^^^^^^^^^^^^^^^

The first step is to import the :guilabel:`Example-Java-Widget` Application into your IDE: 

.. note::
  
   If you are using an IDE other than IntelliJ IDEA, please have a look at :ref:`sdk_6_import_project` section.


* If you are in the Welcome Screen, click on the :guilabel:`Open` button. Otherwise, click either on :guilabel:`File` > :guilabel:`Open...` or on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project From Existing Sources...`.
* Select the ``Example-Java-Widget`` directory located where you downloaded it and click on the :guilabel:`OK` button.

      .. figure:: images/gettingStarted/iMX93/getting-started-import-demo.png
         :alt: Import demo application
         :align: center
         :scale: 70%

* If you are asked to choose a project model, select :guilabel:`Gradle`. 

      .. raw:: html

         <div style="display:block;margin-bottom:24px;">
            <table>
               <tr>
                  <td style="width:50%;text-align:center;vertical-align:middle;" alt="Project Model Selection when Opening in IntelliJ IDEA">
                     <img src="../_images/intellij-import-gradle-project-01.png">
                  </td>
                  <td style="width:50%;text-align:center;vertical-align:middle;" alt="Project Model Selection when Importing in IntelliJ IDEA">
                     <img src="../_images/intellij-import-gradle-project-02.png">
                  </td>
               </tr>
               <tr>
                  <td style="width:50%;text-align:center;font-size:18px;font-style:italic;">
                     Fig 1. Project Model Selection when Opening in IntelliJ IDEA
                  </td>
                  <td style="width:50%;text-align:center;font-size:18px;font-style:italic;">
                     Fig 2. Project Model Selection when Importing in IntelliJ IDEA
                  </td>
               </tr>
            </table>
         </div>

      .. |image1| image:: images/intellij-import-gradle-project-01.png
      .. |image2| image:: images/intellij-import-gradle-project-02.png

* Click on the :guilabel:`Create` button.

The Gradle project should now be imported into IntelliJ IDEA. Your workspace contains the following projects: 

      .. figure:: images/gettingStarted/iMX93/getting-started-project-view.png
         :alt: Workspace view
         :align: center
         :scale: 70%

Select the VEE Port
^^^^^^^^^^^^^^^^^^^

In the gradle build file ``build.gradle.kts``, replace the VEE dependency ``microejVEE`` with the i.MX93, like this:

.. code-block::

   dependencies {
      microejVee("com.microej.veeport.imx93:VEEPort:1.0.0")
   }

For more information about how to select a VEE Port please refer to the following section: :ref:`sdk_6_select_veeport`.

.. _sdk_6_getting_started_imx93_eula:

Accept the MICROEJ SDK EULA
---------------------------

You may have to accept the SDK EULA if you haven't already done so, please have a look at :ref:`sdk_6_eula_acceptation`.

.. _sdk_6_getting_started_imx93_run_virtual_device:

Run an Application on the Virtual Device
----------------------------------------

To execute the :guilabel:`Example-Java-Widget` Application on the Virtual Device, the SDK provides the Gradle :guilabel:`runOnSimulator` task. 

.. note::
  
   If you are using another IDE than IntelliJ IDEA, please have a look at the :ref:`sdk_6_run_on_simulator` section.

* Double-click on the :guilabel:`runOnSimulator` task in the Gradle tasks view. It may take a few seconds.

      .. figure:: images/gettingStarted/iMX93/getting-started-runOnSimulator.png
         :alt: runOnSimulator task
         :align: center
         :scale: 70%

The Virtual Device starts and executes the :guilabel:`Example-Java-Widget` application.

      .. figure:: images/gettingStarted/iMX93/getting-started-virtual-device.png
         :alt: Virtual Device
         :align: center
         :scale: 70%

.. figure:: images/gettingStarted/well-done-mascot.png
   :alt: Well Done
   :align: center
   :scale: 70%

Well done!
----------

Now you know how to run an application on a Virtual Device.

If you want to learn how to run an application on your i.MX93 Evaluation Kit, you can continue this Getting Started: :ref:`Run an Application on i.MX93 Evaluation Kit <sdk_6_getting_started_imx93_run_on_device>`.

Otherwise, learn how to :ref:`Modify the Java Application <sdk_6_getting_started_imx93_modify_java_application>`.

.. _sdk_6_getting_started_imx93_run_on_device:

Run an Application on i.MX93 Evaluation Kit
-------------------------------------------

To deploy :guilabel:`Example-Java-Widget` application on your board, you will have to:

* Set up your environment (toolchain, hardware setup).
* Request a 30 days :ref:`Evaluation License <sdk_eula>` and install an activation key.
* Build the Executable.
* Run the Executable on board.

Environment Setup
^^^^^^^^^^^^^^^^^

This chapter takes approximately one hour and will take you through the steps to build a VEE Executable and set up the evaluation kit.

Flash the image on an SD card
"""""""""""""""""""""""""""""

The Linux image is available here: (TBD)

For this getting started we use a Linux image flashed on an SD card.

Linux
+++++

To flash the image on Linux, use the following command (assuming the SDCard device is /dev/mmcblk0):

.. code-block::

   bmaptool copy lib32-core-image-microej-microej-imx93.wic.gz /dev/mmcblk0

Windows
+++++++

To flash the image on Windows, do the following:

* Install Rufus: https://rufus.ie/en/.
* Extract the ``.wic`` file from the archive ``lib32-core-image-microej-microej-imx93.wic.gz``.
* Select your SD card device in the list at the top (see example of configuration below).
* Select your ``.wic`` file by clicking on ``SELECT``
* Finally click on ``START`` at the bottom and wait for the process to finish.

      .. figure:: images/gettingStarted/iMX93/getting-started-rufus.png
         :alt: Rufus
         :align: center

Configure boot
""""""""""""""

By default, the i.MX93 evaluation kit will boot from the eMMC.
To change the boot mode to micro SD, set the DIP switch ``BMODE`` to ``0010``.

Insert the flashed SD card and boot the device. After a few seconds, the display will show the IMX93 Getting Started Welcome page.
If no display is attached, information such as device IP address and documentation link will also be printed in the logs.

LVDS display support
""""""""""""""""""""

This Getting Started has been tested with an HDMI display with a 1280x720 resolution.
If you want to use the official display instead (the `DY1212W-4856 <https://www.nxp.com/design/design-center/development-boards-and-designs/i-mx-evaluation-and-development-boards/dy1212w-4856:DY1212W-4856>`_) 
you will need to reconfigure the device tree:

* Boot your i.MX93 Evaluation Kit.
* Stop the booting process to access the U-boot menu by pressing a key on the serial console.
* In the U-boot menu, run the following commands:

.. code-block ::

   setenv fdtfile imx93-11x11-evk-boe-wxga-lvds-panel.dtb
   saveenv
   boot

* After the boot has completed you can test the display with: ``modetest -M imx-drm -s 35@33:1280x800-60.03``.

Install the Yocto SDK
"""""""""""""""""""""

The Executable is built using a Yocto SDK. It contains the following:

* The C toolchain.
* The cross-compiled libraries.
* All the necessary headers (libc, but also the headers of the kernel and the libraries installed in the firmware rootfs).
* An environment setup script (to set $CC, $LD, $SDKSYSROOT variables).

A prebuilt version of the Yocto SDK is available here: (TBD)

To install the Yocto SDK, use the following commands in WSL or Linux:

.. code-block::

   $ chmod +x oecore-x86_64-armv7at2hf-neon-vfpv4-toolchain-nodistro.0.sh
   $ ./oecore-x86_64-armv7at2hf-neon-vfpv4-toolchain-nodistro.0.sh
   MicroEJ: 32-bit userspace + 64-bit kernel SDK installer version nodistro.0
   ==========================================================================
   Enter target directory for SDK (default: /usr/local/oecore-x86_64): 
   You are about to install the SDK to "/usr/local/oecore-x86_64". Proceed [Y/n]? Y
   [sudo] password for xxxxx:
   Extracting SDK.................................................................................done
   Setting it up...done
   SDK has been successfully set up and is ready to be used.
   Each time you wish to use the SDK in a new shell session, you need to source the environment setup script e.g.
   $ . /usr/local/oecore-x86_64/environment-setup-armv7at2hf-neon-vfpv4-oemllib32-linux-gnueabi
   $ . /usr/local/oecore-x86_64/environment-setup-cortexa55-oe-linux

The installation path can then be used to build the VEE Executable.

Install required packages
"""""""""""""""""""""""""

Some additionnal packages will be required in order to build an executable. Run the following command (either in Linux or WSL):

.. code-block::

   sudo apt-get update && sudo apt-get install dos2unix make

Hardware Setup
""""""""""""""

To setup the hardware you will need to connect the following on the EVK:

* A USB C cable for the power (provided with the EVK).
* A USB C cable for the serial port.
* A USB C cable for the touchscreen device.
* A RJ45 cable to access the network.
* An HDMI cable connected to the IMX-HDMI-MIPI adapter.

      .. figure:: images/gettingStarted/iMX93/getting-started-setup.png
         :alt: Setup
         :align: center
         :scale: 70%

Congratulations! You have finished the setup of your environment. You are now ready to discover how to build and run a MicroEJ application.

Build the Executable for i.MX93 Evaluation Kit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To build the Executable of the :guilabel:`Example-Java-Widget` Application, the SDK provides the Gradle :guilabel:`buildExecutable` task.

.. note::
  
   If you are using an IDE other than IntelliJ IDEA, please have a look at the :ref:`sdk_6_build_executable` section.
   Come back to this page if you need to activate an Evaluation License.

* Before using this task, you will have to configure some environment variables that depend on the OS you are using.

  * To do so, right-click on ``buildExecutable`` then ``Modify Run Configuration...``.
  * Fill in your variables in ``Environment variables``, each one separated by a semicolon (see screenshot): 

    * If you changed the default Yocto SDK installation path, set the following environment variable

      * ``APP_SDK_INSTALL=/usr/local/oecore-x86_64`` (replace it with your own path)

    * When using Windows with WSL, set the WSL distribution name, which you can get with the command :guilabel:` wsl --list` in Windows terminal

      * ``WSL_DISTRIBUTION_NAME=``: Name of the WSL distribution, for example ``Ubuntu`` (default value).

      .. figure:: images/gettingStarted/iMX93/getting-started-intellij-variables.png
         :alt: IntelliJ variables
         :align: center
         :scale: 70%

* Double-click on the :guilabel:`buildExecutable` task in the Gradle tasks view.
* The build stops with a failure.
* Go to the top project in the console view and scroll up to get the following error message:

      .. figure:: images/gettingStarted/iMXRT1170/getting-started-console-output-license-uid.png
         :alt: Console Output License UID
         :align: center
         :scale: 70%

* Copy the UID. It will be required to activate your Evaluation license.

Request your Evaluation License:

* You can request your Evaluation license by following the :ref:`evaluation_license_request_activation_key` instructions. You will be asked to fill in the machine UID you just copied.

* When you have received your activation key by email, drop it in the license directory by following the :ref:`evaluation_license_install_license_key` instructions (drop the license key zip file to the ``~/.microej/licenses/`` directory).

Now your Evaluation license is installed, you can relaunch your application build by double-clicking on the :guilabel:`buildExecutable` task in the Gradle tasks view. It may take some time.

The gradle task deploys the Application in the BSP and then builds the BSP using Make.

The :guilabel:`Example-Java-Widget` application is built and ready to be flashed on i.MX93 Evaluation Kit once the hardware setup is completed.

Run the Application on the i.MX93 Evaluation Kit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To run the :guilabel:`Example-Java-Widget` Application on i.MX93 Evaluation Kit, the application provides the Gradle :guilabel:`runOnDevice` task.

.. note::
  
   If you are using another IDE than IntelliJ IDEA, please have a look at the :ref:`sdk_6_run_on_device` section.

* Before using this task, you will have to configure the device IP Address in the environment variables.

  * To do so, right-click on ``runOnDevice`` then ``Modify Run Configuration...``.
  * Fill in your variables in ``Environment variables``, each one separated by a semicolon:

    * ``SSH_USER=root``
    * ``SSH_HOSTNAME``: IP address of the i.MX93 Evaluation Kit.
    * ``APP_SDK_INSTALL``: Path to the Yocto SDK (by default ``/usr/local/oecore-x86_64/``).
    * ``WSL_DISTRIBUTION_NAME``: Name of the WSL distribution if using Windows.

* Double-click on the :guilabel:`runOnDevice` task in the Gradle tasks view. It may take some time.

      .. figure:: images/gettingStarted/iMXRT1170/getting-started-runOnDevice.png
         :alt: runOnDevice task
         :align: center
         :scale: 70%

Once the application is running, you should see the :guilabel:`Example-Java-Widget` on your board.      

.. _sdk_6_getting_started_imx93_modify_java_application:

Modify the Java Application
---------------------------

With MicroEJ, it is easy to modify and test your Java application on the Virtual Device.

For example, we can modify the color of the items in the main page list.

* Open :guilabel:`MainPage.java` located in the :guilabel:`src/main/java/com/microej/demo/widget/main/MainPage.java` folder
* Odd items background color is set line 74, replace the following line:

.. code-block::

   style.setBackground(new GoToBackground(GRAY));

with

.. code-block::

   style.setBackground(new GoToBackground(Colors.CYAN));

* Follow :ref:`sdk_6_getting_started_imx93_run_virtual_device` instructions to launch the modified application on the Virtual Device.


      .. figure:: images/gettingStarted/iMX93/getting-started-runOnSimulator-modified.png
         :alt: runOnDevice task
         :align: center
         :scale: 70%

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
