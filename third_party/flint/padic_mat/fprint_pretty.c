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

    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include "fmpz_mat.h"
#include "padic_mat.h"

int padic_mat_fprint_pretty(FILE * file, 
                            const padic_mat_t A, const padic_ctx_t ctx)
{
    const slong r = padic_mat(A)->r;
    const slong c = padic_mat(A)->c;

    slong i, j, v;
    fmpz_t u;

    fmpz_init(u);

    fputc('[', file);
    for (i = 0; i < r; i++)
    {
        fputc('[', file);
        for (j = 0; j < c; j++)
        {
            v = A->val + fmpz_remove(u, padic_mat_entry(A, i, j), ctx->p);

            _padic_fprint(file, u, v, ctx);

            if (j != c - 1)
                fputc(' ', file);
        }
        fputc(']', file);
        if (i != r - 1)
            fputc('\n', file);
    }
    fputc(']', file);

    fmpz_clear(u);

    return 1;
}

