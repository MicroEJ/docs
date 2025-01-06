.. _veeport_qualification:

======================
VEE Port Qualification
======================

Introduction
============

A VEE Port integrates one or more Foundation Libraries with their
respective Abstraction Layers.

VEE Port Qualification is the process of validating the conformance of the Abstraction
Layer that implements the :ref:`Low Level APIs <low_level_api>` of a Foundation Library.

.. figure:: images/qualification-overview.png
   :align: center
   :scale: 80%

   VEE Port Qualification Overwiew

For each Low Level API, an Abstraction Layer implementation is
required.  The validation of the Abstraction Layer implementation is
performed by running tests at two-levels:

- In C, by calling Low Level APIs (usually manually).
- In Java, by calling Foundation Library APIs (usually automatically using :ref:`vee_port_testsuite`).

The following figure depicts an example for the FS Pack:

.. figure:: images/qualification-test-suite-fs.png
   :align: center
   :scale: 80%

   VEE Port Qualification Example for FS Pack

MicroEJ provides a set of tools and pre-defined projects aimed at
simplifying the steps for validating VEE Ports in the form of the 
VEE Port Qualification Tools (PQT):

.. tabs::

   .. group-tab:: SDK 6
      
      In SDK 6, it is located at:

      - the ``validation`` folder of the `VEE Port Project Template <https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/master/vee-port/validation>`__ for the Java Testsuites.
      - the `AbstractionLayer Tests repository <https://gitlab.cross/M0124_BSP-Framework/M0124_AbstractionLayer-Tests>`__ for the C tests.

   .. group-tab:: SDK 5
      
      In SDK 5, it is located at the `VEE Port Qualification Tools (PQT) repository <https://github.com/MicroEJ/VEEPortQualificationTools>`__.

.. _pqt_overview:

VEE Port Qualification Tools Overview
=====================================

The VEE Port Qualification Tools provide the following components:

- Build and Run Scripts examples:

  - Used to generate and deploy an Executable on a device by
    invoking a third-party toolchain for the BSP.
  - Added when integrating the BSP to the VEE Port (see
    :ref:`bsp_connection_build_script` and
    :ref:`bsp_connection_run_script` or check the training :ref:`tutorial_create_platform_build_and_run_scripts`).

- C and Java Test Suites:

  - Used to validate the Low Level APIs implementations.
  - Validated during the BSP development and whenever an Abstraction
    Layer implementation is added or changed (see
    :ref:`vee_port_testsuite` or check the section
    :ref:`run_test_suite_on_device`).

- **(Only for SDK 5)** Platform Configuration Additions (PCA):

  - Used to:

    - Manage Architecture, Packs dependencies and the VEE Port
      build with the MicroEJ Module Manager.
    - Configure the BSP connection to call the build and run scripts.

  - Added when creating a VEE Port (see :ref:`new_platform_creation`
    or check the training :ref:`tutorial_create_firmware_from_scratch`).

Please refer to the VEE Port Qualification Tools README in `SDK 5
<https://github.com/MicroEJ/VEEPortQualificationTools>`__ or in `SDK 6
<https://github.com/MicroEJ/Tool-Project-Template-VEEPort/tree/master/vee-port/validation>`__ for more
details and the location of the components.

.. _vee_port_testsuite:

VEE Port Test Suite
===================

The purpose of a VEE Port Test Suite is to validate the
Abstraction Layer that implements the :ref:`Low Level APIs
<low_level_api>` of a Foundation Libraries by automatically running
Java tests on the device.

The :ref:`testsuite_engine` is used for building,
running a Test Suite, and providing a report.

A Test Suite contains one or more tests. For each test, the Test Suite Engine will:

1. Build an Executable for the test.

2. Run the Executable onto the device.

3. Retrieve the execution traces.

4. Analyze the traces to determine whether the test has ``PASSED`` or ``FAILED``.

5. Append the result to the Test Report.

6. Repeat until all tests of the Test Suite have been executed.

.. figure:: images/testsuite-engine-overview.png
   :alt: VEE Port Test Suite on Device Overview
   :align: center

   VEE Port Test Suite on Device Overview

.. _test_suite_versioning:

Test Suite Versioning
=====================

