.. _architecture7_migration:

Architecture 7.x Migration
==========================

This chapter describes the steps to migrate a VEE Port from Architecture ``7.x`` to Architecture ``8.0.0``.

As a reminder, refer to the :ref:`Architecture 8.0.0 Changelog <changelog-8.0.0>` section for the complete list of changes and updates.

Update Platform Configuration Additions
---------------------------------------

Architecture ``8.0.0`` now directly integrates the :ref:`bsp_connection` mechanism.
The Platform Configuration Additions must be updated accordingly. 
Contact `our support team <https://www.microej.com/contact/#form_2>`_ to get detailed instructions. 

Update BSP with new Sections Names
----------------------------------

The Core Engine sections have been renamed to respect the standard ELF convention. See :ref:`Core Engine Link <core_engine_link>` section for further details.

All references to section names in your BSP must be updated. 
This is usually only used in your linker script file, but section names are sometimes also hardcoded in the C Code.
Here is an example of a GNU LD script highlighting the typical changes that must be made:

.. figure:: images/ExampleLD-Architecture7diff8.png
   :alt: Example of LD Script File Migration
   :align: center
   :scale: 100%

   Example of LD Script File Migration

Remove LLBSP_IMPL_isInReadOnlyMemory
------------------------------------

The ``LLBSP_IMPL_isInReadOnlyMemory`` has been removed since it is no more called by the Core Engine. You can simply remove your implementation function.

Migrate Built-in Modules
------------------------

The following built-in legacy modules have been removed from the Architecture:

- Device
- ECOM-COMM

In the Platform Editor, these modules now appear in gray with Architecture ``8.x``:

.. figure:: images/architecture7_removed_modules.png
   :scale: 100%

To remove these modules, open the ``.platform`` file using a text editor and remove the following XML elements:

.. code-block:: xml

    <group name="device"/>
    <group name="ecom"/>


Migrate Device Module
~~~~~~~~~~~~~~~~~~~~~

The latest `Device Pack`_ available on the :ref:`central_repository` is backward compatible with the built-in Architecture module.

.. _Device Pack: https://repository.microej.com/modules/com/microej/pack/device/device-pack/

The following dependency must be added to the :ref:`module.ivy <mmm_module_description>` of the VEE Port configuration project:
      
  .. code:: xml
      
     <dependency org="com.microej.pack.device" name="device-pack" rev="1.1.1" />

Migrate ECOM-COMM Module
~~~~~~~~~~~~~~~~~~~~~~~~

There are two options:
  
- either migrate to the latest ECOM-COMM Pack,
- or integrate the legacy ECOM-COMM Pack files as-is into your VEE Port ``dropins`` folder.

Contact `our support team <https://www.microej.com/contact/#form_2>`_ to get the best migration strategy and detailed instructions. 

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
