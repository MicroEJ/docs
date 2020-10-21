.. _mmm:

MicroEJ Module Manager
======================

Introduction
------------

Modern electronic device design involves many parts and teams to
collaborate to finally obtain a product to be sold on its market.
MicroEJ encourages modular design which involves various stake holders:
hardware engineers, UX designers, graphic designers, drivers/BSP
engineers, software engineers, etc.

Modular design is a design technique that emphasizes separating the
functionality of an application into independent, interchangeable
modules. Each module contains everything necessary to execute only one
aspect of the desired functionality. In order to have team members
collaborate internally within their team and with other teams, MicroEJ
provides a powerful modular design concept, with smart module
dependencies, controlled by the MicroEJ Module Manager (MMM). MMM frees
engineers from the difficult task of computing module dependencies.
Engineers specify the bare minimum description of the module
requirements.

The following schema introduces the main concepts detailed in this chapter.

.. figure:: images/mmm_flow.png
   :alt: MMM Overview
   :align: center
   :scale: 70%

   MMM Overview

MMM is based on the following tools:

-  Apache Ivy (`<http://ant.apache.org/ivy>`_) for dependencies
   resolution and module publication;

-  Apache EasyAnt
   (`<https://ant.apache.org/easyant/history/trunk/reference.html>`_) for
   module build from source code.

.. _mmm_specification:

Specification
-------------

MMM provides a non ambiguous semantic for dependencies
resolution. Please consult the MMM specification available on
`<https://developer.microej.com/packages/documentation/TLT-0831-SPE-MicroEJModuleManager-2.0-D.pdf>`_.


.. _mmm_module_skeleton:

Module Project Skeleton
-----------------------

In MicroEJ SDK, a new MicroEJ module project is created as following:

