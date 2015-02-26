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

    Copyright (C) 2012 Lina Kulakova

******************************************************************************/

#include <math.h>
#include "fmpz_mod_poly.h"

void
fmpz_mod_poly_factor(fmpz_mod_poly_factor_t res,
                     const fmpz_mod_poly_t f)
{
    slong n = fmpz_mod_poly_degree(f);
    mp_bitcnt_t bits = fmpz_bits(&f->p);

    if (5 * bits + n > 75)
        fmpz_mod_poly_factor_kaltofen_shoup(res, f);
    else
        fmpz_mod_poly_factor_cantor_zassenhaus(res, f);
}
