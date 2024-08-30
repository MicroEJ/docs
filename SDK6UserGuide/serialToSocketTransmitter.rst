.. _sdk6_tool_serial_to_socket:

============================
Serial to Socket Transmitter
============================


Principle
=========

The MicroEJ Serial to Socket Transmitter is a tool which
transfers all bytes from a serial port to a TCP client or TCP server.

It is typically used to transfer the output traces of a testsuite executed on a device.

Use
===

To start transfering data from the ``COM8`` serial port to the port ``5555``, 
execute the ``execTool`` task as followed:

.. code:: console

    ./gradlew execTool --name=serialToSocketTransmitter \
      --toolProperty="serail.to.socket.comm.port=COM8" \
      --toolProperty="serail.to.socket.comm.baudrate=115200" \
      --toolProperty="serail.to.socket.server.port=5555" \
      --console plain


Options
=======

Serial Port
^^^^^^^^^^^

*Option Name*: ``serail.to.socket.comm.port``

*Default value*: ``COM0``

*Description*: Defines the COM port:


Windows - ``COM1``, ``COM2``, ``...``, ``COM*n*``


Linux - ``/dev/ttyS0``, ``/dev/ttyUSB0``, ``...``, ``/dev/ttyS*n*``,
``/dev/ttyUSB*n*``



Baudrate
^^^^^^^^

*Option Name*: ``serail.to.socket.comm.baudrate``

*Default value*: ``115200``

*Available values*:


``9600``

``38400``

``57600``

``115200``


*Description*: Defines the COM baudrate.


Socket Port
^^^^^^^^^^^

*Option Name*: ``serail.to.socket.server.port``

*Default value*: ``5555``

*Description*: Defines the TCP server port.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
