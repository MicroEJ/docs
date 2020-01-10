Principle
=========

The MULTIAPP capability of the MJVM allows a main application (called
STANDALONE) to install and execute at runtime additional applications
(called APPs).

The MJVM implements the [KF] specification. A Kernel is a STANDALONE
generated on a MULTIAPP-enabled platform. A Feature is a APP generated
against a Kernel.

A APP may be dynamically downloaded at runtime or integrated at
build-time within the executable application.

Note that the MULTIAPP is a capability of the MJVM. The SIMJPF always
runs an application as a STANDALONE.
