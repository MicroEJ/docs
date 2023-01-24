.. _sdk6_manage_versioning:

Manage Versioning
=================

The SDK 5 used a specific notation for the snapshot versions. 
Instead of using the ``-SNAPSHOT`` prefix (e.g.,``1.0.0-SNAPSHOT``), 
it used the ``-RCxxx`` prefix, where ``xxx`` is the timestamp (e.g., ``1.0.0-RC202212021535``).

In order to be able to transition from SDK 5 to SDK 6 smoothly, it is recommended to continue to publish snapshot versions with the ``-RCxxx`` prefix.
This can be done by setting the Gradle module version with the ``-RC`` prefix. For example::

    version = "1.0.0-RC"

The SDK will automatically append the timestamp to the version to keep the same notation than MMM.
This way, SDK 5 projects will be able to fetch modules published by the SDK 6.

.. note::

  You are free to use any version number notation you want, but you have to be aware that SDK 5 projects 
  will not be able to depend on snapshot modules published without the ``-RCxxx`` prefix.


..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
