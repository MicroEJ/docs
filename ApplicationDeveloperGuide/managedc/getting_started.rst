.. _managedc.getting_started:


Getting Started
===============

To use Managed C in your MicroEJ application, follow these steps:

1. **Install the MMM CLI (Command Line Interface):** Follow the instructions in the :ref:`MMM CLI (Command Line Interface) <mmm_build_kit>`.

2. **Create a Standalone Application Project:**

   Run the following command:

   .. code:: console

        mmm init -Dskeleton.org=com.is2t.easyant.skeletons -Dskeleton.module=firmware-singleapp -Dskeleton.rev=2.2.0 -Dproject.org=com.mycompany -Dproject.module=myproject -Dproject.rev=1.0.0 -Dskeleton.target.dir=myproject

   Adjust the property values according to your needs. For more details, refer to the :ref:`MMM CLI init command documentation <mmm_cli.commands.init>`.

3. **Add the Managed C Function Annotation:**

   Add the ``ManagedCFunction`` annotation in your Java code:

   .. code:: java

        package com.mycompany;

        import java.lang.annotation.ElementType;
        import java.lang.annotation.Target;

        @Target(ElementType.METHOD)
        public @interface ManagedCFunction {
        }

4. **Define a Native Java Method:**

   Define a native Java method with the ``ManagedCFunction`` annotation in your main application class:

   .. code:: java

        @ManagedCFunction
        public static final native int factorial(int n);

5. **Call the Managed C function:**

   Add the following lines in your application's main method:

   .. code:: java

        System.out.println("factorial(10) = " + factorial(10));

6. **Create the C File:**

   Create a file named ``factorial.c`` in the folder ``src/main/c``:

   .. code:: c

        int factorial(int n) {
            if (n == 1) {
                return 1;
            } else {
                return n * factorial(n - 1);
            }
        }

   .. warning:: Ensure that the Managed C function name and signature in the C file match the Java annotated native method.

7. **Compilation and Build:**

   Follow :ref:`these steps <managedc.compilation>` to compile your Managed C code.

8. **Copy the WebAssembly File:**

   Copy the WebAssembly file to the folder ``src/main/resources`` and name it ``factorial.wasm``.

9. **Build the Project:**

   In a terminal, navigate to the folder containing the ``module.ivy`` file and build the project:

   .. code:: console

        mmm build

   You should see the following message at the end of the build:

   .. code:: console

        BUILD SUCCESSFUL

        Total time: 20 seconds

10. **Run the Executable:**

    .. warning:: 
    
        Managed C is not currently supported in simulation.


    Once the application is built, execute it on a real hardware. You should see the following output:

    .. code:: console

        factorial(10) = 3628800


For further details, refer to the following sub-sections:

- :ref:`Limitations <managedc.limitations>`: An overview of the constraints and limitations associated with Managed C.
- :ref:`Troubleshooting <managedc.troubleshooting>`: Assistance for resolving common issues when working with Managed C.

..
   | Copyright 2023, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
