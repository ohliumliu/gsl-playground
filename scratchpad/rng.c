# include <stdio.h>
# include <math.h>
# include <gsl/gsl_rng.h>
# include <gsl/gsl_randist.h>

int
main (void)
{
const gsl_rng_type * T;
gsl_rng * r;
int i, n = 50000000;
double a = 1e-6;
double b = 1e-6;
/* create a generator chosen by the
environment variable GSL_RNG_TYPE */
gsl_rng_env_setup();
T = gsl_rng_default;
r = gsl_rng_alloc (T);
gsl_rng_set(r, 10);
/* print n random variates chosen from
the poisson distribution with mean
parameter mu */
int bin_1 = 0;
int bin_0 = 0;
for (i = 0; i < n; i++)
{
	double beta = gsl_ran_beta(r, a, b);
	if (beta > 0.9)
		bin_1 += 1;
	else
		bin_0 += 1;

}
printf("%d\t%d\t\n", bin_1, bin_0);
printf ("\n");
gsl_rng_free (r);
return 0;
}
