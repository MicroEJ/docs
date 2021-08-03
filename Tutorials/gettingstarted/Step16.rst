Popup
=====

Using the Popup
----------------
- The main idea behind the popup shown here is to show a Widget(In a desktop that overlaps another)
- The usage looks like this

  .. code:: java
    
	public static void main(String[] args) {
		MicroUI.start();
		Desktop desktop = new Desktop();
		CascadingStylesheet css = new CascadingStylesheet();
		EditableStyle style = css.getSelectorStyle(new TypeSelector(Button.class));
		style.setBackground(new RectangularBackground(Colors.BLUE));
		style = css.getSelectorStyle(new TypeSelector(Canvas.class));
		style.setBackground(new RectangularBackground(Colors.WHITE));

		desktop.setStylesheet(css);

		Canvas canvas = new Canvas();

		desktop.setWidget(canvas);
		desktop.requestShow();

		Popup popup = new Popup();
		Button b = new Button("Test");
		b.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick() {
				System.out.println("Print this");
			}
		});
		popup.setWidget(b);
		popup.requestShow();
	}


- First, create a main desktop, and then, create the popup and show it with it's widget

  .. image:: images/openPopup.png
    :align: center

  .. note:: 
    A nice suggestion is a message box widget

The Popup Code
--------------

- Since popup will receive a widget to show, it can be an extension of desktop.
- The ``layOut()`` method will be used to check if widget is not ``null``.

  .. code:: java

    @Override
	void layOut() {
		Widget widget = this.getWidget();
		if (widget != null) {
			Display display = Display.getDisplay();
			int displayWidth = display.getWidth();
			int displayHeight = display.getHeight();

			widget.computeOptimalSize(displayWidth, displayHeight);
			widget.layOut(0, 0, widget.getWidth(), widget.getHeight());
		}
	}

- First,to hide this popup in the event that the user clicks outside of the widget, it's overriding the handleEvent.

  .. code:: java

    public boolean handleEvent(int event) {
		int type = Event.getType(event);
		if (type == Pointer.EVENT_TYPE) {
			Pointer pointer = (Pointer) Event.getGenerator(event);
			pointer.setOrigin(this.clipX, this.clipY);
			int pointerX = pointer.getX();
			int pointerY = pointer.getY();
			System.out.println("Pointer X:" + pointerX + " PointerY:" + pointerY); //$NON-NLS-2$
			int action = Buttons.getAction(event);
			if (action == Buttons.RELEASED) {
				if (!getWidget().contains(pointerX, pointerY)) {
					this.requestHide();
					return false;
				}
			}
		}
		return super.handleEvent(event);
	}

- Both methods for requesting show and hide are implemented like this:

  .. code:: java

	@Override
	public void requestShow() {
		Displayable displayable = Display.getDisplay().getDisplayable();
		if (displayable instanceof Desktop) {
			this.previous = (Desktop) displayable;
			this.setStylesheet(this.previous.getStylesheet());
		}
		super.requestShow();
	}

	@Override
	public void requestHide() {
		super.requestHide();
		if (this.previous != null) {
			this.previous.requestShow();
		}
	}
    
- A render policy is a strategy that MWT uses in order to repaint the entire desktop or to repaint a specific widget
- Finally, a RenderPolicy will be used for this desktop

  .. code:: java

    class MyRenderPolicy extends DefaultRenderPolicy {

		/**
		* @param desktop
		*/
		public MyRenderPolicy(Desktop desktop) {
			super(desktop);
		}

		@Override
		public void requestRender(Widget widget, int x, int y, int width, int height) {
			super.requestRender(widget, x + Popup.this.clipX, y + Popup.this.clipY, width, height);
		}

		@Override
		public void renderDesktop() {
			Desktop desktop = getDesktop();
			Widget widget = desktop.getWidget();
			if (widget != null) {
				// reset translation and clip
				final Display display = Display.getDisplay();
				final GraphicsContext g = display.getGraphicsContext();
				g.resetTranslation();
				g.resetClip();

				final int displayWidth = display.getWidth();
				final int displayHeight = display.getHeight();
				final int contentWidth = widget.getWidth();
				final int contentHeight = widget.getHeight();
				int x = Alignment.computeLeftX(contentWidth, 0, displayWidth, Alignment.HCENTER);
				int y = Alignment.computeTopY(contentHeight, 0, displayHeight, Alignment.VCENTER);

				g.setClip(x, y, contentWidth, contentHeight);
				g.setTranslation(x, y);

				Popup.this.clipX = x;
				Popup.this.clipY = y;
				Popup.this.clipW = contentWidth;
				Popup.this.clipH = contentHeight;

				// render widget
				desktop.renderWidget(g, widget);
			}
		}
    }

