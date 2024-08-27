.. _sdk_6_veeport_create:

=================
Create a VEE Port
=================

This section describes the steps to create a new VEE Port with the SDK 6, 
and options to connect it to an external Board Support Package (BSP) as well as a third-party C toolchain. 


.. note::
   
   If you own a legacy VEE Port, you can either create your VEE Port again from scratch,
   or follow the :ref:`former_platform_migration` chapter.


.. _veeport_project_creation:

VEE Port Project Creation
=========================

The first step is to create a VEE Port configuration project:

.. tabs::

    .. tab:: Android Studio

    .. tab:: IntelliJ IDEA

        - Select :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`,
        - Select :guilabel:`Java`,
        - Enter a :guilabel:`Name`. The name is arbitrary and can be changed later. The usual convention is to use the name of the VEE Port,

        .. figure:: images/intellij-create-veeport-project.png
            :alt: VEE Port Project Creation
            :align: center

        - Click on :guilabel:`Create` button. A new project is created,
        - Delete the ``build.gradle.kts`` file and the ``src`` folder,

        - Right-click on the project folder,
        - Select :guilabel:`New` > :guilabel:`Module...`,
        - Select :guilabel:`Java`,
        - Enter a :guilabel:`Name`. The name is arbitrary and can be changed later. 
          The usual convention is to use the name of the VEE Port suffixed by ``-configuration`` (for example ``my-veeport-configuration``),

        .. figure:: images/intellij-create-veeport-configuration-module.png
            :alt: VEE Port Configuration Module Creation
            :align: center

        - Click on :guilabel:`Create` button. A new module is created,
        - Delete all the files and folders of this new module, except the ``build.gradle.kts`` file,
        - Replace the whole content of the ``build.gradle.kts`` file by::

            plugins {
                id("com.microej.gradle.veeport")
            }

            group = "org.example"
            version = "1.0.0-RC"

            dependencies {
                
            }

        You should get a VEE Port configuration project that looks like:

        .. figure:: images/intellij-create-veeport-project-structure.png
            :alt: VEE Port Project Skeleton
            :align: center


    .. tab:: Eclipse

    .. tab:: Visual Studio Code

    .. tab:: Command Line Interface


Architecture Selection
======================

The next step is to select an :ref:`Architecture <architecture_overview>` compatible with your device instructions set and C compiler.
A VEE Port requires exactly one Architecture.
MicroEJ Corp. provides MicroEJ Evaluation Architectures for most common instructions sets and compilers
at https://repository.microej.com/modules/com/microej/architecture. 
Please refer to the chapter :ref:`architectures_toolchains` for the details of ABI and compiler options.

If the requested MicroEJ Architecture is not available for evaluation or to get a MicroEJ Production Architecture,
please contact your MicroEJ sales representative or :ref:`our support team <get_support>`.

Once you know which Architecture to use, add it as a dependency of the VEE Port configuration project in the ``build.gradle.kts`` file:

.. code-block:: java
    :emphasize-lines: 3

    dependencies {

        microejArchitecture("com.microej.architecture.[ISA].[TOOLCHAIN]:[UID]:[VERSION]")

    }

The ``[UID]`` of the dependency needed for your VEE Port can be found in the chapter :ref:`architectures_toolchains`.
Check the table of your corresponding Architecture and follow the link in the :guilabel:`Module` column.

For example, to declare the MicroEJ Evaluation Architecture version ``8.1.1`` for Arm® Cortex®-M4 microcontrollers compiled with GNU CC toolchain:


.. code-block:: java
    :emphasize-lines: 3

    dependencies {

        microejArchitecture("com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25:8.1.1")

    }

Runtime Capability
------------------

Depending on the selected Architecture, several Runtime Capabilities are available: ``mono``, ``multi`` or ``tiny``.
The Capability used for the VEE Port can be defined thanks to the ``com.microej.runtime.capability`` property in the configuration file of the VEE Port Configuration project::

  com.microej.runtime.capability=multi


.. _sdk_6_veeport_pack_import:

Pack Import
===========

:ref:`MicroEJ Pack <pack_overview>` provides additional features on top of the MicroEJ Architecture such as Graphical User Interface or Networking.
This is the primary mechanism for augmenting the capabilities of a VEE Port.

A MicroEJ Pack is a group of related files (Foundation Libraries, scripts, link files, C libraries, Simulator Mock, tools, etc.) 
that together provide all or part of a VEE Port capability. 

A Pack can extend an Architecture with additional capabilities such as:

- Runtime Capability (e.g. :ref:`multisandbox`, :ref:`section_externalresourceloader`) , 
- Foundation Library Implementation (e.g. :ref:`MicroUI <section_microui_installation>`, :ref:`NET <network_core>`),
- Simulator (e.g. :ref:`section_frontpanel`),
- Tool (e.g. :ref:`tool_javah`).

.. note::

   MicroEJ Packs are optional. You can skip this section if you intend to integrate MicroEJ runtime only with custom libraries.

To add a MicroEJ Pack, add it as a dependency of the VEE Port configuration project in the ``build.gradle.kts`` file:

.. code-block:: java
    :emphasize-lines: 4,7,10

    dependencies {

        // MicroEJ Architecture Specific Pack
        microejPack("com.microej.architecture.[ISA].[TOOLCHAIN]:[UID]-[NAME]-pack:[VERSION]")

        // MicroEJ Generic Pack
        microejPack("com.microej.pack.[NAME]:[NAME]-pack:[VERSION]")

        // Legacy MicroEJ Generic Pack
        microejPack("com.microej.pack:[NAME]:[VERSION]")

    }

For example, to declare the `MicroEJ Architecture Specific Pack UI version 14.0.1`_ for MicroEJ Architecture ``flopi4G25`` on Arm®
Cortex®-M4 microcontrollers compiled with GNU CC toolchain:

.. code-block:: java
    :emphasize-lines: 4

    dependencies {

        // MicroEJ Architecture Specific Pack
        microejPack("com.microej.architecture.CM4.CM4hardfp_GCC48:flopi4G25-ui-pack:14.0.1")

    }

To declare the `MicroEJ Generic Pack Bluetooth version 2.1.0`_:

.. code-block:: java
    :emphasize-lines: 4

    dependencies {

        // MicroEJ Generic Pack
        microejPack("com.microej.pack.bluetooth:bluetooth-pack:2.1.0")

    }

And to declare the `Legacy MicroEJ Generic Pack Net version 9.2.3`_:

.. code-block:: java
    :emphasize-lines: 4

    dependencies {

        // Legacy MicroEJ Generic Pack
        microejPack("com.microej.pack:net:9.2.3")

    }

.. _MicroEJ Architecture Specific Pack UI version 14.0.1: https://repository.microej.com/modules/com/microej/architecture/CM4/CM4hardfp_GCC48/flopi4G25-ui-pack/14.0.1/
.. _MicroEJ Generic Pack Bluetooth version 2.1.0: https://repository.microej.com/modules/com/microej/pack/bluetooth/bluetooth-pack/2.1.0/
.. _Legacy MicroEJ Generic Pack Net version 9.2.3: https://repository.microej.com/modules/com/microej/pack/net/9.2.3/

.. _sdk_6_veeport_pack_enable_modules:

Enabling/Disabling modules of Legacy and Architecture Specific Packs
--------------------------------------------------------------------

Architecture Specific Packs and Legacy Packs may contain multiple modules.
They are all automatically installed during the VEE Port build, but can de disabled individually by configuration.
This is not the case for the Generic Packs, which always contain only one module.
Therefore, if you want to disable the module of a Generic Pack, simply remove the Pack dependency.

The modules of the Architecture Specific Packs and Legacy Packs can be enabled/disabled in the configuration file of the VEE Port Configuration project 
by adding the property ``com.microej.runtime.<module>.<feature>.enabled=true|false`` for each module that must be enabled/disabled.
The ``<feature>`` is optional. When no feature is defined, the whole module is enabled/disabled.
Here are some examples::

    # Disable the "display_decoder_bmpm" feature of the "ui" module of the Pack UI
    com.microej.runtime.ui.display_decoder_bmpm.enabled=false

    # Disable the whole "ssl" module of the Pack Net
    com.microej.runtime.ssl.enabled=false

.. _sdk_6_veeport_pack_configuration:

Packs Configuration
===================

Packs can be configured in the properties file of the VEE Port Configuration project.
Each Pack provides a set of option which follows the pattern name ``com.microej.pack.<module>.<option>=<value>``.
Here are some examples::

    # Defines the number of bits per pixels the display device is using to render a pixel
    com.microej.pack.display.bpp=argb8888

    # Defines the native file system user directory
    com.microej.pack.fs.user.dir=/home/microej

    # Defines the native stack you want to use
    com.microej.pack.net.stack=bsd

.. _sdk_6_veeport_build:

VEE Port Usage
==============

Depending on your use case, there are different ways to use the VEE Port.

VEE Port project inside a multi-project
---------------------------------------

When the VEE Port project is in the same multi-project than the component which needs it (an Application for example), 
the VEE Port project should be declared as a project dependency.

For example if the multi-project contains an Application subproject named ``my-app`` and a VEE Port configuration subproject called ``my-veeport-configuration``,
the VEE Port project must be declared as a dependency in the ``build.gradle.kts`` file of the ``my-app`` subproject as follows::

    dependencies {

        microejVee(project(":my-veeport-configuration"))

    }

The VEE Port will be automatically built when it is required by the Application.
For example when running the Application on the Simulator (with the ``runOnSimulator`` task) 
or when building the Application Executable (with the ``buildExecutable``),
the VEE Port will be built before executing the requested task.

Local VEE Port project outside a multi-project
----------------------------------------------

When the VEE Port project is in the same repository than the the component which needs it (an Application for example), 
the VEE Port project can be import thanks to the `Gradle Composite Build <https://docs.gradle.org/current/userguide/composite_builds.html>`_ feature.

