/*
 * Tractorgen, an ASCII tractor generator
 *
 * Copyright (C) 2000 Conrad Parker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>

int
tractorgen (int nr_wheels)
{
  int w;
  int tractor_coefficient = (nr_wheels - 3) * 2 -1;

  printf ("         r");
  for (w=0; w < tractor_coefficient; w++) putchar('-');
  putchar('\n');

  printf ("        _|\n");

  printf ("       / |");
  for (w=0; w < tractor_coefficient; w++) putchar('_');
  printf ("\\_    \\\\\n");

  printf ("      |   ");
  for (w=0; w < tractor_coefficient; w++) putchar(' ');
  printf ("|o|----\\\\\n");

  printf ("      |___");
  for (w=0; w < tractor_coefficient; w++) putchar('_');
  printf ("___\\_--_\\\\\n");

  printf ("     (O)_O");
  for (w=0; w < (nr_wheels - 3); w++) printf("_O");
  printf ("_(O)    \\\\\n");
}

int
main (int argc, char **argv)
{
  int nr_wheels=7;

  if (argc >= 2)
    nr_wheels = atoi (argv[1]);

  if (nr_wheels < 4) {
    fprintf (stderr, "tractorgen: ERROR!! Tractors must have at least four wheels!! FOOL!\n");
    abort ();
  }

  tractorgen(nr_wheels);
}
