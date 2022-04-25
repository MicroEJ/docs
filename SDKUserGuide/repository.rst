.. _module_repositories:

-------------------
Module Repositories
-------------------

This chapter describes the :ref:`module repositories <module_repository>` provided by MicroEJ Corp.

.. _central_repository:

Central Repository
==================

The Central Repository is the module repository distributed and maintained by
MicroEJ Corp. It contains Foundation Library APIs and numerous Add-On Libraries. 

Use
---

By default, the SDK is configured to connect the online Central Repository. 

You can manually browse the repository at https://repository.microej.com/modules/.

Before starting to develop production code, it is strongly recommended to import the repository to your local environment. 
Please follow the steps described at `<https://developer.microej.com/central-repository/>`_.

.. _central-repository-licensing:

Licensing
---------

The Central Repository is a set of modules distributed under various software licenses, including the :ref:`sdk_eula` for some of them.
Please consult the ``LICENSE.txt`` file attached to each module.

Changelog
---------

The Central Repository content is versioned. The changelog is available at https://repository.microej.com/.

Please consult the ``CHANGELOG.md`` file attached to each module.

Javadoc
-------

To consult the APIs documentation (Javadoc) of all :ref:`libraries <libraries>` available in the repository, please visit `<https://repository.microej.com/javadoc/microej_5.x/apis/>`_.

.. _developer_repository:

Developer Repository
====================

The developer repository is an online repository hosted by MicroEJ Corp., contains community modules provided "as-is".
It is similar to what `Maven Central Repository <https://repo1.maven.org/maven2/>`_ are for hosting Java standard modules.

MicroEJ Corp. contributes to the developer repository in the following cases:

- Demos (Platforms, Firmware, Virtual Devices, Applications),
- Incubating Libraries,
- Former Central Repository versions,
- Hardware specific modules.

Use
---

By default, the SDK is configured to connect the developer repository [#warning_require_sdk_5_4]_.

You can also manually browse the repository at https://forge.microej.com/artifactory/microej-developer-repository-release/.

Before starting to develop production code, it is strongly recommended to transfer the desired modules to your local environment by creating your own :ref:`module repository <module_repository>` copy.

.. [#warning_require_sdk_5_4] Require SDK version ``5.4.0`` or higher.

Licensing
---------

Please consult the ``LICENSE.txt`` file attached to each module.

Changelog
---------

The developer repository is populated from multiple sources, thus there is no changelog for the whole repository content as it is the case of the Central Repository.

Please consult the ``CHANGELOG.md`` file attached to each module.

Javadoc
-------

To consult the APIs documentation (Javadoc) of :ref:`libraries <libraries>` available in the developer repository, please consult the javadoc attached to each module.

Community
---------

The developer repository can host modules developed by the community. 
If your organization plan to develop such module, please contact :ref:`our support team <get_support>` to get dedicated credentials for publication.

Content Organization
====================

The following table describes how are organized the :ref:`modules natures <module_natures>` within the repository.

.. list-table:: Modules Organization
   :widths: 40 40
   :header-rows: 1

   * - Organization
     - Module Nature
   * - ``ej.api``,
       ``com.microej.api``
     - Foundation Library API
   * - ``com.microej.architecture``
     - :ref:`Architecture <architecture_overview>`
   * - ``com.microej.pack``
     - :ref:`Pack <pack_overview>`
   * - ``ej.tool``,
       ``com.microej.tool``
     - Tool or Add-On processor
   * - Any other
     - Add-On Library

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.