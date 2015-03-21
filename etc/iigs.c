/* IIgs */

#include <string.h>

static char rcsid[] = "$Id$";

#ifndef LCCDIR
#define LCCDIR "/usr/local/lib/lcc-816/"
#endif

// -DGNO 
char *suffixes[] = { ".c", ".i", ".s", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { LCCDIR "cpp",
	"-D__STDC__=1", "-D__appleiigs__", "-D__65816__",
	"$1", "$2", "$3", 0 };

char *include[] = { "-I" LCCDIR "include", "-I" LCCDIR "toolbox", 0 };
char *com[] = { LCCDIR "rcc", "-target=wdc65816/iigs",
	"$1", "$2", "$3", 0 };
char *as[] = { LCCDIR "as", "-o", "$3", "$1", "$2", 0 };
char *ld[] = { LCCDIR "ld", "-o", "$3", "$1", 
	LCCDIR "lib/startup.o", "-L" LCCDIR "lib/", 0 };

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
