.. _managedc.getting_started:


Getting Started
===============

Welcome to the Managed C Getting Started Guide. This guide is designed to help application developers quickly get up to speed with Managed C. You’ll learn how to set up your environment and build your first Managed C application. Let’s get started!

.. _managedc_getting_started_prerequisites:

Prerequisites
-------------

Before you begin, ensure that the following elements are available on your workstation:

.. tabs:: 

      .. tab:: SDK6

         - A pre-built VEE Port using an Architecture v8.4.0 or higher.

      .. tab:: SDK 5

         - A pre-built VEE Port using an Architecture v8.4.0 or higher.
         - :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>`, for building the demo module from command line.         

Steps
-----

To use Managed C in your Application, follow these steps:

#. **Install WASI-SDK:**

   Download the `WASI SDK version 20 or higher <https://github.com/WebAssembly/wasi-sdk/releases>`__.
   
   Extract it at the location of your choice on your machine. 
   This location will be referred to as ``[path_to_wasi_sdk]`` in the rest of the documentation.

#. **Create a Standalone Application Project:**

   In the terminal, run the following command:

   .. tabs::

      .. tab:: SDK 6

         .. code:: bash

               git clone https://github.com/MicroEJ/Tool-Project-Template-Application.git
               cd Tool-Project-Template-Application
               rm -rf .git*

      .. tab:: SDK 5

         .. code:: bash

               mmm init -Dskeleton.org=com.is2t.easyant.skeletons -Dskeleton.module=firmware-singleapp -Dskeleton.rev=2.+ -Dproject.org=com.mycompany -Dproject.module=myproject -Dproject.rev=1.0.0 -Dskeleton.target.dir=myproject

         .. note::

            The project property values can be adjusted according to your needs. For more details, refer to the :ref:`MMM CLI init command documentation <mmm_cli.commands.init>`.

         .. note::

            If you're using PowerShell, prepend the token \--% before passing the arguments to prevent PowerShell from parsing them. For example: ``mmm init --% -D...``.
   

#. **Add the WASI Add-on Library to Your Project:**

   The MicroEJ WASI library provides utility classes, annotations, and WASI implementation required for developping Managed C.

   .. tabs::

      .. tab:: Gradle (build.gradle.kts)

         .. code-block:: kotlin

            implementation("ej.library.runtime:wasi:0.1.0")

      .. tab:: MMM (module.ivy)

         .. code-block:: xml

            <dependency org="ej.library.runtime" name="wasi" rev="0.1.0"/>

#. **Configure your Java Class to Call a Managed C Function:**

   Add the ``WasmModule`` annotation to the ``Main`` class with the Wasm module name:   

         .. code-block:: java      
            :emphasize-lines: 1,3

            import ej.wasm.*;

            @WasmModule("example")
            public class Main {
               ...
            }

   Define a native Java method in your main application class using the ``WasmFunction`` annotation:

         .. code-block:: java      
            :emphasize-lines: 8,9

            import ej.wasm.*;   

            @WasmModule("example")
            public class Main {

               ...

               @WasmFunction
               public static native synchronized int factorial(int n);
            }

   Finalize your application's ``main`` method with a call to the ``factorial`` function:

      .. code-block:: java
         :emphasize-lines: 5
         
         @WasmModule("example")
         public class Main {
            
            public static void main(String[] args) {
               System.out.println("factorial(10) = " + factorial(10));
            }
            
            @WasmFunction
            public static native synchronized int factorial(int n);
         }

#. **Create the C File:**

   Create a file named ``example.c`` in the directory ``src/main/c``:

   .. code:: c

        int factorial(int n) {
            if (n == 1) {
                return 1;
            } else {
                return n * factorial(n - 1);
            }
        }

   .. note:: The name and signature of the Managed C function in the C file must match the annotated Java native method.

#. **Compile the C File to WebAssembly:**

   In the terminal, navigate to your application base directory and run the following command to compile the C code to WebAssembly:

   .. code:: bash
   
      [path_to_wasi_sdk]/bin/clang -Wl,--no-entry -Wl,--stack-first -Wl,--allow-undefined -z stack-size=4096 -mcpu=mvp -O3 -Wl,--export=factorial src/main/c/example.c -o src/main/resources/example.wasm

   .. note::
         
         To call a Managed C function from Java, you need to export it using the ``-Wl,--export=[function_name]`` link option.
         In this case, the ``factorial`` function is exported with ``-Wl,--export=factorial``.

   .. note::
         
         The generated file name ``example.wasm`` matches the module name of the annotated Java class
         and is created in the ``src/main/resources`` directory to facilitate inclusion in the Application classpath.

#. **Build the Application:**

   In the terminal, navigate to your application base directory and perform the following steps:

   .. tabs::
   
      .. tab:: SDK 6

         Edit the file ``build.gradle.kts`` and add the location to :ref:`your prebuilt VEE Port <managedc_getting_started_prerequisites>` using ``microejVee(files("/path/to/veeport"))``.
            
         Then run the following command to build the Application:
      
         .. code:: bash

            ./gradlew buildExecutable
      
         .. note::

            Please refer to the :ref:`sdk_6_select_veeport` section for alternative methods to connect your VEE Port.

      .. tab:: SDK 5

         Run the following command to build the Application:            

         .. code:: bash

               mmm build -Dplatform-loader.target.platform.dir=<prebuilt_veeport_path>/source
            
         .. note::
         
               Replace ``<prebuilt_veeport_path>`` with the location of :ref:`your prebuilt VEE Port <managedc_getting_started_prerequisites>`.   
               See :ref:`platform_selection` section for alternative ways to connect your VEE Port.    

#. **Run the Executable:**

    Once the Application is built, execute it on your device. 
    
.. tabs::
   
   .. tab:: SDK 6

      Run the following command:
      
      .. code:: bash

         ./gradlew runOnDevice
      
   .. tab:: SDK 5

      Refer to :ref:`device_build` section.

After deployment, you should see the following output:

.. code:: console

   factorial(10) = 3628800

Congratulations! You have successfully run your first Managed C code. You are now ready to explore how to build more complex Managed C projects.

For further details, refer to the following sub-sections:

- :ref:`managedc.compilation`: Instructions on how to compile and link an existing C or C++ project to WebAssembly.
- :ref:`managedc.binding`: Information on how to seamlessly link your Java and Managed C code.
- :ref:`Linear memory <managedc.linear.memory>`: Instructions to configure WebAssembly Linear memory.
- :ref:`wasm.wasi`: Explore WASI, the WebAssembly System Interface implemented by MicroEJ.
- :ref:`Troubleshooting <managedc.troubleshooting>`: Help with resolving common issues when working with Managed C.

..
   | Copyright 2023-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