Foundation Libraries are integrated in a VEE Port using :ref:`Packs <pack_overview>`.
Use the Test Suite version compliant with the API version provided by the Foundation Library 
to validate the Abstraction Layer implementation.
For example, the `Test Suite FS module 3.0.3`_ should be used to validate the Abstraction Layer 
implementation of the :ref:`Low Level API FS <LLFS-API-SECTION>` provided by the `FS Pack 5.1.2`_.

.. note:: A Pack can provide several Foundation Libraries.

.. _test_suite_versioning_core:

Core Engine
-----------

.. list-table:: Core Engine Validation
   :widths: 20 20

   * - Architecture
     - Test Suite
   * - 7.0.0 or higher
     - `Core Engine Test Suite <https://github.com/MicroEJ/VEEPortQualificationTools/tree/master/tests/core>`__

.. _Test Suite FS module 3.0.3: https://repository.microej.com/modules/com/microej/pack/fs/fs-testsuite/3.0.3/
.. _FS Pack 5.1.2: https://repository.microej.com/modules/com/microej/pack/fs/5.1.2/

.. _test_suite_versioning_ui:

UI Pack
-------

.. list-table:: UI Validation
   :widths: 20 20

   * - UI Pack
     - C Test Suite
   * - 13.0.0 or higher (UI3)
     - `Graphical User Interface Test Suite <https://github.com/MicroEJ/VEEPortQualificationTools/blob/master/tests/ui/ui3>`__
   * - [6.0.0-12.1.5] (UI2)
     - `Graphical User Interface Test Suite <https://github.com/MicroEJ/VEEPortQualificationTools/blob/master/tests/ui/ui2>`__

.. _test_suite_versioning_fs:

FS Pack
-------

