.. _download.hardware.simulator:

Download and Install a MicroEJ Platform
=======================================

MicroEJ SDK being a cross development tool, it does not build software
targeted to your host desktop platform. In order to run MicroEJ
applications, a target hardware is required. Several commercial targets
boards from main MCU/MPU chip manufacturers can be prepared to run
MicroEJ applications, you can also run your applications without one of
these boards with the help of a MicroEJ Simulator.

A MicroEJ Platform is a software package including the resources and
tools required for building and testing an application for a specific
MicroEJ-ready device. MicroEJ Platforms are available at
``https://developer.microej.com/5/getting-started-sdk.html``.

After downloading the MicroEJ Platform, launch MicroEJ SDK on your
desktop to start the process of Platform installation :

-  Open the Platform view in MicroEJ SDK, select
   ``Window > Preferences > MicroEJ > Platforms``. The view should be
   empty on a fresh install of the tool

-  Press ``Import...`` button.

-  Choose ``Select File...`` and use the ``Browse`` option to navigate
   to the ``.jpf`` file containing your MicroEJ Platform, then read and
   accept the license agreement to proceed.

-  The MicroEJ Platform should now appear in the ``Platforms`` view,
   with a green valid mark.
