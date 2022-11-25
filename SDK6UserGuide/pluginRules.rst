.. _sdk6_plugin_rules:

Gradle Plugin Rules
===================

The MicroEJ Gradle plugin adds specific rules for compilation, building, resolving dependencies, versioning and publishing.

.. _sdk6_plugin_rules_versioning:

Versioning
----------

Dependencies
~~~~~~~~~~~~

Contrary to the SDK 5, the version declared in the dependencies of a build file are explicit in the SDK 6, meaning that:

- a fixed version (i.e. ``1.0.0``) refers to a release version only, not to its snapshot versions (``-RC``) as well.
- to depends on a snapshot version (``-RC``) of a module, it must be declared explicitly with the ``-RC+`` suffix, i.e. ``1.0.0-RC+``.

Module Version
~~~~~~~~~~~~~~

The SDK 5 used a specific notation for the snapshot versions. 
Instead of using the ``-SNAPSHOT`` prefix (i.e. ``1.0.0-SNAPSHOT``), 
it used the ``-RCxxx`` prefix, where ``xxx`` is the timestamp (i.e. ``1.0.0-RC202212021535``).

In order to be able to transition from SDK 5 to SDK 6 smoothly, it is recommended to continue to publish snapshot versions with the ``-RCxxx`` prefix.
This can be done by setting the Gradle module version with the ``-RC`` prefix. For example::

  .. code::

    version = "1.0.0-RC"

The SDK will automatically append the timestamp to the version to keep the same notation than MMM.
This way, SDK 5 projects will be able to fetch modules published by the SDK 6.

.. note::

  You are free to use any version number notation you want but you have to be aware that SDK 5 projects 
  will not be able to depend on snapshot modules published wihtout the ``-RCxxx`` prefix.

.. _sdk6_plugin_rules_conflicts:

Conflict Resolution Rules
-------------------------

Gradle comes with a powerful dependency manager.
One of its job is to resolve the conflicts in the dependencies graph, to determine which version should be added to the graph.
By default Gradle selects the highest version amongst all the versions requested for a dependency. 
There are ways to influence the dependencies resolution, 
but we believe additional rules should be added to provide a better and safer conflict resolution.

.. note::
  You can learn more on the Gradle conflicts resolution and the way to configure it in `the official documentation <https://docs.gradle.org/current/userguide/dependency_resolution.html>`__.

The MicroEJ Gradle plugin adds the 2 following rules:

- the resolution fails when a dependency is requested with 2 incompatible versions in the graph, according to the `Semantic Versioning specification <https://semver.org/>`__.
  So it means that if 2 versions do not have the same major version, the build fails.
  For example, this dependency graph makes the build fail because the ``moduleC`` dependency is requested in 2 incompatible versions:

  .. code::

    - moduleA:1.0.0
       |- moduleC:2.0.0
    - moduleB:1.0.0
       |- moduleC:3.0.0

- the resolution fails when a direct dependency is resolved with a higher minor version than the one declared.
  For example, this dependency graphs makes the build fails because the ``moduleA`` dependency is resolved in version ``1.1.0`` (the highest one), 
  which is higher than the direct declared version (``1.0.0``):

  .. code::

    - moduleA:1.0.0
    - moduleB:1.0.0
       |- moduleA:1.1.0

If you want to come back to the Gradle default behavior,
these 2 rules can be disabled by setting the ``microejConflictResolutionRulesEnabled`` property 
of the ``microej`` configuration block to ``false`` in the project build file:

.. code:: java

  microej {
    microejConflictResolutionRulesEnabled = false
  }

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
