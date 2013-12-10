%{
#include <stdio.h>
#include <stdlib.h>
#include "lburg.h"
static char rcsid[] = "$Id$";
/*lint -e616 -e527 -e652 -esym(552,yynerrs) -esym(563,yynewstate,yyerrlab) */
static int yylineno = 0;
%}
%union {
	int n;
	char *string;
	Tree tree;
}
%term TERMINAL
%term START
%term PPERCENT

%token  <string>        ID TEMPLATE CODE
%token  <n>             INT
%type	<string>	nonterm cost
%type   <tree>          tree
%%
spec	: decls PPERCENT rules		{ yylineno = 0; }
	| decls				{ yylineno = 0; }
	;

decls	: /* lambda */
	| decls decl
	;

decl	: TERMINAL  blist '\n'
	| START nonterm '\n'		{
		if (nonterm($2)->number != 1)
			yyerror("redeclaration of the start symbol\n");
		}
	| '\n'
	| error '\n'			{ yyerrok; }
	;

blist	: /* lambda */
	| blist ID '=' INT      	{ term($2, $4); }
	;

rules	: /* lambda */
	| rules nonterm ':' tree TEMPLATE cost '\n'	{ rule($2, $4, $5, $6); }
	| rules '\n'
	| rules error '\n'		{ yyerrok; }
	;

nonterm	: ID				{ nonterm($$ = $1); }
	;

tree	: ID                            { $$ = tree($1,  0,  0); }
	| ID '(' tree ')'               { $$ = tree($1, $3,  0); }
	| ID '(' tree ',' tree ')'      { $$ = tree($1, $3, $5); }
	;

cost	: CODE				{ if (*$1 == 0) $$ = "0"; }
	;
%%
#include <assert.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

int errcnt = 0;
FILE *infp = NULL;
FILE *outfp = NULL;
static char buf[BUFSIZ], *bp = buf;
static int ppercent = 0;
static int code = 0;

static int get(void) {
	if (*bp == 0) {
		int raw = 0;
		bp = buf;
		*bp = 0;

		for(;;)
		{
			if (fgets(buf, sizeof buf, infp) == NULL)
			{
				if (raw) yywarn("unterminated %{...%}\n");
				return EOF;
			}
			yylineno++;
			if (raw)
			{
				if (strcmp(buf,"%}\n") == 0) {
					raw = 0;
				} else {
					fputs(buf, outfp);
				}
				continue;
			}

			/* # comment */
			if (buf[0] == '#') continue;

			/* %{ code */
			if (strcmp(buf,"%{\n") == 0) {
				raw++;
				continue;
			}

			break;
		}
	}
	return *bp++;
}

void yyerror(char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	if (yylineno > 0)
		fprintf(stderr, "line %d: ", yylineno);
	vfprintf(stderr, fmt, ap);
	if (fmt[strlen(fmt)-1] != '\n')
		 fprintf(stderr, "\n");
	errcnt++;
	va_end(ap);
}

int yylex(void) {
	int c;

	if (code) {
		char *p;
		bp += strspn(bp, " \t\f");
		p = strchr(bp, '\n');
		if (p == NULL)
			p = strchr(bp, '\n');
		while (p > bp && isspace(p[-1]))
			p--;
		yylval.string = alloc(p - bp + 1);
		strncpy(yylval.string, bp, p - bp);
		yylval.string[p - bp] = 0;
		bp = p;
		code--;
		return CODE;
	}
	while ((c = get()) != EOF) {
		switch (c) {
		case ' ': case '\f': case '\t':
			continue;
		case '\n':
		case '(': case ')': case ',':
		case ':': case '=':
			return c;
		}
		if (c == '%' && *bp == '%') {
			bp++;
			return ppercent++ ? 0 : PPERCENT;
		} else if (c == '%' && strncmp(bp, "term", 4) == 0
		&& isspace(bp[4])) {
			bp += 4;
			return TERMINAL;
		} else if (c == '%' && strncmp(bp, "start", 5) == 0
		&& isspace(bp[5])) {
			bp += 5;
			return START;
		} else if (c == '"') {
			char *p = strchr(bp, '"');
			if (p == NULL) {
				yyerror("missing \" in assembler template\n");
				p = strchr(bp, '\n');
				if (p == NULL)
					p = strchr(bp, '\0');
			}
			assert(p);
			yylval.string = alloc(p - bp + 1);
			strncpy(yylval.string, bp, p - bp);
			yylval.string[p - bp] = 0;
			bp = *p == '"' ? p + 1 : p;
			code++;
			return TEMPLATE;
		} else if (c == '{') {
			/* multi-line template */
			char *buffer = NULL;
			int bsize = 0;
			int tsize = 0;
			int lastc = '\n';
			int xxlineno = yylineno;
			int indent = 0;

			for(;;)
			{
				c = get();
				if (c == EOF) {
					int tmp = yylineno;
					yylineno = xxlineno;
					yyerror("unterminated template\n");
					yylineno = tmp;
				}
				if (lastc == '\n' && isspace(c))
				{
					indent++;
					continue;
				}
				if (lastc == '\n' && c == '}') break;
				if (bsize < tsize + 4)
				{
					bsize *= 2;
					if (!bsize) bsize = 512;
					buffer = realloc(buffer, bsize);
					assert(buffer);
				}

				if (indent)
				{
					// indent line.
					buffer[tsize++] = '\\';
					buffer[tsize++] = 't';
				}
				lastc = c;
				indent = 0;

				switch(c)
				{
				case '\\':
					buffer[tsize++] = '\\';
					buffer[tsize++] = '\\';
					break;
				case '\n':
					buffer[tsize++] = '\\';
					buffer[tsize++] = 'n';
					break;
				case '\t':
					buffer[tsize++] = '\\';
					buffer[tsize++] = 't';
					break;
				default: 
					buffer[tsize++] = c;
					break;
				}
			}

			yylval.string = alloc(tsize + 1);
			strncpy(yylval.string, buffer, tsize);
			yylval.string[tsize] = 0;
			code++;
			free(buffer);
			return TEMPLATE;
		
		} else if (isdigit(c)) {
			int n = 0;
			do {
				int d = c - '0';
				if (n > (INT_MAX - d)/10)
					yyerror("integer greater than %d\n", INT_MAX);
				else
					n = 10*n + d;
				c = get();
			} while (c != EOF && isdigit(c));
			bp--;
			yylval.n = n;
			return INT;
		} else if (isalpha(c)) {
			char *p = bp - 1;
			while (isalpha(*bp) || isdigit(*bp) || *bp == '_')
				bp++;
			yylval.string = alloc(bp - p + 1);
			strncpy(yylval.string, p, bp - p);
			yylval.string[bp - p] = 0;
			return ID;
		} else if (isprint(c))
			yyerror("invalid character `%c'\n", c);
		else
			yyerror("invalid character `\\%03o'\n", (unsigned char)c);
	}
	return 0;
}

void yywarn(char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	if (yylineno > 0)
		fprintf(stderr, "line %d: ", yylineno);
	fprintf(stderr, "warning: ");
	vfprintf(stderr, fmt, ap);
}
