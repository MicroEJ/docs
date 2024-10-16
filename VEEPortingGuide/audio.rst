.. _pack_audio:

=====
Audio
=====

Principle
=========

The Audio Foundation Library defines a low-level Audio framework for embedded devices.
It allows to manage abstract audio streams without worrying about the native underlying Audio device kind.

Functional Description
======================

The MicroEJ Application manages Audio devices using audio streams abstraction. 
The Audio implementation made for each VEE Port is responsible for surfacing the native Audio device specific behavior.

Dependencies
============

- ``LLAUDIO_RECORD_impl.h`` and ``LLAUDIO_TRACK_impl.h`` implementations (see :ref:`LLAUDIO-API-SECTION`).

Installation
============

Audio is an additional module. 
To enable it, the Audio :ref:`Pack <pack_overview>` module must be installed in your VEE Port:

.. tabs::

   .. tab:: SDK 6 (build.gradle.kts)

      .. code-block:: kotlin

         microejPack("com.microej.pack.audio:audio-pack:1.0.0")

   .. tab:: SDK 5 (module.ivy)

      .. code-block:: xml

         <dependency org="com.microej.pack.audio" name="audio-pack" rev="1.0.0"/>

Use
===

See :ref:`Audio API <audio_api_usage>` chapter in Application Developer Guide.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
