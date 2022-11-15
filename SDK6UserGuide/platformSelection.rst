.. _sdk_6_platform_selection:

Platform Selection
===================

Building or running an Application or a Test Suite with the SDK requires a Platform.

There are 4 different ways to provide a Platform for a module project:

- Set the build property ``platformFile`` to the path of a Platform file (``.zip``, ``.jpf`` or ``.vde``).
- Set the build property ``platformDir`` to the path of the ``source`` folder of an already imported :ref:`Source Platform <source_platform_import>`.
- Declare a module dependency with the conf ``microejPlatform``:

   .. code:: java

      dependencies {
         microejPlatform("com.mycompany:myplatform:1.0.0")
      }

At least 1 of these 3 ways is required to build an Application with a Platform.
If several ways are used, the following rules are applied:

- If ``platformFile`` or ``platformDir`` is set, the other options are ignored.
- If the module project defined several Platforms, the build fails. For example the following cases are not allowed:

  - Setting a platform with the option ``platformFile`` and another one with the option ``platformDir``
  - Declaring 2 platforms as Dependencies

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.