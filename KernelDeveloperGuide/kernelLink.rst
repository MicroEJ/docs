.. _kernel_link:

Kernel Linking
==============

This chapter describes how a Kernel Application is linked.

Basically, a Kernel Application is linked as a Standalone Application.
The main difference is that a Kernel Application defines :ref:`Kernel APIs <kernel.api>`, and require to embed additional information that will be used later to build a Sandboxed Application against this Kernel (by linking with the Kernel APIs). 
Such additional information is called the Kernel Metadata.

Link Flow
---------

The following figure shows the general process of linking a Firmware, applied to a Kernel Application.

.. figure:: png/link_kernel.png
   :alt: Kernel Link Flow
   :align: center
   :scale: 80%

   Kernel Link Flow

The Platform must be configured with :ref:`Multi-Sandbox capability <multisandbox>`.

By default, the Kernel Metadata is included in the ``.debug.soar`` section which also serve for debug purpose (:ref:`stack_trace_reader`, :ref:`Heap Dumper <heapdumper>`).
Particularly, it contains resolved absolute addresses of Kernel APIs.

.. _kernel_metadata_generation:

Kernel Metadata Generation
--------------------------

To :ref:`build a Sandboxed Application on Device <build_feature_on_device>`, the Kernel Metadata must be exported after the Firmware link from the ``.debug.soar`` section.

This is achieved by the Kernel Metadata Generator tool. It produces a ``.kdat`` file that will be provided to the software implementation of the ``KernelMetadataProvider``.

.. figure:: png/kernel_metadata_generator.png
   :alt: Kernel Metadata Generator
   :align: center
   :scale: 80%

   Kernel Metadata Generator

The ``.kdat`` file is optimized for size. When linking a Sandboxed Application ``.fso`` file, only the required metadata will be loaded in Java heap.
It will be loaded from a standard `InputStream <https://repository.microej.com/javadoc/microej_5.x/apis/java/io/InputStream.html>`_,
so that it can be stored to a non byte-addressable memory.

.. note::

   The Kernel Metadata ``.kdat`` file can also be integrated in a Firmware executable file using post-link tools such as binutils objcopy,
   provided a dedicated section has been reserved by the third-party linker.


.. _firmware_linker:

Firmware Linker
---------------

Firmware Linker is a tool that links a Feature within a Multi-Sandboxed Firmware.

It takes as input the executable application (``.out`` file) and the Feature binary
code (``.fo`` file) into which to be linked. It outputs a new executable application
file, including the Installed Feature. This tool can be used to append
multiple Features, by setting as the input file the output file of the
previous pass. Features linked this way are then called Installed Features. 

The Kernel should have been linked for dimensioning the maximum size (code,
data) for such Installed Features. See :ref:`Core Engine link sections <core_engine_link>`.

The Firmware Linker tool is automatically called when declaring :ref:`System Applications <system_application_input_ways>` to a Multi-Sandbox module description.
It is also available as a :ref:`MicroEJ Tool <MicroEJToolsSection>` named :guilabel:`Firmware Linker`.

.. figure:: png/build_flow_zoom_workspace_firmware_linker_only.png
   :alt: Firmware Linker using MicroEJ Launch
   :align: center
   :scale: 80%

   Firmware Linker using MicroEJ Launch
   
.. warning::

   Features linked using the Firmware Linker tool could not be dynamically uninstalled using `Kernel.uninstall(Feature) <https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/Kernel.html#uninstall-ej.kf.Feature->`_ method.

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
