Building a MicroEJ Firmware
===========================

A MicroEJ Firmware is built from several input resources and tools.
Each resource and tool has a specific version that must be carefully
respected in order to build a firmware.

.. image:: images/qa_resources-v3.png
	:align: center

This document describes the components involved and the process to
build a MicroEJ Firmware.

Requirements
------------

* MicroEJ SDK 5 is installed with an activated license (evaluation
  license or production license).
* The reader is familiar with the :ref:`chapter-glossary`
* The reader has run one of the MicroEJ SDK getting started
  https://developer.microej.com/get-started/
* The reader has read the :ref:`platform-developer-guide`.

The MicroEJ SDK IDE [.exe or .zip].
-----------------------------------

* Download from https://developer.microej.com/get-started/


MicroEJ Architecture [.xpf, .xpfp]
----------------------------------

A MicroEJ Architecture contains the runtime port to a target
instruction set (ISA) and a C compiler (CC) and MicroEJ Foundation
Libraries.

The MicroEJ Architectures are distributed into 2 formats:

* EVAL: evaluation license with runtime limitations (explained in SDK
  developer guide).
* DEV: production license (these versions are only distributed by
  MicroEJ sales & Customer Care team).

The list of supported MicroEJ Architectures can be found here
https://developer.microej.com/mej32-embedded-runtime-architectures/#arch

The MicroEJ Architecture is either provided from:

* the ``/platformArchitecture`` folder in a MicroEJ Architecture
  (downloaded from https://developer.microej.com/).
* MicroEJ sales or customer care team.
* For DEV license only: SDK license site https://license.microej.com/
  (:guilabel:`MyProduct` > :guilabel:`Download additional products`
  will list the downloads available).

A MicroEJ Architecture must be imported in SDK with:

* :guilabel:`File` > :guilabel:`Import…`
* :guilabel:`MicroEJ` > :guilabel:`Platform, Virtual devices and
  Architectures`
* :guilabel:`Select directory` > :guilabel:`Browse…`, choose
  ``x/platformArchitecture/`` > :guilabel:`OK`
* Accept the license (Check the :guilabel:`I agree...` box)
* :guilabel:`Finish`

See :ref:`architecture_overview` for more information.

MicroEJ platform source (.zip)
------------------------------

This package includes:

* the build of a C board support package (BSP, with or without RTOS),
* a MEJ32 Architecture,
* the adaptation layers (ADLAs),
* the MicroEJ Simulator and its associated MicroEJ Mocks.

The zip files contains:

* ``<platform>-configuration``: The configuration of the MicroEJ
  Platform
* ``<platform>-bsp``: The C code for the board-specific files
  (drivers).
* Must be compiled with a compiler.
* ``<platform>-fp``: Front panel mockup for the simulator.

To generate the platform:

* In the ``<platform>-configuration`` module, open the
  :guilabel:`.platform` file and verify the correct MicroEJ
  Architecture is used (see :guilabel:`Content` view).
* Click on :guilabel:`Build Platform`. This action generates a
  ``<platform>-<ISA>-<CC>-<VERSION>`` folder that contains the
  platform runtime library (``microejruntime.lib``).
* This library is usually directly linked from the ``<platform>-bsp``
  project (no manual action to do after the build). Follow the README
  instructions inside the platform .zip.

See :ref:`BSP connection <bsp_connection>` for more information on how
to connect the BSP with a MicroEJ Platform.

MicroEJ Application project (.zip)
----------------------------------

This Java project can be configured (in the :guilabel:`Run
configurations ...` properties):

* to either run on:

  * a simulator (computer desktop),
  * a device (actual embedded hardware).

* to setup:

  * memory (example: Java heap, Java stack),
  * foundation libraries,
  * etc…

This project is compiled against (and optimized for) a specific
MicroEJ SDK platform:

* Generates a ``microejapp.o`` (native object code) that is usually
  directly linked from the ``<platform>-bsp`` project (no manual
  action to do after the build).

* Go in:

  * :guilabel:`Run` > :guilabel:`Run configurations`
  * select the provided :guilabel:`MicroEJ Application` launchers
  * click on :guilabel:`Run`

* Must be imported in SDK with: :guilabel:`File` > :guilabel:`Import…`
  > :guilabel:`General` > :guilabel:`Existing Projects into Workspace`
  > :guilabel:`Select archive file` > :guilabel:`Browse…`, choose
  ``x.zip`` and :guilabel:`Finish` import.

See :ref:`microej.sample.applications` for more information.

Ivy repository
--------------

* MicroEJ Central Repository: an online repository of software
  artifacts (libraries, tools, …), see
  https://repository.microej.com/.

* (Optional) Can be extended with an offline repository (``.zip``)
  that can be imported in the workspace (see
  :ref:`repository_offline`):

  * Unzip the ``x-repository-M.m.p.zip`` file.
  * Open MicroEJ SDK.
  * Go to :guilabel:`Window` > :guilabel:`Preferences` >
    :guilabel:`Ivy` > :guilabel:`Settings`.
  * Configure the ``Ivy settings`` path by clicking the
    :guilabel:`File System...` button.
  * Select the ``ivysettings.xml`` file available in the unzipped
    directory of the ``x-repository-M.m.p.zip`` file.

See :ref:`chapter.module.repository` for more information.

C compiler (GCC, KEIL, IAR, …).
-------------------------------

Used to compile and link the following files into the final firmware
(binary, hex, elf, … that will be programmed on the hardware):

  * the ``microejapp.o`` (application),
  * the ``microejruntime.lib`` or ``microejruntime.a`` (platform),
  * the BSP C files (drivers).
