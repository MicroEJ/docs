Expandable Widget
=================

A simple expandable Widget
--------------------------

- To create an expandable widget, let's create a ``toggle()`` method to change the direction of the motion (animation).

  .. code:: java

    public void toggle() {
        Motion motion;
        if (!this.expanded) {
            motion = new Motion(QuadEaseOutFunction.INSTANCE, getCollapsedHeight(), getExpandedHeight(),
                    getAnimationDuration());
        } else {
            motion = new Motion(QuadEaseOutFunction.INSTANCE, getExpandedHeight(), getCollapsedHeight(),
                    getAnimationDuration());
        }
        this.motionAnimation = new MotionAnimation(this.animator, motion, this);

        this.motionAnimation.start();
        this.expanded = !this.expanded;
    }

- This method just creates a motion for when it should expand or shrink

- Being an expandable widget, it should also expand or collapse when clicked (simply calling toggle), for that you have to add and event handler to handle the pressed event

  .. code:: java

    @Override
    public boolean handleEvent(int event) {
        int type = Event.getType(event);
        if (type == Pointer.EVENT_TYPE) {
            int action = Buttons.getAction(event);
            if (action == Buttons.RELEASED) {
                toggle();
                return true;
            }
        }
        return super.handleEvent(event);
    }

- To change the size you should also override the ``computeContentOptimalSize`` and change the ``size``

  .. code:: java

    protected void computeContentOptimalSize(Size size) {
        size.setHeight(this.motionAnimation != null ? this.motionValue
                : (this.expanded ? getExpandedHeight() : getCollapsedHeight()));
    }

- The final class looks like this 

  .. code:: java

    public class ExpandableWidget extends Widget implements MotionAnimationListener {

        public static final int STYLE_COLLAPSED_HEIGHT = 1;
        public static final int STYLE_EXPANDED_HEIGHT = 2;
        public static final int STYLE_ANIMATION_DURATION = 3;

        private static final int DEFAULT_COLLAPSED_HEIGHT = 48;
        private static final int DEFAULT_EXPANDED_HEIGHT = DEFAULT_COLLAPSED_HEIGHT * 2;
        private static final int DEFAULT_ANIMATION_DURATION = 250;

        private static final int MATERIAL_LABEL_PADDING = 72;
        private static final int MATERIAL_PADDING = 16;


        private int motionValue;

        private final String myLabel;
        private final Animator animator;
        private MotionAnimation motionAnimation;
        private boolean expanded = false;

        public ExpandableWidget(String label, Animator animator) {
            setEnabled(true);
            this.animator = animator;
            this.myLabel = label;
        }

        public void toggle() {
            Motion motion;
            if (!this.expanded) {
                motion = new Motion(QuadEaseOutFunction.INSTANCE, getCollapsedHeight(), getExpandedHeight(),
                        getAnimationDuration());
            } else {
                motion = new Motion(QuadEaseOutFunction.INSTANCE, getExpandedHeight(), getCollapsedHeight(),
                        getAnimationDuration());
            }
            this.motionAnimation = new MotionAnimation(this.animator, motion, this);

            this.motionAnimation.start();
            this.expanded = !this.expanded;
        }

        @Override
        public boolean handleEvent(int event) {
            int type = Event.getType(event);
            if (type == Pointer.EVENT_TYPE) {
                int action = Buttons.getAction(event);
                if (action == Buttons.RELEASED) {
                    toggle();
                    return true;
                }
            }

            return super.handleEvent(event);
        }

        @Override
        protected void computeContentOptimalSize(Size size) {
            size.setHeight(this.motionAnimation != null ? this.motionValue
                    : (this.expanded ? getExpandedHeight() : getCollapsedHeight()));
        }


        @Override
        protected void renderContent(GraphicsContext g, int contentWidth, int contentHeight) {
            final Style style = this.getStyle();
            final Font font = style.getFont();

            g.setColor(style.getColor());
            StringPainter.drawStringInArea(g, this.myLabel, font, MATERIAL_LABEL_PADDING,
                    Alignment.computeTopY(font.getHeight(), 0, getCollapsedHeight(), Alignment.VCENTER), contentWidth,
                    getCollapsedHeight(), style.getHorizontalAlignment(), style.getVerticalAlignment());

            final char expandChar = 'V';
            final int charWidth = font.charWidth(expandChar);
            final int charHeight = font.getHeight();
            final int charX = Alignment.computeLeftX(charWidth, -MATERIAL_PADDING, contentWidth, Alignment.RIGHT);
            final int charY = Alignment.computeTopY(charHeight, 0, getCollapsedHeight(), Alignment.VCENTER);
            TransformPainter.drawRotatedCharBilinear(g, font, expandChar, charX, charY, charX + charWidth / 2,
                    charY + charHeight / 2, this.expanded ? 180 : 0);
        }

        private int getCollapsedHeight() {
            return this.getStyle().getExtraInt(STYLE_COLLAPSED_HEIGHT, DEFAULT_COLLAPSED_HEIGHT);
        }

        private int getExpandedHeight() {
            return this.getStyle().getExtraInt(STYLE_EXPANDED_HEIGHT, DEFAULT_EXPANDED_HEIGHT);
        }

        private int getAnimationDuration() {
            return this.getStyle().getExtraInt(STYLE_ANIMATION_DURATION, DEFAULT_ANIMATION_DURATION);
        }

        @Override
        public void tick(int value, boolean finished) {
            this.motionValue = value;
            this.getParent().requestLayOut();
            requestRender();
        }
    }

