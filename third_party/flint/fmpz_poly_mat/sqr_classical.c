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

#include <stdlib.h>
#include "flint.h"
#include "fmpz_poly.h"
#include "fmpz_poly_mat.h"

#define E fmpz_poly_mat_entry

void
fmpz_poly_mat_sqr_classical(fmpz_poly_mat_t B, const fmpz_poly_mat_t A)
{
    slong n = A->r;

    if (n == 0)
        return;

    if (n == 1)
    {
        fmpz_poly_sqr(E(B, 0, 0), E(A, 0, 0));
        return;
    }

    if (n == 2)
    {
        fmpz_poly_t t, u;

        fmpz_poly_init(t);
        fmpz_poly_init(u);

        fmpz_poly_add(t, E(A, 0, 0), E(A, 1, 1));
        fmpz_poly_mul(u, E(A, 0, 1), E(A, 1, 0));

        fmpz_poly_sqr(E(B, 0, 0), E(A, 0, 0));
        fmpz_poly_add(E(B, 0, 0), E(B, 0, 0), u);

        fmpz_poly_sqr(E(B, 1, 1), E(A, 1, 1));
        fmpz_poly_add(E(B, 1, 1), E(B, 1, 1), u);

        fmpz_poly_mul(E(B, 0, 1), E(A, 0, 1), t);
        fmpz_poly_mul(E(B, 1, 0), E(A, 1, 0), t);

        fmpz_poly_clear(t);
        fmpz_poly_clear(u);
        return;
    }

    fmpz_poly_mat_mul_classical(B, A, A);
}
