.. _sdk_6_publish_project:

Publish a Project
=================

Publishing a module to a repository is achieved by executing the ``publish`` task::

  $ gradle publish

The following artifacts are automatically published:

- the main artifact, which is the JAR file for Application and Add-On Library natures
- the README.md file
- the CHANGELOG.md file
- the LICENSE.txt file
- the Gradle module descriptor file
- the Ivy descriptor file (to allow SDK 5 project to fetch it)

The only requirement is to have a ``maven`` publication repository configured.
This can be done in the build file for example, with::

  publishing {
      repositories {
          maven {
              name = "mavenPublish"
              url = uri("https://my.server/repository")
          }
      }
  }

Please refer to `the official documentation <https://docs.gradle.org/current/userguide/publishing_maven.html#publishing_maven:repositories>`__ for more information on publication repositories.

..
   | Copyright 2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
