.. _training_c_managed_code_communication:

==============================
C / Managed Code Communication 
==============================

Description
===========

In this training, you will get an in depth view of the different ways
to perform C / Managed Code communication using Native Interface Mechanisms.

What you will learn:

- SNI Overview
- Exposing a C API in Java
- Immortal Arrays
- Error Management
- Blocking Functions and Asynchronous Code
- Referencing C resources from Managed Code
- Overview of C / Managed Code Communication libraries: Event Queue, UI Pump, Shielded Plug

Intended Audience
=================

This training is designed for developers who want to learn about communication mechanisms between C and Managed Code.

Prerequisites
=============

To get the most out of this training, participants should have:

- A good understanding of the :ref:`overview` section.
- A basic knowledge of the :ref:`chapter-glossary`.
- A basic knowledge of C programming language.
- A basic knowledge of Java programming language.

Training Resources
==================

.. _training_c_managed_code_communication_unit1:

Unit 1: C / Managed Code Communication with MICROEJ VEE
-------------------------------------------------------

.. |c_managed_code_communication_slides| raw:: html

   <a href="https://repository.microej.com/packages/training/DEV-M0127-PRE-C_Managed_Code_Communication-1.4_20250317.pdf" target="_blank">Slides: C / Managed Code Communication with MICROEJ VEE</a>


This training provides a comprehensive overview of the various methods for 
C / Managed Code communication.

This training is provided as a PDF, along with a downloadable ``.zip`` package of resources:

- |c_managed_code_communication_slides|
- :download:`Resources <https://repository.microej.com/packages/training/microej_sdk_basics/gpio-basic_0f5cf862_20250317.zip>`

.. note::
   The ``SNI and Blocking Functions`` section requires to use the `NXP i.MX RT1170 Evaluation Kit <https://www.nxp.com/design/design-center/development-boards-and-designs/i-mx-evaluation-and-development-boards/i-mx-rt1170-evaluation-kit:MIMXRT1170-EVKB>`__
   to run the hand's on.

   The rest of the training is board agnostic.

Unit 2: Implementing a Blocking Java Native Method with SNI
-----------------------------------------------------------

This training describes a use case showing 
how to properly implement a blocking native method:

- :ref:`tutorial_sni_implement_blocking_native_method`

.. toctree::
   :hidden:
   
   tutorialImplementABlockingNativeMethodWithSNI

..
   | Copyright 2024-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.