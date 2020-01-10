Principle
=========

The Embedded COMmunication foundation library (ECOM) is a generic
communication library with abstract communication stream support (a
communication framework only). It allows you to open and use streams on
communication devices such as a COMM port.

This library also provides a device manager, including a generic device
registry and a notification mechanism, which allows plug&play-based
applications.

This library does not provide APIs to manipulate some specific options
for each communication method, but it does provide some generic APIs
which abstract the communication method. After the opening step, the
MicroEJ application can use every communications method (COMM, USB etc.)
as generic communication in order to easily change the communication
method if needed.
