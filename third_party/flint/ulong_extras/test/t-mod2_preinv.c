/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   int i, result;
   FLINT_TEST_INIT(state);
   

   flint_printf("mod2_preinv....");
   fflush(stdout);

   for (i = 0; i < 100000 * flint_test_multiplier(); i++)
   {
      mp_limb_t d, dinv, n, r1, r2;

      d = n_randtest_not_zero(state);
      n = n_randtest(state);
      
      dinv = n_preinvert_limb(d);

      r1 = n_mod2_preinv(n, d, dinv);
      r2 = n%d;

      result = (r1 == r2);
      if (!result)
      {
         flint_printf("FAIL:\n");
         flint_printf("n = %wu, d = %wu, dinv = %wu\n", n, d, dinv); 
         flint_printf("r1 = %wu, r2 = %wu\n", r1, r2);
         abort();
      }
   }

   FLINT_TEST_CLEANUP(state);
   
   flint_printf("PASS\n");
   return 0;
}
