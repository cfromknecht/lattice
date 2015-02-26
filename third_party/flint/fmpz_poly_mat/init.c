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
fmpz_poly_mat_init(fmpz_poly_mat_t A, slong rows, slong cols)
{
    if (rows && cols)
    {
        slong i;

        A->entries = (fmpz_poly_struct *) flint_malloc(rows * cols * sizeof(fmpz_poly_struct));
        A->rows = (fmpz_poly_struct **) flint_malloc(rows * sizeof(fmpz_poly_struct *));

        for (i = 0; i < rows * cols; i++)
            fmpz_poly_init(A->entries + i);

        for (i = 0; i < rows; i++)
            A->rows[i] = A->entries + i * cols;
    }
    else
        A->entries = NULL;

    A->r = rows;
    A->c = cols;
}
