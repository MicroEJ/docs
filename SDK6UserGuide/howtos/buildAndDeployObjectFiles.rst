.. _sdk_6_howto_deploy_object_file_without_building-executable:

How To Build and Deploy Object Files without Building the Executable
====================================================================

If you need to produce the object files of the Application, deploy them to the BSP, 
but delegate the build of the Executable to another build system, 
call the ``buildExecutable`` task with the Application Option ``deploy.bsp.microejscript`` set to ``false``::

    ./gradlew buildExecutable -Ddeploy.bsp.microejscript=false

You should see logs similar to the following ones::

    =============== [ Deployment ] ===============
    The application output file has been generated here: 'C:\Users\johndoe\my-project\my-app\build\application\object\SOAR.o'
    =============== [ Completed Successfully ] ===============
    VEE Port connected to BSP location 'C:\Users\johndoe\my-project\bsp' using platform option 'root.dir' in 'bsp/bsp.properties'.
    =============== [ Deployment ] ===============
    MicroEJ application (microejapp.o) has been deployed to: 'C:\Users\johndoe\my-project\bsp\vee\lib'.
    MicroEJ library (microejruntime.a) has been deployed to: 'C:\Users\johndoe\my-project\bsp\vee\lib'.
    MicroEJ header files (*.h) have been deployed to: 'C:\Users\johndoe\my-project\bsp\vee\inc'.
    =============== [ Completed Successfully ] ===============

..
   | Copyright 2008-2024, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
