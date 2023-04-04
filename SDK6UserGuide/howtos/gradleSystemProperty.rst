.. _sdk_6_howto_gradle_system_property:

How To Pass a Property to Project Build Script
==============================================

It is sometimes needed to use properties to pass values to a project build script.
This avoids to have hardcoded values in the project sources.

Gradle allows to define System Properties with the command line thanks to the ``-D`` prefix:

.. code:: console
   
   $ gradle build -DmyPropertyName="myPropertyValue"

and use them with the API ``providers.systemProperty("myPropertyName").get()``.

For example when the VEE Port of an Application is defined with the ``veePortDir`` variable,
the project can be configured with::

   microej {
      veePortDir = providers.systemProperty("myVeePortDir").get()
   }

and built with:

.. code:: console

   $ gradle build -DmyVeePortDir="C:\\path\\to\\my\\veePort\\directory"

The ``providers.systemProperty("myPropertyName")`` API returns a ``org.gradle.api.provider.Provider`` object, which provides other capabilities like:

- defining a default value if the System Property does not exist: ``providers.systemProperty("myPropertyName").getOrElse("myDefaultValue")``
- returning ``null`` if the value does not exist: ``providers.systemProperty("myPropertyName").getOrNull()``.

..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
