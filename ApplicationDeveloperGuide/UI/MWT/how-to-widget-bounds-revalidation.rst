How compute Optimal Size works
==============================

When created, a widget, will have its size set A container has multiple children widgets.

To compute the size of each of the children on a container every time a widget is laid out, the method ComputeOptimalSize is called, which will calculate the size of this Widget.

Every call to computeOptimalSize stores the Size needed to show the Widget correctly including outlines(Example: Margin, Padding) and sets the Size atrribute.

As a container is also a Widget, it also contains a computeOptimalsize, calculating its size using its children.

on every call to LayOut, the optimal Size is recalculated.

every container has its own way to calculate the optimal size as seen below:

Flow Container
--------------
Each time Compute optimal size is called on a Container(And a widget), Compute content optimal size is also called, in the case of Flow, it computes the size of each children and adds to the total sum

The sample below is a simple computing of the size of a Flow Container:

.. code-block:: Java

	protected void computeContentOptimalSize(Size size) {
		int totalWidth = 0;
		int totalHeight = 0;

		// computes the maximum size of children within the container.
		int childWidthHint = size.getWidth() / getChildrenCount();
		int childHeightHint = size.getHeight();

		// iterates over the children to compute their optimal size.
		for (Widget child : getChildren()) {
			computeChildOptimalSize(child, childWidthHint, childHeightHint);

			// updates the container optimal size
			totalWidth += Math.min(childWidthHint, child.getWidth());
			totalHeight = Math.max(totalHeight, child.getHeight());
		}

		// sets the container optimal size
		size.setSize(totalWidth, totalHeight);
	}


Canvas Container
----------------
Since Canvas can position widgets freely, we calculate the optimal size based on the X and Y position and width of the farthest child,and compare it with the width of the canvas.

This simpler implementation of Canvas will only calculate using the X and Y position of each child and see if it is greater than the one before:

.. code-block:: java

    int widthHint = size.getWidth();
    int heightHint = size.getHeight();
    PackedMap<Widget, Rectangle> widgetBounds = this.widgetBounds;

    int width = 0;
    int height = 0;
    for (Widget child : getChildren()) {
        assert (child != null);

        // get child desired bounds
        Rectangle bounds = widgetBounds.get(child);
        int childX = bounds.getX();
        int childY = bounds.getY();
        int childWidth=child.getWidth();
        int childHeight=child.getHeight();

        width = Math.max(width, childX + childWidth);
        height = Math.max(height, childY + childHeight);
    }

    // set container optimal size
    size.setSize(width, height);
