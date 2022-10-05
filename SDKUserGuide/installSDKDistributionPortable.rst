.. _sdk_installation_portable:

Install Portable SDK Distribution 
---------------------------------

- Download the portable package:

.. list-table::
   :widths: 10 5 30 30 30 30 10

   * - **SDK Distribution**
     - **JDK Version**
     - **Windows**
     - **Linux**
     - **macOS x86_64 (Intel chip)**
     - **macOS aarch64 (M1 chip)**
     - **Eclipse Version**
   * - ``22.06``
     - ``11``
     - `Download Portable for Windows <https://repository.microej.com/packages/SDK/22.06/zip/microej-sdk-22.06-win_x86_64.zip>`__
     - `Download Portable for Linux <https://repository.microej.com/packages/SDK/22.06/zip/microej-sdk-22.06-linux_x86_64.zip>`__
     - `Download Portable for macOS Intel <https://repository.microej.com/packages/SDK/22.06/zip/microej-sdk-22.06-macosx_x86_64.zip>`__
     - `Download Portable for macOS M1 <https://repository.microej.com/packages/SDK/22.06/zip/microej-sdk-22.06-macosx_aarch64.zip>`__
     - ``2022-03``
   * - ``21.11``
     - ``8``
     - `Download Portable for Windows <https://repository.microej.com/packages/SDK/21.11/zip/microej-sdk-21.11-win_x86_64.zip>`__
     - `Download Portable for Linux <https://repository.microej.com/packages/SDK/21.11/zip/microej-sdk-21.11-linux_x86_64.zip>`__
     - `Download Portable for macOS Intel <https://repository.microej.com/packages/SDK/21.11/zip/microej-sdk-21.11-macosx_x86_64.zip>`__
     - `N/A`
     - ``2020-06``

- Extract the zip file in the directory of your choice
- Edit ``MicroEJ-SDK.ini`` file
- Configure the path to the compatible JDK version by adding the option ``-vm`` at the beginning of the file:

  .. code-block::
     :emphasize-lines: 1,2
     
      -vm
      [path_to_jdk]/bin
      -startup
      plugins/org.eclipse.equinox.launcher_1.6.400.v20210924-0641.jar
      ...
- Execute ``MicroEJ-SDK.exe`` on Windows or ``MicroEJ-SDK`` on Linux or macOS to start the SDK.

Now you can check if there is a newer SDK version available (see :ref:`sdk_update` section).

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
