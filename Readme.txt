Michael Gerow
6804481189
gerow@usc.edu

== Build Instructions:
Make sure you are using bash when you build, otherwise the script that adds the necessary binaries to the path will fail.  You can do with just by typing 'bash' in the terminal.

Once in bash, you need to source setup.sh, which should be as easy as running 'source ./setup.sh' from within the project directory.

After that, all you need to do is run 'make' to build the program, and then run './build/src/main' to run it.

It will be looking in the current working directory (pwd) for the input file and will be writing the output file to the current working directory.  Because of this it may be easier to move this executable to a different place while running it.

There is plenty of stuff printed to stdout tracing the execution of the program.  For some difficult problems this can make the program run quite slowly.  It may help, in these cases, to redirect stdout to /dev/null

You can also run the built in test suite with 'make test' or 'make check' if you're one of *those* kinds of people.

== Questions Answered:
1. It is easy to see that the branching factor for this problem is 4. We can also see that each branch gives us a new square with a branching factor of 4, although one of these loops back to the original square. Even so, let's stick with 4 for now.

Since each new square introduces a branching factor of 4 that means that our state space will be 4**S where S is the number of squares.  On a size N square board this is N**2.  So the state space should be something on the order of 4**N**2

2. There is NOT always a solution regardless of the starting positions.  This can be very easily proved by taking a 2 by 2 board and placing A in the bottom left and B in the bottom right like so:

-----
| | |
-----
|A|B|
-----

In this case if A tries to move up then B will have to move right, but that is not a legal move.  Additionally, if A tries to move right B will try to move down, which is also an illegal move.  Since A can also not move left or down because that would be illegal moves for it we can see that there is no solution for this starting position.