- Select :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`,
- Select :guilabel:`MicroEJ` > :guilabel:`MicroEJ Module Project` [#warning_check_former_sdk_versions]_,
- Fill the module information (project name, module organization, name and revision),
- Select one of the suggested skeletons depending on the desired :ref:`module nature <module_nature_skeleton_mapping>`,
- Click on :guilabel:`Finish`.

The project is created and a set of files and directories are generated from the selected skeleton.

.. note:: 
  When an empty Eclipse project already exists or when the skeleton has to be created within an existing directory, 
  the MicroEJ module is created as following:

  - In the `Package Explorer`, click on the parent project or directory,
  - Select :guilabel:`File` > :guilabel:`New` > :guilabel:`Other...`,
  - Select :guilabel:`EasyAnt` > :guilabel:`EasyAnt Skeleton`.

.. _mmm_module_description:

Module Description File
-----------------------

A module description file is an Ivy configuration file named ``module.ivy``, located at the root
of each MicroEJ module project. 
It describes the :ref:`module nature <module_natures>` (also called build type) and dependencies to other modules.

.. code:: xml

   <ivy-module version="2.0" xmlns:ea="http://www.easyant.org" xmlns:m="http://ant.apache.org/ivy/extra" 
                             xmlns:ej="https://developer.microej.com" ej:version="2.0.0"> 
       <info organisation="[organisation]" module="[name]" status="integration" revision="[version]">
           <ea:build organisation="com.is2t.easyant.buildtypes" module="[buildtype_name]" revision="[buildtype_version]">
               <ea:property name="[buildoption_name]" value="[buildoption_value]"/>
           </ea:build>
       </info>
       
       <configurations defaultconfmapping="default->default;provided->provided">
           <conf name="default" visibility="public"/>
           <conf name="provided" visibility="public"/>
           <conf name="documentation" visibility="public"/>
           <conf name="source" visibility="public"/>
           <conf name="dist" visibility="public"/>
           <conf name="test" visibility="private"/>
       </configurations>
       
       <publications>
       </publications>
       
       <dependencies>
         <dependency org="[dep_organisation]" name="[dep_name]" rev="[dep_version]"/>
       </dependencies>
   </ivy-module>        

.. _mmm_configuration:

MicroEJ Module Manager Configuration 
-------------------------------------

By default, when starting an empty workspace, MicroEJ SDK is configured to import dependencies
from :ref:`MicroEJ Central Repository <central_repository>` and to publish built modules to a local folder.
The repository configuration is stored in a :ref:`settings file <mmm_settings_file>` (``ivysettings.xml``), and the default one
is located at ``$USER_HOME\.microej\microej-ivysettings-[VERSION].xml``

.. _mmm_preferences_page:

Preferences Page
~~~~~~~~~~~~~~~~

The MMM preferences page is available at :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Module Manager` [#warning_check_former_sdk_versions]_.

   .. figure:: images/mmm_preferences_5-2_annotated.png
      :alt: MMM Preferences Page
      :align: center

      MMM Preferences Page

This page allows to configure the following elements:

1. ``Settings File``: the file describing how to connect :ref:`module repositories <module_repository>`. See the :ref:`settings file <mmm_settings_file>` section.
2. ``Options``: files declaring MMM options. See the :ref:`Options <mmm_options>` section.
3. ``Use Module repository as Build repository``: 
   the :ref:`settings file <mmm_settings_file>` for connecting the build repository in place of the one bundled in MicroEJ SDK.
   This option shall not be enabled by default and is reserved for advanced configuration.
4. ``Build repository Settings File``:
   the :ref:`settings file <mmm_settings_file>` for connecting the build repository in place of the one bundled in MicroEJ SDK.
   This option is automatically initialized the first time MicroEJ SDK is launched. 
   It shall not be modified by default and is reserved for advanced configuration.
5. ``Set verbose mode``: to enable advanced debug traces when building a module.
6. ``Runtime JRE``: the Java Runtime Environment that executes the build process.
7. ``Max build history size``: the maximum number of previous builds available in :guilabel:`Build Module` shortcut list:
   
   .. figure:: images/mmm_shortcut_build_module.png
      :align: center

.. _mmm_settings_file:

Settings File
~~~~~~~~~~~~~

The settings file is an XML file that describes how MMM connects local or online :ref:`module repositories <module_repository>`.
The file format is described in `Apache Ivy documentation <https://ant.apache.org/ivy/history/2.5.0/settings.html>`_.

To configure MMM to a custom settings file (usually from an :ref:`offline repository <repository_offline>`):

1. Set :guilabel:`Settings file` to a custom ``ivysettings.xml`` settings file [#warning_check_former_sdk_versions]_,
2. Click on :guilabel:`Apply and Close` button

If the workspace is not empty, it is recommended to trigger a full resolution
and rebuild all the projects using this new repository configuration:

1. Clean caches
   
   - In the Package Explorer, right-click on a project;
   - Select :guilabel:`Ivy` > :guilabel:`Clean all caches`.
2. Resolve projects using the new repository
   
   To resolve all the workspace projects, click on the :guilabel:`Resolve All` button in the toolbar:

   .. figure:: images/mmm_shortcut_resolveAll.png
      :align: center

   To only resolve a subset of the workspace projects:
   
   - In the Package Explorer, select the desired projects,
   - Right-click on a project and select :guilabel:`Ivy` > :guilabel:`Clean all caches`.
3. Trigger Add-On Library processors for automatically generated source code
   
   - Select :guilabel:`Project` > :guilabel:`Clean...`,
   - Select :guilabel:`Clean all projects`,
   - Click on :guilabel:`Clean` button.


.. _mmm_options:

Options
~~~~~~~

Options can be used to parameterize a :ref:`module description file <mmm_module_description>` or a :ref:`settings file <mmm_settings_file>`.
Options are declared as key/value pairs in a `standard Java properties file <https://en.wikipedia.org/wiki/.properties>`_, and are expanded using the ``${my_property}`` notation.

A typical usage in a :ref:`settings file <mmm_settings_file>` is for extracting repository server credentials, such as HTTP Basic access authentication:

1. Declare options in a properties file

   .. figure:: images/mmm_preferences_options_settings_declaration.png
      :align: center

2.  Register this property file to MMM options

   .. figure:: images/mmm_preferences_options_settings_register.png
      :align: center

3. Use this option in a :ref:`settings file <mmm_settings_file>`

   .. figure:: images/mmm_preferences_options_settings_usage.png
      :align: center

A typical usage in a :ref:`module description file <mmm_module_description>` is for factorizing dependency versions across multiple modules projects:

1. Declare an option in a properties file

   .. figure:: images/mmm_preferences_options_declaration.png
      :align: center

2. Register this property file to MMM options

   .. figure:: images/mmm_preferences_options_register.png
      :align: center

3. Use this option in a :ref:`module description file <mmm_module_description>`

   .. figure:: images/mmm_preferences_options_usage.png
      :align: center

.. _mmm_build_kit:

Build Kit
---------

The Module Manager build kit is the consistent set of tools and scripts required for building modules. 

It is bundled with MicroEJ SDK and can be exported to run in headless mode using the following steps: [#warning_check_former_sdk_versions]_

- Select :guilabel:`File` > :guilabel:`Export` > :guilabel:`MicroEJ` > :guilabel:`Module Manager Build Kit`,
- Choose an empty :guilabel:`Target directory`,
- Click on the :guilabel:`Finish` button.

Once the build kit is fully exported, the directory content shall look like:

.. figure:: images/mmm_extract_build_kit.png
      :align: center

To go further with headless builds, please consult `Tool-CommandLineBuild <https://github.com/MicroEJ/Tool-CommandLineBuild/README.rst>`_ for command line builds, 
and this :ref:`tutorial <tutorial_setup_jenkins_artifactory>` to setup MicroEJ modules build in continuous integration environments).


.. [#warning_check_former_sdk_versions] If using MicroEJ SDK versions lower than ``5.2.0``, please refer to the :ref:`following section <mmm_former_sdk>`.

.. _mmm_former_sdk:

Former MicroEJ SDK Versions
---------------------------

This section describes MMM configuration elements for MicroEJ SDK versions lower than ``5.2.0``.

New MicroEJ Module Project
~~~~~~~~~~~~~~~~~~~~~~~~~~

The New MicroEJ Module Project wizard is available at :guilabel:`File` > :guilabel:`New` > :guilabel:`Project...`, :guilabel:`EasyAnt` > :guilabel:`EasyAnt Project`.

Preferences Pages
~~~~~~~~~~~~~~~~~

MMM Preferences Pages are located in two dedicated pages. The following pictures show the options mapping using the same options numbers declared in :ref:`Preferences Page <mmm_preferences_page>`.

Ivy Preferences Page
####################

The Ivy Preferences Page is available at :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`Ivy` > :guilabel:`Settings`.

.. figure:: images/mmm_preferences_up_to_5-1_ivy_settings_annotated.png
   :align: center


Easyant Preferences Page
########################

The Easyant Preferences Page is available at :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`EasyAnt4Eclipse`.

.. figure:: images/mmm_preferences_up_to_5-1_ea4eclipse_annotated.png
   :align: center

Export the Build Kit
####################

- Create an empty directory (e.g. ``mmm_sdk_[version]_build_kit``),
- Locate your SDK installation plugins directory (by default, ``C:\Program Files\MicroEJ\MicroEJ SDK-[version]\rcp\plugins`` on Windows OS),
- Open the file ``com.is2t.eclipse.plugin.easyant4e_[version].jar`` with an archive manager,
- Extract the directory ``lib`` to the target directory,
- Open the file ``com.is2t.eclipse.plugin.easyant4e.offlinerepo_[version].jar`` with an archive manager,
- Navigate to directory ``repositories``,
- Extract the file named ``microej-build-repository.zip`` for MicroEJ SDK ``5.x`` or ``is2t_repo.zip`` for MicroEJ SDK ``4.1.x`` to the target directory.

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
