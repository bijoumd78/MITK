/*****************************************************************************

 Copyright (c) 1993-2000,  Div. Medical and Biological Informatics, 
 Deutsches Krebsforschungszentrum, Heidelberg, Germany
 All rights reserved.

 Redistribution and use in source and binary forms, with or without 
 modification, are permitted provided that the following conditions are met:

 - Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

 - All advertising materials mentioning features or use of this software must 
   display the following acknowledgement: 
          
     "This product includes software developed by the Div. Medical and 
      Biological Informatics, Deutsches Krebsforschungszentrum, Heidelberg, 
      Germany."

 - Neither the name of the Deutsches Krebsforschungszentrum nor the names of 
   its contributors may be used to endorse or promote products derived from 
   this software without specific prior written permission. 

   THIS SOFTWARE IS PROVIDED BY THE DIVISION MEDICAL AND BIOLOGICAL
   INFORMATICS AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
   IN NO EVENT SHALL THE DIVISION MEDICAL AND BIOLOGICAL INFORMATICS,
   THE DEUTSCHES KREBSFORSCHUNGSZENTRUM OR CONTRIBUTORS BE LIABLE FOR 
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
   IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN 
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

 Send comments and/or bug reports to:
   mbi-software@dkfz-heidelberg.de

*****************************************************************************/

/** @file
*   this function draws the edge of an ROI in an image
*/
 
/** this function draws the edge of an ROI in an image
 *  @param pic_old    pointer to original image
 *  @param pol_x    vector with the x-coordinates of the points which 
 *              form the roi
 *  @param pol_y   vector with the y-coordinates of the points which 
 *              form the roi
 *  @param no_pts   number of points used to describe ROI
 *
 *  @arg @c this function could just be used for 2D images
 *
 *  @return   image with roi                          
 *
 * AUTHOR & DATE
 */

/* include files                                                       */

#include "ipFuncP.h"

ipPicDescriptor *ipFuncDrawPoly ( ipPicDescriptor *pic_old,
                                  ipUInt4_t       *pol_x,
                                  ipUInt4_t       *pol_y,
                                  ipUInt4_t       no_pts );

#ifndef DOXYGEN_IGNORE

#ifndef lint
  static char *what = { "@(#)ipFuncDrawPoly\t\tDKFZ (Dept. MBI)\t"__DATE__ };
#endif



/* definition of macros                                                 */

#define MAX( x, y ) ( x > y ) ? x : y
#define MIN( x, y ) ( x < y ) ? x : y

