.. _section_ecomcomm_dynamic_connections:

Dynamic Connections
===================

The ECOM Comm stack allows to dynamically add and remove connections
from the `??? <#section_ecomcomm_driver>`__. When a connection is added,
it can be immediately open by the application. When a connection is
removed, the connection cannot be open anymore and
``java.io.IOException`` is thrown in threads that are using it.

In addition, a dynamic connection can be registered and unregistered in
ECOM device manager (see `??? <#section_ecom_dm>`__). The registration
mechanism is done in dedicated thread. It can be enabled or disabled,
see `??? <#workbenchLaunchOptions>`__.

A removed connection is alive until it is closed by the application and,
if enabled, unregistered from ECOM device manager. A connection is
effectively uninstalled (and thus eligible to be reused) only when it is
released by the stack.

The following sequence diagram shows the lifecycle of a dynamic
connection with ECOM registration mechanism enabled.
