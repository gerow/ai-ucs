Michael Gerow
6804481189
gerow@usc.edu

== Build Instructions:
Make sure you are using bash when you build, otherwise the script that adds the necessary binaries to the path will fail.  You can do with just by typing 'bash' in the terminal.

Once in bash, you need to source setup.sh, which should be as easy as running 'source ./setup.sh' from within the project directory.

After that, all you need to do is run 'make' to build the program, and then run './build/src/main' to run it.

It will be looking in the current working directory (pwd) for the input file and will be writing the output file to the current working directory.  Because of this it may be easier to move this executable to a different place while running it.

There is plenty of stuff printed to stdout tracing the execution of the program.  For some difficult problems this can make the program run quite slowly.  It may help, in these cases, to redirect stdout to /dev/null

== Questions Answered:
1.  First, knight seems completely awful.  It consistently gets worse results.  Canberra also gets worse results, while euclidian seems to always require less paths to be evaluated.  This seems to imply that euclidian would be a better heuristic, though, since it requires a square root it actually is pretty expensive computationally while canberra doesn't require such an operation.  Overall you would need to do some performance measurements to see which one _actually_ performs better with your data set, but in terms of reducing the number of paths explored euclidian seems to be the best.

