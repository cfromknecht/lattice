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

#include "fmpq.h"

void fmpq_mul_2exp(fmpq_t res, const fmpq_t x, mp_bitcnt_t exp)
{
    if (fmpq_is_zero(x) || exp == 0)
    {
        fmpq_set(res, x);
    }
    else
    {
        mp_bitcnt_t v = fmpz_val2(fmpq_denref(x));

        if (exp <= v)
        {
            fmpz_set(fmpq_numref(res), fmpq_numref(x));
            fmpz_fdiv_q_2exp(fmpq_denref(res), fmpq_denref(x), exp);
        }
        else
        {
            fmpz_mul_2exp(fmpq_numref(res), fmpq_numref(x), exp - v);
            fmpz_fdiv_q_2exp(fmpq_denref(res), fmpq_denref(x), v);
        }
    }
}
