.. _sdk_6_disable_ivy_descriptor_publication:

How To Disable Ivy Descriptor Publication
=========================================

By default, SDK 6 adds an Ivy descriptor file to published artifacts in order for SDK 5 projects to be able to consume the module (e.g. an application built with SDK 5 depending on a library published with SDK 6).



Disable Ivy Descriptor Publication by Default
---------------------------------------------

If you don't need SDK 5 backward compatibility, you can disable Ivy descriptor publication by setting the Gradle property ``enable.ivy.descriptor.default=false``.

This property can be set in a ``gradle.properties`` file in ``<user.home>/.gradle/`` to apply it globally, or at the root of the Gradle project to
apply it at project level.
It can also passed to command line with ``-Penable.ivy.descriptor.default=false`` option.

.. note::

    You can get more information about Gradle properties in `Gradle offical documentation <https://docs.gradle.org/current/userguide/build_environment.html#sec:gradle_configuration_properties>`__.
  

Force Ivy Descriptor Publication When Disabled by Default
---------------------------------------------------------

Even when Ivy descriptor publication is globally disabled with the Gradle property, it can be forced in a project by adding ``withIvyDescriptor()`` to the ``microej`` block

in ``build.gradle.kts`` file::

  microej {
    withIvyDescriptor()
  }

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
