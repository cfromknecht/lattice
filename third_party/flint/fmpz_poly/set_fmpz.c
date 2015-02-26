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
fmpz_poly_set_fmpz(fmpz_poly_t poly, const fmpz_t c)
{
    if (fmpz_is_zero(c))
        fmpz_poly_zero(poly);
    else
    {
        fmpz_poly_fit_length(poly, 1);
        fmpz_set(poly->coeffs, c);
        _fmpz_poly_set_length(poly, 1);
    }
}
