Event Handling
==============
- MicroUI generates integer-based events that encode the low-level input type and action. The application can handle these events in the ``handleEvent`` method.
The handleEvent method
---------------------------
- Every class that extends ``Widget`` inherits the ``handleEvent()`` method.
- Add custom event handling by overriding the ``handleEvent()`` method of a widget.
- Using the ``Button`` class from the Widget library as a sample:
- Use the handleEvent of the parent class if none of the EventTypes are used

.. code:: java

	@Override
	public boolean handleEvent(int event) {
		int type = Event.getType(event);
		if (type == Pointer.EVENT_TYPE) {
			int action = Pointer.getAction(event);
			if (action == Pointer.PRESSED) {
				setPressed(true);
			} else if (action == Pointer.RELEASED) {
				setPressed(false);
				handleClick();
				return true;
			}
		} else if (type == DesktopEventGenerator.EVENT_TYPE) {
			int action = DesktopEventGenerator.getAction(event);
			if (action == PointerEventDispatcher.EXITED) {
				setPressed(false);
			}
		}

		return super.handleEvent(event);
	}

- It's important to note that only widgets that are "enabled" will receive input events. One can enable a widget by calling ``setEnabled(true)``.
- The handleClick method is where the clickListener is used

.. code:: java
 
    public void handleClick() {
        OnClickListener listener = this.onClickListener;
        if (listener != null) {
            listener.onClick();
        }
    }


Using events with buttons
-------------------------
Events are handled in the same way

- Using the code created in the previous step, let's add a simple action to the button by adding a ``OnClickListener``.

.. code:: java

    button.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick() {
            System.out.println("Clicked!");
        }
    });

When running the modified sample, this should be shown in the console:

.. code:: Console

    =============== [ Initialization Stage ] ===============
    =============== [ Converting fonts ] ===============
    =============== [ Converting images ] ===============
    The watchdog is not configured by the application, so it is enabled. This default behavior will reset the MCU after ~32 seconds of not executing the RTOS idle task
    =============== [ Launching on Simulator ] ===============
    Clicked!
    Clicked!
    Clicked!
    Clicked!
    Clicked!