#define DRAW( type, pic_help, a, b, pol_x, pol_y )                       \
{                                                                        \
   ipUInt4_t   beg;                                                      \
   ipUInt4_t   end;                                                      \
   ipUInt4_t   i, j;                                                     \
   ipUInt4_t   y;                                                        \
   type        max;                                                      \
                                                                         \
   max = ( type ) max_gv;                                                \
   /* draw polygon to pic_help                                         */\
                                                                         \
   for ( i = 0; i < no_pts-1; i++ )                                      \
     {                                                                   \
        if ( pol_x[i] == pol_x[i+1] )                                    \
          {                                                              \
             if ( pol_y[i] < pol_y[i+1] )                                \
               {                                                         \
                  beg = pol_y[i];                                        \
                  end = pol_y[i+1];                                      \
               }                                                         \
             else                                                        \
               {                                                         \
                  end = pol_y[i];                                        \
                  beg = pol_y[i+1];                                      \
               }                                                         \
             for ( j = beg; j < end; j++ )                               \
                (( type * )pic_help->data )[ j * pic_help->n[1] + pol_x[i]] = max;\
          }                                                              \
        else                                                             \
          {                                                              \
             if ( pol_x[i] < pol_x[i+1] )                                \
               {                                                         \
                  beg = pol_x[i];                                        \
                  end = pol_x[i+1];                                      \
               }                                                         \
             else                                                        \
               {                                                         \
                  end = pol_x[i];                                        \
                  beg = pol_x[i+1];                                      \
               }                                                         \
             if ( pol_y[i] == pol_y[i+1] ) end = beg -1;                 \
                                                                         \
             for ( j = beg; j <= end; j++ )                              \
               {                                                         \
                  y = a[i] * j + b[i];                                   \
                  (( type * )pic_help->data )[ y * pic_help->n[1] + j ] = max;\
               }                                                         \
          }                                                              \
                                                                         \
        if ( pol_y[i] == pol_y[i+1] )                                    \
          {                                                              \
             if ( pol_x[i] < pol_x[i+1] )                                \
               {                                                         \
                  beg = pol_x[i];                                        \
                  end = pol_x[i+1];                                      \
               }                                                         \
             else                                                        \
               {                                                         \
                  end = pol_x[i];                                        \
                  beg = pol_x[i+1];                                      \
               }                                                         \
                                                                         \
             for ( j = beg; j < end; j++ )                               \
                (( type * )pic_help->data )[ j + pic_help->n[1] * pol_y[i]] = max;\
          }                                                              \
        else                                                             \
          {                                                              \
             if ( pol_y[i] < pol_y[i+1] )                                \
               {                                                         \
                  beg = pol_y[i];                                        \
                  end = pol_y[i+1];                                      \
               }                                                         \
             else                                                        \
               {                                                         \
                  end = pol_y[i+1];                                      \
                  beg = pol_y[i];                                        \
               }                                                         \
             if ( pol_x[i] == pol_x[i+1] ) end = beg - 1;                \
                                                                         \
             for ( j = beg; j <= end; j++ )                              \
               {                                                         \
                  y =  ( j - b[i] ) / a[i];                              \
                  (( type * )pic_help->data )[ j * pic_help->n[1] + y ] = max;\
               }                                                         \
          }                                                              \
     }                                                                   \
                                                                         \
   if ( pol_x[no_pts-1] == pol_x[0] )                                    \
     {                                                                   \
        if ( pol_y[no_pts-1] < pol_y[0] )                                \
          {                                                              \
             beg = pol_y[no_pts-1];                                      \
             end = pol_y[0];                                             \
          }                                                              \
        else                                                             \
          {                                                              \
             end = pol_y[no_pts-1];                                      \
             beg = pol_y[0];                                             \
          }                                                              \
                                                                         \
        for ( j = beg; j < end; j++ )                                    \
           (( type * )pic_help->data )[ j * pic_help->n[1] + pol_x[no_pts-1]] = max;\
     }                                                                   \
   else                                                                  \
     {                                                                   \
        if ( pol_x[no_pts-1] < pol_x[0] )                                \
          {                                                              \
             beg = pol_x[no_pts-1];                                      \
             end = pol_x[0];                                             \
          }                                                              \
        else                                                             \
          {                                                              \
             end = pol_x[no_pts-1];                                      \
             beg = pol_x[0];                                             \
          }                                                              \
        if ( pol_y[no_pts-1] == pol_y[0] ) end = beg -1;                 \
                                                                         \
        for ( j = beg; j <= end; j++ )                                   \
          {                                                              \
             y = a[no_pts-1] * j + b[no_pts-1];                          \
             (( type * )pic_help->data )[ y * pic_help->n[1] + j ] = max;\
          }                                                              \
     }                                                                   \
                                                                         \
   if ( pol_y[no_pts-1] == pol_y[0] )                                    \
     {                                                                   \
        if ( pol_x[no_pts-1] < pol_x[0] )                                \
          {                                                              \
             beg = pol_x[no_pts-1];                                      \
             end = pol_x[0];                                             \
          }                                                              \
        else                                                             \
          {                                                              \
             end = pol_x[no_pts-1];                                      \
             beg = pol_x[0];                                             \
          }                                                              \
                                                                         \
        for ( j = beg; j < end; j++ )                                    \
           (( type * )pic_help->data )[ j + pic_help->n[1] * pol_y[no_pts-1]] = max;\
     }                                                                   \
   else                                                                  \
     {                                                                   \
        if ( pol_y[no_pts-1] < pol_y[0] )                                \
          {                                                              \
             beg = pol_y[no_pts-1];                                      \
             end = pol_y[0];                                             \
          }                                                              \
        else                                                             \
          {                                                              \
             end = pol_y[no_pts-1];                                      \
             beg = pol_y[0];                                             \
          }                                                              \
        if ( pol_x[no_pts-1] == pol_x[0] ) end = beg - 1;                \
                                                                         \
        for ( j = beg; j <= end; j++ )                                   \
          {                                                              \
             y =  ( j - b[no_pts-1] ) / a[no_pts-1];                     \
             (( type * )pic_help->data )[ j * pic_help->n[1] + y ] = max;\
          }                                                              \
     }                                                                   \
}                                                                         

/* -------------------------------------------------------------------- */

/*
** ipFuncDrawPoly
*/

