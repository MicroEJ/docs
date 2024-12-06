.. _managedc.getting_started:


Getting Started
===============

.. _managedc_getting_started_prerequisites:

Prerequisites
-------------

The following elements must be available on your workstation:

- A pre-built VEE Port using an Architecture v8.3.0 or higher.
- `WASI SDK 20 or higher <https://github.com/Wasm/wasi-sdk/releases>`__, for compiling your C code to Wasm.
- :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>`, for building the demo module from command line.

Steps
-----

To use a Wasm Module in your Application, follow these steps:

#. **Create a Standalone Application Project:**

   In a terminal, run the following command:

   .. code:: console

        mmm init -Dskeleton.org=com.is2t.easyant.skeletons -Dskeleton.module=firmware-singleapp -Dskeleton.rev=2.2.0 -Dproject.org=com.mycompany -Dproject.module=myproject -Dproject.rev=1.0.0 -Dskeleton.target.dir=myproject

   .. note:: 
      
      The project property values can be adjusted according to your needs. For more details, refer to the :ref:`MMM CLI init command documentation <mmm_cli.commands.init>`.

#. **Add the Annotations for Accessing Wasm Module in Java:**

   Create a file named ``WasmModule.java`` in the directory ``src/main/java/com/microej/wasm``  with the following content:

         .. code-block:: java

            package com.microej.wasm;
            
            import java.lang.annotation.ElementType;
            import java.lang.annotation.Retention;
            import java.lang.annotation.RetentionPolicy;
            import java.lang.annotation.Target;
            
            @Retention(RetentionPolicy.CLASS)
            @Target(ElementType.TYPE)
            public @interface WasmModule {
               String value();
            }

   Create a file named ``WasmFunction.java`` in the directory ``src/main/java/com/microej/wasm`` with the following content:
   
         .. code-block:: java

            package com.microej.wasm;
            
            import java.lang.annotation.ElementType;
            import java.lang.annotation.Target;
            
            @Target(ElementType.METHOD)
            public @interface WasmFunction {
               String value() default "";
            }


#. **Configure your Java class to call a Wasm Function:**

   Add the ``WasmModule`` annotation to the ``Main`` class with the Wasm module name:   

         .. code-block:: java      
            :emphasize-lines: 1,3

            import com.microej.wasm.*

            @WasmModule("factorial")
            public class Main {
               ...
            }

   Define a native Java method with the ``WasmFunction`` annotation in your main application class: 

         .. code-block:: java      
            :emphasize-lines: 8,9

            import com.microej.wasm.*    

            @WasmModule("factorial")
            public class Main {

               ...

               @WasmFunction
               public static native int factorial(int n);
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
            public static native int factorial(int n);
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

   .. note:: The Wasm function name and signature in the C file must match the annotated Java native method.

#. **Compile the C File to Wasm:**

   In a terminal, navigate to the module directory containing the ``module.ivy`` file and run the following command to compile the C code to Wasm:

   .. code:: console
   
      [path_to_wasi_sdk]/bin/clang -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -nostdlib -mcpu=mvp -O3 src/main/c/factorial.c -o src/main/resources/factorial.wasm

   .. note:: 
         
         The generated file name ``factorial.wasm`` matches the module name of the annotated Java class without the extension.
         It is generated to the ``src/main/resources`` directory to make it part of the Application classpath.

#. **Build the Application:**

   In a terminal, navigate to the directory containing the ``module.ivy`` file and run the following command to build the Application:

   .. code:: console

        mmm build -Dplatform-loader.target.platform.dir=<prebuilt_veeport_path>/source
        
   .. note::
      
         Replace ``<prebuilt_veeport_path>`` by the location of the root directory of your prebuilt VEE Port (see :ref:`managedc_getting_started_prerequisites`).       


   You should see the following message at the end of the build:

      .. code:: console

         BUILD SUCCESSFUL

         Total time: 20 seconds

#. **Run the Executable:**

    Once the Application is built, execute it on your device. You should get the following output:

    .. code:: console

        factorial(10) = 3628800


For further details, refer to the following sub-sections:

- :ref:`Limitations <managedc.limitations>`: An overview of the constraints and limitations associated with Wasm.
- :ref:`Troubleshooting <managedc.troubleshooting>`: Assistance for resolving common issues when working with Wasm.

..
   | Copyright 2023-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
