.. _tutorial_create_build_scripts:

Create Platform Build and Run Scripts
=====================================

This tutorial describes all the steps to create platform build and run scripts and shows how to use them.

Intended Audience
-----------------

The audience for this document is Platform engineers who want to

- validate their platform using MicroEJ test suites
- configure a full :ref:`BSP connection<bsp_connection>` with their platform
- ease application development by removing the link to the BSP

Prerequisites
-------------

This tutorial is a direct continuation of :ref:`Create a MicroEJ Firmware From Scratch<create_firmware_from_scratch>` tutorial. It should have been completed before starting this one.

Introduction
------------

Build and run scripts are normalized entry points to

- build an application against a platform
- deploy and run the built application on a device.

External tools only need to run these scripts without additional knowledge about the toolchain or deployment tools.

See :ref:`Build Script File and Run Script File<bsp_connection_build_script>` subsections from MicroEJ Platform Creation guide for more information about these scripts. Script examples are provided in `Platform Qualification Tools <https://github.com/MicroEJ/PlatformQualificationTools/tree/master/framework/platform/scripts>`_ repository.

Overview
--------

In  :ref:`Create a MicroEJ Firmware From Scratch<create_firmware_from_scratch>`, the final binary is produced by invoking ``make`` in the FreeRTOS BSP. The command to type is dependant of the toolchain used. The application is then launched in QEMU but could have been instead flashed to a device with another specific command. This tutorial explain how to write `build` and `run` scripts for these two tasks. 

The next sections will

- describe step-by-step how to ceate the build and run scripts both for shell and batch terminals. These scripts automate platform build and firmware execution in QUEMU as presented in :ref:`Create a MicroEJ Firmware From Scratch<create_firmware_from_scratch>` tutorial.
- show a pratical usage of these build and run scipts in a MicroEJ development flow. This will allow to configure Eclipse build the full firmware when building an application.

Create Build and Run Scripts
----------------------------

This section describes how to write build and run scripts.

There are two scripts:

#. ``build.xxx`` which calls the toolchain to build the application executable file. It also ensures that the output file is called ``application.out`` and is located in the directory from where the script was called.
#. ``run.xxx`` which deploys and runs ``application.out`` on the device. In this tutorial, it will only run the application with QEMU instead of flashing it on real hardware.

Each of these scripts come in two flavors: ``.sh`` for unix-like systems, and ``.batch`` for Windows systems.

First, create a ``microej/scripts`` directory in BSP project:

.. code-block:: shell

  $ pwd
  /mnt/c/Users/user/src/tuto-from-scratch/FreeRTOS/FreeRTOS/Demo/CORTEX_LM3S6965_GCC
  $ mkdir microej/scripts

All the script created in the next sections will be put in this directory.

Create `build.sh` and `run.sh` Scripts
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. warning::

  Make sure the build and run scripts have the execution permission.

1. Create a file called ``build.sh`` in the ``microej/scripts`` directory with the following content:

  .. code-block:: shell

    #!/bin/bash

    # Save application current directory and jump one level above scripts
    CURRENT_DIRECTORY=$(pwd)
 
    # Move to the directory where the Makefile is
    cd $(dirname "$0")/../..

    # Build the firmware
    make

    # Copy output the the current directory while renaming it
    cp gcc/RTOSDemo.bin  $CURRENT_DIRECTORY/application.out

    # Restore application directory
    cd $CURRENT_DIRECTORY/

2. Verify that the script succesfully built your firmware and put it in the current directory with the name ``application.out``.

  .. code-block:: shell

    $ pwd
    /mnt/c/Users/user/src/tuto-from-scratch/FreeRTOS/FreeRTOS/Demo/CORTEX_LM3S6965_GCC
    $ make clean
    $ microej/scripts/build.sh
      CC    init/startup.c
      CC    main.c
      CC    ../../Source/list.c
      CC    ../../Source/queue.c
      CC    ../../Source/tasks.c
    [..]
      130 |  __attribute__( ( always_inline ) ) static inline uint8_t ucPortCountLeadingZeros( uint32_t ulBitmap )
          |                                                           ^~~~~~~~~~~~~~~~~~~~~~~
      LD    gcc/RTOSDemo.axf
    $ ls *.out
    application.out

