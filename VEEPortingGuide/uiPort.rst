.. _ui_port:

=======
UI Port
=======

This chapter describes all the steps to port the UI Pack: from the VEE Port Configuration project to more advanced features like using a GPU.
This chapter makes a lot of references to the previous chapters. 
The concepts are overviewed and incomplete (only the typical case is described).

It is recommended to follow the steps in this order:

1. Edit the VEE Port Configuration project to add the UI Pack dependency and configuration,
2. Create the Simulator extension project,
3. Port the minimal implementation of the BSP,
4. Extend the implementation by connecting a GPU.

.. toctree::
    :maxdepth: 2

    uiPortConfiguration
    uiPortSimulation
    uiPortBSP
    uiPortGPU

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
