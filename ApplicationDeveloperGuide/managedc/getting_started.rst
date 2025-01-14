.. _managedc.getting_started:


Getting Started
===============

.. _managedc_getting_started_prerequisites:

Prerequisites
-------------

The following elements must be available on your workstation:

.. tabs:: 

      .. tab:: SDK6

         - A pre-built VEE Port using an Architecture v8.3.0 or higher.
         - `WASI SDK 20 or higher <https://github.com/WebAssembly/wasi-sdk/releases>`__, for compiling your C code to WebAssembly.

      .. tab:: SDK 5

         - A pre-built VEE Port using an Architecture v8.3.0 or higher.
         - `WASI SDK 20 or higher <https://github.com/WebAssembly/wasi-sdk/releases>`__, for compiling your C code to WebAssembly.
         - :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>`, for building the demo module from command line.         

Steps
-----

To use Managed C in your Application, follow these steps:

#. **Create a Standalone Application Project:**


   In a terminal, run the following command:

.. tabs::

   .. tab:: SDK 6

      .. code:: bash

            git clone git@github.com:MicroEJ/Tool-Project-Template-Application.git
            cd Tool-Project-Template-Application
            rm -rf .git*

   .. tab:: SDK 5

      .. code:: bash

            mmm init -Dskeleton.org=com.is2t.easyant.skeletons -Dskeleton.module=firmware-singleapp -Dskeleton.rev=2.+ -Dproject.org=com.mycompany -Dproject.module=myproject -Dproject.rev=1.0.0 -Dskeleton.target.dir=myproject

      .. note::

         The project property values can be adjusted according to your needs. For more details, refer to the :ref:`MMM CLI init command documentation <mmm_cli.commands.init>`.

      .. note::

         If you're using PowerShell, prepend the token \--% before passing the arguments to prevent PowerShell from parsing them. For example: ``mmm init --% -D...``.
   

#. **Add the Annotations for Accessing Wasm Module in Java:**

   Create a file named ``WasmModule.java`` in the directory ``src/main/java/ej/wasm``  with the following content:

         .. code-block:: java

            package ej.wasm;
            
            import java.lang.annotation.ElementType;
            import java.lang.annotation.Retention;
            import java.lang.annotation.RetentionPolicy;
            import java.lang.annotation.Target;
            
            @Retention(RetentionPolicy.CLASS)
            @Target(ElementType.TYPE)
            public @interface WasmModule {
               String value();
            }

   Create a file named ``WasmFunction.java`` in the directory ``src/main/java/ej/wasm`` with the following content:
   
         .. code-block:: java

            package ej.wasm;
            
            import java.lang.annotation.ElementType;
            import java.lang.annotation.Target;
            
            @Target(ElementType.METHOD)
            public @interface WasmFunction {
               String value() default "";
            }


#. **Configure your Java class to call a Managed C Function:**

   Add the ``WasmModule`` annotation to the ``Main`` class with the Wasm module name:   

         .. code-block:: java      
            :emphasize-lines: 1,3

            import ej.wasm.*;

            @WasmModule("factorial")
            public class Main {
               ...
            }

   Define a native Java method with the ``WasmFunction`` annotation in your main application class: 

         .. code-block:: java      
            :emphasize-lines: 8,9

            import ej.wasm.*;   

            @WasmModule("factorial")
            public class Main {

               ...

               @WasmFunction
               public static native synchronized int factorial(int n);
            }

   Finalize your application's ``main`` method with a call to the ``factorial`` function:

      .. code-block:: java
         :emphasize-lines: 5
         
         @WasmModule("factorial")
         public class Main {
            
            public static void main(String[] args) {
               System.out.println("factorial(10) = " + factorial(10));
            }
            
            @WasmFunction
            public static native synchronized int factorial(int n);
         }

#. **Create the C File:**

   Create a file named ``factorial.c`` in the directory ``src/main/c``:

   .. code:: c

        int factorial(int n) {
            if (n == 1) {
                return 1;
            } else {
                return n * factorial(n - 1);
            }
        }

   .. note:: The Managed C function name and signature in the C file must match the annotated Java native method.

#. **Compile the C File to WebAssembly:**

   In a terminal, navigate to your application base directory and run the following command to compile the C code to WebAssembly:

   .. code:: bash
   
      [path_to_wasi_sdk]/bin/clang -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -z stack-size=4096 -nostdlib -mcpu=mvp -O3 src/main/c/factorial.c -o src/main/resources/factorial.wasm

   .. note::
         
         The generated file name ``factorial.wasm`` matches the module name of the annotated Java class.
         It is generated to the ``src/main/resources`` directory as a convenience to make it part of the Application classpath.

#. **Build the Application:**

   In a terminal, navigate to your application base directory and perform the following steps:

.. tabs::
   
   .. tab:: SDK 6

      Edit the file ``build.gradle.kts`` and add the location to :ref:`your prebuilt VEE Port <managedc_getting_started_prerequisites>` using ``microejVee(files("/path/to/veeport"))``.
            
      Then run the following command to build the Application:
      
      .. code:: bash

         ./gradlew buildExecutable
      
      .. note::

         See :ref:`sdk_6_select_veeport` section for alternative ways to connect your VEE Port.

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

    
Once the Executable is deployed on your Device, you should get the following output:

.. code:: console

   factorial(10) = 3628800

Congratulations! You just run your first Managed C code. You are now ready to learn how to build more complex Managed C projects.

For further details, refer to the following sub-sections:

- :ref:`managedc.compilation`: Instructions to compile and link an existing C or C++ project to WebAssembly.
- :ref:`managedc.communication`: Specifies the communication mechanism to seamlessly link your Java and Managed C code together. 
- :ref:`wasm.wasi`: Discover WASI, the WebAssembly System Interface implemented by MicroEJ.
- :ref:`Troubleshooting <managedc.troubleshooting>`: Assistance for resolving common issues when working with Managed C.

..
   | Copyright 2023-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
