.. _javaEventGenerators:

Generic Event Generators
========================

On the application side, the UI extension provides an abstract class
``GenericEventGenerator`` (package ``ej.microui.event``) that must be
implemented by clients who want to define their own event generators.
Two abstract methods must be implemented by subclasses:

-  ``eventReceived``: The event generator received an event from a C
   driver through the low level API ``sendEvent`` function.

-  ``eventsReceived``: The event generator received an event made of
   several ``int``\ s.

-  ``setProperty``: Handle a generic property (key/value pair) set from
   the static initialization file (see `??? <#muiStaticInit>`__)

The event generator is responsible for converting incoming data into a
MicroUI event and sending the event to its listener.
