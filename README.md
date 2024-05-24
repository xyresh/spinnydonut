# spinnydonut
a donut that spins, in opengl

![Screenshot from 2024-05-14 04-28-34](https://github.com/xyresh/spinnydonut/assets/81033344/d3d27522-926f-42e2-8c26-e1a7be0c929a)



depends on glut: 
https://github.com/freeglut/freeglut

you can build a version of this that utilizes Vertex buffer objects (only if hardware acceleration is available) , by simply running: 

`make vbo`

this will automatically check for hardware accelerated renderer, however, if it falsely doesn't detect it you can manually run it with: 
`./dinutvbo`


# Explanation

* **Mathematical Representation:**  
    The donut is represented using parametric equations in polar coordinates.  
    We use two parameters: t , $\theta$  and $\phi$.  
    The `(x, y, z)` coordinates of each point on the donut are calculated as follows:  
    $x = \cos(t) \cdot (3 + \cos(\phi))$  
    $y = \sin(t) \cdot (3 + \cos(\phi))$  
    $z = \sin(\phi)$


  
* **Rotation:**  
   The donut rotates around three axes: X, Y, and Z.  
   The rotation angles `(angleX, angleY, angleZ)` are incremented in each frame.  
   We apply rotation transformations to the `(x, y, z)` coordinates to achieve the spinning effect.  


* **OpenGL Setup:**  
   We use OpenGL for rendering.  
   The glut library provides window management and event handling.  
   The `display()` function draws the points of the donut.  
   The `reshape()` function sets the projection matrix.


* **Colour Cycling:**  
   The donut smoothly cycles through colours.  
   We use the elapsed time `glutGet(GLUT_ELAPSED_TIME)` to smoothly transition colours over time by calculating the hue based on      elapsed time and converting it to RGB.  
   The resulting color changes gradually as the program runs.


* **Idle Function:**  
   The `idle()` function is called continuously.  
   It updates the rotation angles and color, then triggers a redraw.

* **Rendering:**  
   The `glClear()` function clears the color and depth buffers.  
   We draw the points of the donut using `glBegin(GL_POINTS)` and `glVertex3f(x, y, z)`.  
   Finally, we swap the buffers for smooth animation using `glutSwapBuffers()`.  

* **As of now, it offers, vbo rendering**
  we can utilize vertex buffer object rendering if hardware acceleration is available,
  which is implemented in the mainvbo.c file
