Configuration
=============

A GPIO can be configured in any of five modes:

-  Digital input: The MicroEJ application can read the GPIO state (for
   example a button state).

-  Digital input pull-up: The MicroEJ application can read the GPIO
   state (for example a button state); the default GPIO state is driven
   by a pull-up resistor.

-  Digital output: The MicroEJ application can set the GPIO state (for
   example to drive an LED).

-  Analog input: The MicroEJ application can convert some incoming
   analog data into digital data (ADC). The returned values are values
   between ``0`` and ``n - 1``, where ``n`` is the ADC precision.

-  Analog output: The MicroEJ application can convert some outgoing
   digital data into analog data (DAC). The digital value is a
   percentage (0 to 100%) of the duty cycle generated on selected GPIO.
