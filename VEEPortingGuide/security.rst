.. _security:

========
Security
========


Principle
=========

The Security Foundation Library provides access to cryptographic algorithm operations such as SHA-1, SHA-256,
random number generation, signatures, MAC algorithms and other features related to secured communication.


Dependencies
============

- The name of these files match the ``LLSEC_*.h`` pattern (see :ref:`LLSECURITY-API-SECTION`).

.. _security_installation:

Installation
============

The Security Foundation Library is included in the NET pack. You can add this Foundation Library to your VEE Port by
adding the associated module dependency on the NET pack in the ``module.ivy`` file. Please refer to the section :ref:`Installation <network_core_installation>`
of the Network Core Engine page.

Then, update the VEE Port module configuration ``.platform`` file
(see Platform :ref:`Creation <platform_module_configuration>`) 
to add the Security component. A rebuild of the VEE Port is necessary to have an up to date VEE Port including the
new Foundation Library.



..
   | Copyright 2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
