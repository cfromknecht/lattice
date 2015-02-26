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

    Copyright (C) 2010 William Hart

******************************************************************************/

#include <gmp.h>
#include <stdlib.h>
#include "flint.h"
#include "ulong_extras.h"
#include "nmod_vec.h"

void _nmod_vec_randtest(mp_ptr vec, flint_rand_t state, slong len, nmod_t mod)
{
    slong i, sparseness;

    if (n_randint(state, 2))
    {
        for (i = 0; i < len; i++)
            vec[i] = n_randtest(state) % mod.n;
    }
    else
    {
        sparseness = 1 + n_randint(state, FLINT_MAX(2, len));

        for (i = 0; i < len; i++)
        {
            if (n_randint(state, sparseness))
                vec[i] = 0;
            else
                vec[i] = n_randtest(state) % mod.n;
        }
    }
}
