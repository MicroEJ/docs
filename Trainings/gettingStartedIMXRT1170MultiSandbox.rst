.. |MULTI_SANDBOX_EXECUTABLE_LINK| replace:: `NXP-MIMXRT1170-3.0.0_GCC_GREEN-2.1.1.elf <https://repository.microej.com/packages/green/2.1.1/firmware/NXP-MIMXRT1170_GCC/NXP-MIMXRT1170-3_0_0_GCC_GREEN-2.1.1.elf>`__
.. |GREEN_KERNEL_PACKAGE_LINK| replace:: `directory <https://repository.microej.com/packages/green/2.1.1/>`__
.. |GREEN_KERNEL_SOURCES_LINK| replace:: `Kernel GREEN <https://github.com/MicroEJ/Kernel-GREEN>`__
.. |DEMO_SANDBOXED_APPS_SOURCES_LINK| replace:: `Demo-Sandboxed-Applications <https://github.com/MicroEJ/Demo-Sandboxed-Applications>`__
.. |FLASH_COMMAND_LINE| replace:: ``LinkServer flash MIMXRT1176xxxxx:MIMXRT1170-EVKB load NXP-MIMXRT1170-3_0_0_GCC_GREEN-2.1.1.elf``
.. |GREEN_KERNEL_DEPENDENCY| replace:: ``microejVee("com.microej.kernel:NXP-MIMXRT1170-3_0_0_GCC_GREEN:2.1.1")``
.. |DEMO_SANDBOXED_APPS_VERSION| replace:: ``2.0.0``

.. _training_multisandbox_applications_imxrt1170:

===========================================
Get Started with Multi-Sandbox Applications
===========================================

Description
===========

This training will show you how to run Sandboxed Applications
on top of a pre-built Multi-Sandbox Executable for the NXP i.MXRT1170 Evaluation Kit.

During this training, you will learn how
to run Sandboxed Applications in Simulation using
the Virtual Device and on NXP i.MXRT1170:

1. :ref:`training_multisandbox_applications_imxrt1170_run_demo_sandboxed_apps`.
2. :ref:`Create Sandboxed Application and run it <training_multisandbox_applications_imxrt1170_create_app>`.

In case you are not familiar with MicroEJ, please visit `Discover MicroEJ <https://developer.microej.com/discover-microej/>`__ to understand the principles of our technology.

The below schematic summarizes the Multi-Sandbox features that will be demonstrated in this training: 

   .. figure:: images/multiSandbox/iMXRT1170/multiSandboxGettingStartedOverview.png
      :alt: Logs Output on Termite Serial Terminal
      :align: center


Intended Audience
=================

This training is designed for application developers looking to gain a first understanding 
of the Multi-Sandbox development flow.

Prerequisites
=============

.. note::
  
   This Getting Started has been tested in the following conditions:

   - Windows 11.
   - Multi-Sandbox Executable: |MULTI_SANDBOX_EXECUTABLE_LINK|.
   - |DEMO_SANDBOXED_APPS_SOURCES_LINK| |DEMO_SANDBOXED_APPS_VERSION|.

To get the most out of this training, participants should have:

- A good understanding of the :ref:`overview` section.
- A basic knowledge of the :ref:`chapter-glossary`.
- Access to the `NXP i.MX RT1170 Evaluation Kit EVKB <https://www.nxp.com/design/design-center/development-boards-and-designs/i-mx-evaluation-and-development-boards/i-mx-rt1170-evaluation-kit:MIMXRT1170-EVKB>`__.
- Access to the `RK055HDMIPI4MA0 display panel <https://www.nxp.com/part/RK055HDMIPI4MA0>`__.
- A FAT32-formatted microSD card.

Environment Setup
-----------------

To follow this training, you need:

* A FAT32-formatted microSD card.
* An RS232 Terminal (e.g. `Termite <https://www.compuphase.com/software_termite.htm>`__).

Also, follow the steps described in the sections below to complete your environment setup. 

Install MICROEJ SDK 6
~~~~~~~~~~~~~~~~~~~~~

Follow :ref:`MICROEJ SDK 6 installation Guide <sdk_6_install>`.
IntelliJ IDEA is used in this training, but feel free to use your favorite IDE.

Accept the MICROEJ SDK EULA
~~~~~~~~~~~~~~~~~~~~~~~~~~~

You may have to accept the SDK EULA if you haven't already done it, 
please have a look at :ref:`sdk_6_eula_acceptation`.