This allows to consider the VEE Port project as part of the Application project, 
so all changes done to the VEE Port are automatically considered when building or running the Application.

This is done by adding the following line in the ``settings.gradle.kts`` file of the Application project::

  includeBuild("[vee-port-project-absolute-path")

Published VEE Port
------------------

When the VEE Port is intended to be used by developers not having the VEE Port project locally,
it must be published in a remote repository.
Refer to the :ref:`sdk_6_veeport_publication` section to learn how to publish a VEE Port.

Once published, the VEE Port can be used in a component, such as an Application, by declaring it in the dependencies.
For example to use the VEE Port of the :ref:`sdk_6_getting_started_imx93`::

  dependencies {

    microejVee("com.microej.veeport.imx93:VEEPort_eval:1.0.2")

  }

.. _sdk_6_veeport_customization:

VEE Port Customization
======================

The VEE Port Configuration project can contain an optional ``dropins`` folder.
The full content of this folder will be copied in the VEE Port during the build. 
Files in the dropins folder have the highest priority. 
If one file has the same path and name as a file already installed in the VEE Port, 
the file from the dropins folder will be used in the built VEE Port.
This feature allows to add or overwrite libraries, tools, etc. into the VEE Port.

The dropins folder organization should respect the VEE Port files and folders organization. 
For instance, the tools are located in the sub-folder ``tools``. 
In order to see how the VEE Port files and folders are organized, 
launch a VEE Port build without the dropins folder by executing the Gradle task ``buildVeePort``. 
The built VEE Port is located in the folder ``build/vee``.
Then fill the dropins folder with additional features and build again the VEE Port to get a customized VEE Port.


