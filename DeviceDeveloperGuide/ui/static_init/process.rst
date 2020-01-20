Functional Description
======================

The Static MicroUI Initializer tool takes as entry point the
initialization file which describes the MicroUI library extension. This
tool is automatically launched during the MicroUI module installation
(see `??? <#section_microui_installation>`__ ).

The Static MicroUI Initializer tool is able to out until three files:

-  A Java library which extends MicroUI library. This library is
   automatically added to the MicroEJ application classpath when MicroUI
   library is set as a classpath variable. This library is used at
   MicroUI startup to create all instances of I/O devices (``Display``,
   ``EventGenerator`` etc.) and contains the fonts described into the
   configuration file (these fonts are also called "system fonts").

   This MicroUI extension library is always generated and MicroUI
   library cannot run without this extension.

-  A C header file (*.h) file. This H file contains some IDs which are
   used to make a link between an input device (buttons, touch) and its
   MicroUI event generator (see `??? <#section_input>`__).

   This file is useless if the BSP does not provide any input device and
   the Static MicroUI Initializer tool is able to not generate this
   file. Otherwise the MicroUI configuration file has to specify where
   put this file, typically in a BSP ``include`` directory.

-  A Java interface file. This Java file contains the same IDs which are
   used to make a link between an input device (buttons, touch) and its
   MicroUI event generator (see `??? <#section_input>`__).

   This Java file is used to configure the simulator with the same
   characteristics as the BSP.

   This file is useless if the BSP does not provide any input device and
   the Static MicroUI Initializer tool is able to not generate this
   file. Otherwise the MicroUI configuration file has to specify where
   put this file, typically in the simulator project (also called front
   panel project, see `??? <#section_simulation>`__).

.. figure:: static_init/images/process.svg
   :alt: MicroUI Process
   :width: 80.0%

   MicroUI Process
