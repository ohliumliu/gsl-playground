#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_test.h>
#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_cdf.h>

#define BINS 10
#define N 1000
  
gsl_rng *r_global;

static gsl_ran_discrete_t *g1 = NULL;
static gsl_ran_discrete_t *g2 = NULL;
static gsl_ran_discrete_t *g3 = NULL;

void testPDF_withCDF();

int
main (void)
{
  gsl_ieee_env_setup ();

  gsl_rng_env_setup ();
  r_global = gsl_rng_alloc (gsl_rng_default);

#define FUNC(x)  test_ ## x,                     "test gsl_ran_" #x
#define FUNC2(x) test_ ## x, test_ ## x ## _pdf, "test gsl_ran_" #x
#define FUNC3(x) "test gsl_ran_" #x
  testPDF_withCDF();


  gsl_rng_free (r_global);
  gsl_ran_discrete_free (g1);
  gsl_ran_discrete_free (g2);
  gsl_ran_discrete_free (g3);

  exit (gsl_test_summary ());
}

void
testPDF_withCDF ()
{
  char *name = "beta";
  double aa = 1e-1;
  double bb = 1e-1; //shape params
  double count[BINS], edge[BINS], p[BINS];
  double a = -5.0, b = +5.0;
  double dx = (b - a) / BINS;
  double bin;
  double total = 0, mean;
  int i, j, status = 0, status_i = 0, attempts = 0;
  long int n0 = 0, n = N;

  for (i = 0; i < BINS; i++)
    {
      /* Compute the integral of p(x) from x to x+dx */

      double x = a + i * dx;

      if (fabs (x) < 1e-10)     /* hit the origin exactly */
        x = 0.0;

      //p[i]  = integrate (pdf, x, x+dx);
      p[i] = gsl_cdf_beta_P((i+1)*dx, aa, bb) - gsl_cdf_beta_P(i*dx, aa, bb);  
      printf("%4.2f", p[i]);
      
    }


  for (i = 0; i < BINS; i++)
    {
      count[i] = 0;
      edge[i] = 0;
    }

 trial:
  attempts++;

  for (i = n0; i < n; i++)
    {
      double r = gsl_ran_beta(r_global, aa, bb);
      total += r;

      if (r < b && r > a)
        {
          double u = (r - a) / dx;
          double f = modf(u, &bin);
          j = (int)bin;

          if (f == 0)
            edge[j]++;
          else 
            count[j]++;
        }
    }

  /* Sort out where the hits on the edges should go */

  for (i = 0; i < BINS; i++)
    {
      /* If the bin above is empty, its lower edge hits belong in the
         lower bin */

      if (i + 1 < BINS && count[i+1] == 0) {
        count[i] += edge[i+1];
        edge[i+1] = 0;
      }

      count[i] += edge[i];
      edge[i] = 0;
    }

  mean = (total / n);

  status = !gsl_finite(mean);
  if (status) {
    gsl_test (status, "%s, finite mean, observed %g", name, mean);
    return;
  }

  for (i = 0; i < BINS; i++)
    {
      double x = a + i * dx;
      double d = fabs (count[i] - n * p[i]);
      if (!gsl_finite(p[i])) 
        {
          status_i = 1;
        }
      else if (p[i] != 0)
        {
          double s = d / sqrt (n * p[i]);
          status_i = (s > 5) && (d > 2);
        }
      else
        {
          status_i = (count[i] != 0);
        }
      
      /* Extend the sample if there is an outlier on the first attempt
         to avoid spurious failures when running large numbers of tests. */
      if (status_i && attempts < 50) 
        { 
          n0 = n; 
          n = 2.0*n;
          goto trial;
        }

      status |= status_i;
      if (status_i)
        gsl_test (status_i, "%s [%g,%g) (%g/%d=%g observed vs %g expected)",
                  name, x, x + dx, count[i], n, count[i] / n, p[i]);
    }

  if (status == 0)
    gsl_test (status, "%s, sampling against pdf over range [%g,%g) ",
              name, a, b);
}
