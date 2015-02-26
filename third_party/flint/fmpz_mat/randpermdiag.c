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

    Copyright (C) 2010,2011 Fredrik Johansson

******************************************************************************/

#include "fmpz_mat.h"
#include "perm.h"

int
fmpz_mat_randpermdiag(fmpz_mat_t mat, flint_rand_t state,
                      const fmpz * diag, slong n)
{
    int parity;
    slong i;
    slong * rows;
    slong * cols;

    rows = _perm_init(mat->r);
    cols = _perm_init(mat->c);

    parity = _perm_randtest(rows, mat->r, state);
    parity ^= _perm_randtest(cols, mat->c, state);

    fmpz_mat_zero(mat);
    for (i = 0; i < n; i++)
        fmpz_set(fmpz_mat_entry(mat, rows[i], cols[i]), diag + i);

    _perm_clear(rows);
    _perm_clear(cols);

    return parity;
}
