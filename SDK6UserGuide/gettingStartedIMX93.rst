.. _sdk_6_getting_started_imx93:

i.MX93 Evaluation Kit
==========================

During this Getting Started, you will learn to:

* run an Application on the i.MX93 Evaluation Kit Virtual Device,
* run the same Application on your i.MX93 Evaluation Kit.

In case you are not familiar with MicroEJ, please visit `Discover MicroEJ <https://developer.microej.com/discover-microej/>`__ to understand the principles of our technology.

Prerequisites
-------------

.. note::
  
   This Getting Started has been tested on Windows 10 & 11.

This Getting Started is separated in two main parts.

The first part consists of running a demo application on the Virtual Device. All you need is:


* An Internet connection to access Github repositories & :ref:`Module Repositories <module_repositories>`.
* MICROEJ SDK 6 (installed during :ref:`Environment Setup <sdk_6_getting_started_imx93_environment_setup>`).

The second part consists of running the same demo application on your device. For that you will need:

* i.MX93 Evaluation Kit, available `here <https://www.nxp.com/design/design-center/development-boards/i-mx-evaluation-and-development-boards/i-mx-93-evaluation-kit:i.MX93EVK>`__.
* (Optional) An HDMI display.
* Linux image (TBD)
* GCC Toolchain (TBD)

.. _sdk_6_getting_started_imx93_environment_setup:

Environment Setup
-----------------

To follow this Getting Started, you need to: 

* Install MICROEJ SDK 6.
* Get the Example-Java-Widget from Github.

Install MICROEJ SDK 6
^^^^^^^^^^^^^^^^^^^^^

Install MICROEJ SDK 6 by following :ref:`sdk_6_install` instructions. 
IntelliJ IDEA is used on this Getting Started but feel free to use your favorite IDE.

Get Example-Java-Widget
^^^^^^^^^^^^^^^^^^^^^^^

For this Getting Started, the :guilabel:`Example-Java-Widget` Application will be use. You can download it using the following command::
   
   git clone -b 8.0.0 https://github.com/MicroEJ/Example-Java-Widget.git

.. note::
  
   If you don’t have Git installed, you can download the source code directly from our `GitHub repository <https://github.com/MicroEJ/Example-Java-Widget/tree/1.0.0>`__. 
   Then you can click on ::guilabel:`Code > Download ZIP`.

Set up the Application on your IDE
----------------------------------

Import the Project
^^^^^^^^^^^^^^^^^^

The first step is to import the :guilabel:`Example-Java-Widget` Application into your IDE: 

.. note::
  
   If you are using another IDE than IntelliJ IDEA, please have a look at :ref:`sdk_6_import_project` section.


* If you are in the Welcome Screen, click on the :guilabel:`Open` button. Otherwise click either on :guilabel:`File` > :guilabel:`Open...` or on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project From Existing Sources...`.
* Select the ``Example-Java-Widget`` directory located where you downloaded it and click on the :guilabel:`OK` button.

      .. figure:: images/gettingStarted/iMXRT1170/getting-started-import-demo-application.png
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

The Gradle project should now be imported in IntelliJ IDEA, your workspace contains the following projects: 

      .. figure:: images/gettingStarted/iMXRT1170/getting-started-workspace-view.png
         :alt: Workspace view
         :align: center
         :scale: 70%

.. _sdk_6_getting_started_imx93_eula:

Accept the MICROEJ SDK EULA
---------------------------

You may have to accept the SDK EULA if you didn't already do, please have a look at :ref:`sdk_6_eula_acceptation`.

.. _sdk_6_getting_started_imx93_run_virtual_device:

Run an Application on the Virtual Device
----------------------------------------

In order to execute the :guilabel:`Example-Java-Widget` Application on the Virtual Device, the SDK provides the Gradle :guilabel:`runOnSimulator` task. 

.. note::
  
   If you are using another IDE than IntelliJ IDEA, please have a look at :ref:`sdk_6_run_on_simulator` section.

* Double-click on the :guilabel:`runOnSimulator` task in the Gradle tasks view. It may takes few seconds.

      .. figure:: images/gettingStarted/iMXRT1170/getting-started-runOnSimulator.png
         :alt: runOnSimulator task
         :align: center
         :scale: 70%

The Virtual Device starts and executes the :guilabel:`Example-Java-Widget` application.

      .. figure:: images/gettingStarted/iMXRT1170/getting-started-virtual-device.png
         :alt: Virtual Device
         :align: center
         :scale: 70%

.. note::
  
   The Front Panel may be too big for your screen, that is because of the RK055HDMIPI4MA0 display resolution. You can scroll down to see the bottom of the display.

   If you want to know more about the use of the :guilabel:`Example-Java-Widget`, please have a look at its `README.md <https://github.com/MicroEJ/Example-Java-Widget/blob/1.0.0/smart-thermostat/README.md>`__ file.


.. figure:: images/gettingStarted/well-done-mascot.png
   :alt: Well Done
   :align: center
   :scale: 70%

Well done !
-----------

Now you know how to run an application on a Virtual Device.

If you want to learn how to run an application on your i.MX93 Evaluation Kit, you can continue this Getting Started: :ref:`Run an Application on i.MX93 Evaluation Kit <sdk_6_getting_started_imx93_run_on_device>`.

Otherwise, learn how to :ref:`Modify the Java Application <sdk_6_getting_started_imx93_modify_java_application>`.

..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
