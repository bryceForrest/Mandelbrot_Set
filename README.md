# Mandelbrot Set
![mandelbrot](https://user-images.githubusercontent.com/99369790/206013718-b8299dc5-b694-47c4-b064-89535a598a2b.png)

Consider the formula:
$$z_{n+1} = {z_n}^2 + c$$
Choose a constant value, $c$, and use a starting value of $0$ for $z_0$. 

For example, $c = 3$:
$$z_1 = 0^2 + 3 = 3$$
$$z_2 = 3^2 + 3 = 12$$
$$z_3 = 12^2 + 3 = 147$$
$$z_4 = 147^2 + 3 = 21612$$
$$\ldots$$

Notice that we are plugging in the output of the previous iteration into the function for $z_n$ to obtain $z_{n+1}$. This idea is known as ***recursion***, and is common in mathematics and computer science. 

It's clear to see that this quickly races off to increasingly unwieldy numbers, towards infinity. It's tempting to assume that this will happen for any number, but that's not the case.

If, instead, we chose a fractional value, such as $c = -\frac{1}{4}$, something else occurs:
$$z_1 = 0^2 + (-\frac{1}{4}) = -\frac{1}{4}$$
$$z_2 = (-\frac{1}{4})^2 + (-\frac{1}{4}) = -\frac{3}{16}$$
$$z_3 = (-\frac{3}{16})^2 + (-\frac{1}{4}) = -\frac{55}{256}$$
$$z_4 = (-\frac{55}{256})^2 + (-\frac{1}{4}) = -\frac{13359}{65536}$$
$$\ldots$$

While the values in the numerator and denomenator are growing larger and more unmanageable, the decimal value is actually converging, getting closer and closer to a single value. In this case, that value is around $-0.20710678118654752$. Numbers with this property are values for which the function $z_{n+1} = {z_n}^2 + c$ is ***bounded***.

Something more interesting occurs in the case of complex numbers. 

## Complex Numbers:

A complex number, $a + bi$, contains both a real number part, $a$, and an imaginary number part, $bi$. 

An imaginary number is some multiple of $i$, where $i = \sqrt{-1}$. For example, 
$$\sqrt{-25} = \sqrt{25} \cdot \sqrt{-1} = 5i$$

Complex numbers begin to pop out when solving quadratics that we previously regarded as having no solution, for example:

$$x^2 + 2x + 2 = 0$$

Applying the quadratic formula:
$$x = \frac{-2 \pm \sqrt{2^2 - 4(1)(2)}}{2(1)}$$
$$x = \frac{-2 \pm \sqrt{-4}}{2}$$
$$x = \frac{-2 \pm \sqrt{4}\cdot \sqrt{-1}}{2}$$
$$x = \frac{-2}{2} \pm \frac{2\cdot \sqrt{-1}}{2}$$
$$x = -1 \pm i$$

In this case, the solution consists of two complex numbers, $-1 + i$ and $-1 -i$.

It is common to graph complex numbers on a plane consisting of a horizontal real axis and a vertical imaginary axis.

## Applying Complex Numbers
If we apply a complex number to the function above, such as $(-\frac{1}{4} + \frac{1}{4}i)$, we find that, in some cases, this too remains bounded.

$$z_1 = 0^2 + (-\frac{1}{4} + -\frac{1}{4}i) = (-\frac{1}{4} + -\frac{1}{4}i)$$
$$z_2 = (-\frac{1}{4} + -\frac{1}{4}i)^2 + (-\frac{1}{4} + \frac{1}{4}i)$$
Remember that $i^2 = -1$. Multiplying out and combining the real and imaginary parts... 
$$z_2 = (\frac{1}{16} - \frac{2}{16}i + \frac{1}{16}i^2) + (-\frac{1}{4} + \frac{1}{4}i) = (-\frac{1}{4} + \frac{1}{8}i)$$
$$z_3 = (-\frac{1}{4} + \frac{1}{8}i)^2 + (-\frac{1}{4} + -\frac{1}{4}i) = (-\frac{13}{64} + \frac{3}{16}i)$$
$$z_4 = (-\frac{13}{64} + \frac{3}{16})^2 + (-\frac{1}{4} + -\frac{1}{4}i) = (-\frac{999}{4096} + \frac{89}{512}i)$$
$$\ldots$$

Once again, the fractional components are growing exponentially larger and larger, while the decimal value is approaching a consistent stable value. In this case, that value is $-0.22767334511267742 + 0.17178037486125625i$. You don't have to take my word for it though, if you'd like to work this out for yourself... this example is stable after only about 50 iterations. :)

The numbers for which this function remains bounded are apart of a set called the Mandelbrot set.
If we graph the set on the complex plane, something truly unexpected reveals itself.

This is a visualization of the Mandelbrot Set. Despite having been discovered by Robert W. Brooks and Peter Matelski in 1978, it gets its name from the mathematician Benoit Mandelbrot, who was working at IBM in 1980 when he generated the first high quality images of it.

Since we can't really test infinitely many iterations, we can only approximate the set, by checking an arbitrarily large number of iterations (say, perhaps, 100).

Colorized images of the set are created by coloring each point according to its stability.
Though the proof is beyond the scope of this explanation, if $|z_n| > 2$ (that is, if the ***magnitude*** of the result of any iteration is greater than 2), then the sequence will escape towards infinity. 

A point is colored black if it is stable, and is therefore in the Mandelbrot set, and every point outside of the set is colored according to the number of iterations performed before the numbers exceed the escape radius.
