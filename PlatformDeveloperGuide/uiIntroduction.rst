Principle
=========

The User Interface Extension features one of the fastest graphical engines, associated with a unique int-based event management system. It provides :ref:`[MUI] library <esr-specifications>` implementation. 

The diagram below shows a simplified view of the components involved in the provisioning of User Interface Extension.

.. figure:: images/java-c-ui-interface.*
   :alt: Overview
   :width: 70.0%
   :align: center   

   Overview

Display, Input and LED are respectively called Graphical engine, Input engine and LED engine. These three low level parts connect MicroUI library to the user-supplied drivers code (coded in C). The drivers can use hardware accelerators like DMA and GPU to perform specific actions (buffers copy, drawings etc.).

The MicroEJ Simulator provides all features of MicroUI library. The three engines are grouped together in a module called Front Panel. The Front Panel is supplied with a set of software widgets that generically support a range of input devices, such as buttons, joysticks and touchscreens, and output devices such as displays and LEDs. With the help of the Front Panel Designer tool that forms part of the MicroEJ Workbench the user must define a front panel mock-up using these widgets. 

The graphical engine manages fonts and images. The fonts and images are pre-processed before compiling the MicroEJ application. The following diagram depicts the components involved in its design, along with the provided tools:

.. figure:: images/ui_overview2.*
   :alt: The User Interface Extension Components along with a Platform
   :width: 50.0%
   :align: center

   The User Interface Extension Components along with a Platform

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
