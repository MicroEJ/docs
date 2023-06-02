Principle
=========

The Vector Graphics Pack features an extension of the :ref:`User Interface Pack <pack_gui>` that implements the :ref:`MicroVG API <section_app_microvg>`.

The diagram below shows a simplified view of the components involved in the provisioning of Vector Graphics Extension.

.. figure:: images/java-c-vg-interface.*
   :alt: Overview
   :width: 50%
   :align: center   

   Overview

The modules responsible to manage the Matrix, the Path, the Gradient, the Image and the Font are respectively called :ref:`Matrix module <section_vg_matrix>`, :ref:`Path module <section_vg_path>`, :ref:`Gradient module <section_vg_gradient>`, :ref:`Image module <section_vg_image>` and :ref:`Font module <section_vg_font>`.
These five low-level parts connect the MicroVG library to the user-supplied drivers code (coded in C). 
The drivers can use hardware accelerators like GPU to perform specific actions (matrix computations, path rendering, font decoding, etc.).

The MicroEJ Simulator provides all features of the MicroVG library. 
The five modules are grouped in a module called :ref:`Front Panel <section_vg_simulation>`. 
The Front Panel is an extension of the :ref:`UI Pack's Front Panel mock <section_ui_simulation>`.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
