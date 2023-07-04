.. _sdk_installation_portable:

Install Portable SDK Distribution 
=================================

The portable package allows you to install the SDK Distribution when the use of the SDK Distribution installer is not possible or not desired, for example:

- you do not have administrator privileges on your workstation;
- you want to install SDK Distribution ``23.07`` but JDK 11 is not your default JDK version;
- you want to install SDK Distribution up to ``21.11`` but JDK 8 is not your default JDK version.

Perform the following steps:

- Download the Portable SDK Distribution for your operating system:

.. list-table::
   :widths: 10 5 30 30 30 30

   * - **SDK Distribution**
     - **JDK Version**
     - **Windows**
     - **Linux**
     - **macOS x86_64 (Intel chip)**
     - **macOS aarch64 (M1 chip)** [#warning_architecture_7_18_0]_
   * - ``23.07``
     - ``11``
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/23.07/zip/microej-sdk-23.07-win_x86_64.zip>`__
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/23.07/zip/microej-sdk-23.07-linux_x86_64.zip>`__
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/23.07/zip/microej-sdk-23.07-macosx_x86_64.zip>`__
     - `Portable  (.zip) <https://repository.microej.com/packages/SDK/23.07/zip/microej-sdk-23.07-macosx_aarch64.zip>`__
   * - ``23.02``
     - ``11``
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/23.02/zip/microej-sdk-23.02-win_x86_64.zip>`__
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/23.02/zip/microej-sdk-23.02-linux_x86_64.zip>`__
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/23.02/zip/microej-sdk-23.02-macosx_x86_64.zip>`__
     - `Portable  (.zip) <https://repository.microej.com/packages/SDK/23.02/zip/microej-sdk-23.02-macosx_aarch64.zip>`__
   * - ``21.11``
     - ``8``
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/21.11/zip/microej-sdk-21.11-win_x86_64.zip>`__
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/21.11/zip/microej-sdk-21.11-linux_x86_64.zip>`__
     - `Portable (.zip) <https://repository.microej.com/packages/SDK/21.11/zip/microej-sdk-21.11-macosx_x86_64.zip>`__
     - `N/A`

- Once downloaded, extract the zip file in a local directory of your choice
- Edit the ``MicroEJ-SDK.ini`` file
- Configure the path to the JDK version indicated above by adding the option ``-vm`` at the beginning of the file.
  If you don't have any JDK installed, see the :ref:`get_jdk` section.

  .. code-block::
     :emphasize-lines: 1,2
     
      -vm
      [path_to_jdk]/bin
      -startup
      plugins/org.eclipse.equinox.launcher_1.6.400.v20210924-0641.jar
      ...

   
- Start the SDK by executing ``MicroEJ-SDK.exe`` on Windows or ``MicroEJ-SDK`` on Linux or macOS.

Once the SDK is started, it is recommended to check if updates are available (see :ref:`sdk_update` section).
If your are running SDK on Windows OS, it is also strongly recommended to configure :ref:`Windows defender exclusion rules <sdk_install_troubleshooting_windows>`.

.. [#warning_architecture_7_18_0] SDK Distribution for macOS aarch64 (M1 chip) requires :ref:`Architecture 7.18.0 or higher <changelog-7.18.0>`.
..
   | Copyright 2021-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
