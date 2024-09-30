.. _section_architecture_releasenotes:

=============
Release Notes
=============

.. _section_architecture_api:

Foundation Libraries
====================

The following table describes Foundation Libraries API versions implemented in MicroEJ Architectures.

.. list-table:: Architecture API Implementation
   :widths: 20 10 10 10 10 10 10 10 10
   :header-rows: 1

   * - Architecture Range
     - EDC
     - BON
     - KF
     - SNI
     - SP
     - Trace
     - Device
     - ECOM-COMM
   * - [8.0.0-8.1.1]
     - `1.3 <https://repository.microej.com/modules/ej/api/edc/1.3.7/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/bon/1.4.3/>`__
     - `1.7 <https://repository.microej.com/modules/ej/api/kf/1.7.0/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/sni/1.4.3/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/trace/1.1.1/>`__
     - N/A [1]_
     - N/A [2]_
   * - [7.17.0-7.20.1]
     - `1.3 <https://repository.microej.com/modules/ej/api/edc/1.3.7/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/bon/1.4.3/>`__
     - `1.6 <https://repository.microej.com/modules/ej/api/kf/1.6.1/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/sni/1.4.3/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/trace/1.1.1/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__
   * - [7.13.0-7.16.0]
     - `1.3 <https://repository.microej.com/modules/ej/api/edc/1.3.7/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/bon/1.4.3/>`__
     - `1.5 <https://repository.microej.com/modules/ej/api/kf/1.5.1/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/sni/1.4.3/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/trace/1.1.1/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__
   * - [7.11.0-7.12.0]
     - `1.3 <https://repository.microej.com/modules/ej/api/edc/1.3.7/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/bon/1.4.3/>`__
     - `1.5 <https://repository.microej.com/modules/ej/api/kf/1.5.1/>`__
     - `1.3 <https://repository.microej.com/modules/ej/api/sni/1.3.1/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/trace/1.1.1/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__
   * - [7.10.0-7.10.1]
     - `1.2 <https://repository.microej.com/modules/ej/api/edc/1.2.3/>`__
     - `1.3 <https://repository.microej.com/modules/ej/api/bon/1.3.0/>`__
     - `1.5 <https://repository.microej.com/modules/ej/api/kf/1.5.1/>`__
     - `1.3 <https://repository.microej.com/modules/ej/api/sni/1.3.1/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/trace/1.0.0/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__
   * - [7.0.0-7.9.1]
     - `1.2 <https://repository.microej.com/modules/ej/api/edc/1.2.3/>`__
     - `1.3 <https://repository.microej.com/modules/ej/api/bon/1.3.0/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/kf/1.4.4/>`__
     - `1.3 <https://repository.microej.com/modules/ej/api/sni/1.3.1/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/trace/1.0.0/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__
   * - [6.13.0-6.18.0]
     - `1.2 <https://repository.microej.com/modules/ej/api/edc/1.2.3/>`__
     - `1.3 <https://repository.microej.com/modules/ej/api/bon/1.3.0/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/kf/1.4.4/>`__
     - `1.2 <https://repository.microej.com/modules/ej/api/sni/1.2.5/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/trace/1.0.0/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__
   * - [6.11.0-6.12.0]
     - `1.2 <https://repository.microej.com/modules/ej/api/edc/1.2.3/>`__
     - `1.2 <https://repository.microej.com/modules/ej/api/bon/1.2.3/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/kf/1.4.4/>`__
     - `1.2 <https://repository.microej.com/modules/ej/api/sni/1.2.5/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/trace/1.0.0/>`__
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__
   * - [6.9.0-6.10.0]
     - `1.2 <https://repository.microej.com/modules/ej/api/edc/1.2.3/>`__
     - `1.2 <https://repository.microej.com/modules/ej/api/bon/1.2.3/>`__
     - `1.4 <https://repository.microej.com/modules/ej/api/kf/1.4.4/>`__
     - `1.2 <https://repository.microej.com/modules/ej/api/sni/1.2.5/>`__
     - `2.0 <https://repository.microej.com/modules/ej/api/sp/2.0.4/>`__
     - N/A
     - `1.0 <https://repository.microej.com/modules/ej/api/device/1.0.2/>`__
     - `1.1 <https://repository.microej.com/modules/ej/api/ecom-comm/1.1.4/>`__


.. [1]
   See :ref:`architecture7_migration_device`.
   
.. [2]
   See :ref:`architecture7_migration_ecom`.

..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
