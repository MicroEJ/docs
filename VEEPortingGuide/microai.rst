.. _pack_microai:

=======
MicroAI
=======

Principle
=========

The MicroAI Foundation Library defines a low-level Machine Learning framework for embedded devices.
It allows to run inferences on trained Machine Learning models.

Functional Description
======================

A typical Application using MicroAI will load a model binary file, read its input/output characteristics, and finally perform an inference.

The MicroAI integration in a VEE port relies on a native AI framework (Tensorflow-lite, ONNX Runtime, etc...) to implement all of the above functionalities.

Dependencies
============

- ``LLML_impl.h`` implementation (see :ref:`LLMICROAI-API-SECTION`).

Installation
============

MicroAI is an additional module. 
To enable it, the MicroAI :ref:`Pack <pack_overview>` must be installed in your VEE Port:

.. code-block:: kotlin

   api("ej.api:microai:2.0.0")

Use
===

See :ref:`MicroAI API <microai_api_usage>` chapter in Application Developer Guide.

..
   | Copyright 2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
