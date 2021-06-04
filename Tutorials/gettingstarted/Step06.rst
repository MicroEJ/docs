Event Handling
==============

The handleEvent method
---------------------------
- Every class that extends Widget inherits the handleEvent method
- It is possible to handle events overriding this class on a created sample
- Using as a sample the Button class

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
-------------------------------
Events are handled in the same way

- Using the code created in the Last Step, it is possible to simply add the onClick Listener

.. code:: java

    button.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick() {
            System.out.println("Clicked!");
        }
    });

This should be shown in the console

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
