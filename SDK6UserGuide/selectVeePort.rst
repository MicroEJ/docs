.. _sdk_6_select_veeport:

Select a VEE Port
=================

Building or running an Application or a Test Suite with the SDK requires a VEE Port.

There are 3 different ways to provide a VEE Port for a module project:

- Set the build property ``veePortFile`` to the path of a VEE Port file (``.zip``, ``.jpf`` or ``.vde``).
- Set the build property ``veePortDir`` to the path of the ``source`` folder of an already imported :ref:`Source VEE Port <source_platform_import>`.
- Declare a module dependency with the conf ``microejVeePort``:

   .. code:: java

      dependencies {
         microejVeePort("com.mycompany:myveeport:1.0.0")
      }

At least 1 of these 3 ways is required to build an Application with a VEE Port.
If several ways are used, the following rules are applied:

- If ``veePortFile`` or ``veePortDir`` is set, the other options are ignored.
- If the module project defined several VEE Ports, the build fails. For example the following cases are not allowed:

  - Setting a VEE Port with the option ``veePortFile`` and another one with the option ``veePortDir``
  - Declaring 2 VEE Ports as Dependencies

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.