.. _sdk_6_veeport_publication:

VEE Port Publication
====================

Publishing a VEE Port in a repository allows to make it easily available to any project.

To be able to publish a VEE Port, you have to make sure that the ``group`` and `` version`` property are defined in the ``build.gradle.kts`` file::

  group = "com.mycompany"
  version = "1.0.0"

The name of the artifact can be defined in the ``settings.gradle.kts`` file with the ``rootProject.name`` property.
It is set by default to the folder name of the project.

Once these properties are defined, the publication of a VEE Port is done, as any other Gradle project, 
by executing the ``publish`` task.

An important point to notice is that publishing a VEE Port does not publish the built VEE Port, 
it publishes all the configuration, dropins and BSP files of the project.
The VEE Port is then built on the fly when it is required (when building the Executable of an Application for example).

BSP Connection
==============

In order to build the Executable of an Application, the BSP Connection must be configured.
Refer to the :ref:`bsp_connection` section for more details.

.. _sdk_6_veeport_link_time_option:

Link-Time Option
================

It is possible to define custom :ref:`Application options <application_options>` that can be passed to the BSP through an ELF symbol defined at link-time, hence the term `link-time option`.
This allows to provide configuration options to the Application developer without the need to rebuild the BSP source code.

To define a link-time option, first choose an option name with only alphanumeric characters (``[a-zA-Z][a-zA-Z0-9]*`` without spaces). 

Proceed with the following steps by replacing ``[my_option]`` with your option name everywhere:

- Create a folder inside your :ref:`sdk_6_veeport_customization` part (e.g: ``[platform]-configuration/dropins/scripts/init-[my_option]``)
- Create an init script file and put it inside (e.g: ``[platform]-configuration/dropins/scripts/init-[my_option]/init-[my_option].xml`` file). 
  Here is the init script file template content: 

  .. code-block:: xml
	
    <project name="[my_option]-init">
      <target name="init/execution/[my_option]" extensionOf="init/execution" if="onBoard">
        <!-- Set option default value -->
        <property name="[my_option]" value="0"/>

        <!-- Create tmp dir -->
        <local name="link.files.dir"/>
        <microejtempfile deleteonexit="true" prefix="link[my_option]" property="link.files.dir"/>
        <mkdir dir="${link.files.dir}"/>
        <!-- Get tmp link file name -->
        <local name="link.[my_option]"/>
        <property name="link.[my_option]" value="${link.files.dir}/[my_option].lscf" />
        <echoxml file="${link.[my_option]}" append="false">
          <lscFragment>
            <defSymbol name="[my_option]" value="${[my_option]}" rootSymbol="true"/>
          </lscFragment>
        </echoxml>
        <!-- Add link file in linker's link files path -->
        <augment id="partialLink.lscf.path">
          <path location="${link.files.dir}"/>
          <path location="${jpf.dir}/link"/>
        </augment>
      </target>
    </project>

- In your BSP source code, define an ELF symbol ``[my_option]`` can then be used inside C files in your BSP with:
 	
  .. code-block:: c
  
    // Declare the symbol as an extern global
    extern int [my_option];
        
    void my_func(void){
       // Get the symbol value
       int [my_option]_value = ((int)(&[my_option]));
     
       // Get the symbol value
       if([my_option]_value == 1){
         ...
       }
       else{
         ...
       }
    }

.. warning::

    A Link-time option should avoid to be set to ``0``. 
    Some third-party linkers consider such symbols as undefined, even if they are declared.


..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