Hardware Setup for NXP i.MXRT1170 EVKB
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Refer to the NXP i.MXRT1170 EVKB :ref:`sdk_6_getting_started_rt1170_hardware_setup` guide.

Additionally, make sure to:

* Insert a micro-SD card (FAT32-formatted) in the board connector.
* Connect the ``1GB`` Ethernet connector to the internet.

Flash the Multi-Sandbox Executable on your NXP i.MXRT1170 Evaluation Kit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Download the Multi-Sandbox Executable: |MULTI_SANDBOX_EXECUTABLE_LINK|.

.. note::
   
   The Multi-Sandbox Executable used in this documentation is built from the
   |GREEN_KERNEL_SOURCES_LINK| sources.
   Refer to the :ref:`training_kernel_green_imxrt1170`
   training to build your own Multi-Sandbox Executable.

   If you want more information about this Multi-Sandbox Executable,
   the Javadoc and the Release notes are available in this
   |GREEN_KERNEL_PACKAGE_LINK|.

Flash the Multi-Sandbox Executable using ``LinkServer``:

- Download and install `LinkServer for Microcontroller <https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/linkserver-for-microcontrollers:LINKERSERVER>`_ (minimum version 1.6.133).
- Once installed, the ``LinkServer`` installation folder must be set on your Path. To do so:

  - Open the Edit the system environment variables application on Windows.
  - Click on the ``Environment Variables…`` button.
  - Select ``Path`` variable under the ``User`` variables section and edit it.
  - Click on ``New`` and point to the ``LinkServer`` installation folder located where you installed
    ``LinkServer`` (e.g. ``nxp/LinkServer_1.6.133/``).

- Run the command |FLASH_COMMAND_LINE|.

Set up the logs output:

- Get the COM port where your board is connected 
  (if you are using Windows, you can open your Device Manager from the Windows menu).
- Set up a serial terminal (e.g. Termite) to see output logs from the board.
  Refer to the NXP i.MXRT1170 EVKB :ref:`sdk_6_getting_started_rt1170_hardware_setup` to setup the serial terminal.
- Press the board's reset button.
- Get your board's IP address. You will find it in the logs output:

   .. figure:: images/multiSandbox/iMXRT1170/getting-started-imxrt1170-termite-green-fw-output.png
      :alt: Logs Output on Termite Serial Terminal
      :align: center
      :scale: 60%

Congratulations! The Multi-Sandbox Executable is running on the NXP i.MXRT1170 Evaluation Kit and is ready to be used.

Training Course
===============

.. _training_multisandbox_applications_imxrt1170_run_demo_sandboxed_apps:

Run the Demo-Sandboxed-Applications
-----------------------------------

The |DEMO_SANDBOXED_APPS_SOURCES_LINK| 
showcases the communication between Sandboxed Applications using the Shared Interfaces.

The following projects are provided:

- :guilabel:`app-power-provider`: application responsible for providing random power values in the system.
- :guilabel:`app-gui`: application responsible for visualizing the power values provided by :guilabel:`app-power-provider`.
- :guilabel:`app-mqtt-publisher`: application responsible for publishing the power values provided by :guilabel:`app-power-provider` to an MQTT topic.
- :guilabel:`sharedinterface`: shared library between apps that defines the shared interface for inter-app communication.

.. warning::
   If you are using your own Multi-Sandbox Executable to run this demo, make sure to configure the
   :ref:`images_heap` size of your Kernel project to the size of your screen.
   The formula to compute the required size is ``SCREEN_WIDTH x SCREEN_HEIGHT x BPP / 2``.
   
   Example with a 1280x720 screen in RGB565 format (16BPP).
   Images Heap size should be:

      - 1280x720x16/2 = 1843200 bytes

Import the Project
~~~~~~~~~~~~~~~~~~

Import the project into your IDE:

.. note::
  
   If you are using an IDE other than Android Studio, please have a look at :ref:`sdk_6_import_project` section.

* If you are on the Welcome Screen, click on the :guilabel:`Open` button. Otherwise click either on :guilabel:`File` > :guilabel:`Open...`.
* Select the :guilabel:`Demo-Sandboxed-Applications` directory located where you downloaded it and click on the :guilabel:`OK` button.

The Gradle project should now be imported in Android Studio, your workspace contains the following project in the :guilabel:`Projects` view: 

   .. figure:: images/multiSandbox/getting-started-demo-sandboxed-applications-project.png
      :alt: Workspace view
      :align: center
      :scale: 70%

