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

    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "padic.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("get_set_mpz... ");
    fflush(stdout);

    

    /* Check that Zp(QQ(x)) == x. */
    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        slong N;
        padic_ctx_t ctx;

        padic_t a, b;
        mpz_t c;

        fmpz_init_set_ui(p, n_randtest_prime(state, 0));

        N = n_randint(state, PADIC_TEST_PREC_MAX - PADIC_TEST_PREC_MIN) 
            + PADIC_TEST_PREC_MIN;

        padic_ctx_init(ctx, p, FLINT_MAX(0, N-10), FLINT_MAX(0, N+10), PADIC_SERIES);

        padic_init2(a, N);
        padic_init2(b, N);
        mpz_init(c);

        padic_randtest_int(a, state, ctx);

        padic_get_mpz(c, a, ctx);
        padic_set_mpz(b, c, ctx);

        result = (padic_equal(a, b));
        if (!result)
        {
            flint_printf("FAIL:\n\n");
            flint_printf("a = "), padic_print(a, ctx), flint_printf("\n");
            flint_printf("b = "), padic_print(b, ctx), flint_printf("\n");
            gmp_printf("c = %Zd\n", c);
            abort();
        }

        padic_clear(a);
        padic_clear(b);
        mpz_clear(c);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

