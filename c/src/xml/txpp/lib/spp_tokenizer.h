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
 */

enum 
{
  BT_NONXML,      /* 0: */
  BT_MALFORM,     /* 1: */
  BT_LT,     /* 2:less than */
  BT_AMP,    /* 3:ampersand */
  BT_RSQB,     /* 4: */
  BT_LEAD2,    /* 5: */
  BT_LEAD3,    /* 6: */
  BT_LEAD4,    /* 7: */
  BT_TRAIL,    /* 8: */
  BT_CR,    /* 9: */
  BT_LF,    /* 10:carriage return(new line) */
  BT_GT,    /* 11:greater than */
  BT_QUOT,    /* 12:double quote */
  BT_APOS,    /* 13:single quote */
  BT_EQUALS,    /* 14:equal sign */
  BT_QUEST,    /* 15:question mark(?) */
  BT_EXCL,    /* 16: */
  BT_SOL,    /* 17:slash */
  BT_SEMI,    /* 18: */
  BT_NUM,    /* 19: */
  BT_LSQB,    /* 20: */
  BT_S,        /* 21:space */
  BT_NMSTRT,   /* //22:_, */
  BT_COLON,    /*23:colon */
  BT_HEX,    /* 24:hexadecimal characters */
  BT_DIGIT,    /* 25:digit */
  BT_NAME,    /* 26:dot, */
  BT_MINUS,    /* 27:dash(minus sign) */
  BT_OTHER,     /*28: known not to be a name or name start character... for ex  ` character */
  BT_NONASCII,     /* 29: might be a name or name start character  */
  BT_PERCNT,    /* 30: */
  BT_LPAR,    /* 31: */
  BT_RPAR,    /* 32: */ 
  BT_AST,    /* 33: */
  BT_PLUS,    /* 34: */ 
  BT_COMMA,    /* 35: */
  BT_VERBAR    /* 36: */
};    


#include <stddef.h>


