/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/******************************************************************************

 linear_algebra.c
 
 Routines for dealing with building the final F_2 matrix

 (C) 2006, 2011 William Hart

******************************************************************************/

#define ulong ulongxx /* interferes with system includes */
#include <stdlib.h>
#include <stdio.h>
#undef ulong
#define ulong mp_limb_t 

#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "qsieve.h"
#include "fmpz.h"

/*=========================================================================
   
   Compare relations:
 
   Function: Compare two relations; used by qsort
 
==========================================================================*/

int qsieve_ll_relations_cmp(const void * a, const void * b)
{
  la_col_t * ra = *((la_col_t **) a);
  la_col_t * rb = *((la_col_t **) b);
  slong point;

  if (ra->weight > rb->weight) return 1;
  else if (ra->weight < rb->weight) return -1;
  
  for (point = ra->weight - 1; point >= 0 
                            && (ra->data[point] == rb->data[point]); point--)
  {
      ;
  }
  
  if (point == -1) return 0;

  if (ra->data[point] > rb->data[point]) return 1;
  else if (ra->data[point] < rb->data[point]) return -1;

  return 0;
}

int qsieve_ll_relations_cmp2(const void * a, const void * b)
{
  la_col_t * ra = (la_col_t *) a;
  la_col_t * rb = (la_col_t *) b;
  slong point;

  if (ra->weight > rb->weight) return 1;
  else if (ra->weight < rb->weight) return -1;
  
  for (point = ra->weight - 1; point >= 0 
                            && (ra->data[point] == rb->data[point]); point--)
  {
      ;
  }
  
  if (point == -1) return 0;

  if (ra->data[point] > rb->data[point]) return 1;
  else if (ra->data[point] < rb->data[point]) return -1;

  return 0;
}
  
/*==========================================================================
   Merge sort:

   Function: Merge a list of sorted new relations into a list of existing
             sorted relations. Sort is done using a merge sort algorithm
             with a short stack.
   
===========================================================================*/

slong qsieve_ll_merge_sort(qs_t qs_inf)
{
   la_col_t * matrix = qs_inf->matrix;
   slong columns = qs_inf->columns;
   la_col_t ** qsort_arr = qs_inf->qsort_arr;
   slong num_unmerged = qs_inf->num_unmerged;
   slong dups = 0;
   int comp;
   slong i;

   for (i = columns + num_unmerged - WORD(1); i >= dups; i--) 
   {
      if (!columns) comp = -1;
      else if (!num_unmerged) comp = 1;
      else 
         comp = qsieve_ll_relations_cmp2(matrix + columns - WORD(1), qsort_arr[num_unmerged - WORD(1)]);
      
      switch (comp)
      {
         case -1: 
         {
            copy_col(matrix + i, qsort_arr[num_unmerged - WORD(1)]);
            clear_col(qsort_arr[num_unmerged - WORD(1)]);
            num_unmerged--;
            break;
         }
         case 1: 
         {
            copy_col(matrix + i, matrix + columns - WORD(1));
            columns--;
            break;
         }
         case 0: 
         {
            free_col(qsort_arr[num_unmerged - WORD(1)]);
            clear_col(qsort_arr[num_unmerged - WORD(1)]);
            num_unmerged--;
            copy_col(matrix + i, matrix + columns - WORD(1));
            columns--;
            dups++;
            break;
         }
      } 
   }
   
   columns = qs_inf->columns + qs_inf->num_unmerged - dups;
   
   if (dups)
   {
      slong i;
      for (i = 0; i < columns; i++)
          copy_col(matrix + i, matrix + i + dups);
      
      for ( ; i < columns + dups; i++)
          clear_col(matrix + i);
   }
            
   qs_inf->columns = columns;
   columns = qs_inf->num_unmerged - dups;
   qs_inf->num_unmerged = 0;

#if (QS_DEBUG & 64)
   flint_printf("%wd new, %wd dups\n", columns, dups);
#endif   

   return columns;
}

/*==========================================================================
   Merge relations:

   Function: Merge unmerged relations into the matrix
   
===========================================================================*/

slong qsieve_ll_merge_relations(qs_t qs_inf)
{
   const slong num_unmerged = qs_inf->num_unmerged;
   la_col_t * unmerged = qs_inf->unmerged;
   la_col_t ** qsort_arr = qs_inf->qsort_arr;
   
   if (num_unmerged)
   {
      slong i;

      for (i = 0; i < num_unmerged; i++)
         qsort_arr[i] = unmerged + i;
      
      qsort(qsort_arr, num_unmerged, sizeof(la_col_t *), qsieve_ll_relations_cmp);

      return qsieve_ll_merge_sort(qs_inf);
   }
   
   return 0;
}

/*==========================================================================
   Insert relation:

   Function: Insert the relation into the matrix and store the Y value
   
===========================================================================*/

slong qsieve_ll_insert_relation(qs_t qs_inf, fmpz_t Y)
{
   la_col_t * unmerged = qs_inf->unmerged;
   slong num_unmerged = qs_inf->num_unmerged;
   slong * small = qs_inf->small;
   slong num_factors = qs_inf->num_factors; 
   fac_t * factor = qs_inf->factor; 
   slong * curr_rel = qs_inf->curr_rel;
   slong fac_num = 0; 
   slong i;

   clear_col(unmerged + num_unmerged);
   
   for (i = 0; i < qs_inf->small_primes; i++)
   {
       if (small[i] & 1) insert_col_entry(unmerged + num_unmerged, i);
       if (small[i]) 
       {
          curr_rel[2*fac_num + 1] = i;
          curr_rel[2*fac_num + 2] = small[i];
          fac_num++;
       }
   }
   
   for (i = 0; i < num_factors; i++)
   {
       if (factor[i].exp & 1) insert_col_entry(unmerged + num_unmerged, factor[i].ind);
       curr_rel[2*fac_num + 1] = factor[i].ind;
       curr_rel[2*fac_num + 2] = factor[i].exp;
       fac_num++;
   }

   curr_rel[0] = fac_num;
   
   unmerged[num_unmerged].orig = qs_inf->num_relations;
   
   fmpz_set(qs_inf->Y_arr + qs_inf->num_relations, Y); 
   
   qs_inf->curr_rel += qs_inf->max_factors*2;
   qs_inf->num_unmerged++;
   qs_inf->num_relations++;
   
   if (qs_inf->num_unmerged == qs_inf->qsort_rels)
      return qsieve_ll_merge_relations(qs_inf);
   
   return 0;
}

