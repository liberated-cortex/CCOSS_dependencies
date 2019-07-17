/*         ______   ___    ___ 
 *        /\  _  \ /\_ \  /\_ \ 
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___ 
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      Makedoc's man output routines.
 *
 *      By Shawn Hargreaves.
 *
 *      See readme.txt for copyright information.
 *
 *      See allegro/docs/src/makedoc/format.txt for a brief description of
 *      the source of _tx files.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "makeman.h"
#include "makedoc.h"
#include "makemisc.h"



char manheader[256] = "";
char mansynopsis[256] = "";

char *man_shortdesc_force1;
char *man_shortdesc_force2;

static int _mpreformat = 0;
static int _mpreindent = 0;



static void _write_man_xref(FILE *f, char *xref, char *ext, int notfirst);
static char *_man_name(char *p);
static void _mfputs(char *p, FILE *f);
static void _write_short_desc(FILE *f, LINE *line);



/* write_man:
 * Entry point of man page generation function.
 */
int write_man(char *filename)
{
   char buf[256], buf2[256];
   char *xref[256];
   int xrefs = 0;
   LINE *line = head;
   LINE *l2;
   FILE *f = NULL;
   FILE *f2;
   char *p;
   int i;

   /* Free strings if not both of them where specified. */
   if (!(man_shortdesc_force1 && man_shortdesc_force2)) {
      if (man_shortdesc_force1)
	 free(man_shortdesc_force1);
      if (man_shortdesc_force2)
	 free(man_shortdesc_force2);
      man_shortdesc_force1 = man_shortdesc_force2 = 0;
   }

   while (line) {
      if (line->flags & (HEADING_FLAG | DEFINITION_FLAG | NODE_FLAG)) {
	 /* close off any previous manpage */
	 if (f) {
	    if (xrefs > 0) {
	       fprintf(f, ".SH SEE ALSO\n");
	       for (i=0; i<xrefs; i++)
		  _write_man_xref(f, xref[i], get_extension(filename), i);
	       fprintf(f, "\n");
	       xrefs = 0;
	    }

	    fclose(f);
	    f = NULL;
	 }
      }

      if (line->flags & MAN_FLAG) {
	 if (line->flags & RETURN_VALUE_FLAG) {
	    fprintf(f, ".SH \"RETURN VALUE\"\n");
	 }
	 else if (line->flags & DEFINITION_FLAG) {
	    /* start a manpage */
	    p = _man_name(line->text);

	    if (p) {
	       strcpy(buf, filename);
	       strcpy(get_filename(buf), p);
	       strcat(buf, ".");
	       strcat(buf, get_extension(filename));

	       /*printf("writing %s\n", buf);*/
	       f = fopen(buf, "w");
	       if (!f)
		  return 1;

	       fprintf(f, ".\\\" Generated by the Allegro makedoc utility\n");
	       fprintf(f, ".TH %s %s %s\n", p, get_extension(filename), manheader);
	       fprintf(f, ".SH NAME\n");

	       fprintf(f, "%s", p);

	       if (!(line->flags & CONTINUE_FLAG)) {
		  l2 = line->next;

		  while ((l2) && (l2->flags & DEFINITION_FLAG)) {
		     p = _man_name(l2->text);

		     if (p)
			fprintf(f, ", %s", p);

		     l2 = l2->next;
		  }
	       }

	       _write_short_desc(f, line);

	       fprintf(f, "\n.SH SYNOPSIS\n");

	       if (mansynopsis[0])
		  fprintf(f, ".B %s\n\n", mansynopsis);

	       /* go ahead and find all the header lines */
	       l2 = line;
	       while (l2 && l2->flags & CONTINUE_FLAG) l2=l2->next;

	       if (l2) {
		  l2 = l2->next;
		  while (l2 && (l2->flags & HEADER_FLAG)) {
		    fprintf(f, ".B %s\n", l2->text);
		    l2 = l2->next;
		    if (l2 && (l2->flags & HEADER_FLAG)) {
		       fprintf(f, ".br\n");
		    }
		  }
	       }
	       fprintf(f, ".sp\n");

	       fputs(".B ", f);
	       _mfputs(line->text, f);

	       i = (line->flags & CONTINUE_FLAG);

	       while ((line->next) && (line->next->flags & DEFINITION_FLAG)) {
		  line = line->next;

		  if (!i) {
		     /* multiple entries require a crosslink file */
		     p = _man_name(line->text);

		     if (p) {
			strcpy(buf2, filename);
			strcpy(get_filename(buf2), p);
			strcat(buf2, ".");
			strcat(buf2, get_extension(filename));

			/*printf("writing %s\n", buf2);*/
			f2 = fopen(buf2, "w");
			if (!f2)
			   return 1;

			fprintf(f2, ".so man%s/%s\n", get_extension(filename), get_filename(buf));
			fclose(f2);
		     }

		     fputc('\n', f);
		  }

		  fputs(".B ", f);
		  _mfputs(line->text, f);
	       }

	       fprintf(f, ".SH DESCRIPTION\n");

	       _mpreformat = 0;
	    }

	    xrefs = 0;
	 }
	 else {
	    /* normal output mode */
	    if (f)
	       _mfputs(line->text, f);
	 }
      }
      else if (line->flags & XREF_FLAG) {
	 xref[xrefs++] = line->text;
      }

      line = line->next;
   }

   return 0;
}



/* _write_man_xref:
 */
