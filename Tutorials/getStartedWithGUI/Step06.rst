Event Handling
==============

MicroUI generates integer-based events that encode the low-level input type and some data. The application can handle these events in the ``handleEvent`` method.

The handleEvent Method
----------------------

- Every class that extends ``Widget`` inherits the ``handleEvent()`` method.
- Add custom event handling by overriding the ``handleEvent()`` method of a widget.
- As an example, here is the event handling of the ``Button`` class:

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
- In the ``Button`` class, the click triggers an action defined by the registered ``OnClickListener``. The ``handleClick`` method is where the listener is called:

  .. code:: java
 
    public void handleClick() {
        OnClickListener listener = this.onClickListener;
        if (listener != null) {
            listener.onClick();
        }
    }


Using Events with Buttons
-------------------------

As an example of usage of the Button class we reuse the code created in the previous step, and add a simple action to the button by adding a ``OnClickListener``.

  .. code:: java

    button.setOnClickListener(new OnClickListener() {
        @Override
        public void onClick() {
            System.out.println("Clicked!");
        }
    });

When running the modified sample, this is shown in the console:

  .. code:: console

    =============== [ Initialization Stage ] ===============
    =============== [ Converting fonts ] ===============
    =============== [ Converting images ] ===============
    =============== [ Launching on Simulator ] ===============
    Clicked!
    Clicked!
    Clicked!
    Clicked!
    Clicked!

..
   | Copyright 2021-2022, MicroEJ Corp. Content in this space is free 
   for read and redistribute. Except if otherwise stated, modification 
   is subject to MicroEJ Corp prior approval.
   | MicroEJ is a trademark of MicroEJ Corp. All other trademarks and 
   copyrights are the property of their respective owners.

    