3. Check that ``application.out`` successfully runs with QEMU:

  .. code-block:: shell

    $ qemu-system-arm -M lm3s6965evb -nographic -kernel application.out
    Hello, World! printf function is working.
    Hello World!
    QEMU: Terminated // press Ctrl-a x to end the QEMU session

4. Create a file called ``run.sh`` in the ``microej/scripts`` directory with the following content:

  .. code-block:: shell

    #!/bin/bash

    # Add some text to the console before launch
    echo -e "\033[0;32m## Start application in QEMU."
    echo -e "## Use 'Ctrl-a x' to quit.\e[0m"

    # Launch application with QEMU
    qemu-system-arm -M lm3s6965evb -nographic -kernel application.out

5. We can now run the application we just built with the ``run.sh`` script:

  .. code-block:: shell

    $ pwd
    /mnt/c/Users/user/src/tuto-from-scratch/FreeRTOS/FreeRTOS/Demo/CORTEX_LM3S6965_GCC
    $ microej/scripts/run.sh
    ## Start application in QEMU.
    ## Use 'Ctrl-a x' to quit.
    Hello, World! printf function is working.
    Hello World!

.. note::

  This script is very simple because our application is just run with QEMU instead of a real hardware. To deploy the application on a device, the script would have to setup and call a flash tool. See for instance the build and run scripts for `Espressif-ESP-WROVER-KIT-V4.1 <https://github.com/MicroEJ/Platform-Espressif-ESP-WROVER-KIT-V4.1/blob/1.7.0/ESP32-WROVER-Xtensa-FreeRTOS-bsp/Projects/microej/scripts/build.sh>`_. 

Create `build.bat` and `run.bat` Scripts
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As our toolchain has only be configured for Linux in WSL, we create wrappers that call shell scripts through WSL.

1. Create a file called ``build.bat`` in the ``microej/scripts`` directory with the following content:

  .. code-block:: batch

    @echo off
    SETLOCAL ENABLEEXTENSIONS

    REM Reset ERRORLEVEL between multiple run in the same shell
    SET ERRORLEVEL=0

    REM Save application current directory and jump to scripts directory
    SET CURRENT_DIRECTORY=%CD%
    CD "%~dp0"

    REM Get the script directory in a Unix path format
    FOR /F %%i in ('WSL pwd') DO SET SCRIPT_DIRECTORY=%%i

    REM Restore application directory
    CD %CURRENT_DIRECTORY%

    REM Run the bash build script with WSL
    WSL %SCRIPT_DIRECTORY%/build.sh

    IF %ERRORLEVEL% NEQ 0 (
  	  EXIT /B %ERRORLEVEL%
    )

2. Calling this script in PowerShell should produce the following result:

  .. code-block:: shell

    PS C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC> microej\scripts\build.bat
      CC    init/startup.c
      CC    main.c
      CC    ../../Source/list.c
      CC    ../../Source/queue.c
      CC    ../../Source/tasks.c
     [...]
      CC    microej/src/LLMJVM_stub.c
      LD    gcc/RTOSDemo.axf
    Current DIR /mnt/c/Users/user/src/tuto-from-scratch/FreeRTOS/FreeRTOS/Demo/CORTEX_LM3S6965_GCC/microej/scripts
            1 fichier(s) déplacé(s).

.. note::

  This prints the full build output if it is the first build (or after a ``make clean``) otherwise it prints ``make: Nothing to be done for 'all'``.

3. Create a file called ``run.bat`` in the ``microej/scripts`` directory with the following content:

  .. code-block:: batch

    @echo off
    SETLOCAL ENABLEEXTENSIONS

    REM Reset ERRORLEVEL between multiple run in the same shell
    SET ERRORLEVEL=0

    REM Save application current directory and jump to scripts directory
    SET CURRENT_DIRECTORY=%CD%
    CD "%~dp0"

    REM Get the script directory in a Unix path format
    FOR /F %%i in ('WSL pwd') DO SET SCRIPT_DIRECTORY=%%i

    REM Restore application directory
    CD %CURRENT_DIRECTORY%

    REM Run the bash run script with WSL
    WSL %SCRIPT_DIRECTORY%/run.sh

    IF %ERRORLEVEL% NEQ 0 (
    	EXIT /B %ERRORLEVEL%
    )

