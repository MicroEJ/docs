How to compute the optimal size of a Widget
===========================================

The ``computeContentOptimalSize()`` method is called by the MWT framework in order to know the optimal size of a widget.
The optimal size of the widget should be big enough to contain all the drawings of the widget.

The ``Size`` parameter of the ``computeContentOptimalSize()`` method initially contains the size available for the widget.
An available width or height equal to ``Widget.NO_CONSTRAINT`` means that the optimal size should be computed without considering any restriction on the respective axis.
Before the method returns, the size object should be set to the optimal size of the widget.

When implementing this method, the ``getStyle()`` method may be called in order to retrieve the style of the widget.

.. note::

   The outlines defined in the style (Margin, Border and Padding) don't need to be taken in count to compute the optimal size of the widget, it will be added automatically by MWT.

For example, the following snippet computes the optimal size of a label:

.. code-block:: Java

	@Override
	protected void computeContentOptimalSize(Size size) {
		Font font = getStyle().getFont();
		int width = font.stringWidth(this.text);
		int height = font.getHeight();
		size.setSize(width, height);
	}

Compute the optimal size of a Container
---------------------------------------

The container is responsible for computing the optimal size of every child. 
The optimal size of the container should be big enough so that each child can be laid out with a size at least as big as its own optimal size.

To do so, the ``computeChildOptimalSize()`` method should be called for every child.
After this method is called, the optimal size of the child can be retrieved by calling ``getWidth()`` and ``getHeight()`` on the child widget.

The following snippet shows how ``computeContentOptimalSize()`` of a ``List`` is done.
``computeChildOptimalSize`` is called on every child of the list, according to the orientation of the list, the width or height is equal to the sum of the children width/height. The other dimension is equal to the greater width/height of the children.

.. code-block:: Java

    @Override
	protected void computeContentOptimalSize(Size size) {
		// perform quick optimization if there is no child
		int childrenCount = getChildrenCount();
		if (childrenCount == 0) {
			size.setSize(0, 0);
			return;
		}

		// compute size hint for children
		boolean isHorizontal = (this.orientation == LayoutOrientation.HORIZONTAL);
		int childWidthHint = size.getWidth();
		int childHeightHint = size.getHeight();

		// compute total children size
		int totalWidth = 0;
		int totalHeight = 0;

		for (Widget widget : getChildren()) {
			assert (widget != null);

			// compute child optimal size
			computeChildOptimalSize(widget, childWidthHint, childHeightHint);

			// update total children size
			if (isHorizontal) {
				totalWidth += widget.getWidth();
				totalHeight = Math.max(totalHeight, widget.getHeight());
			} else {
				totalWidth = Math.max(totalWidth, widget.getWidth());
				totalHeight += widget.getHeight();
			}
		}

		// save total children size for layout
		this.totalLength = (isHorizontal ? totalWidth : totalHeight);

		// set container optimal size
		size.setSize(totalWidth, totalHeight);
	}