ipPicDescriptor *ipFuncDrawPoly ( ipPicDescriptor *pic_old,
                                  ipUInt4_t       *pol_x,
                                  ipUInt4_t       *pol_y,
                                  ipUInt4_t       no_pts )
{

   ipUInt4_t       min_x, max_x;    /* min, max x-coordinate of ROI     */
   ipUInt4_t       min_y, max_y;    /* min, max y-coordinate of ROI     */
   ipFloat8_t      min_gv, max_gv;
   ipFloat8_t      *a, *b;          /* Gerade y = ax+b                  */
   ipFloat8_t      diff;            /* difference between two points    */
   ipPicDescriptor *pic_help;
   ipUInt4_t       i;

   /* check data                                                        */

   if ( _ipFuncError ( pic_old ) != ipFuncOK ) return ( ipFuncERROR );
   if ( pic_old->dim > 2 ) 
     {
        _ipFuncSetErrno ( ipFuncDIM_ERROR );
        return ( ipFuncERROR );
     }

   if ( _ipFuncExtT ( pic_old->type, pic_old->bpe, &min_gv, &max_gv ) != ipFuncOK )
     return ( ipFuncERROR );

   /* calculate min. and max. coordiantes of ROI                        */

   min_x = pol_x[0];
   min_y = pol_y[0];
   max_x = pol_x[0];
   max_y = pol_y[0];
   for ( i = 1; i < no_pts; i++ )
     {
        min_x = MIN ( min_x, pol_x[i] );
        min_y = MIN ( min_y, pol_y[i] );
        max_x = MAX ( max_x, pol_x[i] );
        max_y = MAX ( max_y, pol_y[i] );
     }

   /* check whether ROI is in image                                     */

   /* Expression is always false.
   if ( min_x < 0 ) 
     {
       _ipFuncSetErrno ( ipFuncDATA_ERROR );
       return ( ipFuncERROR );
     }
   */

   if ( max_x > pic_old->n[0] ) 
     {
       _ipFuncSetErrno ( ipFuncDATA_ERROR );
       return ( ipFuncERROR );
     }

   /* Expression is always false.
   if ( min_y < 0 ) 
     {
       _ipFuncSetErrno ( ipFuncDATA_ERROR );
       return ( ipFuncERROR );
     }
   */

   if ( max_y > pic_old->n[1] ) 
     {
       _ipFuncSetErrno ( ipFuncDATA_ERROR );
       return ( ipFuncERROR );
     }

   /* allocate memory for a and b                                       */

   a = ( ipFloat8_t * ) malloc ( no_pts * sizeof ( ipFloat8_t ) );
   if ( !a )
     {
       _ipFuncSetErrno ( ipFuncMALLOC_ERROR );
       return ( ipFuncERROR );
     }
   b = ( ipFloat8_t * ) malloc ( no_pts * sizeof ( ipFloat8_t ) );
   if ( !b )
     {
       free ( a );
       _ipFuncSetErrno ( ipFuncMALLOC_ERROR );
       return ( ipFuncERROR );
     }

   /* Geraden zwischen zwei benachbarten Punkten berechnen              */

   for ( i = 0; i < no_pts-1;  i++ )
     {
        diff = ( ipFloat8_t ) pol_x[i+1] - ( ipFloat8_t ) pol_x[i];
        if ( diff )
          {
            a[i] = ( ( ipFloat8_t ) pol_y[i+1] - ( ipFloat8_t ) pol_y[i] ) / diff;

            b[i] = ( ( ipFloat8_t ) pol_y[i] - a[i] * ( ipFloat8_t )pol_x[i] );
          }
        else
          {
            b[i] = 0.;
            a[i] = 0.;
           }
     }
   diff = ( ipFloat8_t ) pol_x[no_pts-1] - ( ipFloat8_t )  pol_x[0];
   if ( diff )
     {
        a[no_pts-1] = ( ( ipFloat8_t ) pol_y[no_pts-1] - ( ipFloat8_t ) pol_y[0] ) / diff;
        b[no_pts-1] = ( pol_y[no_pts-1] - a[no_pts-1] * pol_x[no_pts-1] );
     }
   else
     {
        b[no_pts-1] = 0.;
        a[no_pts-1] = 0.;
     }


   /* allocate memory for pic help                                      */

   pic_help = ipPicClone ( pic_old );
   if ( pic_help == NULL )
     {
        free ( a );
        free ( b );
        _ipFuncSetErrno ( ipFuncPICNEW_ERROR );
        return ( ipFuncERROR );
     }

   ipPicFORALL_4 ( DRAW, pic_help, a, b, pol_x, pol_y );

   free ( a );
   free ( b );

   /* Copy Tags */

   ipFuncCopyTags(pic_help, pic_old);

   return ( pic_help );
}
#endif
