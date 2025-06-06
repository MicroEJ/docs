.. _sdk_6_licenses:

Licenses
========

.. _sdk6_eula:

SDK EULA
--------

MICROEJ SDK is licensed under the `SDK End User License Agreement (EULA) <https://repository.microej.com/licenses/sdk/LAW-0011-LCS-MicroEJ_SDK-EULA-v3.1C.txt>`_. The following figure shows a detailed view of the elements.

.. figure:: images/sdk_6_content.png
   :alt: SDK Detailed View
   :align: center
   :scale: 100%

   SDK Detailed View

.. _commercial_component_license:

Commercial Component License
----------------------------

One of the main features of MICROEJ SDK is to download, install and link modules with MICROEJ VEE to produce a binary Executable for a target device.
Modules provided by MicroEJ Corp. are hosted in various :ref:`repositories <module_repositories>`, each distributed under specific license terms detailed in its respective ``LICENSE.txt`` file.
Some of these modules are licensed under the `Commercial Component License <https://repository.microej.com/licenses/sdk/LAW-0988-LCS-CommercialComponents-1.1-A.txt>`_.
The Commercial Component license extends the SDK EULA terms by adding specific requirements and restrictions related to production deployment.

.. _sdk6_license_manager:

License Manager Overview
------------------------

Architectures are distributed in two different versions:

- Evaluation Architectures, associated with a software license key. They can be downloaded at `<https://repository.microej.com/modules/com/microej/architecture/>`_.
- Production Architectures, associated with a hardware license key stored on a USB dongle. They can be requested to :ref:`our support team <get_support>`.

The license manager is provided with Architectures and then integrated into VEE Ports.

License Check
-------------

The table below summarizes where the license is checked.

.. list-table::
   :widths: 30 10 10 20

   * - **Application**
     - **Run on Simulator**
       **(Virtual Device)**
     - **Build on Device**
     - **Documentation Link**
   * - Application containing a Java main class
     - NO
     - **YES**
     - :ref:`sdk_6_run_on_device`
   * - Application containing a Feature class
     - NO
     - NO
     - :ref:`application_link`

.. _sdk_6_eula_acceptation:

SDK EULA Acceptation
--------------------

The use of MICROEJ SDK 6 requires to accept the :ref:`sdk6_eula`.
If the SDK EULA is not accepted, the following message is displayed when executing a Gradle task:

.. code:: text

  > The MICROEJ SDK End-User License Agreement (EULA) must be accepted before it can start.
    The license terms for this product can be downloaded from
    https://repository.microej.com/licenses/sdk/LAW-0011-LCS-MicroEJ_SDK-EULA-v3.1C.txt
    You can accept the EULA by setting the system property systemProp.accept-microej-sdk-eula-v3-1c=YES in a gradle.properties file
          - in your Gradle User Home folder ($USER_HOME/.gradle/),
          - or in the root folder of your project,
    or specifying the -Daccept-microej-sdk-eula-v3-1c=YES command line option, 
    or setting the ACCEPT_MICROEJ_SDK_EULA_V3_1C=YES environment variable.

As mentioned in the message, there are several ways to accept the SDK EULA:

- define the ``accept-microej-sdk-eula-v3-1c`` system property in a ``gradle.properties`` file with the ``systemProp.`` prefix:

   .. code:: properties

      systemProp.accept-microej-sdk-eula-v3-1c=YES

  This can be in the ``gradle.properties`` of your Gradle User Home folder (located by default at ``$USER_HOME/.gradle/gradle.properties``),
  or in the ``gradle.properties`` file at the root of your project for example.

- define the ``accept-microej-sdk-eula-v3-1c`` system property in the command line:

   .. code:: console
      
      ./gradlew build -Daccept-microej-sdk-eula-v3-1c=YES

- set the ``ACCEPT_MICROEJ_SDK_EULA_V3_1C`` environment variable to ``YES``.

.. _sdk6_evaluation_license:

Evaluation Licenses
-------------------

This section should be considered when using Evaluation Architectures, which
use software license keys. A machine UID needs to be provided
to activate an Evaluation license on the MicroEJ Licenses Server. The machine UID is a 16 hexadecimal digits number.

Get your Machine UID
~~~~~~~~~~~~~~~~~~~~

