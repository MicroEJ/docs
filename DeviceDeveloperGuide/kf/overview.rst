Principle
=========

The Multi applications capability of the MicroEJ core engine allows a
main application (called standalone application) to install and execute
at runtime additional applications (called sandboxed applications).

The MicroEJ core engine implements the [KF] specification. A Kernel is a
standalone application generated on a Multi applications-enabled
platform. A Feature is a sandboxed application generated against a
Kernel.

A sandboxed application may be dynamically downloaded at runtime or
integrated at build-time within the executable application.

Note that the Multi applications is a capability of the MicroEJ core
engine. The MicroEJ simulator always runs an application as a standalone
application.