- The final popup looks like this:

  .. code-block:: java

    public class Popup extends Desktop {

		int clipX;
		int clipY;
		int clipW;
		int clipH;

		@Override
		/* package */void layOut() {
			Widget widget = this.getWidget();
			if (widget != null) {
				Display display = Display.getDisplay();
				int displayWidth = display.getWidth();
				int displayHeight = display.getHeight();

				widget.computeOptimalSize(displayWidth, displayHeight);
				widget.layOut(0, 0, widget.getWidth(), widget.getHeight());
			}
		}

		@Override
		public boolean handleEvent(int event) {
			int type = Event.getType(event);
			if (type == Pointer.EVENT_TYPE) {
				Pointer pointer = (Pointer) Event.getGenerator(event);
				pointer.setOrigin(this.clipX, this.clipY);
				int pointerX = pointer.getX();
				int pointerY = pointer.getY();
				int action = Buttons.getAction(event);
				if (action == Buttons.RELEASED) {
					if (!getWidget().contains(pointerX, pointerY)) {
						this.requestHide();
						return false;
					}
				}
			}

			return super.handleEvent(event);
		}

		@Override
		protected RenderPolicy createRenderPolicy() {
			return new MyRenderPolicy(this);
		}

		Desktop previous;

		@Override
		public void requestShow() {
			Displayable displayable = Display.getDisplay().getDisplayable();
			if (displayable instanceof Desktop) {
				this.previous = (Desktop) displayable;
				this.setStylesheet(this.previous.getStylesheet());
			}
			super.requestShow();
		}

		@Override
		public void requestHide() {
			super.requestHide();
			if (this.previous != null) {
				this.previous.requestShow();
			}
		}

		class MyRenderPolicy extends DefaultRenderPolicy {

			/**
			* @param desktop
			*/
			public MyRenderPolicy(Desktop desktop) {
				super(desktop);
			}

			@Override
			public void requestRender(Widget widget, int x, int y, int width, int height) {
				super.requestRender(widget, x + Popup.this.clipX, y + Popup.this.clipY, width, height);
			}

			@Override
			public void renderDesktop() {
				Desktop desktop = getDesktop();
				Widget widget = desktop.getWidget();
				if (widget != null) {
					// reset translation and clip
					final Display display = Display.getDisplay();
					final GraphicsContext g = display.getGraphicsContext();
					g.resetTranslation();
					g.resetClip();

					final int displayWidth = display.getWidth();
					final int displayHeight = display.getHeight();
					final int contentWidth = widget.getWidth();
					final int contentHeight = widget.getHeight();
					int x = Alignment.computeLeftX(contentWidth, 0, displayWidth, Alignment.HCENTER);
					int y = Alignment.computeTopY(contentHeight, 0, displayHeight, Alignment.VCENTER);

					g.setClip(x, y, contentWidth, contentHeight);
					g.setTranslation(x, y);

					Popup.this.clipX = x;
					Popup.this.clipY = y;
					Popup.this.clipW = contentWidth;
					Popup.this.clipH = contentHeight;

					// render widget
					desktop.renderWidget(g, widget);
				}
			}
		}
    }
    

