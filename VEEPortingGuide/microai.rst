.. _pack_microai:

=======
MicroAI
=======

Principle
=========

The MicroAI Foundation Library defines a low-level Machine Learning framework for embedded devices.
It allows to interact with trained Machine Learning models, especially to run inferences.

Functional Description
======================

The MicroEJ Application manages MicroAI models using Model instantiation/Inference/Tensor abstraction.
The MicroAI implementation made for each MicroEJ platform is responsible for surfacing the native Machine Learning specific behavior.

Dependencies
============

- ``LLML_impl.h`` implementation (see :ref:`LLMICROAI-API-SECTION`).

Installation
============

MicroAI is an additional module. 
To enable it, the MicroAI :ref:`Pack <pack_overview>` must be installed in your VEE Port:

.. code-block:: kotlin

   microejPack("ej.api:microai:1.0.0")

Use
===

See :ref:`MicroAI API <microai_api>` chapter in Application Developer Guide.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
