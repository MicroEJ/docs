.. _bsp_connection:

==============
BSP Connection
==============

Principle
---------

Using a MicroEJ VEE Port, the user can compile a Application on that VEE Port. 
The result of this compilation is a ``microejapp.o`` file.

This file has to be linked with the VEE Port runtime file (``microejruntime.a``) 
and a third-party C project, called the Board Support Package (BSP),
to obtain the final binary file (the Executable).
For more information, please consult the :ref:`MicroEJ build process overview <fig_overall-process>`.

The BSP connection can be configured by defining 4 folders where the following files are located:

- Application file (``microejapp.o``).
- VEE Port runtime file (``microejruntime.a``, also available in the VEE Port ``lib`` folder).
- VEE Port header files (``*.h``, also available in the VEE Port ``include`` folder).
- BSP project :ref:`build script <bsp_connection_build_script>` file (``build.bat`` or ``build.sh``).

Once the Application file (``microejapp.o``) is built, the files are then copied to these locations 
and the ``build.bat`` or ``build.sh`` file is executed to produce the Executable (``application.out``).

.. note::

   The final build stage to produce the Executable can be done outside of the SDK, and thus 
   the BSP connection configuration is optional.
   
   BSP connection configuration is only required in the following cases:

   - Use the SDK to produce the Executable of a Mono-Sandbox Application (recommended).
   - Use the SDK to run a :ref:`MicroEJ Test Suite <vee_port_testsuite>` on device.
   - Build a the Executable of a Multi-Sandbox Application.

.. _bsp_connection_cases:

MicroEJ provides a flexible way to configure the BSP connection to target any kind of projects, teams organizations and company build flows.
To achieve this, the BSP connection can be configured either at VEE Port level or at MicroEJ Application level (or a mix of both). 

The 3 most common integration cases are:

- Case 1: No BSP connection

  The VEE Port does not know the BSP at all.

  BSP connection can be configured when building the MicroEJ Application (absolute locations).

  .. figure:: images/bsp-connection-cases-none.png
     :alt: VEE Port with no BSP connection
     :align: center
     :scale: 80%

     VEE Port with no BSP connection

  This case is recommended when:

  - the Executable is built outside the SDK.
  - the same VEE Port is intended to be reused on multiple BSP projects which do not share the same structure.

- Case 2: Partial BSP connection
  
  The VEE Port knows how the BSP is structured.

  BSP connection is configured when building the VEE Port (relative locations within the BSP), 
  and the BSP root location is configured when building the MicroEJ Application (absolute directory).

  .. figure:: images/bsp-connection-cases-partial.png
     :alt: VEE Port with partial BSP connection
     :align: center
     :scale: 80%

     VEE Port with partial BSP connection

  This case is recommended when:
  
  - the VEE Port is used to build one MicroEJ Application on top of one BSP. 
  - the Application and BSP are slightly coupled, thus making a change in the BSP just requires to build the Executable again.

- Case 3: Full BSP connection
  
  The VEE Port includes the BSP.

  BSP connection is configured when building the VEE Port (relative locations within the BSP), 
  as well as the BSP root location (absolute directory).
  No BSP connection configuration is required when building the MicroEJ Application.

  .. figure:: images/bsp-connection-cases-full.png
     :alt: VEE Port with full BSP connection
     :align: center
     :scale: 80%

     VEE Port with full BSP connection

  This case is recommended when:

  - the VEE Port is used to build various MicroEJ Applications.
  - the VEE Port is validated using MicroEJ test suites. 
  - the VEE Port and BSP are delivered as a single standalone module (same versioning), perhaps
    subcontracted to a team or a company outside the application project(s).

.. _bsp_connection_options:

Options
-------

BSP connection options can be specified as VEE Port options or as Application options or a mix of both.

The following table describes the VEE Port options, which can be set in the VEE Port configuration project,

  - in SDK 6, in the configuration properties file, prefixed by ``com.microej.pack.bsp.``.
  - in SDK 5, in the  ``bsp/bsp.properties`` file.

.. list-table:: VEE Port Options for BSP Connection
   :widths: 1 5 3 
   :header-rows: 1

   * - Option Name   
     - Description
     - Example
   * - ``microejapp.relative.dir``
     - The path relative to BSP ``root.dir`` where to deploy the MicroEJ Application file (``microejapp.o``).
     - ``MicroEJ/lib``
   * - ``microejlib.relative.dir``
     - The path relative to BSP ``root.dir`` where to deploy the VEE Port runtime file (``microejruntime.a``).
     - ``MicroEJ/lib``
   * - ``microejinc.relative.dir``
     - The path relative to BSP ``root.dir`` where to deploy the VEE Port header files (``*.h``). 
     - ``MicroEJ/inc``
   * - ``microejscript.relative.dir``
     - The path relative to BSP ``root.dir`` where to execute the BSP build script file (``build.bat`` or ``build.sh``). 
     - ``Project/MicroEJ``
   * - ``root.dir``
     - The 3rd-party BSP project absolute directory, to be included to the VEE Port.
     - ``c:\\Users\\user\\mybsp`` on Windows systems or ``/home/user/bsp`` on Unix systems.

