.. _sdk_6_multi_repo:

How To Configure Multiple Gradle Repositories
=============================================

If you want to make MicroEJ repositories available only to some projects, here is an example of configuration:

- Create a folder ``repositories`` in ``<user.home>/.gradle/init.d``.
- Move ``microej.init.gradle.kts`` to the ``repositories`` folder.
- Create a new ``repositories.init.gradle.kts`` file in ``<user.home>/.gradle/init.d`` with the following content::

   val defaultRepository = "myOtherRepo" // can be set to null
   val selectedRepository = System.getProperty("gradle.repository") ?: defaultRepository

   when (selectedRepository) {
      "microejCentral" ->
         apply {
            from("repositories/microej.init.gradle.kts")
         }
   // "myOtherRepo" ->
   //    apply {
   //       from("repositories/other.gradle.kts")
   //    }
   }

- Add the following property to a ``gradle.properties`` file at the root of your MicroEJ SDK 6 projects::

   systemProp.gradle.repository=microejCentral

This way, only projects defining the ``gradle.repository`` system property will use MicroEJ repositories. If you want to
activate these repositories by default, you can edit the ``defaultRepository`` in the ``repositories.init.gradle.kts`` file.

.. note::

   The name of the property ``gradle.repository`` is only given as exemple. You can choose the name you want as long as the
   propety defined in your ``gradle.properties`` file and in ``repositories.init.gradle.kts`` is the same.

.. warning::

   If you put a repository configuration file that ends with ``.gradle.kts`` at the root of ``<user.home>/.gradle/init.d``,
   it will be automatically loaded. Contrary to what the official Gradle documentation says, the files does not need to end
   with ``.init.gradle.kts``. That is the reason why we recommend to put the files in a folder. These files also need to end
   with ``.gradle.kts``.

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
