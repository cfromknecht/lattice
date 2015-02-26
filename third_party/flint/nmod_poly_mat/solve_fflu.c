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

#include "flint.h"
#include "nmod_poly.h"
#include "nmod_poly_mat.h"
#include "perm.h"

int
nmod_poly_mat_solve_fflu(nmod_poly_mat_t X, nmod_poly_t den,
                    const nmod_poly_mat_t A, const nmod_poly_mat_t B)
{
    nmod_poly_mat_t LU;
    slong dim, *perm;
    int result;

    if (nmod_poly_mat_is_empty(B))
    {
        nmod_poly_one(den);
        return 1;
    }

    dim = nmod_poly_mat_nrows(A);
    perm = _perm_init(dim);
    nmod_poly_mat_init_set(LU, A);
    result = (nmod_poly_mat_fflu(LU, den, perm, LU, 1) == dim);

    if (result)
        nmod_poly_mat_solve_fflu_precomp(X, perm, LU, B);
    else
        nmod_poly_zero(den);

    _perm_clear(perm);
    nmod_poly_mat_clear(LU);
    return result;
}
