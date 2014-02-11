/* multifit/test_nonlinear.c
 * 
 * Copyright (C) 2007, 2013, 2014 Brian Gough, Patrick Alken
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

typedef struct
{
  const char *name;
  double *x0;       /* initial parameters (size p) */
  double *x_sol;    /* solution parameters (size p) */
  double *f_sumsq;  /* ||f(x_sol)||^2 */
  double *sigma;
  double *epsrel;   /* relative tolerance for solution checking */
  gsl_multifit_function_fdf *fdf;
} test_fdf_problem;

#include "test_bard.c"
#include "test_beale.c"
#include "test_biggs.c"
#include "test_box.c"
#include "test_brown1.c"
#include "test_brown2.c"
#include "test_brown3.c"
#include "test_enso.c"
#include "test_exp1.c"
#include "test_gaussian.c"
#include "test_hahn1.c"
#include "test_helical.c"
#include "test_jennrich.c"
#include "test_kirby2.c"
#include "test_kowalik.c"
#include "test_lin1.c"
#include "test_lin2.c"
#include "test_lin3.c"
#include "test_meyer.c"
#include "test_meyerscal.c"
#include "test_osborne.c"
#include "test_powell1.c"
#include "test_powell2.c"
#include "test_powell3.c"
#include "test_rosenbrock.c"
#include "test_rosenbrocke.c"
#include "test_roth.c"
#include "test_watson.c"
#include "test_wood.c"

static void test_fdf(const gsl_multifit_fdfsolver_type * T,
                     const double xtol, const double gtol,
                     const double ftol, const double x0_scale,
                     test_fdf_problem *problem);
static void test_scale_x0(gsl_vector *x0, const double scale);

/*
 * These test problems are taken from
 *
 * H. B. Nielsen, UCTP test problems for unconstrained optimization,
 * IMM Department of Mathematical Modeling, Tech. Report IMM-REP-2000-17,
 * 2000.
 */
static test_fdf_problem *test_fdf_nielsen[] = {
  &meyer_problem,      /* 10 */
  &lin1_problem,       /* 1 */
  &lin2_problem,       /* 2 */
  &lin3_problem,       /* 3 */
  &rosenbrock_problem, /* 4 */
  &helical_problem,    /* 5 */
  &powell1_problem,    /* 6 */
  &roth_problem,       /* 7 */
  &bard_problem,       /* 8 */
  &kowalik_problem,    /* 9 */
  &meyer_problem,      /* 10 */
  &watson_problem,     /* 11 */
  &box_problem,        /* 12 */
  &jennrich_problem,   /* 13 */
  &brown1_problem,     /* 14 */
  &brown2_problem,     /* 16 */
  &osborne_problem,    /* 17 */
  &exp1_problem,       /* 18 */
  &meyerscal_problem,  /* 20 */

  &powell2_problem,

  NULL
};

/*
 * These tests are from
 *
 * J. J. More, B. S. Garbow and K. E. Hillstrom, Testing
 * Unconstrained Optimization Software, ACM Trans. Math. Soft.
 * Vol 7, No 1, 1981.
 */
static test_fdf_problem *test_fdf_more[] = {
  &powell3_problem,      /* 3 */
  &brown3_problem,       /* 4 */
  &beale_problem,        /* 5 */
  &gaussian_problem,     /* 9 */
  &wood_problem,         /* 14 */
  &biggs_problem,        /* 18 */
  &rosenbrocke_problem,  /* 21 */

  NULL
};

/* NIST test cases */
static test_fdf_problem *test_fdf_nist[] = {
  &enso_problem,
  &kirby2_problem,
  &hahn1_problem,
  NULL
};

