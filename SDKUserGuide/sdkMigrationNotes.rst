Migration Notes
---------------

-------------------
From 5.2.x to 5.3.x
-------------------

This section applies if MicroEJ SDK ``5.3.x`` is started on a workspace
that was previously created using MicroEJ SDK ``5.2.x``.

Workspace migration warning
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Starting with the MicroEJ SDK Distribution 20.10, when opening a
workspace which has been created with an older MicroEJ Distribution, a
message is displayed with the following warning:

::

    The workspace was written with an older version. Continue and update workspace which may make it incompatible with older versions?

This is a generic warning from Eclipse which can be safely ignored as
long as you don't intend to open it back with an older MicroEJ SDK
Distribution then.

-------------------
From 5.1.x to 5.2.x
-------------------

This section applies if MicroEJ SDK ``5.2.x`` is started on a workspace
that was previously created using MicroEJ SDK ``5.1.x``.

Enable New Wizards Shortcuts in MicroEJ Perspective
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Eclipse perspective settings are stored in the workspace metadata, so
the new wizards shortcuts (:guilabel:`Add-On Library Project` and
:guilabel:`Module Project`) are not visible in the :guilabel:`File` > :guilabel:`New` menu.

The MicroEJ perspective must be reset to its default settings as
following:

-  Click on :guilabel:`Windows` > :guilabel:`Perspective` > :guilabel:`Open Perspective` > :guilabel:`Other...` menu
-  Select :guilabel:`MicroEJ` perspective
-  Click on :guilabel:`Windows` > :guilabel:`Perspective` > :guilabel:`Reset Perspective...` menu
-  Click on :guilabel:`Yes` button to accept to reset the MicroEJ perspective to
   its defaults.

The new wizards shortcuts are now visible into :guilabel:`File` > :guilabel:`New` menu.

Re-enable the Ivy Preferences Pages (Advanced Use)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The original :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Ivy` pages can be re-enabled as
following:

-  Close all running instances of MicroEJ Studio / SDK
-  Edit ``MicroEJ-[SDK[Studio].ini`` and add the property
   ``-Dorg.apache.ivy.showAdvancedPrefs=true``
-  Start MicroEJ Studio / SDK again
-  Go to :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Module Manager` page

A new link ``Ivy settings`` should appear on the bottom of the page. It
opens a popup window with the original Ivy preferences pages.


-----------------
From 4.1.x to 5.x
-----------------

This section applies if MicroEJ SDK ``5.x`` is started on a workspace
that was previously created using MicroEJ SDK ``4.1.x``.

Wadapps Application Update
~~~~~~~~~~~~~~~~~~~~~~~~~~

The Wadapps code generator has been moved from IDE to an Addon Processor
coming with ``ej.library.wadapps.framework`` module (``v1.9.0`` or
higher is required).

A Wadapps Application Project can be updated as follows:

-  Right-click on the project, then
   :guilabel:`Configure` > :guilabel:`Remove Sandboxed Application Nature`
-  Right-click on the project, then
   :guilabel:`Configure` > :guilabel:`Add Sandboxed Application Nature`
-  Update ``module.ivy`` dependency to fetch
   ``ej.library.wadapps.framework`` version ``1.9.0`` (or perform
   MicroEJ Module Manager update as defined below)
-  Delete remaining folder ``src/.generated~`` if any
-  Check that project compiles and folder ``src-adpgenerated/wadapps``
   is generated

MicroEJ Module Manager Update
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is highly recommended to migrate ``module.ivy`` to the MicroEJ Module
Manager semantic, since the default Ivy resolution will be no more
maintained in future versions.

The ``module.ivy`` can be updated as follows:

-  Right-click on ``module.ivy``, then :guilabel:`Update Module Dependencies...`

This has for effect to both migrate the ``module.ivy`` to the MicroEJ
Module Manager semantic and also to update dependencies version to the
latest available in the target repository.

Meta build Project Update
~~~~~~~~~~~~~~~~~~~~~~~~~

A project using ``microej-meta-build`` version ``1.x`` can be updated to
version ``2.x`` as follows:

-  Edit ``module.ivy``

   -  Replace the ``microej-meta-build`` version by ``2.0.+``
   -  Update all properties declaration to append the ``metabuild.inject.`` prefix (e.g. ``<ea:property name="skip.test" value="true" />`` must be updated to ``<ea:property name="metabuild.inject.skip.test" value="true" />``)
   -  Optionally remove or comment the root folder declaration as it is the default. (``<ea:property name="metabuild.root" value=".." />``)
-  Delete ``module.properties``. It only contains the property
   ``easyant.fork.build=true``. This property is now automatically set
   by ``easyant-build-component`` since version ``1.12.0``. Otherwise it
   must be explicitly injected by the build system as an Ant property:
   ``easyant.inject.easyant.fork.build=true``
-  Extract from ``override.module.ant`` the projects declarations lines:

   -  Extract the project declarations of ``local.submodule.dirs.id`` into a new file named ``private.modules.list`` (one project per line)
   -  Extract the project declarations of ``submodule.dirs.id`` into a new file names ``public.modules.list`` (one project per line)
-  Delete ``override.module.ant``

The new file system structure shall look like:

::

    metabuild-project
        module.ivy
        private.modules.list
        public.modules.list

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
