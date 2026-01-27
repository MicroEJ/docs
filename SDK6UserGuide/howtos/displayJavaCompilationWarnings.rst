.. _sdk_6_java_compilation_warnings:

How To Display Java Compilation Warnings
========================================

Starting from SDK 6 1.6.0, the Java compilation warnings are not displayed by default. 
This helps avoid `this Eclipse Compiler for Java known bug <SDK6UserGuide/howtos/disableIvyDescriptorPublication.rst>`__.

If you still want to see these warnings, you can enable them by setting the Gradle property ``java.compilation.warnings.enabled`` to ``true``.
You can configure this property in several ways:  
- In a ``gradle.properties`` file located in ``<USER_HOME>/.gradle/`` to apply it globally.  
- In a ``gradle.properties`` file located at the root of your Gradle project to apply it only at the project level.  
- Pass it directly via the command line using the option ``-Pjava.compilation.warnings.enabled=true``.

..
   | Copyright 2008-2026, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
