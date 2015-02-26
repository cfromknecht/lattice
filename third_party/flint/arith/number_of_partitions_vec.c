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

#include "arith.h"

void
arith_number_of_partitions_vec(fmpz * res, slong len)
{
    fmpz * tmp;
    slong k, n;

    if (len < 1)
        return;

    tmp = _fmpz_vec_init(len);

    tmp[0] = WORD(1);

    for (n = k = 1; n + 4*k + 2 < len; k += 2)
    {
        tmp[n] = WORD(-1);
        tmp[n + k] = WORD(-1);
        tmp[n + 3*k + 1] = WORD(1);
        tmp[n + 4*k + 2] = WORD(1);
        n += 6*k + 5;
    }

    if (n < len) tmp[n] = WORD(-1);
    if (n + k < len) tmp[n + k] = WORD(-1);
    if (n + 3*k + 1 < len) tmp[n + 3*k + 1] = WORD(1);

    _fmpz_poly_inv_series(res, tmp, len);

    _fmpz_vec_clear(tmp, len);
}
