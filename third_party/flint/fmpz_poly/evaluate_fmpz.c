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

    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"

void
_fmpz_poly_evaluate_fmpz(fmpz_t res, const fmpz * f, slong len, const fmpz_t a)
{
    if (len <= 50)
        _fmpz_poly_evaluate_horner_fmpz(res, f, len, a);
    else
        _fmpz_poly_evaluate_divconquer_fmpz(res, f, len, a);
}

void
fmpz_poly_evaluate_fmpz(fmpz_t res, const fmpz_poly_t f, const fmpz_t a)
{
    if (res == a)
    {
        fmpz_t t;

        fmpz_init(t);
        _fmpz_poly_evaluate_fmpz(t, f->coeffs, f->length, a);
        fmpz_swap(res, t);
        fmpz_clear(t);
    }
    else
        _fmpz_poly_evaluate_fmpz(res, f->coeffs, f->length, a);
}
