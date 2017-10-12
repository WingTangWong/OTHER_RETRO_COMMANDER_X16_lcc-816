/* IIgs */

#include <string.h>

static char rcsid[] = "$Id$";

#ifndef LCCDIR
#define LCCDIR "/usr/local/share/lcc-816/"
#endif

// -DGNO 
/*
	$1 is extra arguments (from the command line)
	$2 is the input file
	$3 is the output file.
*/

char *suffixes[] = { ".c", ".i", ".s", ".omf", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { LCCDIR "bin/cpp",
	"-D__STDC__=1", "-D__appleiigs__", "-D__65816__",
	"$1", "$2", "$3", 0 };

char *include[] = { "-I" LCCDIR "include", "-I" LCCDIR "include/toolbox", 0 };
char *com[] = { LCCDIR "bin/rcc", "-target=wdc65816/iigs",
	"$1", "$2", "$3", 0 };
char *as[] = { LCCDIR "bin/asm-816", "-o", "$3", "$1", "$2", 0 };
char *ld[] = { LCCDIR "bin/ld-816", 
	"-o", "$3", 
	"$1", 
	LCCDIR "lib/crt.omf", 
	"-L" LCCDIR "lib/", 
	"$2", 
	0 };

extern char *concat(char *, char *);

int option(char *arg) {

	// options...	
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat(&arg[8], "/cpp");
		com[0] = concat(&arg[8], "/rcc");
		return 0;
	}

	// -nda, etc to use different link flags.
	// -gno to use gno headers, -DGNO?
	return 1;
}
