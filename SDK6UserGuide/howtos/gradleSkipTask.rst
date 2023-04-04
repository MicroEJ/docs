.. _sdk_6_howto_gradle_skip_task:

How To Skip a Gradle Task
=========================

When a task is executed, it is possible to skip one or more of the tasks on which the called task depends.
For example, you can skip the ``test`` task if you want to build a project without executing the tests.

If you want to skip a task, one of the following ways can be used :

- Add the ``-x`` or ``--exclude-task`` option in the command line::

   gradle build -x test

  The task is skipped for this execution only.

- Exclude the task in the build script of the project ::

   project.gradle.startParameter.excludedTaskNames.add("test")

  The task is never executed.

When one of these two ways is used, not only the task but also all the tasks on which it depends are skipped.
For example, if you choose to skip the ``test`` task, all the tasks which are used to produce 
the test runtime classpath are also skipped.

Skip the task only
------------------

It is possible to skip a task but still execute the tasks on which it depends using one of the following ways : 

- Disable the task in the build script of the project::

   tasks.test {
     enabled = false
   }

  The task is never executed.

- Define a predicate in the build script of the project::

   tasks.test {
     val skipProvider = providers.gradleProperty("skipTest")
     onlyIf {
       !skipProvider.isPresent() 
     }
   }

  The task is skipped each time the predicate evaluates to ``false``. In this example, 
  the ``test`` task is not executed if the ``skipTest`` property is added in the command line::

   gradle build -PskipTest


..
   | Copyright 2008-2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
