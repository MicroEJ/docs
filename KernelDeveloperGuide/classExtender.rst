.. _class-extender:

Extend Kernel APIs
==================

This chapter explains how to extend Kernel APIs when building a multi-app firmware. Extending an API does not require to
have access to the libraries source code.

Apply Extension During Kernel Development
-----------------------------------------

Foundation and Add-on libraries can be extended by adding new methods to their existing classes. The new methods - either 
static or instance methods - are implemented in other classes and compiled in independant artifacts. Extensions can thus
be retrieved by the Kernel and applied during multi-app firmware build.

Class Extender tool works at binary level. It takes original libraries jar files on the one hand, and extension jar files 
on the other hand and applies all the extensions targeting the original libraries classes. As a result, the original 
libraries jar files are updated: extension methods bytecode is injected into  Foundation and Add-on libraries.

To make the extensions available for Application developers, Kernel APIs must be updated too. The ``runtuime-api`` 
build-type takes base Java APIs, extended APIs and new Kernel API and builds a custom runtime API including the new 
``kernel.api``, the updated source APIs and the corresponding Javadoc.

The following diagram illustrates the process of extending `String` class from EDC from a Kernel developer point of view:

.. image:: png/graph_build_string_methods.png
   :align: center
   :width: 1280px
   :height: 783px

Two processes are taking place to apply extensions:

   1. A Custom Runtime API is built using the `runtime-api` build type. It takes three components

      - EDC foundation library which contains String class we want to extend
      - a :ref:`kernel.api` file definition which includes new methods
      - a new ``String.java`` API source file which includes new methods
	  
      It builds a custom runtime API composed of three componentes:

      - an Add-on library containing the new ``kernel.api``
      - the Runtime API containing the extended String API
      - the corresponding Javadoc including the extended methods

   2. An extended EDC implementation is build during Firmware build calling Class Extender tool. It takes two components:

      - the original EDC Foundation library implementation jar file
      - the String extension Add-on librarty jar file

      It overrides the original EDC Foundation library implementation jar file.

Use Extended APIs During Application Development
------------------------------------------------

From an application developper perspective, the application only depends on custom APIs that include orginial APIs and
extensions.  
   
.. image:: png/graph_build_string_methods_app_dev.png
   :align: center
   :width: 524px
   :height: 396px

Writing a Class Extension
-------------------------

Refer to `Class Extender tool README <https://repository.microej.com/modules/com/microej/tool/class-extender/1.0.0/README-1.0.0.md>`_ for more information about class extension and integration to Firmware.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.