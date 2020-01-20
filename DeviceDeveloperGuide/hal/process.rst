Functional Description
======================

The MicroEJ application configures and uses some physical GPIOs, using
one unique identifier per GPIO. The HAL implementation made for each
MicroEJ Platform has the responsibility of verifying the veracity of the
GPIO identifier and the valid GPIO configuration.

Theoretically, a GPIO can be reconfigured at any time. For example a
GPIO is configured in OUTPUT first, and later in ADC entry. However the
HAL implementation can forbid the MicroEJ application from performing
this kind of operation.
