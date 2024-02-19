Usage
=====

To use the widgets provided by the widget library, add `Widget library module`_ to the project build file:

.. tabs::

   .. tab:: Gradle (build.gradle.kts)

      .. code-block:: java

         implementation("ej.library.ui:widget:4.1.0")

   .. tab:: MMM (module.ivy)

      .. code-block:: xml

         <dependency org="ej.library.ui" name="widget" rev="4.1.0"/>

To fork one of the provided widgets, duplicate the associated Java class from the widget library JAR into the source code of your application.
It is recommended to move the duplicated class to an other package and to rename the class in order to avoid confusion between your forked class and the original class.

.. _Widget library module: https://repository.microej.com/modules/ej/library/ui/widget/    
..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
