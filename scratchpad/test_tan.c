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
#include <gsl/gsl_sf.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>

gsl_complex gsl_complex_tanh_smallR (gsl_complex a);

gsl_complex
gsl_complex_tanh_smallR (gsl_complex a)
{                               /* z = tanh(a) */
  double R = GSL_REAL (a), I = GSL_IMAG (a);

  gsl_complex z;

  if (2.0 < 1.0) // this branch is always used 
    {
      double D = pow (cos (I), 2.0) + pow (sinh (R), 2.0);
      
      GSL_SET_COMPLEX (&z, sinh (R) * cosh (R) / D, 0.5 * sin (2 * I) / D);
    }
  else // this branch is not used in this function
    {
      double D = pow (cos (I), 2.0) + pow (sinh (R), 2.0);
      double F = 1 + pow (cos (I) / sinh (R), 2.0);

      GSL_SET_COMPLEX (&z, 1.0 / (tanh (R) * F), 0.5 * sin (2 * I) / D);
    }

  return z;
}


int
main (void)
{
  gsl_complex x_complex;
  gsl_complex z;

  gsl_ieee_env_setup ();
  
  x_complex = gsl_complex_rect(0, -1000);
  z = gsl_complex_tan(x_complex);
  printf("gsl_complex_tan(%4.2f + %4.2fi) = \n", GSL_REAL(x_complex), GSL_IMAG(x_complex));
  printf("%4.32f + %4.32fi\n", GSL_REAL(z), GSL_IMAG(z));

 
  x_complex = gsl_complex_rect(0, 1000);
  z = gsl_complex_tan(x_complex);
  printf("gsl_complex_tan(%4.2f + %4.2fi) = \n", GSL_REAL(x_complex), GSL_IMAG(x_complex));
  printf("%4.32f + %4.32fi\n", GSL_REAL(z), GSL_IMAG(z));
  
  printf("Use gsl_complex_tanh:\n");
  x_complex = gsl_complex_rect(1000, 0);
  z = gsl_complex_tanh(x_complex);
  printf("gsl_complex_tanh(%4.2f + %4.2fi) = \n", GSL_REAL(x_complex), GSL_IMAG(x_complex));
  printf("%4.32f + %4.32fi\n", GSL_REAL(z), GSL_IMAG(z));
                          
  x_complex = gsl_complex_rect(-1000, 0);
  z = gsl_complex_tanh(x_complex);
  printf("gsl_complex_tanh(%4.2f + %4.2fi) = \n", GSL_REAL(x_complex), GSL_IMAG(x_complex));
  printf("%4.32f + %4.32fi\n", GSL_REAL(z), GSL_IMAG(z));
  
  printf("Use gsl_complex_tanh_smallR:\n");
  x_complex = gsl_complex_rect(1000, 0);
  z = gsl_complex_tanh_smallR(x_complex);
  printf("gsl_complex_tanh_smallR(%4.2f + %4.2fi) = \n", GSL_REAL(x_complex), GSL_IMAG(x_complex));
  printf("%4.32f + %4.32fi\n", GSL_REAL(z), GSL_IMAG(z));
   
  x_complex = gsl_complex_rect(-1000, 0);
  z = gsl_complex_tanh_smallR(x_complex);
  printf("gsl_complex_tanh_smallR(%4.2f + %4.2fi) = \n", GSL_REAL(x_complex), GSL_IMAG(x_complex));
  printf("%4.32f + %4.32fi\n", GSL_REAL(z), GSL_IMAG(z));
  
  printf("sinh(1000)=%4.32f\tsinh(-1000)=%4.32f\n", sinh(1000), sinh(-1000));
  
  double u = exp (1000);
  double C = 2 * u / (1 - pow (u, 2.0));
  double D = pow (sinh (1000), 2.0);
  printf("u = %4.32f\tC = %4.32f\nD = %4.32f\n", u, C, D);
  
  exit (gsl_test_summary ());
}
