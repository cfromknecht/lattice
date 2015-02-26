/*============================================================================

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

    Copyright (C) 2011, 2012 Sebastian Pancratz
 
******************************************************************************/

#include "qadic.h"

void qadic_set_fmpz_poly(qadic_t rop, const fmpz_poly_t op, 
                         const qadic_ctx_t ctx)
{
    const slong len = op->length;

    if (len == 0)
    {
        qadic_zero(rop);
    }
    else
    {
        padic_poly_fit_length(rop, len);
        _padic_poly_set_length(rop, len);
        _fmpz_vec_set(rop->coeffs, op->coeffs, len);
        rop->val = 0;

        qadic_reduce(rop, ctx);
    }
}

