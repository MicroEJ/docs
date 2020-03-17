Principle
=========

The User Interface Extension features one of the fastest graphical
engines, associated with a unique int-based event management system. It
provides [MUI] library implementation. The following diagram depicts the
components involved in its design, along with the provided tools:

.. figure:: images/ui_overview2.*
   :alt: The User Interface Extension Components along with a Platform
   :width: 70.0%
   :align: center

   The User Interface Extension Components along with a Platform

The diagram below shows a simplified view of the components involved in
the provisioning of a Java user interface.

.. figure:: images/java-c-ui-interface2.*
   :alt: Overview
   :width: 70.0%
   :align: center

   Overview

Stacks are the native parts of MicroUI. They connect the MicroUI library
to the user-supplied drivers code (coded in C).

Drivers for input devices must generate events that are sent, via a
MicroUI *Event Generator*, to the MicroEJ Application. An event
generator accepts notifications from devices, and generates an event in
a standard format that can be handled by the application. Depending on
the MicroUI configuration, there can be several different types of event
generator in the system, and one or more instances of each type. Each
instance has an unique id.

Drivers may either interface directly with event generators, or they can
send their notifications to a *Listener*, also written in C, and the
listener passes the notifications to the event generator. This
decoupling has two major benefits:

-  The drivers are isolated from the MicroEJ libraries – they can even
   be existing code.

-  The listener can translate the notification; so, for example, a
   joystick could generate pointer events.

For the MicroEJ Simulator, the platform is supplied with a set of
software widgets that generically support a range of input devices, such
as buttons, joysticks and touchscreens, and output devices such as
pixelated displays and LEDs. With the help of the Front Panel Designer
tool that forms part of the MicroEJ workbench the user must define a
front panel mock-up using these widgets. The user must provide a set of
listeners that connects the input widgets to event generators. The user
may choose to simulate events that will ultimately come from a
special-purpose input device using one of the standard input widgets;
the listener will do the necessary translation. The user must also
supply, in Java, a display extension that adapts the supplied display
widget to the specifics of the hardware being simulated.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
