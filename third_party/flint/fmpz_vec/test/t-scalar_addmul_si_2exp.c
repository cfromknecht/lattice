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

    Copyright (C) 2009 William Hart

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "ulong_extras.h"
#include "long_extras.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("scalar_addmul_si_2exp....");
    fflush(stdout);

    

    /* Compare with alternative method of computation */
    for (i = 0; i < 1000 * flint_test_multiplier(); i++)
    {
        fmpz *a, *b, *c, *d;
        slong len, x;
        mp_bitcnt_t exp;

        len = n_randint(state, 100);

        a = _fmpz_vec_init(len);
        b = _fmpz_vec_init(len);
        c = _fmpz_vec_init(len);
        d = _fmpz_vec_init(len);

        _fmpz_vec_randtest(a, state, len, 200);
        _fmpz_vec_randtest(b, state, len, 200);
        _fmpz_vec_set(c, b, len);

        x = z_randtest(state);
        exp = n_randint(state, 200);

        _fmpz_vec_scalar_addmul_si_2exp(b, a, len, x, exp);
        _fmpz_vec_scalar_mul_2exp(d, a, len, exp);
        _fmpz_vec_scalar_addmul_si(c, d, len, x);

        result = (_fmpz_vec_equal(b, c, len));
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("x = %wd, exp = %wu\n", x, exp);
            _fmpz_vec_print(b, len), flint_printf("\n\n");
            _fmpz_vec_print(c, len), flint_printf("\n\n");
            abort();
        }

        _fmpz_vec_clear(a, len);
        _fmpz_vec_clear(b, len);
        _fmpz_vec_clear(c, len);
        _fmpz_vec_clear(d, len);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
