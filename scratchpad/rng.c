# include <stdio.h>
# include <math.h>
# include <gsl/gsl_rng.h>
# include <gsl/gsl_randist.h>

int
main (void)
{
const gsl_rng_type * T;
gsl_rng * r;
int i, n = 5;
double a = 1e-5;
double b = 1e-5;
/* create a generator chosen by the
environment variable GSL_RNG_TYPE */
gsl_rng_env_setup();
T = gsl_rng_default;
r = gsl_rng_alloc (T);
/* print n random variates chosen from
the poisson distribution with mean
parameter mu */
for (i = 0; i < n; i++)
{
double beta = gsl_ran_beta(r, a, b);
printf ("%4.2f\n", beta);
}
printf ("\n");
gsl_rng_free (r);
return 0;
}
