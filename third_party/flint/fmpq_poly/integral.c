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

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "fmpq_poly.h"

void _fmpq_poly_integral(fmpz * rpoly, fmpz_t rden, 
                           const fmpz * poly, const fmpz_t den, slong len)
{
    slong k;
    fmpz_t t;

    fmpz_init(t);
    fmpz_one(t);

    for (k = len - 1; k > 0; k--)
    {
        fmpz_mul(rpoly + k, poly + k - 1, t);
        fmpz_mul_ui(t, t, k);
    }

    fmpz_mul(rden, den, t);

    fmpz_set_ui(t, UWORD(2));
    for (k = 3; k < len; k++)
    {
        fmpz_mul(rpoly + k, rpoly + k, t);
        fmpz_mul_ui(t, t, k);
    }

    fmpz_zero(rpoly);
    _fmpq_poly_canonicalise(rpoly, rden, len);
    fmpz_clear(t);
}

void fmpq_poly_integral(fmpq_poly_t res, const fmpq_poly_t poly)
{
    slong len = poly->length;

    if (len == 0)
    {
        fmpq_poly_zero(res);
        return;
    }

    fmpq_poly_fit_length(res, len + 1);
    _fmpq_poly_integral(res->coeffs, res->den, poly->coeffs, poly->den, len + 1);
    _fmpq_poly_set_length(res, len + 1);
}
