Functional Description
======================

`figure_title <#ecom_flow>`__ shows the overall process to open a
connection on a hardware device.

.. figure:: core/images/process.svg
   :alt: ECOM Flow
   :width: 80.0%

   ECOM Flow

1. Step 1 consists of opening a connection on a hardware device. The
   connection kind and its configuration are fixed by the parameter
   ``String connectionString`` of the method ``Connection.open``.

2. Step 2 consists of opening an ``InputStream`` on the connection. This
   stream allows the MicroEJ application to access the "RX" feature of
   the hardware device.

3. Step 3 consists of using the ``InputStream`` APIs to receive in the
   MicroEJ application all hardware device data.

4. Step 4 consists of opening an ``OutputStream`` on the connection.
   This stream allows the MicroEJ application to access the "TX" feature
   of the hardware device.

5. Step 5 consists of using the ``OutputStream`` APIs to transmit some
   data from the MicroEJ application to the hardware device.

Note that steps 2 and 4 may be performed in parallel, and do not depend
on each other.
