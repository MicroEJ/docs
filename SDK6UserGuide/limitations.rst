.. _sdk_6_limitations:

Scope and Limitations
=====================

The SDK 6 covers all the SDK 5 features, except:

- Build of Foundation Libraries, Packs and Offline Repositories.
- Launch of some MicroEJ tools, such as the Kernel Metadata Generator.

If you need these features, you have to use :ref:`the SDK 5 <sdk_user_guide>`.

It is also important to note the following SDK 5 / SDK 6 compatibility rules:

- Libraries produced with SDK 6 can be fetched by SDK 5 projects.
- SDK 6 VEE Port cannot be used by SDK 5 Applications and Libraries.
- Architecture 8.1 is recommended to have full support on the SDK 6 features (especially to Debug with IntelliJ IDEA and Android Studio).
- SDK 6 Virtual Device cannot be used by SDK 5 Applications.
- SDK 5 Virtual Device cannot be used to build the Virtual Device of a SDK 6 Application (augmented Virtual Device).

When :ref:`the VEE transitive resolution <gradle_vee_transitivity_chapter>` is enabled, 
the VEE Ports and Kernels built with SDK 6 prior to ``1.3.0`` or SDK 5 are not supported, except if they are available locally in a directory or as an archive. 
It is highly recommended to update your VEE Port or Kernel if necessary, as the feature will be enabled by default in the next SDK 6 major version.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
