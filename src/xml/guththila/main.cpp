/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *  @author Dinesh Premalal (xydinesh@gmail.com
 *			     premalal@opensource.lk)
 *
 */

#include "XMLParserGuththila.hpp"

int main ()
{
  FILE *f = fopen ("response.xml","r");
  FileInputStream *file = new FileInputStream (f);
  XMLParserGuththila *guth = new XMLParserGuththila (file);
  int i = 0;
  while (i<20)
    {
      int ix = 0;
      const AnyElement *e = guth->next ();
      
      if (e)
	{
	  switch (e->m_type)
	    {
	    case 0:
	      char *p;
	      if (e->m_type2 == 0)
		{
		  if (!strncmp (e->m_pchNameOrValue,"xml",3))
		    printf ("<?xml");
		  else 
		    {
		      printf ("<");
		      p = (char *) e->m_pchNameOrValue;
		      printf ("%s", p);
		      free (p);
		      if (e->m_pchNamespace)
		      printf (" xmlns:%s", e->m_pchNamespace);
		    }
		}
	      else 
		{
		  printf ("</");
		  p = (char *)e->m_pchNameOrValue;
		  printf ("%s", p);
		  free (p);
		}
		  for (int ia = 0; e->m_pchAttributes[ia]; ia += 3)
		    {
		      printf (" ");
		      p = (char *)e->m_pchAttributes[ia+1];
		      if (p)
			{
			  printf ("%s:", p);
			 free (p);
			}
		      p = (char *)e->m_pchAttributes[ia];
		      printf ("%s=\"", p);
		      free (p);
		      p = (char *)e->m_pchAttributes[ia+2];
		      printf ("%s\"", p);
		       free (p);
		    }


		  printf (">");
	      break;
	    case 1:
	      char *q;
	      q = (char *)e->m_pchNameOrValue;
	      printf ("%s", q);
	      break;
	    case 2:
	      char *r;
	      printf ("<");
	      r = (char *)e->m_pchNameOrValue;
	      printf ("%s", r);
	      if (e->m_pchNamespace)
	      printf (" xmlns: %s", (char *)e->m_pchNamespace);
	      printf (">");
	      free (r);
	      break;
	    };
      
	}
      else 
	break;
	
      i++;
    }
  return 0;
}
