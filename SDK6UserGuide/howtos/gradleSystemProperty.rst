.. _sdk_6_howto_gradle_system_property:

How To Pass a Property to Project Build Script
==============================================

It is sometimes needed to use properties to pass values to a project build script.
This avoids to have hardcoded values in the project sources.

Gradle allows to define System Properties with the command line thanks to the ``-D`` prefix:

.. code:: console
   
   $ ./gradlew build -DmyPropertyName="myPropertyValue"

and use them with the API ``providers.systemProperty("myPropertyName").get()``.

For example to define a local VEE Port directory, the project can be configured with::

   dependencies {
      microejVee(files(providers.systemProperty("myVeePortPath").get()))
   }

and built with:

.. code:: console

   $ ./gradlew build -DmyVeePortPath="C:\\path\\to\\my\\veePort\\directory"

The ``providers.systemProperty("myPropertyName")`` API returns a ``org.gradle.api.provider.Provider`` object, which provides other capabilities like:

- defining a default value if the System Property does not exist: ``providers.systemProperty("myPropertyName").getOrElse("myDefaultValue")``
- returning ``null`` if the value does not exist: ``providers.systemProperty("myPropertyName").getOrNull()``.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
