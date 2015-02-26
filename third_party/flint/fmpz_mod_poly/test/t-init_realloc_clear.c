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
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int i;
    FLINT_TEST_INIT(state);

    flint_printf("init/init2/realloc/clear....");
    fflush(stdout);

    

    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        fmpz_mod_poly_t a;

        fmpz_init(p);
        fmpz_randtest_unsigned(p, state, 2 * FLINT_BITS);
        fmpz_add_ui(p, p, 2);

        fmpz_mod_poly_init2(a, p, n_randint(state, 100));
        fmpz_mod_poly_clear(a);

        fmpz_clear(p);
    }

    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        fmpz_mod_poly_t a;

        fmpz_init(p);
        fmpz_randtest_unsigned(p, state, 2 * FLINT_BITS);
        fmpz_add_ui(p, p, 2);

        fmpz_mod_poly_init2(a, p, n_randint(state, 100));
        fmpz_mod_poly_realloc(a, n_randint(state, 100));
        fmpz_mod_poly_clear(a);

        fmpz_clear(p);
    }

    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        fmpz_mod_poly_t a;

        fmpz_init(p);
        fmpz_randtest_unsigned(p, state, 2 * FLINT_BITS);
        fmpz_add_ui(p, p, 2);

        fmpz_mod_poly_init(a, p);
        fmpz_mod_poly_randtest(a, state, n_randint(state, 100));
        fmpz_mod_poly_clear(a);

        fmpz_clear(p);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
