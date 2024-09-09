# ascii-animation

What started as a simple progression to learn the basic syntax and behavior of C turned into a 3 week incursion
into the (very) basics of computer graphics and a huge walk down memory lane of college linear algebra. Super fun!

![cube](https://github.com/user-attachments/assets/a9ff3001-b2ff-44cd-aced-4168e47a9415)

## 3D Animations

1. donut.c: this is the coolest one, a directionally-illuminated rotating torus, and follows the famous program layed out here: https://www.a1k0n.net/2011/07/20/donut-math.html
2. cube.c
3. cone.c
4. rotate-square-3D.c: my first 3D animation, just rotating a square plate in 3D

## 2D Animations

5. rotate-square.c: rotating a square in 2D
6. rectangle.c: first time taking user input with scanf()
7. square.c
8. box.c
9. spinner.c: my first real C program, just the star spinner

## How to run these

If you want to see these for yourself, download the .c file, and compile it on your linux machine using `gcc <file.c>`.
For all rotation animations (1-5), you need to link the C math library with the `-lm` option. On macOS, you'll need to use the clang compiler.

Then just run the compiled file with `./a.out`. You might need to add permissions with `chmod +x a.out`.

## Future additions

1. I want to generalize the 3D code of donut.c, cube.c, and cone.c (and maybe more shapes) into a single file that accepts user input to select the shape to show
2. I want to add user interaction that enables the user to dynamically alter:

- the rotation speed (or just the rotation, so you can move the shape around, like a CAD program)
- the lighting direction
- the distance to the object
- the scaling of the object (distance to the "screen")