Using the ExpandableWidget with the Scroll List
-----------------------------------------------

- To add, simply add the expandable widget to the ScrollList

  .. code:: java

    public static void main(String[] args) {
        MicroUI.start();

        Desktop desktop = new Desktop();

        final Animator animator = new Animator();
        ScrollableList list = new ScrollableList(LayoutOrientation.VERTICAL);
        for (int i = 1; i < 15; i++) {
            ExpandableWidget item = new ExpandableWidget("item " + i, animator);
            list.addChild(item);
        }

        Scroll scroll = new Scroll(LayoutOrientation.VERTICAL, animator);
        scroll.setChild(list);

        CascadingStylesheet css = new CascadingStylesheet();
        populateStylesheet(css);
        desktop.setStylesheet(css);

        desktop.setWidget(scroll);
        desktop.requestShow();
    }

- Also, for viewing purposes, let's set a style for the widget

  .. code:: java

    static final int DEFAULT_BACKGROUND = 0xffffff
    static final int DEFAULT_FOREGROUND = 0x262a2c
    static final int DEFAULT_BORDER = 0x97a7af

    private static void populateStylesheet(CascadingStylesheet stylesheet) {
    EditableStyle style = stylesheet.getDefaultStyle();
    style.setColor(DEFAULT_FOREGROUND);
    style.setBackground(new RectangularBackground(DEFAULT_BACKGROUND));

    style = stylesheet.getSelectorStyle(new TypeSelector(Scrollbar.class));
    style.setBackground(NoBackground.NO_BACKGROUND);
    style.setDimension(new FixedDimension(10, Widget.NO_CONSTRAINT));
    style.setColor(DEFAULT_FOREGROUND);

    style = stylesheet.getSelectorStyle(new TypeSelector(ExpandableWidget.class));
    style.setBorder(new FlexibleRectangularBorder(DEFAULT_BORDER, 1, 0, 0, 0));
    style.setHorizontalAlignment(Alignment.LEFT);
    style.setBackground(new RectangularBackground(DEFAULT_BACKGROUND));

    style = stylesheet.getSelectorStyle(
            new AndCombinator(new TypeSelector(ExpandableWidget.class), OddChildSelector.ODD_CHILD_SELECTOR));
    style.setBackground(new RectangularBackground(ALTERNATE_BACKGROUND));
    }

  .. image:: images/expanded.png
   :align: center
