.. _resolve_dependencies_in_workspace:

---------------------------------
Resolve Dependencies in Workspace
---------------------------------


When resolving the modules' dependencies, if the project of a dependency is imported and opened in the same workspace as the module, 
the project is directly used for compilation and execution instead of using the dependency,
provided that the dependency's project has the same version as the one required by the module.

For example, suppose that the workspace contains a module ``myApp`` and its dependency ``mylib`` :

.. figure:: images/dependencyInWorkspace.png
   :alt:  A module and its dependency opened in the same workspace
   :align: center
   :scale: 100%

   A module and its dependency opened in the same workspace

If the ``mylib`` project's version is ``1.0.0``, it is used for compilation and execution.
Otherwise the published artifact is downloaded from the artifact repository.

To avoid a dependency to be resolved in the workspace, you can close the corresponding project or remove it from the workspace.

.. warning::
   If you open, close, import or remove a project, you must refresh the dependency resolution of other previously imported projects
   by clicking on the :guilabel:`Resolve All` button :

   .. figure:: images/mmm_shortcut_resolveAll.png
      :alt: Resolve all the workspace projects
      :align: center
      :scale: 100%
   
      Resolve all the workspace projects


.. _resolve_foundation_libraries_in_workspace:

-----------------------------------------
Resolve Foundation Libraries in Workspace
-----------------------------------------

A :ref:`Foundation Library <libraries>` is composed of : 

- An API project that contains Java classes, methods and fields used at compile time with their associated Javadoc,
  
- An Implementation project that contains the runtime code executed by the Platform and Low Level C header files

Beside Foundation Library projects, there is usually a :ref:`Mock <mock>` project that contains the implementation of native methods for simulation.

.. note::

   To learn how to setup a Foundation Library, please consult the How-to available on 
   `<https://github.com/MicroEJ/How-To/tree/master/FoundationLibrary-Get-Started>`_.

When the API is set as a dependency, the Implementation project is automatically used at runtime if it is opened in the workspace.

If a Mock project or a Front Panel project is also opened in the workspace, it is automatically used for execution on Simulator. 

.. note::

   When opened in the workspace, Foundation Library Implementation projects, Mock projects and Front Panel projects
   are loaded, regardless of their version, prior to the ones provided by the Platform (if any).

To avoid the use of an Implementation project, a Mock project or a Front Panel project, 
uncheck the :guilabel:`Resolve Foundation Library in workspace` option in :guilabel:`Window` > :guilabel:`Preferences` > :guilabel:`MicroEJ` > :guilabel:`Settings`.

.. figure:: images/resolve.png
   :alt: Resolve Foundation Library in workspace
   :align: center
   :scale: 100%

   Resolve Foundation Library in workspace


.. _resolve_front_panel_in_workspace:

--------------------------------
Resolve Front Panel in Workspace
--------------------------------

A Front Panel is a "mock" of the control panel of the device. 
The Front Panel generates a graphical representation of the device, 
and is displayed in a window on the user's development machine when the application is executed in the Simulator.

.. note::

   To learn more about Front Panels, consult the :ref:`Front Panel section <section_frontpanel>`.

When a Front Panel project is opened in the workspace, it is automatically used at runtime when launching the Simulator.

If the workspace contains several Front Panel projects, they are all automatically used by the Simulator, which can very probably causes issues.
You can select the Front Panel you want to use by closing all the other Front Panel projects.

Also, a Front Panel project can contain several Front Panel descriptor files.
Refer to the :ref:`section_frontpanel_multiple_fp_files` section to know how to select the file you want to use.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
