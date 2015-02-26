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

#include "fmpq_mat.h"

void
fmpq_mat_set_fmpz_mat_div_fmpz(fmpq_mat_t X, const fmpz_mat_t Xnum,
                                                const fmpz_t den)
{
    slong i, j;

    if (fmpz_is_one(den))
    {
        fmpq_mat_set_fmpz_mat(X, Xnum);
    }
    else if (*den == WORD(-1))
    {
        fmpz_t t;
        fmpz_init(t);
        fmpz_set(t, den);

        for (i = 0; i < Xnum->r; i++)
        {
            for (j = 0; j < Xnum->c; j++)
            {
                fmpz_neg(fmpq_mat_entry_num(X, i, j),
                    fmpz_mat_entry(Xnum, i, j));
                fmpz_one(fmpq_mat_entry_den(X, i, j));
            }
        }

        fmpz_clear(t);
    }
    else
    {
        for (i = 0; i < Xnum->r; i++)
        {
            for (j = 0; j < Xnum->c; j++)
            {
                fmpz_set(fmpq_mat_entry_num(X, i, j),
                                fmpz_mat_entry(Xnum, i, j));
                fmpz_set(fmpq_mat_entry_den(X, i, j), den);
                fmpq_canonicalise(fmpq_mat_entry(X, i, j));
            }
        }
    }
}
