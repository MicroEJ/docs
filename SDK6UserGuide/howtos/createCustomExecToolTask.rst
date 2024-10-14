.. _sdk_6_create_cutom_exectool_task:

How To Create Custom ExecTool Task
==================================

MicroEJ provides the Gradle ``execTool`` task that allows to execute all :ref:`Command Line Tools <sdk6_microejtools>`. 
However, it is possible to create a custom task of type ``ExecToolTask`` specific to a tool. This task can then be used to execute the tool before or after another task when 
building your project for example.

You can create a new ``ExecToolTask`` in the build file of your project as follows:

- Import the ``ExecToolTask`` and ``LoadVeeTask`` classes::

    import com.microej.gradle.tasks.ExecToolTask
    import com.microej.gradle.tasks.LoadVeeTask

- Create a new task of type ``ExecToolTask``::

    val loadVee = tasks.withType(LoadVeeTask::class).named("loadVee")
    val mainSourceSet = project.extensions.getByType(SourceSetContainer::class).getByName(SourceSet.MAIN_SOURCE_SET_NAME)

    tasks.register<ExecToolTask>("myCustomTask") {
        veeDir.set(loadVee.flatMap { it.loadedVeeDir })
        resourcesDirectories.from(mainSourceSet.output.resourcesDir, layout.buildDirectory.dir("generated/microej-app-wrapper/resources"))
        classesDirectories.from(mainSourceSet.output.classesDirs, layout.buildDirectory.dir("generated/microej-app-wrapper/classes"))
        classpathFromConfiguration.from(project.configurations.getByName("runtimeClasspath"))

        toolName = "microej_tool_name"
        toolProperties.putAll(mapOf(
            "property1" to "value1",
            "property2" to "value2",
            ...
        ))
    }

.. note::

    Only the ``toolName`` and ``toolProperties`` inputs are specific to the tool. The other task inputs are common to all tasks of type ``ExecToolTask``.

- The custom task can then be executed::

    $ ./gradlew myCustomTask

As an example, here is how to create a task which calls the :ref:`sdk6_localDeployTool` tool::

    import com.microej.gradle.tasks.ExecToolTask
    import com.microej.gradle.tasks.LoadKernelExecutableTask
    import com.microej.gradle.tasks.LoadVeeTask

    plugins {
        id("com.microej.gradle.application") version "0.19.0"
    }

    group="com.mycompany"
    version="1.0.0"

    microej {
        applicationEntryPoint = "com.mycompany.MyFeature"
    }

    dependencies {
        ...
        microejVee("com.mycompany:myKernel:1.0.0")
        ...
    }

    ...

    val loadVee = tasks.withType(LoadVeeTask::class).named("loadVee")
    val loadKernelExecutable = tasks.withType(LoadKernelExecutableTask::class).named("loadKernelExecutable")
    val mainSourceSet = project.extensions.getByType(SourceSetContainer::class).getByName(SourceSet.MAIN_SOURCE_SET_NAME)
    val buildDirectory = layout.buildDirectory

    tasks.register<ExecToolTask>("localDeploy") {
        // These inputs are required for all custom tasks of type "ExecToolTask".
        veeDir.set(loadVee.flatMap { it.loadedVeeDir })
        resourcesDirectories.from(mainSourceSet.output.resourcesDir, buildDirectory.dir("generated/microej-app-wrapper/resources"))
        classesDirectories.from(mainSourceSet.output.classesDirs, buildDirectory.dir("generated/microej-app-wrapper/classes"))
        classpathFromConfiguration.from(project.configurations.getByName("runtimeClasspath"))

        // These inputs are specific to the Local Deployment Socket.
        toolName = "localDeploymentSocket"
        inputs.file(loadKernelExecutable.flatMap { it.loadedKernelExecutableFile })
        toolProperties.putAll(mapOf(
            "application.main.class" to microej.applicationEntryPoint,
            "board.server.host" to "10.0.0.171",
            "board.server.port" to "4000",
            "board.timeout" to "120000",
            "use.storage" to "true"
        ))

        doFirst {
            // Use the Executable of the Kernel provided as dependency to build the Feature file.
            toolProperties["kernel.filename"] = loadKernelExecutable.get().loadedKernelExecutableFile.get().asFile.absolutePath
        }
    }

You can then execute the task to build and deploy the Feature file of the Application::

    $ ./gradlew localDeploy

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