Run the Demo-Sandboxed-Applications on the Virtual Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In order to execute the applications on the Virtual Device, use the Gradle :guilabel:`runOnSimulator`
task:

* Double-click on the :guilabel:`runOnSimulator` task of one the applications (:guilabel:`app-gui`, :guilabel:`app-power-provider`, :guilabel:`app-mqtt-publisher`):

   .. figure:: images/multiSandbox/getting-started-runOnSimulator-demo-sandboxed-applications.png
      :alt: runOnSimulator task
      :align: center

.. note::
  
   Each application is bound to each other. Running one of the applications on the Simulator will run all the applications.

The Virtual Device starts and executes the Demo-Sandboxed-Applications:

.. raw:: html

        <div class="figure align-center">
                <video width="640" height="360" controls="controls" >
                        <source src="https://repository.microej.com/packages/videos/DEV-M0127_VID_Demo-Sandboxed-Applications_NXP_i.MXRT1170_SIM_20241127.webm" type="video/webm">
                </video>
        </div>

Run the Demo on the NXP i.MXRT1170 Evaluation Kit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :guilabel:`Demo-Sandboxed-Applications` applications can be deployed on the NXP i.MXRT1170 Evaluation Kit using the ``localDeploy`` tool.
Each application needs to be deployed individually.

Configure the ``localDeploy`` tool in the project:

* Open the ``gradle.properties`` file located at the root of the :guilabel:`Demo-Sandboxed-Applications` project.
* Get your board's IP address and add it to the ``ipAddress`` field.

Open the Gradle tasks view to deploy the applications on your NXP i.MXRT1170 Evaluation Kit.
Deploy them in the following order:

1. Deploy :guilabel:`app-power-provider`: double-click on the :guilabel:`app-power-provider > Tasks > microej > localDeploy` task.
2. Deploy :guilabel:`app-gui`: double-click on the :guilabel:`app-gui > Tasks > microej > localDeploy` task.
3. Deploy :guilabel:`app-mqtt-publisher`: double-click on the :guilabel:`app-mqtt-publisher > Tasks > microej > localDeploy` task. 

The applications are running on the NXP i.MXRT1170 Evaluation Kit:

.. raw:: html

        <div class="figure align-center">
                <video width="640" height="360" controls="controls" >
                        <source src="https://repository.microej.com/packages/videos/DEV-M0127_VID_Demo-Sandboxed-Applications_NXP_i.MXRT1170_EMB_20241127.webm" type="video/webm">
                </video>
        </div>

Subscribe to the MQTT Topic to Get the Power Values
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, the :guilabel:`app-mqtt-publisher` publishes the power values
to a public MQTT Broker: ``test.mosquitto.org``.

The MQTT topic is randomly generated at each application startup.
It can be seen in the console logs:

   .. figure:: images/multiSandbox/getting-started-demo-sandboxed-applications-mqtt-topic.png
      :alt: MQTT topic
      :align: center
      :scale: 70%

Use an MQTT client to subscribe to the topic, for example, using Docker:

.. code-block::

   docker run -it --rm eclipse-mosquitto mosquitto_sub -h test.mosquitto.org -p 1883 -q 1 -t microej/demo/sandbox/power_[YOUR_TOPIC_ID]

Every time a power value is published, it can be seen in the MQTT client console:

   .. figure:: images/multiSandbox/getting-started-demo-sandboxed-applications-mqtt-subscribe.png
      :alt: MQTT topic
      :align: center
      :scale: 70%


Managing Applications Lifecycle
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Multi-Sandbox Executable provides a web server
to interact with the applications. Either through a Web UI or an HTTP API.
This server listens on port ``4001`` by default.

The Server URL can be seen in the console logs:

   .. figure:: images/multiSandbox/getting-started-hokapp-ip.png
      :alt: MQTT topic
      :align: center
      :scale: 70%

Open the URL in a web browser, the installed applications can be seen. 
They can be ``Started / Stopped / Uninstalled``:

   .. figure:: images/multiSandbox/getting-started-hokapp-webui.png
      :alt: Hokapp WebUI
      :align: center
      :scale: 70%


.. figure:: images/well-done-mascot.png
   :alt: Well Done
   :align: center
   :scale: 70%

Well Done!
-----------

Now you know how to run Sandboxed Applications on a Multi-Sandbox Executable!

