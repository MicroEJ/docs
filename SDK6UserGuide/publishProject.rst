.. _sdk_6_publish_project:

Publish a Project
=================

Publishing is the process by which the built artifacts of a module is made available to other modules or any other systems.

The requirements to publish a module are:

- Defining the ``name`` of the module. It is set by default to the name of the module folder,
  and can be changed in the ``settings.gradle.kts`` file located at the root of the module, thanks to the property ``rootProject.name``::
    
    rootProject.name = "myModule"

- Defining the ``group`` and ``version`` properties.
  They can be set in the ``build.gradle.kts`` file::

    group = "com.mycompany"
    version = "1.0.0"

  .. warning::

    Refer to :ref:`Manage Versioning page <sdk6_manage_versioning>` to know how to version your module.

- Declaring a ``maven`` publication repository.
  This can be done in the build file for example, with::

    publishing {
        repositories {
            maven {
                name = "mavenPublish"
                url = uri("https://my.server/repository")
            }
        }
    }

  Refer to `the official documentation <https://docs.gradle.org/current/userguide/publishing_maven.html#publishing_maven:repositories>`__ for more information on publication repositories.

Then the publication of a module to a repository is achieved by executing the ``publish`` task::

  $ ./gradlew publish

The following artifacts are automatically published:

- The main artifact, which is the JAR file for Application and Add-On Library natures.
- The README.md file.
- The CHANGELOG.md file.
- The LICENSE.txt file.
- The ASSEMBLY_EXCEPTION.txt file.
- The Gradle module descriptor file.
- The Ivy descriptor file (to allow SDK 5 project to fetch it).
- The WPK file, if the project is an Application.

.. note::

  Ivy descriptor publication can be disabled. You can refer to :ref:`disable Ivy Descriptor publication How-to page <sdk_6_disable_ivy_descriptor_publication>`
  if you don't need to publish Ivy descriptor. 

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
