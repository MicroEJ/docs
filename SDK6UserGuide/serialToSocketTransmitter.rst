.. _sdk6_tool_serial_to_socket:

============================
Serial to Socket Transmitter
============================


Principle
=========

The MicroEJ Serial to Socket Transmitter is a tool which
transfers all bytes from a serial port to a TCP client or TCP server.

It is typically used to transfer the output traces of a testsuite executed on a device.

Use
===

.. tabs::

    .. group-tab:: SDK 6 1.6.0 and higher

        To start transferring data from the ``COM0`` serial port to the port ``5555``,
        execute the ``serialToSocket`` task as follows:

        .. code:: console

            ./gradlew serialToSocket

        After the execution of the task, you should see a message similar to the following one:

        
        .. code:: console

            INFO: Now listening on Serial Port COM0
            INFO: Redirecting to localhost:5555.

        To customize the serial port, baudrate, socket port or socket address,
        you can provide the corresponding properties (see :ref:`options`). 

    .. group-tab:: SDK 6 1.5.0 and below

        To start transferring data from the ``COM8`` serial port to the port ``5555``,
        execute the ``execTool`` task as followed:

        .. code:: console

            ./gradlew execTool --name=serialToSocketTransmitter \
            --toolProperty=serial.to.socket.comm.port="COM8" \
            --toolProperty=serial.to.socket.comm.baudrate="115200" \
            --toolProperty=serial.to.socket.server.port="5555" \
            --console plain

        |

        **Run Serial to Socket Transmitter with Custom Task**

        To simplify the use of the Serial to Socket Transmitter, it is also possible to create a :ref:`custom task <sdk_6_create_cutom_exectool_task>`
        in the ``build.gradle.kts`` file of your project as follows:

        - Import the ``ExecToolTask`` and ``LoadVeeTask`` classes::

            import com.microej.gradle.tasks.ExecToolTask
            import com.microej.gradle.tasks.LoadVeeTask

        - Create a new task of type ``ExecToolTask``::

            val loadVee = tasks.withType(LoadVeeTask::class).named("loadVee")
            val mainSourceSet = project.extensions.getByType(SourceSetContainer::class).getByName(SourceSet.MAIN_SOURCE_SET_NAME)

            tasks.register<ExecToolTask>("serialToSocketTransmitter") {
                group = "microej"
                veeDir.set(loadVee.flatMap { it.loadedVeeDir })
                resourcesDirectories.from(mainSourceSet.output.resourcesDir, layout.buildDirectory.dir("generated/microej-app-wrapper/resources"))
                classesDirectories.from(mainSourceSet.output.classesDirs, layout.buildDirectory.dir("generated/microej-app-wrapper/classes"))
                classpathFromConfiguration.from(project.configurations.getByName("runtimeClasspath"))

                toolName = "serialToSocketTransmitter"
                toolProperties.putAll(mapOf(
                    "serial.to.socket.comm.port" to "COM8",
                    "serial.to.socket.comm.baudrate" to "115200",
                    "serial.to.socket.server.port" to "5555"
                ))
            }

        - The custom task can then be executed::

            $ ./gradlew serialToSocketTransmitter

.. _options:

Options
=======

.. tabs::

    .. group-tab:: SDK 6 1.6.0 and higher

        The Serial to Socket Transmitter can be configured using the following options in the ``microej.serialToSocket`` block of the ``gradle.properties`` file::

            microej {
                serialToSocket {
                    serialPort = "COM0"
                    socketPort = 5555
                    baudRate = 115200
                    dataBits = 8
                    stopBits = 1
                    parity = "none"
                }
            }

        - ``serialPort``: Defines the COM port.

            - **Default value**: ``COM0``

                - Windows: ``COM1``, ``COM2``, ``…``, ``COM*n*``

                - Linux: ``/dev/ttyS0``, ``/dev/ttyUSB0``, ``…``, ``/dev/ttyS*n*``, ``/dev/ttyUSB*n*``

        - ``socketPort``: Defines the TCP server port.

            - **Default value**: ``5555``

        - ``socketAddress``: Defines the TCP server address.

            - This option has no default value, if not set, the transmitter will act as a TCP server (hosting on ``localhost``),
              otherwise it will act as a TCP client connecting to the specified address.

        - ``baudRate``: Defines the COM baud rate.

            - **Default value**: ``115200``

            - Available values:
                - ``9600``
                - ``38400``
                - ``57600``
                - ``115200``

        - ``dataBits``: Defines the number of data bits transmitted in each serial frame.

            - **Default value**: ``8``

        - ``stopBits``: Defines the number of stop bits used to signal the end of a serial frame.

            - **Default value**: ``1``

        - ``parity``: Defines the parity checking method.

            - **Default value**: ``none``

            - Available values:
                - ``none``
                - ``even``
                - ``odd``

    .. group-tab:: SDK 6 1.5.0 and below

        - **Serial Port**

            - **Option Name**: ``serial.to.socket.comm.port``

            - **Default value**: ``COM0``

            - **Description**: Defines the COM port:
                - Windows: ``COM1``, ``COM2``, ``…``, ``COM*n*``

                - Linux: ``/dev/ttyS0``, ``/dev/ttyUSB0``, ``…``,
                    ``/dev/ttyS*n*``, ``/dev/ttyUSB*n*``

        - **Baudrate**

            - **Option Name**: ``serial.to.socket.comm.baudrate``

            - **Default value**: ``115200``

            - **Available values**:
                - ``9600``
                - ``38400``
                - ``57600``
                - ``115200``

            - **Description**: Defines the COM baudrate.

        - **Socket Port**

            - **Option Name**: ``serial.to.socket.server.port``

            - **Default value**: ``5555``

            - **Description**: Defines the TCP server port.

..
   | Copyright 2008-2025, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
