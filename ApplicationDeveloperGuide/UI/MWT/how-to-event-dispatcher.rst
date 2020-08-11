How-To Create a Desktop Event Dispatcher
========================================

Two use cases:

* [Dispatch] Extending an EventDispatcher is used to dispatch the events. For example, the FocusEventDispatcher will send the events to the widget owning the focus.
* [Handle] Overriding the desktop is used to directly trigger a behaviour. For example "BACK" command shows the previous page.

To create a custom event dispatcher, a new class should be created, extending the ``EventDispatcher`` class.
Event dispatcher subclasses have to implement a method and may override optional methods, as explained in the following sections.

Dispatching the events to the widgets
-------------------------------------

The ``dispatchEvent()`` method is called by the MWT framework in order to dispatch a MicroUI event to the widgets of the desktop.
The ``getDesktop()`` method may be called in order to retrieve the desktop with which the event dispatcher is associated.
This is useful in order to browse the widget hierarchy of the desktop, for example by using the ``getWidget()`` and ``getWidgetAt()`` methods of ``Desktop``.

In order to send an event to one of the widgets of the hierarchy, the ``sendEventToWidget()`` should be used.
The ``dispatchEvent()`` method should return whether or not the event was dispatched and consumed by a widget.

For example, the following snippet dispatches every event to the widget of the desktop:

.. code-block:: Java

	@Override
	public boolean dispatchEvent(int event) {
		Widget desktopWidget = getDesktop().getWidget();
		if (desktopWidget != null) {
			return sendEventToWidget(desktopWidget, event);
		} else {
			return false;
		}
	}

In addition to dispatching the provided events, an event dispatcher may generate custom events.
This may be done by using a ``DesktopEventGenerator``. Its ``buildEvent()`` method allows to build an event which may be sent to a widget using the ``sendEventToWidget()`` method.

Initializing and disposing the dispatcher
-----------------------------------------

``EventDispatcher`` subclasses may override the ``initialize()`` and ``dispose()`` methods in order to allocate and free the necessary resources.

For example, the ``initialize()`` may be overridden to create an event generator and to add it to the system pool of MicroUI:

.. code-block:: Java

	@Override
	public void initialize() {
		this.eventGenerator = new DesktopEventGenerator();
		this.eventGenerator.addToSystemPool();
	}

Likewise, the ``dispose()`` method may be overridden to remove the event generator from the system pool of MicroUI:

.. code-block:: Java

	@Override
	public void dispose() {
		this.eventGenerator.removeFromSystemPool();
	}

..
   | Copyright 2008-2020, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
