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

    Copyright (C) 2010 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
    int n;

    FLINT_TEST_INIT(state);
    
    flint_printf("prime_pi....");
    fflush(stdout);

    for (n=1; n<10000 * FLINT_MIN(10, flint_test_multiplier()); n++)
    {
        if ((n_prime_pi(n-1)+1 == n_prime_pi(n)) != n_is_prime(n))
        {
            flint_printf("FAIL:\n");
            flint_printf("expected pi(%d) + 1 = pi(%d)\n", n-1, n); 
            abort();
        }
    }

    for (n=1; n<5000 * FLINT_MIN(10, flint_test_multiplier()); n++)
    {
        if (n_prime_pi(n_nth_prime(n)) != n)
        {
            flint_printf("FAIL:\n");
            flint_printf("expected pi(prime(%d)) = %d\n", n, n); 
            abort();
        }
    }

    FLINT_TEST_CLEANUP(state);
    flint_printf("PASS\n");
    return 0;
}
