Principle
=========

The User Interface Extension features one of the fastest graphics engines, associated with a unique int-based event management system. 

This chapter describes the *UI3* notions, available since MicroEJ Architecture UI pack 13.0.0 and higher: MicroUI 3.0, Front Panel v6, Abstraction Layer APIs ``LLUI_xxx``, etc.

The diagram below shows a simplified view of the components involved in the provisioning of User Interface Extension.

.. figure:: images/java-c-ui-interface.*
   :alt: Overview
   :width: 600px
   :align: center   

   Overview

The modules responsible to manage the Display, the Input and the LED are respectively called :ref:`Display module <section_display>`, :ref:`Input module <section_input>` and :ref:`LED module <section_leds>`.
These three low-level parts connect MicroUI library to the user-supplied drivers code (coded in C). The drivers can use hardware accelerators like DMA and GPU to perform specific actions (buffers copy, drawings, etc.).

The MicroEJ Simulator provides all features of MicroUI library. The three modules are grouped together in a module called :ref:`Front Panel <section_ui_simulation>`. The Front Panel is supplied with a set of software widgets that generically support a range of input devices such as buttons, joysticks and touchscreens, and output devices such as displays and LEDs. With the help of the Front Panel Designer tool that forms part of the MicroEJ Workbench the user must define a Front Panel mock-up using these widgets. 

The Display module also manages fonts and images. The fonts and images are pre-processed before compiling the application. The following diagram depicts the components involved in its design, along with the provided tools:

.. figure:: images/ui_overview2.*
   :alt: The User Interface Extension Components along with a VEE Port
   :width: 600px
   :align: center

   The User Interface Extension Components along with a VEE Port

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
