The Front Panel Project
=======================

Creating a Front Panel Project
------------------------------

A Front Panel project is created using the New Front Panel Project
wizard. Select:

``New > Project... > MicroEJ > Front Panel Project``

The wizard will appear:

.. figure:: ui/simulation/images/newfp.png
   :alt: New Front Panel Project Wizard
   :width: 50.0%

   New Front Panel Project Wizard

Enter the name for the new project.

Project Contents
----------------

.. figure:: ui/simulation/images/project-content.png
   :alt: Project Contents

   Project Contents

A Front Panel project has the following structure and contents:

-  The ``src`` folder is provided for the definition of ``Listeners``
   and ``DisplayExtensions``. It is initially empty. The creation of
   ``Listeners`` and ``DisplayExtensions`` will be explained later.

-  The ``JRE System Library`` is referenced, because a Front Panel
   project needs to support the writing of Java for the ``Listeners``
   and ``DisplayExtensions``.

-  The ``mockFPWidgets.jar`` contains the code for the front panel
   simulation, the widgets it supports and the types needed to implement
   ``Listeners`` and ``DisplayExtensions``.

-  The ``definitions`` folder holds the file or files that define the
   contents and layout of the front panel, with a ``.fp`` extension (the
   fp file or files), plus some supporting files. A newly created
   project will have a single fp file with the same name as the project,
   as shown above. The contents of fp files are detailed later in this
   document.

-  The ``widgets.desc`` file contains descriptions of the widgets
   supplied with the Front Panel Designer. It is used by the Front Panel
   Designer tool and must not be edited.

-  The ``resources`` folder holds images used to create the mockFP. It
   is initially empty.
