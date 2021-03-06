calcCMD
=======

A free command line calculator

calcCMD is designed to be an easy-to-use, Keep-It-Simple calculator for a line
interface. It enables the user to quickly make calculations without having to
deal with a GUI that might be tedious to work with.

calcCMD currently has four modes: classic, postfix, factorial, and orderly. Just
running `calccmd` defaults to orderly mode, since the key advantage of using a
program like calcCMD is its ability to use the order of operations effectively.
Running `calccmd -c` will activate classic mode, which does all math operations
in the order they were entered. `calccmd -p` will parse the arguments following
as reverse Polish notation (or postfix). `calccmd -f` will take one additional
argument and get its factorial.

Calculations can be made more verbose with the `v` option. This can be done in
classic mode with `calccmd -cv`, since (as of version 0.3) options are contained
in a class with attributes.

calcCMD is free software, released under the GNU General Public License, meaning
you have the freedom to do as you wish with the software, including modifying,
distributing copies, and studying the source code. You are free to make your
own modified version and distribute/sell it as long as the freedoms you were
given are also given to your users (it must be released under the same license).

calcCMD was created initially by David McMackins during February of 2014 to
practice using Vim. The simplicity of the program makes it great for new and
aspiring C++ programmers to study the source code and learn how a simple
program works (with minimal understanding required). If you'd like to join the 
development team, please e-mail mcmackinsd@gmail.com
