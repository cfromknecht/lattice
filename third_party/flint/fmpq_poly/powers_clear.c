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

    Copyright (C) 2013 William Hart
   
******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "fmpq_poly.h"

void 
_fmpq_poly_powers_clear(fmpq_poly_struct * powers, slong len)
{
   slong i;
   for (i = 0; i < 2*len - 1; i++)
      fmpq_poly_clear(powers + i);

   flint_free(powers);
}

void 
fmpq_poly_powers_clear(fmpq_poly_powers_precomp_t pinv)
{
   _fmpq_poly_powers_clear(pinv->powers, pinv->len);
}