The next step is about creating a Sandboxed Application project from scratch and
running it on the Virtual Device and on the NXP i.MXRT1170 board.

.. _training_multisandbox_applications_imxrt1170_create_app:

Create and Run a Sandboxed Application
--------------------------------------

Create the Sandboxed Application Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::
  
   If you are using an IDE other than IntelliJ IDEA, please have a look at :ref:`sdk_6_create_project` section.

Create a new Sandboxed Application project as follows in IntelliJ IDEA:

- Click on :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`.
- Select :guilabel:`MicroEJ`.
- Fill in the name of the project in the :guilabel:`Name` field.
- Select the location of the project in the :guilabel:`Location` field.
- Select the :guilabel:`Application` project type.
- Fill the version of the artifact to publish in the :guilabel:`Version` field.
- Fill the group of the artifact to publish in the :guilabel:`Group` field.
- Fill the name of the artifact to publish in the :guilabel:`Artifact` field.
- Keep the default JDK in the :guilabel:`JDK` field.

   .. figure:: images/intelliJ/intellij-create-project.png
      :alt: Project Creation in IntelliJ IDEA
      :align: center
      :scale: 70%

- Click on the :guilabel:`Create` button. The new project is created and opened:

.. figure:: images/intelliJ/intellij-new-project.png
      :alt: New in IntelliJ IDEA
      :align: center
      :scale: 70%

.. _training_multisandbox_applications_imxrt1170_run_virtual_device:

Run the Sandboxed Application on the Virtual Device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MicroEJ provides `ready to use kernels on the Developer Repository <https://forge.microej.com/ui/repos/tree/General/microej-developer-repository-release/com/microej/kernel>`__.

The :guilabel:`MyApplication` project needs to be configured to use a kernel:

- Open the ``build.gradle.kts`` file of the :guilabel:`MyApplication` project.
- Add the dependency to the NXP i.MXRT1170 kernel: |GREEN_KERNEL_DEPENDENCY|

.. note::
   To use your own Kernel, refer to the
   procedure described in :ref:`sdk_6_getting_started_rt1170_kernel_green_run_application`.

In order to execute the :guilabel:`MyApplication` project on the Virtual Device, the SDK provides the Gradle :guilabel:`runOnSimulator` task. 

.. note::
  
   If you are using an IDE other than IntelliJ IDEA, please have a look at :ref:`sdk_6_run_on_simulator` section.

* Double-click on the :guilabel:`runOnSimulator` task in the Gradle tasks view. It may take a few seconds to start:

   .. figure:: images/multiSandbox/getting-started-runOnSimulator.png
      :alt: runOnSimulator task
      :align: center
      :scale: 70%

The Virtual Device starts and executes the :guilabel:`MyApplication` project.
The ``Hello World!`` message can be seen in the console:

   .. figure:: images/multiSandbox/iMXRT1170/getting-started-imxrt1170-myapplication-sim.png
      :alt: Virtual Device
      :align: center
      :scale: 70%

Run the Sandboxed Application on the NXP i.MXRT1170 Evaluation Kit
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Multi-Sandbox Executable embeds a server that listens for Sandboxed Applications deployment commands.

The :guilabel:`MyApplication` project can be deployed on the NXP i.MXRT1170 Evaluation Kit using the ``localDeploy`` tool.
This tool will deploy the application on the NXP i.MXRT1170 Evaluation Kit through your local network.

Configure the ``localDeploy`` tool in :guilabel:`MyApplication` project:

- Open the ``build.gradle.kts`` file of the :guilabel:`MyApplication` project.
- Paste the following code at the beginning of the file:

   .. code-block:: kotlin

      import com.microej.gradle.tasks.BuildFeatureTask
      import okhttp3.MediaType.Companion.toMediaType
      import okhttp3.MultipartBody
      import okhttp3.OkHttpClient
      import okhttp3.Request
      import okhttp3.RequestBody.Companion.asRequestBody
      import java.util.*

