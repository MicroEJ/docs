Principle
=========

Stack Trace Reader is a MicroEJ tool which reads and decodes the MicroEJ
stack traces. When an exception occurs, the MicroEJ core engine prints
the stack trace on the standard output ``System.out``. The class names
and method names obtained are encoded with a MicroEJ internal format.
This internal format prevents the embedding of all class names and
method names in the flash, in order to save some memory space. The Stack
Trace Reader tool allows you to decode the stack traces by replacing the
internal class names and method names with their real names. It also
retrieves the line number in the MicroEJ application.
