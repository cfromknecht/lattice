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

void
fmpz_poly_mat_mul_classical(fmpz_poly_mat_t C, const fmpz_poly_mat_t A,
    const fmpz_poly_mat_t B)
{
    slong ar, bc, br;
    slong i, j, k;
    fmpz_poly_t t;

    ar = A->r;
    br = B->r;
    bc = B->c;

    if (br == 0)
    {
        fmpz_poly_mat_zero(C);
        return;
    }

    if (C == A || C == B)
    {
        fmpz_poly_mat_t T;
        fmpz_poly_mat_init(T, ar, bc);
        fmpz_poly_mat_mul_classical(T, A, B);
        fmpz_poly_mat_swap(C, T);
        fmpz_poly_mat_clear(T);
        return;
    }

    fmpz_poly_init(t);

    for (i = 0; i < ar; i++)
    {
        for (j = 0; j < bc; j++)
        {
            fmpz_poly_mul(fmpz_poly_mat_entry(C, i, j),
                          fmpz_poly_mat_entry(A, i, 0),
                          fmpz_poly_mat_entry(B, 0, j));

            for (k = 1; k < br; k++)
            {
                fmpz_poly_mul(t, fmpz_poly_mat_entry(A, i, k),
                                 fmpz_poly_mat_entry(B, k, j));

                fmpz_poly_add(fmpz_poly_mat_entry(C, i, j),
                              fmpz_poly_mat_entry(C, i, j), t);
            }
        }
    }

    fmpz_poly_clear(t);
}
