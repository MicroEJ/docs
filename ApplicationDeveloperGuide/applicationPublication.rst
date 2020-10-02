Application Publication
=======================

.. _section.build.wadapps.package:

Build the WPK
-------------

When the application is ready for deployment, the last step in MicroEJ
Studio is to create the WPK (Wadapps PacKage) file that is intended to
be published on a MicroEJ Forge instance for end users.

In MicroEJ Studio, right-click on the Sandboxed Application project name
and select ``Build Module``.

The WPK build process will display messages in MicroEJ console, ending
up the following message:

::

    [echo] project hello published locally with version 0.1.0-RC201907091602

    BUILD SUCCESSFUL

    Total time: 1 minute 6 seconds


.. _section.publish.on.a.microej.store:

Publish on a MicroEJ Forge Instance
-----------------------------------

The WPK file produced by the build process is located in a dedicated
``target~/artifacts`` folder in the project.

The ``.wpk`` file is ready to be uploaded to a MicroEJ Forge instance.
Please consult `<https://community.microej.com>`_ for more information.


..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
