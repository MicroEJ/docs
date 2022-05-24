.. _kf_specification:

Kernel & Features Specification
===============================

MicroEJ Multi-Sandboxing is based on the Kernel & Features semantic (KF).
It allows an application code to be split
between multiples parts: the main application, called the *Kernel* and
zero or more sandboxed applications called *Features*.

The Kernel part is mandatory and is assumed to be reliable, trusted and
cannot be modified. If there is only one application, i.e only one
``main`` entry point that the system starts with, then this application
is considered as the Kernel and called a Standalone Application. Even if
there are more applications in the platform, there is still only one
entry point. This entry point is the Kernel. Applications (downloaded or
preinstalled) are "code extensions" (called "Features"), that are called
by the Kernel. These Features are fully controlled by the Kernel: they
can be installed, started, stopped and uninstalled at any time
independently of the system state (particularly, a Feature never
depends on an other Feature to be stopped).

.. list-table::
   :widths: 10 30

   * - **Documentation**
     - **Link**
   * - Java APIs
     - https://repository.microej.com/javadoc/microej_5.x/apis/ej/kf/package-summary.html
   * - Specification
     - http://www.e-s-r.net/download/specification/ESR-SPE-0020-KF-1.4-F.pdf
   * - Module
     - https://repository.microej.com/modules/ej/api/kf/

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
