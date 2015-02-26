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
#include <limits.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"

static void check(fmpz_t x, int expected)
{
    if (fmpz_abs_fits_ui(x) != expected)
    {
        flint_printf("FAIL:\n\n");
        flint_printf("x = "), fmpz_print(x), flint_printf("\n");
        abort();
    }
}

int
main(void)
{
    slong i;
    fmpz_t x;

    FLINT_TEST_INIT(state);
    
    flint_printf("abs_fits_ui....");
    fflush(stdout);

    fmpz_init(x);

    fmpz_set_si(x, COEFF_MIN);
    check(x, 1);

    fmpz_set_si(x, COEFF_MAX);
    check(x, 1);

    fmpz_set_ui(x, UWORD_MAX);
    check(x, 1);

    fmpz_set_ui(x, UWORD_MAX);
    fmpz_neg(x, x);
    check(x, 1);

    fmpz_set_ui(x, UWORD_MAX);
    fmpz_add_ui(x, x, UWORD(1));
    check(x, 0);

    fmpz_neg(x, x);
    check(x, 0);

    for (i = 0; i < 100 * flint_test_multiplier(); i++)
    {
        fmpz_set_ui(x, UWORD(1));
        fmpz_mul_2exp(x, x, i);
        check(x, i < FLINT_BITS);
        fmpz_neg(x, x);
        check(x, i < FLINT_BITS);
    }

    fmpz_clear(x);

    FLINT_TEST_CLEANUP(state);
    flint_printf("PASS\n");
    return 0;
}
