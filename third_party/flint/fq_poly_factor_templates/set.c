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
    Copyright (C) 2012 Lina Kulakova
    Copyright (C) 2013 Mike Hansen

******************************************************************************/


#ifdef T

#include "templates.h"

void
TEMPLATE(T, poly_factor_set) (TEMPLATE(T, poly_factor_t) res,
                              const TEMPLATE(T, poly_factor_t) fac,
                              const TEMPLATE(T, ctx_t) ctx)
{
    if (res != fac)
    {
        if (fac->num == 0)
        {
            TEMPLATE(T, poly_factor_clear) (res, ctx);
            TEMPLATE(T, poly_factor_init) (res, ctx);
        }
        else
        {
            slong i;

            TEMPLATE(T, poly_factor_fit_length) (res, fac->num, ctx);
            for (i = 0; i < fac->num; i++)
            {
                TEMPLATE(T, poly_set) (res->poly + i, fac->poly + i, ctx);
                res->exp[i] = fac->exp[i];
            }
            for (; i < res->num; i++)
            {
                TEMPLATE(T, poly_zero) (res->poly + i, ctx);
                res->exp[i] = 0;
            }
            res->num = fac->num;
        }
    }
}


#endif