static void _write_man_xref(FILE *f, char *xref, char *ext, int notfirst)
{
   char *tok, *p;

   tok = strtok(xref, ",;");

   while (tok) {
      while ((*tok) && (myisspace(*tok)))
	 tok++;

      p = tok;

      while (*p) {
	 if ((!myisalnum(*p)) && (*p != '_'))
	    break;
	 p++;
      }

      if (!*p) {
	 if (notfirst)
	    fprintf(f, ",\n");

	 fprintf(f, ".BR %s (%s)", tok, ext);
	 notfirst = 1;
      }

      tok = strtok(NULL, ",;");
   }
}



/* _man_name:
 */
static char *_man_name(char *p)
{
   static char buf[256];
   int i = 0;

   while ((*p) && (*p != '"'))
      p++;

   if (*p == '"') {
      p++;

      while ((*p) && (*p != '"')) {
	 if ((!myisalnum(*p)) && (*p != '_'))
	    return NULL;

	 buf[i++] = *(p++);
      }

      if (i) {
	 buf[i] = 0;
	 return buf;
      }
   }

   return NULL;
}



/* _mfputs:
 */
static void _mfputs(char *p, FILE *f)
{
   int state = 0;
   int i;

   if (_mpreformat) {
      if (_mpreindent < 0) {
	 _mpreindent = 0;

	 while ((*p) && (myisspace(*p))) {
	    _mpreindent++;
	    p++;
	 }
      }
      else {
	 for (i=0; i<_mpreindent; i++) {
	    if ((!*p) || (!myisspace(*p)))
	       break;
	    p++;
	 }
      }

      fputs("   ", f);
   }
   else {
      while ((*p) && (myisspace(*p)))
	 p++;
   }

   while (*p) {
      /* less-than HTML tokens */
      if ((p[0] == '&') && 
	  (mytolower(p[1]) == 'l') && 
	  (mytolower(p[2]) == 't')) {
	 fputc('<', f);
	 p += 3;
	 state = 1;
      }
      /* greater-than HTML tokens */
      else if ((p[0] == '&') && 
	       (mytolower(p[1]) == 'g') && 
	       (mytolower(p[2]) == 't')) {
	 fputc('>', f);
	 p += 3;
	 state = 1;
      }
      /* bold HTML tokens */
      else if ((p[0] == '<') &&
	       (mytolower(p[1]) == 'b') &&
	       (p[2] == '>')) {
	 if (state)
	    putc('\n', f);
	 fputs(".B ", f);
	 p += 3;
      }
      /* end bold HTML tokens */
      else if ((p[0] == '<') &&
	       (mytolower(p[1]) == '/') &&
	       (mytolower(p[2]) == 'b') &&
	       (p[3] == '>')) {
	 if (state)
	    fputc('\n', f);
	 state = -1;
	 p += 4;
      }
      /* line break HTML tokens */
      else if ((p[0] == '<') &&
	       (mytolower(p[1]) == 'b') &&
	       (mytolower(p[2]) == 'r') &&
	       (p[3] == '>')) {
	 if (state >= 0) {
	    fputc('\n', f);
	    state = 0;
	 }
	 p += 4;
      }
      /* enter preformatted mode */
      else if ((p[0] == '<') &&
	       (mytolower(p[1]) == 'p') &&
	       (mytolower(p[2]) == 'r') &&
	       (mytolower(p[3]) == 'e') &&
	       (p[4] == '>')) {
	 fputs("\n.nf\n", f);
	 state = -1;
	 _mpreformat = 1;
	 _mpreindent = -1;
	 p += 5;
      }
      /* leave preformatted mode */
      else if ((p[0] == '<') &&
	       (mytolower(p[1]) == '/') &&
	       (mytolower(p[2]) == 'p') &&
	       (mytolower(p[3]) == 'r') &&
	       (mytolower(p[4]) == 'e') &&
	       (p[5] == '>')) {
	 fputs("\n.fi\n", f);
	 state = -1;
	 _mpreformat = 0;
	 p += 6;
      }
      /* strip other HTML tokens */
      else if (p[0] == '<') {
	 while ((*p) && (*p != '>'))
	    p++;
	 if (*p)
	    p++;
      }
      /* output other characters */
      else {
	 if (*p == '\\')
	    fputc('\\', f);

	 fputc(*p, f);
	 p++;
	 state = 1;
      }
   }

   if (state >= 0)
      fputc('\n', f);
}

/* _write_short_desc:
 * Advances the line pointer until the next man page definition
 * looking for a short description, which would be printed to
 * the currently open file.
 */
static void _write_short_desc(FILE *f, LINE *line)
{
   assert(f);
   assert(line);
   assert(line->flags & (MAN_FLAG | DEFINITION_FLAG));

   /* Jump current definition. */
   while (line && line->flags & DEFINITION_FLAG)
      line = line->next;
      
   while (1) {
      if (!line)
	 goto empty_title;
      if (line->flags & (MAN_FLAG | DEFINITION_FLAG))
	 goto empty_title;
      if (line->flags & (HEADING_FLAG | DEFINITION_FLAG | NODE_FLAG))
	 goto empty_title;

      if (line->flags & SHORT_DESC_FLAG) {
	 /* Do we need to add the forced text to the title? */
	 if (man_shortdesc_force1 && !mystristr(line->text, man_shortdesc_force1))
	    fprintf(f, " \\- %s %s\\&", line->text, man_shortdesc_force2);
	 else
	    fprintf(f, " \\- %s\\&", line->text);
	 return ;
      }
         
      line = line->next;
   }

   empty_title:
   /* If we reach here, we didn't find a short description. Force one? */
   if (man_shortdesc_force1)
      fprintf(f, " \\- %s\\&", man_shortdesc_force2);
}



