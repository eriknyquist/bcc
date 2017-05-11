Brainfuck compiler
==================

Compiles `Brainfuck <https://en.wikipedia.org/wiki/Brainfuck>`_ source code into
executable format.

(Actually, more like a brainfuck-to-C translator that invokes GCC to get an
executable)

Two sample brainfuck programs, ``hello_world.b`` (prints "Hello world!" to the
terminal), and ``sierpinski.b`` (prints a pretty ASCII triangle to the
terminal) are provided in this repository.

Install
=======

::

    > make
    > sudo make install

Now, you have two new programs installed:

    * ``btoc`` (reads a brainfuck source file, prints C to stdout)
    * ``bfcc`` (reads a brainfuck source file, and creates an executable by
      running ``btoc`` and piping it to ``gcc``)

Compile a brainfuck program
===========================

If you have GCC and a C standard lib. installed, you can use ``bfcc`` to compile
brainfuck programs directly into executable format. Here is an example, Using
``hello_world.b``

::

    > bfcc hello_world.b -o hello_world
    > ./hello_world

    Hello World!

    >

Or, if (for some reason) you want to see the C code, you can just run ``btoc``
on the brainfuck program yourself

::

    > btoc hello_world.b > hello_world.c
