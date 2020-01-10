.. _testsuite-trace-analyzer:

Using the trace analyzer
========================

This section will shortly explains how to use the ``Trace Analyzer``.
The MicroEJ Test-Suite comes with an archive containing the
``Trace Analyzer`` which can be used to analyze the output trace of an
application. It can be used from different forms;

-  The ``FileTraceAnalyzer`` will analyze a file and research for the
   given tags, failing if the success tag is not found.

-  The ``SerialTraceAnalyzer`` will analyze the data from a serial
   connection.

.. _testsuite-trace-analyzer-options:

The TraceAnalyzer tasks options
-------------------------------

Here is the common options to all TraceAnalyzer tasks:

-  ``successTag``: the regular expression which is synonym of success
   when found (by default ``.*PASSED.*``).

-  ``failureTag``: the regular expression which is synonym of failure
   when found (by default ``.*FAILED.*``).

-  ``verboseLevel``: int value between 0 and 9 to define the verbose
   level.

-  ``waitingTimeAfterSuccess``: waiting time (in s) after success before
   closing the stream (by default 5).

-  ``noActivityTimeout``: timeout (in s) with no activity on the stream
   before closing the stream. Set it to 0 to disable timeout (default
   value is 0).

-  ``stopEOFReached``: boolean value. Set to ``true`` to stop analyzing
   when input stream EOF is reached. If ``false``, continue until
   timeout is reached (by default ``false``).

-  ``onlyPrintableCharacters``: boolean value. Set to ``true`` to only
   dump ASCII printable characters (by default ``false``).

.. _testsuite-trace-analyzer-file:

The FileTraceAnalyzer task options
----------------------------------

Here is the specific options of the FileTraceAnalyzer task:

-  ``traceFile``: path to the file to analyze.

.. _testsuite-trace-analyzer-serial:

The SerialTraceAnalyzer task options
------------------------------------

Here is the specific options of the SerialTraceAnalyzer task:

-  ``port``: the comm port to open.

-  ``baudrate``: serial baudrate (by default 9600).

-  ``databits``: databits (5|6|7|8) (by default 8).

-  ``stopBits``: stopbits (0|1|3 for (1_5)) (by default 1).

-  ``parity``: ``none`` \| ``odd`` \| ``event`` (by default ``none``).