.. _bsp_connection_application_options:

The following table describes the Application options, which can be set as regular :ref:`MicroEJ Application Options <application_options>`.

.. list-table:: MicroEJ Application Options for BSP Connection
   :widths: 1 5
   :header-rows: 1

   * - Option Name   
     - Description
   * - ``deploy.bsp.microejapp``
     - Deploy the MicroEJ Application file (``microejapp.o``) to the location defined by the VEE Port (defaults to ``true`` when VEE Port option ``microejapp.relative.dir`` is set).
   * - ``deploy.bsp.microejlib``
     - Deploy the VEE Port runtime file (``microejruntime.a``) to the location defined by the VEE Port (defaults to ``true`` when VEE Port option ``microejlib.relative.dir`` is set).
   * - ``deploy.bsp.microejinc``
     - Deploy the VEE Port header files (``*.h``) to the location defined by the VEE Port (defaults to ``true`` when VEE Port option ``microejinc.relative.dir`` is set). 
   * - ``deploy.bsp.microejscript``
     - Execute the BSP build script file (``build.bat`` or ``build.sh``) at the location specified by the VEE Port. (defaults to ``false`` and requires ``microejscript.relative.dir`` VEE Port option to be set). 
   * - ``deploy.bsp.root.dir``
     - The 3rd-party BSP project absolute directory. This option is required if at least one the 4 options described above is set to ``true`` and the VEE Port does not include the BSP.
   * - ``deploy.dir.microejapp``
     - Absolute path to the directory where to deploy the MicroEJ Application file (``microejapp.o``). An empty value means no deployment.
   * - ``deploy.dir.microejlib``
     - Absolute path to the directory where to deploy the VEE Port runtime file (``microejruntime.a``) to this absolute directory. An empty value means no deployment.
   * - ``deploy.dir.microejinc``
     - Absolute path to the directory where to deploy the VEE Port header files (``*.h``) to this absolute directory. An empty value means no deployment.
   * - ``deploy.dir.microejscript``
     - Absolute path to the directory that contains the BSP build script file (``build.bat`` or ``build.sh``). An empty value means no build script execution.


.. note::

   It is also possible to configure the BSP root directory by setting the :ref:`build option <mmm_build_options>` ``toolchain.dir``, 
   instead of the application option ``deploy.bsp.root.dir``.
   This allows to build the Executable by specifying both the VEE Port (using the ``target.platform.dir`` option) and the BSP 
   at build level, without having to modify the application options files.

For each :ref:`VEE Port BSP connection case <bsp_connection_cases>`, here is a summary of the options to set: 

- No BSP connection, Executable built outside the SDK
  :: 

    VEE Port Options:
      [NONE]

    Application Options:
      [NONE]

- No BSP connection, Executable built using the SDK
  :: 

    VEE Port Options:
      [NONE]

    Application Options:
      deploy.dir.microejapp=[absolute_path]
      deploy.dir.microejlib=[absolute_path]
      deploy.dir.microejinc=[absolute_path]
      deploy.dir.microejscript=[absolute_path]

- Partial BSP connection, Executable built outside the SDK
  :: 

    VEE Port Options:
      microejapp.relative.dir=[relative_path]
      microejlib.relative.dir=[relative_path]
      microejinc.relative.dir=[relative_path]

    Application Options:
      deploy.bsp.root.dir=[absolute_path]

- Partial BSP connection, Executable built using the SDK
  :: 

    VEE Port Options:
      microejapp.relative.dir=[relative_path]
      microejlib.relative.dir=[relative_path]
      microejinc.relative.dir=[relative_path]
      microejscript.relative.dir=[relative_path]   

    Application Options:
      deploy.bsp.root.dir=[absolute_path]
      deploy.bsp.microejscript=true

- Full BSP connection, Executable built using the SDK
  :: 

    VEE Port Options:
      microejapp.relative.dir=[relative_path]
      microejlib.relative.dir=[relative_path]
      microejinc.relative.dir=[relative_path]
      microejscript.relative.dir=[relative_path]
      root.dir=[absolute_path]

    Application Options:
      deploy.bsp.microejscript=true

.. _bsp_connection_build_script:

Build Script File
-----------------

The BSP build script file is used to invoke the third-party C toolchain (compiler and linker)
to produce the Executable (``application.out``).

