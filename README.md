# Command-Line-Chess
Basic 2-player chess application that runs in your command line.

## Build
Run `make` from the command line to build the program. Execute `game` to play.

If you have GoogleTest set up on your system, you can run `make all` to run the gcov and gtest suites. Note that you must uncomment the `GTFLAGS` line (8) in the makefile first, as it has been disabled to allow make to build properly on systems without gtest.