4. Calling this script in PowerShell should produce the following result:

  .. code-block:: shell

    C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\application.out
    1 fichier(s) copié(s)
    ## Start application in QEMU.
    ## Use 'Ctrl-a x' to quit.
    Hello, World! printf function is working.
    Hello World!

Use Build and Run Scripts in MicroEJ Application Project
--------------------------------------------------------

In this section, we illustrate how built scripts are used in pratice.

We will first configure Eclipse and the platform to enable full firmware build (build application, build BSP + link to platform) when building `HelloWorld` application from launcher.

We will then configure a full BSP connection. This will remove the need to configure the path of the BSP in the application launcher.

.. note::

    Build and run scripts do not require to configure a full BSP connection. This last part has only be added to finish a MicroEJ Application project independant from the BSP.

Build Firmware at Once from Eclipse 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Right click on the ``HelloWorld`` application project
2. In the menu, select :guilabel:`Run as` > :guilabel:`Run Configurations...`
3. Select the :guilabel:`Configuration` tab
4. Select :guilabel:`Device` > :guilabel:`Deploy` entry in the configurations menu
5. Check :guilabel:`Execute the MicroEJ script (build.bat) at the location known by the 3rd-party BSP project` checkbox

  .. image::  images/configure_build_bat_eclipse.png
    :scale: 80 %

6. Click on the :guilabel:`Run` button. It should print the following:

  .. code-block:: none

    =============== [ Initialization Stage ] ===============
    Platform connected to BSP location 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC' using application option 'deploy.bsp.root.dir'.
    [INFO ] Launching in Evaluation mode. Your UID is 0120202834374C4A.
    =============== [ Launching SOAR ] ===============
    =============== [ Launching Link ] ===============
    =============== [ Deployment ] ===============
    MicroEJ files for the 3rd-party BSP project are generated to 'C:\Users\user\src\tuto-from-scratch\workspace\HelloWorld\com.mycompany.Main\platform'.

    FAIL
    The following error occurred while executing this line:
    C:\Users\user\src\tuto-from-scratch\workspace\lm3s811evb-Platform-CM0_GCC48-0.0.1\source\scripts\deploy.xml:30: The following error occurred while executing this line:
    C:\Users\user\src\tuto-from-scratch\workspace\lm3s811evb-Platform-CM0_GCC48-0.0.1\source\scripts\deployInBSP.xml:97: The following error occurred while executing this line:
    C:\Users\user\src\tuto-from-scratch\workspace\lm3s811evb-Platform-CM0_GCC48-0.0.1\source\scripts\deployInBSP.xml:260: Option 'deploy.bsp.microejscript' is enabled but this Platform does no define a well-known location. Either update the Platform configuration (option 'deploy.bsp.microejscript.relative.dir' in 'bsp/bsp.properties') or disable this option.

7. Edit the file ``bsp/bsp.properties`` as follow:

  .. code-block:: properties

    # Specify BSP external scripts files ('build.bat' and 'run.bat') parent directory.
    # This is a '/' separated directory relative to 'bsp.root.dir'.
    microejscript.relative.dir=microej/scripts

8. Run the `HelloWorld` application once again. This should print the following result:

  .. code-block:: none

    =============== [ Initialization Stage ] ===============
    Platform connected to BSP location 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC' using platform option 'deploy.bsp.root.dir'.
    [INFO ] Launching in Evaluation mode. Your UID is 0120202834374C4A.=============== [ Launching SOAR ] ===============
    =============== [ Launching Link ] ===============
    =============== [ Deployment ] ===============
    MicroEJ files for the 3rd-party BSP project are generated to 'C:\Users\user\Workspaces\_test_fw_tuto\HelloWorld\com.mycompany.Main\platform'.
    The MicroEJ application (microejapp.o) has been deployed to: 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\lib'.
    The MicroEJ platform library (microejruntime.a) has been deployed to: 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\lib'.
    The MicroEJ platform header files (*.h) have been deployed to: 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\inc'.
    Execution of script 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\scripts\build.bat' started...
    LD    gcc/RTOSDemo.axf
    Current DIR /mnt/c/Users/user/Workspaces/_test_fw_tuto/HelloWorld/com.mycompany.Main
    Execution of script 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\scripts\build.bat' done.
    =============== [ Completed Successfully ] ===============

    SUCCESS

