Java API
========

Opening a connection is done using
``ej.ecom.io.Connector.open(String name)`` . The connection string (the
``name`` parameter) must start with "comm:", followed by the Comm port
identifier, and a semicolon-separated list of options. Options are the
baudrate, the parity, the number of bits per character, and the number
of stop bits:

-  baudrate=n (9600 by default)

-  bitsperchar=n where n is in the range 5 to 9 (8 by default)

-  stopbits=n where n is 1, 2, or 1.5 (1 by default)

-  parity=x where x is odd, even or none (none by default)

All of these are optional. Illegal or unrecognized parameters cause an
``IllegalArgumentException`` .