If your VEE Port is :ref:`defined <sdk_6_select_veeport>` in the ``build.gradle.kts`` of your project,
the machine UID will be displayed when building an :ref:`Executable <sdk_6_build_executable>`.

.. code-block:: console
   :emphasize-lines: 1

   [INFO ] Launching in Evaluation mode. Your UID is XXXXXXXXXXXXXXXX.
   [ERROR] Invalid license check (No license found).

.. _sdk6_evaluation_license_request_activation_key:

Request your Activation Key
~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Go to MicroEJ Licenses Server https://license.microej.com.
- Click on :guilabel:`Create a new account` link.
- Create your account with a valid email address. You will receive a confirmation email a few minutes after. Click on the confirmation link in the email and log in with your new account.
- Click on :guilabel:`Activate a License`.
- Set :guilabel:`Product P/N:` to ``9PEVNLDBU6IJ``.
- Set :guilabel:`UID:` to the machine UID you copied before.
- Click on :guilabel:`Activate`.
- The license is being activated. You should receive your activation by email in less than 5 minutes. If not, please contact :ref:`our support team <get_support>`.
- Once received by email, save the attached zip file that contains your activation key.

.. _sdk6_evaluation_license_install_license_key:

Install the License Key
~~~~~~~~~~~~~~~~~~~~~~~