Reading the traces, we see that the `HelloWorld` application and the platform MicroEJ Platform library have been deployed to the BSP and the ```build.bat`` script has been called to rebuild the BSP. The output is then ``application.out`` binary that can be flashed on the board (or run on QEMU).

Convert from partial BSP connection to full BSP connection (optional)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this section, we configure the BSP root directory in the platform.

When launching the ``HelloWorld`` application from Eclipse, the launcher knows how to find the BSP because we have configured its path in ``HelloWorld/build/emb.properties`` file which is imported in the launcher.

1. Cut ``deploy.bsp.root.dir`` property value from ``HelloWorld/build/emb.properties`` file configured in :ref:`Create a MicroEJ Firmware From Scratch<create_firmware_from_scratch>` tutorial
2. Paste the value in ``bsp/bsp.properties`` as follow:

  .. code-block:: properties

    # Specify the BSP root directory. Can use ${project.parent.dir} which target the parent of platform configuration project
    # For example, '${workspace}/${project.prefix}-bsp' specifies a BSP project beside the '-configuration' project
    root.dir=[absolute_path] to FreeRTOS\\FreeRTOS\\Demo\\CORTEX_LM3S811_GCC

3. Rebuild your platform with a right-click on the platform project and click on :guilabel:`Build Module`.

The platform is now fully connected to the BSP.
  
4. Launch ``HelloWorld`` project from Eclipse launcher, it should print the following result:

  .. code-block:: none

    =============== [ Initialization Stage ] ===============
    Platform connected to BSP location 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC' using platform option 'root.dir' in 'bsp/bsp.properties'.
    [INFO ] Launching in Evaluation mode. Your UID is 0120202834374C4A.
    =============== [ Launching SOAR ] ===============
    =============== [ Launching Link ] ===============
    =============== [ Deployment ] ===============
    MicroEJ files for the 3rd-party BSP project are generated to 'C:\Users\user\src\tuto-from-scratch\workspace\HelloWorld\com.mycompany.Main\platform'.
    The MicroEJ application (microejapp.o) has been deployed to: 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\lib'.
    The MicroEJ platform library (microejruntime.a) has been deployed to: 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\lib'.
    The MicroEJ platform header files (*.h) have been deployed to: 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\inc'.
    Execution of script 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GCC\microej\scripts\build.bat' started...
      LD    gcc/RTOSDemo.axf
    Current DIR /mnt/c/Users/user/src/tuto-from-scratch/FreeRTOS/FreeRTOS/Demo/CORTEX_LM3S6965_GCC/microej/scripts
    Execution of script 'C:\Users\user\src\tuto-from-scratch\FreeRTOS\FreeRTOS\Demo\CORTEX_LM3S6965_GC  C\microej\scripts\build.bat' done.
    =============== [ Completed Successfully ] ===============

    SUCCESS

  .. note::

    You can notice the difference in the second line of the trace that now says that the connection is `using platform option 'root.dir' in 'bsp/bsp.properties'.` instead of `using platform option 'deploy.bsp.root.dir'.` in the previous launch.

 The application launcher does not know anymore where the BSP is located. Nevertheless it still builds a full firmware ready to be flashed. The link to the BSP is now configured in the platform and every MicroEJ mono-sandboxed application projects can use it without extra configuration.

Going Further
-------------

- More about build scripts in :ref:`Build Script File and Run Script File<bsp_connection_build_script>` subsections from MicroEJ Platform Creation guide
- Some build scripts examples from `Platform Qualification Tools <https://github.com/MicroEJ/PlatformQualificationTools/tree/master/framework/platform/scripts>`_
- :ref:`Run a testsuite on device<run_test_suite_on_device>` tutorial