The build script must comply with the following specification:

- On Windows operating system, it is a Windows batch file named ``build.bat``.
- On macOS or Linux operating systems, it is a shell script named ``build.sh``, with execution permission enabled.
- On error, the script must end with a non zero exit code.
- On success

  - The Executable must be copied to a file named ``application.out`` in the directory from
    where the script has been executed.
  - The script must end with zero exit code.

Many build script templates are available for most commonly used C toolchains in the 
`VEE Port Qualification Tools repository <https://github.com/MicroEJ/VEEPortQualificationTools/tree/master/framework/platform/scripts>`_.

The build script can also be launched before the VEE Port publication, see :ref:`platform_publication` for more details.

.. note::

    The Executable must be an ELF executable file.  On
    Unix, the command ``file(1)`` can be use to check the format of a
    file.  For example:

    .. code-block:: sh

       ~$ file application.out
       ELF 32-bit LSB executable
    
.. _bsp_connection_run_script:

Run Script File
---------------

This script is required only for VEE Ports intended to run a :ref:`MicroEJ Testsuite <vee_port_testsuite>` on device.

The BSP run script is used to invoke a third-party tool to upload and start the Executable on device.

The run script must comply with the following specification:

- On Windows operating system, it is a Windows batch file named ``run.bat``.
- On macOS or Linux operating systems, it is a shell script named ``run.sh``, with execution permission enabled.
- The Executable filename is passed as first script parameter if there is one, otherwise it is the ``application.out`` file located in the directory from where the script has been executed.
- On error, the script must end with a non zero exit code.
- On success:

  - The Executable (``application.out``) has been uploaded and started on the device
  - The script must end with zero exit code.

The run script can optionally redirect execution traces. If it does not implement execution traces redirection,
the testsuite must be configured with the following :ref:`application_options` in order to take its input from a TCP/IP socket server, 
such as :ref:`tool_serial_to_socket`.

.. code-block:: properties

  testsuite.trace.ip=localhost
  testsuite.trace.port=5555


.. _default_vee_port_application:

Default Application
-------------------

As of :ref:`Architecture 8.1.0 <changelog-8.1.0>`, a default pre-built application (``microejapp.o``) is provided with the VEE Port.
It simplifies the early-stage integration into a BSP project by eliminating the need to create and build an Application project within the SDK,
thereby removing the requirement to obtain a valid SDK license.

The default pre-built application is available at ``[VEE_PORT_DIR]/defaultApp/microejapp.o``.
It prints a splash with :ref:`architecture_characteristics` on the standard output:

.. code-block::
    
    MicroEJ START

    ,--.   ,--.,--.                    ,------.     ,--. ,--.   ,--.,------.,------.
    |   `.'   |`--' ,---.,--.--. ,---. |  .---'     |  |  \  `.'  / |  .---'|  .---'
    |  |'.'|  |,--.| .--'|  .--'| .-. ||  `--, ,--. |  |   \     /  |  `--, |  `--,
    |  |   |  ||  |\ `--.|  |   ' '-' '|  `---.|  '-'  /    \   /   |  `---.|  `---.
    `--'   `--'`--' `---'`--'    `---' `------' `-----'      `-'    `------'`------'

                                      **********
                                  ********************
                                *************************
                            ******************************
                            **********+=--::::--=++**********
                          *******++:...           ..:=+*******
                        ******+:..                  ...+******
                        *****+:.                        .:+*****
                        ****+....--.                .:-:  .=****
                        ***+...:****-.             .****=...=****
                      ****-...=****+.             -****+...:****
                      ****:...-****=.             :****+...:+***
                      ****:....-++-                :++=....:+***
                        ***+........                 .......=****
                      ******=..........           .........-******
                      *******+.......++-:......:-=+:......=*******
                      *********=.......:=++++++=:.......-*********
                    ************+-..................:+************
                ******   ***********+=-:......:-=++**********   ******
                *****    #***********************************    *****
                  ***     #*********************************     ***
                    *****   ********************************   *****
                  ********  ##****************************  ********
                  ****   ***  ###***********************##  ***   ****
                  ***    *     ###******************###     *    ***
                    **           #####************#####           **
                                  ##################
                                    ##############
                                        ######




                              ::::::::::::::::::::::::::::
                                ::::::::::::::::::::::

    You successfully linked your first Application with the following Architecture characteristics:
    - Name:                         atsauce6
    - Version:                      8.1.0 (20231220-1011)
    - Usage:                        Production
    - Core Engine Capability:       Multi-Sandbox
    - Instruction Set Architecture: x86
    - Compilation Toolchain:        GNU GCC (GNUvX_X86Linux)
    MicroEJ END (exit code = 0)

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