static void
test_nonlinear(void)
{
  const double xtol = 1e-15;
  const double gtol = 1e-15;
  const double ftol = 0.0;
  size_t i;

#if 1
  /* Nielsen tests */
  for (i = 0; test_fdf_nielsen[i] != NULL; ++i)
    {
      double x0_scale = 10.0;

#if 0
      test_fdf(gsl_multifit_fdfsolver_lmniel, xtol, gtol, ftol,
               x0_scale, test_fdf_nielsen[i]);
#endif
      test_fdf(gsl_multifit_fdfsolver_lmsder, xtol, gtol, ftol,
               x0_scale, test_fdf_nielsen[i]);
    }
  exit(1);
#endif

  /* More tests */
  for (i = 0; test_fdf_more[i] != NULL; ++i)
    {
      double x0_scale = 1.0;

      test_fdf(gsl_multifit_fdfsolver_lmniel, xtol, gtol, ftol,
               x0_scale, test_fdf_more[i]);
    }

#if 1
  /*
   * NIST tests - the tolerances for the lmsder/lmder routines must
   * be set low or they produce errors like "not making progress
   * toward solution"
   */
  for (i = 0; test_fdf_nist[i] != NULL; ++i)
    {
      test_fdf_problem *problem = test_fdf_nist[i];
      double scale = 1.0;

      test_fdf(gsl_multifit_fdfsolver_lmniel, xtol, gtol, ftol,
               scale, problem);
      test_fdf(gsl_multifit_fdfsolver_lmsder, 1e-5, 1e-5, 0.0, scale,
               problem);
      test_fdf(gsl_multifit_fdfsolver_lmder, 1e-5, 1e-5, 0.0, scale,
               problem);

      problem->fdf->df = NULL;
      problem->fdf->fdf = NULL;
      test_fdf(gsl_multifit_fdfsolver_lmsder, 1e-5, 1e-5, 0.0, scale,
               problem);
      test_fdf(gsl_multifit_fdfsolver_lmder, 1e-5, 1e-5, 0.0, scale,
               problem);
    }
#endif
}

/*
test_fdf()
  Test a nonlinear least squares problem

Inputs: T        - solver to use
        xtol     - tolerance in x
        gtol     - tolerance in gradient
        ftol     - tolerance in residual vector
        x0_scale - to test robustness against starting points,
                   the standard starting point in 'problem' is
                   multiplied by this scale factor:
                   x0 <- x0 * x0_scale
                   If x0 = 0, then all components of x0 are set to
                   x0_scale
        problem  - contains the nonlinear problem and solution point
*/

static void
test_fdf(const gsl_multifit_fdfsolver_type * T, const double xtol,
         const double gtol, const double ftol,
         const double x0_scale, test_fdf_problem *problem)
{
  gsl_multifit_function_fdf *fdf = problem->fdf;
  const size_t n = fdf->n;
  const size_t p = fdf->p;
  const double *sigma = problem->sigma;
  const double epsrel = *(problem->epsrel);
  const size_t max_iter = 1000;
  gsl_vector *x0 = gsl_vector_alloc(p);
  gsl_vector_view x0v = gsl_vector_view_array(problem->x0, p);
  gsl_multifit_fdfsolver *s = gsl_multifit_fdfsolver_alloc (T, n, p);
  const char *pname = problem->name;
  const char *sname = gsl_multifit_fdfsolver_name(s);
  int status, info;
  size_t i;

  /* scale starting point x0 */
  gsl_vector_memcpy(x0, &x0v.vector);
  test_scale_x0(x0, x0_scale);

  gsl_multifit_fdfsolver_set(s, fdf, x0);

  printf("working on %s/%s\n", sname, pname);

  status = gsl_multifit_fdfsolver_solve(s, max_iter, xtol, gtol, ftol, &info);
  gsl_test(status, "%s/%s did not converge, status=%s",
           sname, pname, gsl_strerror(status));

  printf("iter = %zu, info = %d\n", s->niter, info);

  /* check computed x = x_sol */
  if (problem->x_sol)
    {
      for (i = 0; i < p; ++i)
        {
          double xi = gsl_vector_get(s->x, i);
          double xi_exact = problem->x_sol[i];

          gsl_test_rel(xi, xi_exact, epsrel,
                       "%s/%s solution i=%zu",
                       sname, pname, i);
        }
    }

  {
    double s2;
    double s2_exact = *(problem->f_sumsq);

    /* check computed/exact ||f||^2 */
    gsl_blas_ddot(s->f, s->f, &s2);
    gsl_test_rel(s2, s2_exact, epsrel,
                 "%s/%s sumsq", sname, pname);

    /* check variances */
    if (sigma)
      {
        gsl_matrix * covar = gsl_matrix_alloc (p, p);
        gsl_multifit_covar (s->J, 0.0, covar);

        for (i = 0; i < p; i++) 
          {
            double ei = sqrt(s2/(n-p))*sqrt(gsl_matrix_get(covar,i,i));
            gsl_test_rel (ei, sigma[i], epsrel, 
                          "%s/%s, sigma(%d)", sname, pname, i) ;
          }

        gsl_matrix_free (covar);
      }
  }

  gsl_multifit_fdfsolver_free(s);
  gsl_vector_free(x0);
}

static void
test_scale_x0(gsl_vector *x0, const double scale)
{
  double nx = gsl_blas_dnrm2(x0);

  if (nx == 0.0)
    gsl_vector_set_all(x0, scale);
  else
    gsl_vector_scale(x0, scale);
} /* test_scale_x0() */
