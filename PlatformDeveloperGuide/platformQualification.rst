.. _platform_qualification:

======================
Platform Qualification
======================

Introduction
============

Platform Qualification is the process of validating implementations of
:ref:`Low Level APIs <low_level_api>` provided by a Platform connected to a custom Board Support Package.

Such validation is performed by running tests at two-levels:

- In C, by calling Low Level APIs (usually manually).
- In Java, by calling Foundation Library APIs (usually automatically using :ref:`platform_testsuite`).

MicroEJ provides a set of tools and pre-defined projects aimed at simplifying the steps 
for validating Platforms. Please refer to https://github.com/MicroEJ/PlatformQualificationTools.

.. _platform_testsuite:

Platform Test Suite
===================

The purpose of a MicroEJ Platform Test Suite is to validate
an implementation of a Low Level API by automatically running Java tests on the device.

The :ref:`testsuite_engine` is used for building,
running a Test Suite, and providing a report.

A Platform Test Suite contains one or more tests.  For each test, the Test Suite Engine will:

1. Build a MicroEJ Firmware for the test.

2. Program the MicroEJ Firmware onto the device.

3. Retrieve the execution traces.

4. Analyze the traces to determine whether the test has ``PASSED`` or ``FAILED``.

5. Append the result to the Test Report.

6. Repeat until all tests of the Test Suite have been executed.

.. figure:: images/testsuite-engine-overview.png
   :alt: Platform Test Suite on Device Overview
   :align: center

   Platform Test Suite on Device Overview

..
   | Copyright 2008-2021, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
