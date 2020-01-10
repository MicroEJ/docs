Functional Description
======================

The MULTIAPP process extends the overall process described in
`??? <#processOverviewId>`__.

.. figure:: kf/images/process-multiapp-overview.png
   :alt: MULTIAPP Process
   :width: 50.0%

   MULTIAPP Process

Once a Kernel has been generated, additional MicroEJ application code
(Feature) can be built against the Kernel by :

-  Creating one launch configuration per feature.

-  Setting the ``Settings`` field in the ``Execution`` tab of each
   feature launch configuration to ``Build Dynamic Feature``.

-  Setting the ``Kernel`` field in the ``Configuration`` tab of each
   feature launch configuration to the .

using the MicroEJ application launch named Build Dynamic Feature. The
binary application file produced (``application.fo``) is compatible only
for the Kernel on which it was generated. Generating a new Kernel
requires that you generate the Features again on this Kernel.

The Features built can be deployed in the following ways:

-  Downloaded and installed at runtime by software. Refer to the [KF]
   specification for ``ej.kf.Kernel`` install APIs.

-  Linked at build-time into the executable application. Features linked
   this way are then called Installed Features. The Kernel should have
   been generated with options for dimensioning the maximum size (code,
   data) for such Installed Features. Features are linked within the
   Kernel using the Firmware linker tool.
