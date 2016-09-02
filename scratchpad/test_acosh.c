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
gsl_complex gsl_complex_arccosh_1 (gsl_complex a);
gsl_complex gsl_complex_arccosh_2 (gsl_complex a);
gsl_complex gsl_complex_arccos_1 (gsl_complex a);


gsl_complex
gsl_complex_arccosh_2 (gsl_complex a) // this function calls gsl_complex_arccosh_real when appropriate
{                               /* z = arccosh(a) */
  double R = GSL_REAL (a), I = GSL_IMAG (a);
  gsl_complex z;
  if (I == 0){
    z = gsl_complex_arccosh_real(R);
  }
  else{
    z = gsl_complex_arccos (a);
    z = gsl_complex_mul_imag (z, GSL_IMAG(z) > 0 ? -1.0 : 1.0);
  }
  return z;
}


gsl_complex
gsl_complex_arccosh_1 (gsl_complex a) // this function calls a modified gsl_complex_arccos_1
{                               /* z = arccosh(a) */
  gsl_complex z = gsl_complex_arccos_1 (a);
  z = gsl_complex_mul_imag (z, GSL_IMAG(z) > 0 ? -1.0 : 1.0);
  return z;
}

gsl_complex
gsl_complex_arccos_1 (gsl_complex a) // this function ignores the brach that deals with real input
{                               /* z = arccos(a) */
  double R = GSL_REAL (a), I = GSL_IMAG (a);
  gsl_complex z;

  if (1 == 0)//ignore this branch
    {
      z = gsl_complex_arccos_real (R);
    }
  else
    {
      double x = fabs (R), y = fabs (I);
      double r = hypot (x + 1, y), s = hypot (x - 1, y);
      double A = 0.5 * (r + s);
      double B = x / A;
      double y2 = y * y;

      double real, imag;

      const double A_crossover = 1.5, B_crossover = 0.6417;

      if (B <= B_crossover)
        {
          real = acos (B);
        }
      else
        {
          if (x <= 1)
            {
              double D = 0.5 * (A + x) * (y2 / (r + x + 1) + (s + (1 - x)));
              real = atan (sqrt (D) / x);
            }
          else
            {
              double Apx = A + x;
              double D = 0.5 * (Apx / (r + x + 1) + Apx / (s + (x - 1)));
              real = atan ((y * sqrt (D)) / x);
            }
        }

      if (A <= A_crossover)
        {
          double Am1;

          if (x < 1)
            {
              Am1 = 0.5 * (y2 / (r + (x + 1)) + y2 / (s + (1 - x)));
            }
          else
            {
              Am1 = 0.5 * (y2 / (r + (x + 1)) + (s + (x - 1)));
            }

          imag = log1p (Am1 + sqrt (Am1 * (A + 1)));
        }
      else
        {
          imag = log (A + sqrt (A * A - 1));
        }

      GSL_SET_COMPLEX (&z, (R >= 0) ? real : M_PI - real, (I >= 0) ? -imag : imag);
    }

  return z;
}

int
main (void)
{
  double x;
  gsl_complex x_complex;
  gsl_complex z, z_expected;

  gsl_ieee_env_setup ();

 
  
  /* test gsl_complex_arccosh and gsl_complex_arccosh_real */
  printf("1. issues of concern.\n"); 
  printf("gsl_complex_arccosh(1.0+0i) returns -0. It still passes gsl_test.\n");
  x_complex = gsl_complex_rect(1.0, 0.0);
  z = gsl_complex_arccosh(x_complex);
  z_expected = gsl_complex_rect(0.0, 0.0);
  gsl_test_abs (GSL_REAL(z), GSL_REAL(z_expected), 0.0, "real part: gsl_complex_arccosh(1)");
  gsl_test_abs (GSL_IMAG(z), GSL_IMAG(z_expected), 0.0, "imaginary part: gsl_complex_arccosh(1)");
  printf("\n");
  
  printf("gsl_complex_arccosh_real(1.0) returns +0. It passes gsl_test.\n");
  x = 1.0;
  z = gsl_complex_arccosh_real(x);
  z_expected = gsl_complex_rect(0.0, 0.0);
  gsl_test_abs (GSL_REAL(z), GSL_REAL(z_expected), 0.0, "real part: gsl_complex_arccosh_real(1)");
  gsl_test_abs (GSL_IMAG(z), GSL_IMAG(z_expected), 0.0, "imaginary part: gsl_complex_arccosh_real(1)");
  printf("============================================\n");
  
  printf("2. The real part of gsl_complex_arccosh(1.0+0.0i) is zero, and its gsl_sign is 1, as expected by the definition of gsl_sign.\n"); 
  printf("gsl_sign(0) = 1 irrespective of IEEE sign bit.\n");
  printf("gsl_complex_arccosh(1.0+0.0i)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccosh(x_complex)),
                           GSL_IMAG(gsl_complex_arccosh(x_complex)));
  printf("sign of real part: %d\n", GSL_SIGN(GSL_REAL(gsl_complex_arccosh(x_complex))));
                           
  printf("In contrast, gsl_complex_arccosh_real(1.0) has +0.0 as its real part.\n");
  printf("gsl_complex_arccosh_real(1.0)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccosh_real(x)),
                           GSL_IMAG(gsl_complex_arccosh_real(x)));
  printf("============================================\n");
  
  printf("3. gsl_complex_arccosh(x) calls gsl_complex_arccos(x), which calls gsl_complex_arccos_real if the input is real.\n");
  printf("In gsl_complex_arccosh_1, it calls gsl_complex_arccos_1, which doesn't call gsl_complex_arccos_real even for real input.\n");
  printf("The result's real part is +0, as desired. However, I have no idea if this breaks other tests.\n");
  printf("gsl_complex_arccosh_1(1.0+0i)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccosh_1(x_complex)),
                           GSL_IMAG(gsl_complex_arccosh_1(x_complex)));
  printf("\n");
  
  printf("The difference lies in the difference between gsl_complex_arccos and gsl_complex_arccos_1.\n");
  printf("Although using gsl_complex_arccos_1 seems to solve the consistency issue for gsl_complex_arccosh,\n");
  printf("gsl_complex_arccos_1 itself is inconsistent with gsl_complex_arccos_real when the input is real.\n");
  printf("gsl_complex_arccos(1.0+0i)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccos(x_complex)),
                           GSL_IMAG(gsl_complex_arccos(x_complex)));
  
  printf("gsl_complex_arccos_1(1.0+0i)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccos_1(x_complex)),
                           GSL_IMAG(gsl_complex_arccos_1(x_complex)));
                           
  printf("gsl_complex_arccos_real(1.0)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccos_real(x)),
                           GSL_IMAG(gsl_complex_arccos_real(x)));
  printf("============================================\n");
  
  printf("3. A naive band-aid. Since gsl_complex_arccos can have a special brach calling gsl_complex_arccos_real,\n");
  printf("maybe we can do the same for gsl_complex_arccosh. This idea is implemented in gsl_complex_arccosh_2.\n");
  printf("gsl_complex_arccosh_2(1.0+0i)=\n");
  printf("%4.32f\t+\t%4.32fi\n", GSL_REAL(gsl_complex_arccosh_2(x_complex)),
                           GSL_IMAG(gsl_complex_arccosh_2(x_complex)));
                           
  exit (gsl_test_summary ());
}
