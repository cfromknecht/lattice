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

void
nmod_poly_mat_add(nmod_poly_mat_t C,
                        const nmod_poly_mat_t A, const nmod_poly_mat_t B)
{
    slong i, j;

    for (i = 0; i < A->r; i++)
        for (j = 0; j < A->c; j++)
            nmod_poly_add(nmod_poly_mat_entry(C, i, j),
                          nmod_poly_mat_entry(A, i, j),
                          nmod_poly_mat_entry(B, i, j));
}
