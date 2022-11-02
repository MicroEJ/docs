How to Create a Desktop Event Dispatcher
========================================

Creating a custom event dispatcher can help you address two use cases:

* [Dispatch] Extending an EventDispatcher is used to dispatch the events. For example, the FocusEventDispatcher will send the events to the widget owning the focus.
* [Handle] Overriding the desktop is used to directly trigger a behavior. For example "BACK" command shows the previous page.

To create a custom event dispatcher, a new class should be created, extending the `EventDispatcher`_ class.
Event dispatcher subclasses have to implement a method and may override optional methods, as explained in the following sections.

.. _EventDispatcher: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/EventDispatcher.html

Dispatching the events to the widgets
-------------------------------------

The `dispatchEvent()`_ method is called by the MWT framework in order to dispatch a MicroUI event to the widgets of the desktop.
The `getDesktop()`_ method may be called in order to retrieve the desktop with which the event dispatcher is associated.
This is useful in order to browse the widget hierarchy of the desktop, for example by using the `getWidget()`_ and `getWidgetAt()`_ methods of `Desktop`_.

In order to send an event to one of the widgets of the hierarchy, the `sendEventToWidget()`_ method should be used.
The `dispatchEvent()`_ method should return whether or not the event was dispatched and consumed by a widget.

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
This may be done by using a `DesktopEventGenerator`_. Its `buildEvent()`_ method allows to build an event which may be sent to a widget using the `sendEventToWidget()`_ method.

.. _dispatchEvent(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/EventDispatcher.html#dispatchEvent-int-
.. _getDesktop(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/EventDispatcher.html#getDesktop--
.. _getWidget(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#getWidget--
.. _getWidgetAt(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html#getWidgetAt-int-int-
.. _Desktop: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/Desktop.html
.. _sendEventToWidget(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/EventDispatcher.html#sendEventToWidget-ej.mwt.Widget-int-
.. _DesktopEventGenerator: https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/DesktopEventGenerator.html
.. _buildEvent(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/DesktopEventGenerator.html#buildEvent-int-

Initializing and disposing the dispatcher
-----------------------------------------

`EventDispatcher`_ subclasses may override the `initialize()`_ and `dispose()`_ methods in order to allocate and free the necessary resources.

For example, the `initialize()`_ method may be overridden to create an event generator and to add it to the system pool of MicroUI:

.. code-block:: Java

	@Override
	public void initialize() {
		this.eventGenerator = new DesktopEventGenerator();
		this.eventGenerator.addToSystemPool();
	}

Likewise, the `dispose()`_ method may be overridden to remove the event generator from the system pool of MicroUI:

.. code-block:: Java

	@Override
	public void dispose() {
		this.eventGenerator.removeFromSystemPool();
	}

.. _initialize(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/EventDispatcher.html#initialize--
.. _dispose(): https://repository.microej.com/javadoc/microej_5.x/apis/ej/mwt/event/EventDispatcher.html#dispose--

..
   | Copyright 2008-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.