- Paste the following code at the end of the file:

   .. code-block:: kotlin

      val buildFeatureTask = tasks.withType(BuildFeatureTask::class).named("buildFeature")
      tasks.register("localDeploy") {
      dependsOn("buildFeature")
      group = "microej"

      // Adjust the following variables to your needs
      val boardIP = "<Board IP Address>" // board ip address
      val boardPort = 4001 // AppConnect port
      val force = true // overwrote existing app with same name
      val start = true // start app after install
      // Note: if your metadata (feature.kf) is part of '/src/main/resources', modify this path accordingly
      val featureKFFilePath = "generated/microej-app-wrapper/feature-resources/feature.kf"

      doLast {
         val applicationFOFile = buildFeatureTask.get().featureFile.get().asFile
         val properties = Properties()
         project.layout.buildDirectory.file(featureKFFilePath).get().asFile.inputStream().use(properties::load)
         val appName = properties.getProperty("name") ?: error("App name not found in $featureKFFilePath")
         val appVersion = properties.getProperty("version") ?: error("App version not found in $featureKFFilePath")

         println("Deploying app $appName $appVersion to board at $boardIP:$boardPort")
         val url = "http://$boardIP:$boardPort/api/app/install?force=$force&start=$start&name=$appName"
         val client = OkHttpClient()
         val multipartBody = MultipartBody.Builder().setType(MultipartBody.FORM) //
            .addFormDataPart(
            "binary",
            applicationFOFile.name,
            applicationFOFile.asRequestBody("application/octet-stream".toMediaType())
            )//
            .build()
         val request = Request.Builder().url(url).post(multipartBody).build()
         client.newCall(request).execute().use { response ->
            if (response.isSuccessful) {
            println("Deployment Successful! Response Code: ${response.code}")
            println("App info: ${response.body?.string()}")
            } else {
            System.err.println("Deployment Failed. Response Code: ${response.code}")
            System.err.println("Cause: ${response.body?.string()}")
            }
         }
      }
      }

      buildscript {
      repositories {
         maven {
            name = "mavenCentral"
            url = uri("https://repo.maven.apache.org/maven2/")
         }
      }
      dependencies {
         classpath("com.squareup.okhttp3:okhttp:4.12.0")
      }
      }


- Update the ``boardIP`` variable with your board IP address.
- Reload the Gradle project:

   .. figure:: images/multiSandbox/getting-started-reload-gradle-project.png
      :alt: Virtual Device
      :align: center
      :scale: 70%

- A :guilabel:`localDeploy` task is now visible in the :guilabel:`microej` tasks list.
- Double-click on the :guilabel:`localDeploy` task to deploy :guilabel:`MyApplication` on the board.
- :guilabel:`MyApplication` is successfully deployed and the ``Hello World!`` is displayed
  in the serial terminal: 

   .. figure:: images/multiSandbox/iMXRT1170/getting-started-imxrt1170-termite-myapplication-output.png
      :alt: Virtual Device
      :align: center
      :scale: 70%

.. note::
   If you update your application, just run the :guilabel:`localDeploy` task again to test the
   updated application on your board!

.. figure:: images/well-done-mascot.png
   :alt: Well Done
   :align: center
   :scale: 70%

Well Done!
-----------

Now you know how to create a Sandboxed Application project from scratch and
run it on your device!

Going Further
-------------

You have now successfully executed Sandboxed Applications on an embedded device, so what's next?

If you are a Kernel Developer, you can follow the
:ref:`trainings_kernel` courses to get familiar with Kernel development.

If you are an application developer, you can continue to explore MicroEJ's APIs and functionalities by running and studying our samples at GitHub:

.. list-table::
   :widths: 33 33 33

   * - Foundation Libraries
     - Eclasspath
     - IoT
   * - This project gathers all the basic examples of the foundation libraries. 
     - This project gathers all the examples of eclasspath. 
     - This project gathers simple applications using net libraries. 
   * - https://github.com/MicroEJ/Example-Foundation-Libraries
     - https://github.com/MicroEJ/Example-Eclasspath
     - https://github.com/MicroEJ/Example-IOT

You can also learn how to build bigger and better applications by reading our :ref:`Application Developer Guide <application-developer-guide>`.

If you are an embedded engineer, you could look at our VEE port examples at `GitHub <https://github.com/microej?q=vee&type=all&language=&sort=>`_. And to learn how create custom VEE ports, you can read our :ref:`VEE Porting Guide <vee-porting-guide>`.

You can also follow the :ref:`Kernel Developer Guide <kernel-developer-guide>` for more information on our multi-application framework or read about our powerful wearable solution called :ref:`VEE Wear <vee-wear>`.

Last but not least, you can choose to learn about specific topics by following one of our many :ref:`trainings` ranging from how to easily debug applications to setting up a Continuous Integration process and a lot of things in between.

..
   | Copyright 2024-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.