The license key zip file must be simply dropped to the ``~/.microej/licenses/`` directory (create it if it doesn't exist).

.. figure:: images/user_license_folder.png
   :alt: MicroEJ Shared Licenses Directory
   :align: center

   MicroEJ Shared Licenses Directory

.. _sdk6_evaluation_license_check:

Check Activation
~~~~~~~~~~~~~~~~

This section contains instructions that will allow you to verify that your Evaluation license has been properly installed.

.. note::
   
   The command line tool requires :ref:`Architecture 8.3.0 <changelog-8.3.0>` or higher. 

To get more details on installed Evaluation licenses, proceed with the following steps:

#. Open a terminal.
#. Change directory to an Evaluation VEE Port.
#. Execute the command:
   
   .. code:: console

      java -Djava.library.path=resources/os/[OS_NAME] -jar licenseManager/licenseManagerKeyHardware.jar

   with ``OS_NAME`` set to ``Windows64`` for Windows OS, ``Linux64`` for Linux OS, ``Mac`` for macOS x86_64 (Intel chip) or ``MacA64`` for macOS aarch64 (M1 chip).

   You should get something similar to the following output:
   
   .. code:: console

      [DEBUG] ===== MicroEJ Evaluation License Debug Tool =====
      [DEBUG] => UID: 39B7C108972A5C36.
      [DEBUG] => Please specify a license directory containing 'keysHardware.txt'

   This step is sufficient if you want to check the machine's UID. 
   For an analysis of the available licenses, proceed with the following steps.

#. :ref:`Build your Executable <sdk_6_build_executable>` with verbose mode enabled.
#. Retrieve in the logs the path to the licenses directory by searching for ``-Dlicenses.working.dir=[path_to_license_dir]``.
#. Execute the same command than before with the path to the licenses directory as argument:
   
   .. code:: console

      java -Djava.library.path=resources/os/[OS_NAME] -jar licenseManager/licenseManagerKeyHardware.jar [path_to_license_dir]

   You should get something similar to the following output:

   .. code:: console

      [DEBUG] ===== MicroEJ Evaluation License Debug Tool =====
      [DEBUG] => UID: 39B7C108972A5C36.
      [DEBUG] => Detected MicroEJ License HQB48-VCQDQ-I7QDL-IAZUF - valid until YYYY-MM-DD.
      [DEBUG] ===== SUCCESS =====

   Now the list of detected licenses and their validity are dumped.

.. _sdk6_evaluation_license_troubleshooting:

Troubleshooting
~~~~~~~~~~~~~~~

Machine UID has changed
"""""""""""""""""""""""

This can occur when the hardware configuration of the machine is changed (especially when the network interfaces have changed).

In this case, you can either request a new activation key for this new UID or go back to the previous hardware configuration.

.. _sdk6_production_license:

Production Licenses
-------------------

This section should be considered when using Production Architectures,
which use hardware license keys stored on a USB dongle.

.. figure:: images/dongle/dongle.jpg
   :alt: MicroEJ USB Dongle
   :align: center
   :scale: 30%

   MicroEJ USB Dongle

.. note :: 

   If your USB dongle has been provided to you by your sales representative and you don't have received an activation certificate by email, it may be a pre-activated dongle.
   Then you can skip the activation steps and directly jump to the :ref:`production_license_check` section.

Request your Activation Key
~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Go to `license.microej.com <https://license.microej.com/>`_.
- Click on :guilabel:`Create a new account` link.
- Create your account with a valid email address. You will receive a confirmation email a few minutes after. Click on the confirmation link in the email and login with your new account.
- Click on :guilabel:`Activate a License`.
- Set :guilabel:`Product P/N:` to **The P/N on the activation certificate**.
- Enter your UID: serial number printed on the USB dongle label (8 alphanumeric char.).
- Click on :guilabel:`Activate` and check the confirmation message.
- Click on :guilabel:`Confirm your registration`.
- Enter the **Registration Code provided on the activation certificate**.
- Click on :guilabel:`Submit`.
- Your Activation Key will be sent to you by email as soon as it is available (12 business hours max.).

.. note:: 
   
   You can check the :guilabel:`My Products` page to verify your product registration status, the Activation Key availability, and download the Activation Key when available.

Once the Activation Key is available, download and save the Activation Key ZIP file to a local directory.

.. _sdk6_production_license_activate:

Activate your USB Dongle
~~~~~~~~~~~~~~~~~~~~~~~~

This section contains instructions that will allow you to flash your
USB dongle with the proper activation key.

You shall ensure that the following prerequisites are met :

-  Your :ref:`operating system <system-requirements>` is Windows 

-  The USB dongle is plugged and recognized by your operating system
   (see :ref:`production_license_troubleshooting` section)

-  No more than one USB dongle is plugged into the computer while running the
   update tool

-  The update tool is not launched from a network drive or a USB
   key

-  The activation key you downloaded is the one for the dongle UID on
   the sticker attached to the dongle (each activation key is tied to
   the unique hardware ID of the dongle).

You can then proceed to the USB dongle update: 

- Unzip the ``Activation Key`` file to a local directory 
- Enter the directory just created by your ZIP extraction tool.
- Launch the executable program.
- Accept running the unsigned software if requested (Windows 10/11)
  
  .. figure:: images/dongle/updateWarningUnknownPublisher.png
     :scale: 80%    

- Click on the :guilabel:`Update` button (no password needed)

  .. figure:: images/dongle/updateTool.png
     :alt: Dongle Update Tool

     Dongle Update Tool

- On success, an ``Update successfully`` message shall appear. On failure, an
  ``Error key or no proper rockey`` message may appear.

  .. figure:: images/dongle/updateSuccessful.png
     :alt: Successful dongle update

     Successful Dongle Update

.. _sdk6_production_license_check:

Check Activation
~~~~~~~~~~~~~~~~

This section contains instructions that will allow you to verify that your USB dongle has been properly activated.

To get more details on connected USB dongle(s), run the debug tool as following:

#. Open a terminal.
#. Change directory to a Production VEE Port.
#. Execute the command:
   
.. tabs::

   .. tab:: Architecture v8.1.0 or higher
   
      .. code:: console

            java -Djava.library.path=resources/os/[OS_NAME] -jar licenseManager/licenseManagerProduct.jar

   .. tab:: Architecture v8.0.0 or lower 

      .. code:: console

            java -Djava.library.path=resources/os/[OS_NAME] -jar licenseManager/licenseManagerUsbDongle.jar

with ``OS_NAME`` set to ``Windows64`` for Windows OS, ``Linux64`` for Linux OS, ``Mac`` for macOS x86_64 (Intel chip) or ``MacA64`` for macOS aarch64 (Apple Silicon chip).

If your USB dongle has been properly activated, you should get the following output:
   
   .. code:: console

      [DEBUG] ===== MicroEJ Dongle Debug Tool =====
      [DEBUG] => Detected dongle UID: XXXXXXXX.
      [DEBUG] => Dongle UID has valid MicroEJ data: XXXXXXXX (only the first one is listed).
      [DEBUG] => Detected MicroEJ License XXXXX-XXXXX-XXXXX-XXXXX - valid until YYYY-MM-DD.
      [DEBUG] ===== SUCCESS =====


.. _sdk6_production_license_linux:

USB Dongle on GNU/Linux
~~~~~~~~~~~~~~~~~~~~~~~

For GNU/Linux Users (Ubuntu at least), by default, the dongle access has not been granted to the user, you have to modify udev rules.
Please create a ``/etc/udev/rules.d/91-usbdongle.rules`` file with the following contents:

::

   ACTION!="add", GOTO="usbdongle_end"
       SUBSYSTEM=="usb", GOTO="usbdongle_start"
       SUBSYSTEMS=="usb", GOTO="usbdongle_start"
       GOTO="usbdongle_end"
       
       LABEL="usbdongle_start"
       
       ATTRS{idVendor}=="096e" , ATTRS{idProduct}=="0006" , MODE="0666"
       
       LABEL="usbdongle_end"

Then, restart udev: ``sudo /etc/init.d/udev restart``

You can check that the device is recognized by running the ``lsusb`` command.
The output of the command should contain a line similar to the one below for each dongle:
``Bus 002 Device 003: ID 096e:0006 Feitian Technologies, Inc.``

.. _sdk6_production_license_docker_linux:

USB Dongle with Docker on Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you use the `SDK Docker image <https://hub.docker.com/r/microej/sdk>`__ on a Linux host to build an Executable, 
the dongle must be mapped to the Docker container.
First, it requires to add a symlink on the dongle by following the instructions of the :ref:`production_license_linux` section but
with this ``/etc/udev/rules.d/91-usbdongle.rules`` file:

::

   ACTION!="add", GOTO="usbdongle_end"
       SUBSYSTEM=="usb", GOTO="usbdongle_start"
       SUBSYSTEMS=="usb", GOTO="usbdongle_start"
       GOTO="usbdongle_end"
       
       LABEL="usbdongle_start"
       
       ATTRS{idVendor}=="096e" , ATTRS{idProduct}=="0006" , MODE="0666" , SYMLINK+="microej_dongle"
       
       LABEL="usbdongle_end"

Then the symlink has to be mapped in the Docker container by adding the following option in the Docker container creation command line:

::

   --device /dev/microej_dongle:/dev/bus/usb/999/microej_dongle

The ``/dev/microej_dongle`` symlink can be mapped to any device path as long as it is in ``/dev/bus/usb``.

USB Dongle with WSL
~~~~~~~~~~~~~~~~~~~

.. note::
   The following steps have been tested on WSL2 with Ubuntu 22.04.2 LTS.

To use a USB dongle with WSL, you first need to install `usbipd` following the steps described in `Microsoft WSL documentation <https://learn.microsoft.com/en-us/windows/wsl/connect-usb#install-the-usbipd-win-project>`__:

First, check that WSL2 is installed on your system. If not, install it or update it following `Microsoft Documentation <https://learn.microsoft.com/en-us/windows/wsl/install>`__

Then, you need install usbipd-win v4.0.0 or higher on Windows from `usbipd-win Github repository <https://github.com/dorssel/usbipd-win/releases>`__.

And then, install usbipd and update hardware database inside you WSL installation:

   .. code-block:: console

      sudo apt install linux-tools-generic hwdata
      sudo update-alternatives --install /usr/local/bin/usbip usbip /usr/lib/linux-tools/*-generic/usbip 20

Add the udev rule described in :ref:`production_license_linux`, and restart udev:

   .. code-block:: console

      sudo /etc/init.d/udev restart

Ensure your USB dongle is plugged, then start a PowerShell terminal in administrator mode.

List the connected devices with the following command:

  .. code-block:: console

      usbipd.exe list

You should see your USB dongle connected with ``VID:PID==096e:0006``:

.. code-block:: console   
   :emphasize-lines: 9

      PS C:\Users\user> usbipd list
      Connected:
      BUSID  VID:PID    DEVICE                                                        STATE
      2-6    0c45:674c  Integrated Webcam, Integrated IR Webcam, USB DFU              Not shared
      2-8    0a5c:5843  Dell ControlVault w/ Fingerprint Touch Sensor, Microsoft ...  Not shared
      2-10   8087:0033  Intel(R) Wireless Bluetooth(R)                                Not shared
      3-1    0bda:8153  Realtek USB GbE Family Controller                             Not shared
      4-6    413c:c010  Dell DA310                                                    Not shared
      6-4    096e:0006  USB Input Device                                              Not shared
      6-6    046d:0819  USB Video Device, USB Audio Device                            Not shared
      7-1    045e:0084  USB Input Device                                              Not shared
      7-2    04d9:1400  USB Input Device                                              Not shared
      7-3    10d5:55a2  USB Input Device                                              Not shared

Here the ``BUSID`` is ``6-4``.

Bind and attach the dongle to WSL:

  .. code-block:: console

      usbipd.exe bind --busid <BUSID>
      usbipd.exe attach --wsl  --busid <BUSID>

Open a bash terminal in your WSL instance, and check the USB dongle is successfully mounted with the following command:

  .. code-block:: console

      lsusb

You should see your USB dongle connected with ``ID 096e:0006``:

.. code-block:: console
   :emphasize-lines: 2

      Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
      Bus 001 Device 002: ID 096e:0006 Feitian Technologies, Inc. HID Dongle (for OEMs - manufacturer string is "OEM")
      Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

.. note::

      You'll need to follow these steps each time you system is rebooted or the dongle is plugged/unplugged.

.. _sdk6_production_license_troubleshooting:

Troubleshooting
~~~~~~~~~~~~~~~

This section contains instructions to check that your
operating system correctly recognizes your USB dongle.

Windows Troubleshooting
"""""""""""""""""""""""

- If the :ref:`dongle activation <production_license_activate>` failed with ``No rockey`` message, check there is one and only one dongle recognized with the following hardware ID :

  ::

     HID\VID_096E&PID_0006&REV_0201

  Go to the :guilabel:`Device Manager` > :guilabel:`Human Interface Devices` and
  check among the :guilabel:`USB Input Device` entries that the
  :guilabel:`Details` > :guilabel:`Hardware Ids` property match the ID mentioned before.


- If the :ref:`dongle activation <production_license_activate>` was successful with ``Update successfully`` message but the license does not appear in the SDK or is not updated, 
  try to activate again by starting the executable with administrator privileges:

  .. figure:: images/dongle/runAsAdministrator.png

- If the following error message is thrown when building an Executable, either the dongle plugged is a verbatim dongle or it has not been successfully :ref:`activated <production_license_activate>`:

  .. code-block:: console

     Invalid license check (Dongle found is not compatible).

VirtualBox Troubleshooting
""""""""""""""""""""""""""

In a VirtualBox virtual machine, USB drives must be enabled to be recognized correctly.
Make sure to enable the USB dongle by clicking on it in the VirtualBox menu :guilabel:`Devices` > :guilabel:`USB`.

To make this setting persistent, go to :guilabel:`Devices` > :guilabel:`USB` > :guilabel:`USB Settings...`
and add the USB dongle in the :guilabel:`USB Devices Filters` list.

WSL Troubleshooting
"""""""""""""""""""

Check that your dongle is attached to WSL from PowerShell:

  .. code-block:: console

      usbipd.exe list

You should have a  line saying ``Attached - Ubuntu``:

  .. code-block:: console

      PS C:\Users\sdkuser> usbipd.exe list
      BUSID  VID:PID    DEVICE                                                        STATE
      2-1    096e:0006  USB Input Device                                              Attached - Ubuntu
      2-6    0c45:6a10  Integrated Webcam                                             Not attached
      2-10   8087:0026  Intel(R) Wireless Bluetooth(R)                                Not attached
      3-1    045e:0823  USB Input Device                                              Not attached
      3-4    046d:c31c  USB Input Device                                              Not attached

In you WSL console, the dongle must also be recognized. Ckeck by using ``lsusb``:

   .. code-block:: console

      skduser@host:~/workspaces/docs$ lsusb
      Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
      Bus 001 Device 003: ID 096e:0006 Feitian Technologies, Inc. HID Dongle (for OEMs - manufacturer string is "OEM")
      Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

This might not be sufficient. If you're still facing license issues, restart udev, abd attach your dongle to WSL once again.

.. note::
   Hibernation may have unattached your dongle. Reload udev, unplug/plug your dongle and attach it from PowerShell.

Remote USB Dongle Connection
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When the dongle cannot be physically plugged to the machine running the SDK (cloud builds, virtualization, missing permissions, ...),
it can be configured using USB redirection over IP network. 

There are many hardware and software solutions available on the market. Among others, this has been tested with https://www.net-usb.com/ and https://www.virtualhere.com/.
Please contact :ref:`our support team <get_support>` for more details.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
