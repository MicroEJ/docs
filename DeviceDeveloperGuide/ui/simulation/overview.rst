Principle
=========

A major strength of the MicroEJ environment is that it allows
applications to be developed and tested in a simulator rather than on
the target device, which might not yet be built. To make this possible
for devices that have a display or controls operated by the user (such
as a touch screen or buttons), the simulator must connect to a "mock" of
the control panel (the "Front Panel") of the device. This mock is called
the *mockFP*. The mockFP generates a graphical representation of the
required front panel, and is displayed in a window on the user's
development machine when the application is executed in the simulator.
The mockFP is the equivalent of the three embedded modules (Display,
Inputs and LED) of the MicroEJ platform (see
`??? <#section_microui>`__).

The Front Panel mock enhances the development environment by allowing
User Interface  applications to be designed and tested on the computer
rather than on the target device (which may not yet be built). The mock
interacts with the user's computer in two ways:

-  output: LEDs, graphical displays

-  input: buttons, joystick, touch, haptic sensors
