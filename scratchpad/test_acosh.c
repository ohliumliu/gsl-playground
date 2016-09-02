/* sys/test.c
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000, 2007 Brian Gough
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "../config.h"
#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>


int
main (void)
{
  double y, y_expected;
  gsl_complex z, z_expected;
  //int e, e_expected;

  gsl_ieee_env_setup ();

 
  /* Test for acosh */

  y = gsl_acosh (1.0);
  y_expected = 0.0;
  gsl_test_rel (y, y_expected, 1e-15, "gsl_acosh(1.0)");

  y = gsl_acosh (1.1);
  y_expected = 4.435682543851151891329110663525e-1;
  gsl_test_rel (y, y_expected, 1e-15, "gsl_acosh(1.1)");

  y = gsl_acosh (10.0);
  y_expected = 2.9932228461263808979126677137742e0;
  gsl_test_rel (y, y_expected, 1e-15, "gsl_acosh(10.0)");

  y = gsl_acosh (1e10);
  y_expected = 2.3718998110500402149594646668302e1;
  gsl_test_rel (y, y_expected, 1e-15, "gsl_acosh(1e10)");

  /* test gsl_complex_arccosh and gsl_complex_arccosh_real */
    
  z = gsl_complex_rect(GSL_REAL(gsl_complex_arccosh_real (1.0)), 
                       GSL_IMAG(gsl_complex_arccosh_real (1.0)));
  z_expected = gsl_complex_rect(0, 0);
  gsl_test_rel (GSL_REAL(z), GSL_REAL(z_expected), 1e-15, "gsl_complex_arccosh_real(1)");
  gsl_test_rel (GSL_IMAG(z), GSL_IMAG(z_expected), 1e-15, "gsl_complex_arccosh_real(1)");
  
  
  z = gsl_complex_rect(GSL_REAL(gsl_complex_arccosh (gsl_complex_rect(1.0, 0))), 
                       GSL_IMAG(gsl_complex_arccosh (gsl_complex_rect(1.0, 0))));
  z_expected = gsl_complex_rect(0, 0);
  gsl_test_rel (GSL_REAL(z), GSL_REAL(z_expected), 1e-15, "gsl_complex_arccosh(1)");
  gsl_test_rel (GSL_IMAG(z), GSL_IMAG(z_expected), 1e-15, "gsl_complex_arccosh(1)");
  
  printf("gsl_complex_arccosh(1.0+0i)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccosh(gsl_complex_rect(1.0, 0))),
                           GSL_IMAG(gsl_complex_arccosh(gsl_complex_rect(1.0, 0))));
                           
  printf("gsl_complex_arccosh_real(1.0)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccosh_real(1.0)),
                           GSL_IMAG(gsl_complex_arccosh_real(1.0)));
  

  exit (gsl_test_summary ());
}
