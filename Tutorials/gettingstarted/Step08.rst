Animation
=========

-  To use animation, the Animation class is going to be used
-  The main goal with animation is to set the widget graphics in motion
   to make the GUI more appealing and more lively 

Usage
-----

-  Using Animation is easy, just override the method tick() in the
   Animator class
-  Every time the method is called on, the widget should be re-rendered, or
   else, it is not going to show 
   
   .. code:: java 
   
    Animation lblAnimation = new Animation() { 
        @Override public boolean tick(longcurrentTimeMillis) { 
            label.setText(Integer.toString(tick++));
            label.requestRender();
            return true; 
        } 
    };
    Animator animator = new Animator();
    animator.startAnimation(lblAnimation); 

- The code above updates the label text everytime it is called

|image0| 

- The final code should look like this

.. code:: java

    public static void main(String[] args) {
        MicroUI.start();
        Desktop desktop = new Desktop();
        final Label label = new Label("hello");

        Flow flow = new Flow(LayoutOrientation.VERTICAL);
        flow.addChild(label);

        Animation lblAnimation = new Animation() {

            int tick = 0;

            @Override
            public boolean tick(long currentTimeMillis) {
                label.setText(Integer.toString(this.tick++));
                label.requestRender();
                return true;
            }
        };
        Animator animator = new Animator();
        animator.startAnimation(lblAnimation);
        desktop.setWidget(flow);
        desktop.requestShow();
    }

.. |image0| image:: images/ticking.png
