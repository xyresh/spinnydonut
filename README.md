# spinnydonut
a donut that spins, in opengl

depends on glut: 
https://github.com/freeglut/freeglut

#Explanation

*Mathematical Representation:
    The donut is represented using parametric equations in polar coordinates.
    We use two parameters: t $\theta$  and $\phi$.
    The `(x, y, z)` coordinates of each point on the donut are calculated as follows:
    $(x = \cos(t) \cdot (3 + \cos(\phi)))$
    $(y = \sin(t) \cdot (3 + \cos(\phi)))$
    $(z = \sin(\phi))$
