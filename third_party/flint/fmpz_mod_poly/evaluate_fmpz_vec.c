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

    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 William Hart

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "fmpz_mod_poly.h"

void
_fmpz_mod_poly_evaluate_fmpz_vec(fmpz * ys, const fmpz * coeffs, 
                        slong len, const fmpz * xs, slong n, const fmpz_t mod)
{
    if (len < 32)
        _fmpz_mod_poly_evaluate_fmpz_vec_iter(ys, coeffs, len, xs, n, mod);
    else
        _fmpz_mod_poly_evaluate_fmpz_vec_fast(ys, coeffs, len, xs, n, mod);
}

void
fmpz_mod_poly_evaluate_fmpz_vec(fmpz * ys,
        const fmpz_mod_poly_t poly, const fmpz * xs, slong n)
{
    _fmpz_mod_poly_evaluate_fmpz_vec(ys, poly->coeffs,
                                        poly->length, xs, n, &(poly->p));
}
