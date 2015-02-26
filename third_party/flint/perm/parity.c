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

#include "perm.h"

int
_perm_parity(const slong *vec, slong n)
{
    slong i, k;
    int * encountered;
    int parity;

    if (n <= 1)
        return 0;

    parity = 0;
    encountered = flint_calloc(n, sizeof(int));

    for (i = 0; i < n; i++)
    {
        if (encountered[i] != 0)
        {
            parity ^= 1;
        }
        else
        {
            k = i;
            do
            {
                k = vec[k];
                encountered[k] = 1;
            }
            while (k != i);
        }
    }

    flint_free(encountered);
    return parity;
}