.. list-table:: FS API Implementation and Validation
   :widths: 20 10 10

   * - FS Pack
     - FS API
     - Java Test Suite
   * - [6.0.0-6.1.0[
     - `2.1.1 <https://repository.microej.com/modules/ej/api/fs/2.1.1/>`__
     - `3.0.8 <https://repository.microej.com/modules/com/microej/pack/fs/fs-testsuite/3.0.8/>`__
   * - [5.1.2-5.2.0[
     - `2.0.6 <https://repository.microej.com/modules/ej/api/fs/2.0.6/>`__
     - `3.0.3 <https://repository.microej.com/modules/com/microej/pack/fs/fs-testsuite/3.0.3/>`__
   * - [4.0.0-4.1.0[
     - `2.0.6 <https://repository.microej.com/modules/ej/api/fs/2.0.6/>`__
     - On demand [1]_

.. _test_suite_versioning_bluetooth:

Bluetooth Pack
--------------

.. list-table:: Bluetooth API Implementation and Validation
   :widths: 20 10 10

   * - Bluetooth Pack
     - Bluetooth API
     - Java Test Suite
   * - [2.3.0-2.5.0[
     - `2.2.2 <https://repository.microej.com/modules/ej/api/bluetooth/2.2.2/>`__
     - `2.1.0 <https://repository.microej.com/modules/com/microej/pack/bluetooth/bluetooth-testsuite/2.1.0/>`__
   * - [2.1.0-2.3.0[
     - `2.1.1 <https://repository.microej.com/modules/ej/api/bluetooth/2.1.1/>`__
     - `2.0.1 <https://repository.microej.com/modules/com/microej/pack/bluetooth/bluetooth-testsuite/2.0.1/>`__
   * - [2.0.0-2.1.0[
     - `2.0.0 <https://repository.microej.com/modules/ej/api/bluetooth/2.0.0/>`__
     - `2.0.1 <https://repository.microej.com/modules/com/microej/pack/bluetooth/bluetooth-testsuite/2.0.1/>`__

NET Pack
--------

.. list-table:: NET, SSL and SECURITY APIs Implementations and Validations
   :widths: 15 10 10 10 15 15 15

   * - NET Pack
     - NET API
     - SSL API
     - SECURITY API
     - NET Java Test Suite
     - SSL Java Test Suite
     - SECURITY Java Test Suite
   * - [8.1.2-8.2.0]
     - `1.1.0 <https://repository.microej.com/modules/ej/api/net/1.1.0/>`__
     - `2.1.0 <https://repository.microej.com/modules/ej/api/ssl/2.1.0/>`__
     - N/A
     - 3.4.0 (On demand [1]_)
     - 3.0.1 (On demand [1]_)
     - N/A
   * - 9.0.0
     - `1.1.0 <https://repository.microej.com/modules/ej/api/net/1.1.0/>`__
     - `2.2.0 <https://repository.microej.com/modules/ej/api/ssl/2.2.0/>`__
     - `1.3.1 <https://repository.microej.com/modules/ej/api/security/1.3.1/>`__
     - 3.4.0 (On demand [1]_)
     - 3.1.4 (On demand [1]_)
     - 1.1.0 (On demand [1]_)
   * - [9.0.1-9.4.1]
     - `1.1.1 <https://repository.microej.com/modules/ej/api/net/1.1.1/>`__
     - `2.2.0 <https://repository.microej.com/modules/ej/api/ssl/2.2.0/>`__
     - `1.3.1 <https://repository.microej.com/modules/ej/api/security/1.3.1/>`__
     - 3.5.2 (On demand [1]_)
     - 3.1.4 (On demand [1]_)
     - 1.1.0 (On demand [1]_)
   * - [10.0.0-10.5.0]
     - `1.1.4 <https://repository.microej.com/modules/ej/api/net/1.1.4/>`__
     - `2.2.3 <https://repository.microej.com/modules/ej/api/ssl/2.2.3/>`__
     - `1.4.2 <https://repository.microej.com/modules/ej/api/security/1.4.2/>`__
     - `4.1.1 <https://repository.microej.com/modules/com/microej/pack/net/net-1_1-testsuite/4.1.1/>`__
     - `4.0.1 <https://repository.microej.com/modules/com/microej/pack/net/net-ssl-2_2-testsuite/4.0.1/>`__
     - `1.3.1 <https://repository.microej.com/modules/com/microej/pack/security/security-1_4-testsuite/1.3.1/>`__
   * - [11.0.1-11.0.2]
     - `1.1.4 <https://repository.microej.com/modules/ej/api/net/1.1.4/>`__
     - `2.2.3 <https://repository.microej.com/modules/ej/api/ssl/2.2.3/>`__
     - `1.4.2 <https://repository.microej.com/modules/ej/api/security/1.4.2/>`__
     - `4.1.1 <https://repository.microej.com/modules/com/microej/pack/net/net-1_1-testsuite/4.1.1/>`__
     - `4.0.2 <https://repository.microej.com/modules/com/microej/pack/net/net-ssl-2_2-testsuite/4.0.2/>`__
     - `1.3.1 <https://repository.microej.com/modules/com/microej/pack/security/security-1_4-testsuite/1.3.1/>`__
   * - 11.1.0
     - `1.1.4 <https://repository.microej.com/modules/ej/api/net/1.1.4/>`__
     - `2.2.3 <https://repository.microej.com/modules/ej/api/ssl/2.2.3/>`__
     - `1.4.2 <https://repository.microej.com/modules/ej/api/security/1.4.2/>`__
     - `4.1.1 <https://repository.microej.com/modules/com/microej/pack/net/net-1_1-testsuite/4.1.1/>`__
     - `4.0.2 <https://repository.microej.com/modules/com/microej/pack/net/net-ssl-2_2-testsuite/4.0.2/>`__
     - `1.7.0 <https://repository.microej.com/modules/com/microej/pack/net/security-1_7-testsuite/1.7.0/>`__

Audio Pack
----------

.. list-table:: Audio API Implementation and Validation
   :widths: 20 10 10

   * - Audio Pack
     - Audio API
     - Java Test Suite
   * - [1.0.0-1.1.0[
     - `1.0.0 <https://repository.microej.com/modules/ej/api/audio/1.0.0/>`__
     - `1.0.0 <https://repository.microej.com/modules/com/microej/pack/audio/audio-testsuite/1.0.0/>`__

.. _test_suite_versioning_event_queue:

EVENT QUEUE Pack
----------------

.. list-table:: EVENT QUEUE API Implementation and Validation
   :widths: 20 10 10

   * - EVENT QUEUE Pack
     - EVENT QUEUE API
     - Java Test Suite
   * - 2.0.1
     - `2.0.0 <https://forge.microej.com/artifactory/microej-developer-repository-release/ej/api/event/2.0.0/>`__
     - `2.0.0 <https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/pack/event/event-testsuite/2.0.0/>`__

.. [1] Test Suite available on demand, please contact :ref:`MicroEJ Support<get_support>`.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free
   for read and redistribute. Except if otherwise stated, modification
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and
   copyrights are the property of their respective owners.
