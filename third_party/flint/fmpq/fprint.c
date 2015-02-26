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
    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include "fmpq.h"

void _fmpq_fprint(FILE * file, const fmpz_t num, const fmpz_t den)
{
    if (fmpz_is_one(den))
    {
        fmpz_fprint(file, num);
    }
    else
    {
        fmpz_fprint(file, num);
        fputc('/', file);
        fmpz_fprint(file, den);
    }
}

void fmpq_fprint(FILE * file, const fmpq_t x)
{
    _fmpq_fprint(file, &x->num, &x->den);
}
