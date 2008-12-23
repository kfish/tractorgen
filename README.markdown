
TRACTORGEN
==========

Generates ASCII tractors.

This program generates ASCII tractors using the universal tractor
coefficient (TC). The intended audience is practical ASCII tractor
theorists and lay people interested in abstract tractor theory.

Before using this program, ensure that you understand the fundamental
theorem of ASCII tractor mechanics:

        "ASCII Tractors must have at least four wheels." [1]

Note that this theorem applies to side-on views. No useful models of
two-sided ASCII tractors have been found, nor is there even any
concrete proof of their existence.

In keeping with this theorem, TRACTORGEN will politely inform the user
if any attempt to make tractors with less than four wheels is made
(by calling abort(2) and dumping core).

USAGE
-----

Tractorgen takes one argument. This argument is indirectly related
to the TC and is a cardinal enumerating the desired wheel
configuration. If no argument is given, the optimal configuration
of 7 is generated.

For example, if you want a tractor with 5 wheels, type at the shell
prompt:

$ tractorgen 5

Conversely, if you want a tractor with 113 wheels, type:

$ tractorgen 113

Remember that tractors with large numbers of wheels may overflow the
width of your terminal, with unpredictable results. Actually, it will
probably just look like shit.

WEB PAGE
--------

For updates and news regarding TRACTORGEN (both completely unlikely),
see http://www.vergenet.net/~conrad/software/tractorgen/

LICENSE
-------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version. See the file COPYING for details.

Though I have no idea why you'd want to do any of this.

AUTHOR
------

This was written by Kbert (k@vergenet.net), more as a dare than
anything else. Original inspiration from SCOboy for asking a dumb
question.

REFERENCES
----------

[1] See, for example, "Introductory ASCII tractor design, vols 3-7",
Blum&Merven, Slarken Press 1973.

