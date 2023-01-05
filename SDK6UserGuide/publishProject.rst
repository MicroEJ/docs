.. _sdk_6_publish_project:

Publish a Project
=================

Publishing is the process by which the built artifacts of a module is made available to other modules or any other systems.

The requirements to publish a module are:

- defining the ``group``, ``name`` and ``version`` properties.
  The ``name`` can be set in the ``settings.gradle.kts`` file, thanks to the property ``rootProject.name`` (for example ``rootProject.name = "myModule"``).
  The ``group`` and version ``version`` properties can be set in the ``build.gradle.kts`` file::

    group = "com.mycompany"
    version = "1.0.0"

- declaring a ``maven`` publication repository.
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

  $ gradle publish

The following artifacts are automatically published:

- the main artifact, which is the JAR file for Application and Add-On Library natures.
- the README.md file.
- the CHANGELOG.md file.
- the LICENSE.txt file.
- the Gradle module descriptor file.
- the Ivy descriptor file (to allow SDK 5 project to fetch it).

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
