.. _sdk_6_howto_class_loading_verbose_logs:

How To Enable Class Loading Verbose Logs
========================================

To display verbose logs about classes loaded by the JVM, you can define the ``org.gradle.jvmargs`` property combined with JVM ``-Xlog:class`` option using file redirection. 
Here is a typical usage:

.. tabs::

   .. tab:: Windows

      .. code-block::
        
        -Dorg.gradle.jvmargs=-Xlog:class+load=info:file=%TEMP%/gradle-daemon-classes.log:time,level

   .. tab:: Linux/MacOS

      .. code-block::
        
        -Dorg.gradle.jvmargs=-Xlog:class+load=info:file=$TMPDIR/gradle-daemon-classes.log:time,level

This redirects the logs in the file ``gradle-daemon-classes.log`` in the OS temporary folder.
It should contain such logs::

  [2026-01-27T15:27:16.858+0100][info] org.slf4j.Marker source: file:/C:/Users/jdoe/.gradle/wrapper/dists/gradle-8.10.2-bin/a04bxjujx95o3nb99gddekhwo/gradle-8.10.2/lib/slf4j-api-1.7.36.jar
  [2026-01-27T15:27:16.858+0100][info] org.slf4j.helpers.BasicMarker source: file:/C:/Users/jdoe/.gradle/wrapper/dists/gradle-8.10.2-bin/a04bxjujx95o3nb99gddekhwo/gradle-8.10.2/lib/slf4j-api-1.7.36.jar
  [2026-01-27T15:27:16.859+0100][info] org.slf4j.LoggerFactory source: file:/C:/Users/jdoe/.gradle/wrapper/dists/gradle-8.10.2-bin/a04bxjujx95o3nb99gddekhwo/gradle-8.10.2/lib/slf4j-api-1.7.36.jar
  [2026-01-27T15:27:16.859+0100][info] org.slf4j.event.LoggingEvent source: file:/C:/Users/jdoe/.gradle/wrapper/dists/gradle-8.10.2-bin/a04bxjujx95o3nb99gddekhwo/gradle-8.10.2/lib/slf4j-api-1.7.36.jar

The JVM provides more options and logs categories, refer to `the official documentation <https://openjdk.org/jeps/158>`__ to learn more.

..
   | Copyright 2008-2026, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
