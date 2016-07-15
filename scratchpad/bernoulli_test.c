# include <stdio.h>
# include <math.h>
# include <gsl/gsl_rng.h>
# include <gsl/gsl_randist.h>
# include <gsl/gsl_cdf.h>

int
main (void)
{
const gsl_rng_type * T;
gsl_rng * r;
int i, n = 500000; // number of random numbers generated
double a = 1e-3; // shape factor, a
double b = 1e-3; // shape factor, b
/* create a generator chosen by the
environment variable GSL_RNG_TYPE */
gsl_rng_env_setup();
T = gsl_rng_default;
r = gsl_rng_alloc (T);
gsl_rng_set(r, 10);

double sum = 0; //sum
double ssum = 0; //squre sum
double max_1 = 0.9; // max of high values
double min_1 = 1; // min of high values
double max_0 = 0; // max of low values
double min_0 = 0.1; // min of low values
double beta;
for (i = 0; i < n; i++)
{
    beta = gsl_ran_beta(r, a, b);
    sum += beta;
    ssum += pow(beta, 2);
    if (beta>0.9)
    {
        max_1 = (beta > max_1)? beta : max_1;
        min_1 = (beta < min_1)? beta : min_1;
    }
    else if (beta < 0.1)
    {
        max_0 = (beta > max_0)? beta : max_0;
        min_0 = (beta < min_0)? beta : min_0;
    }
}
printf("%d numbers generated\n", n);
printf("mean = %.18e, expection = 0.5\n", sum/n);
printf("var = %.18e, expection = 0.25\n", (ssum - n * pow(sum/n, 2))/(n-1));
printf("high-value cluster: [%.18e, %.18e]\n", min_1, max_1);
printf("low-value cluster: [%.18e, %.18e]\n", min_0, max_0);
printf ("\n");
gsl_rng_free (r);

int bins = 10;
double step = 1./bins;
for (i = 0; i<bins; i++)
{
    printf("cdf_p: %.18e\n", gsl_cdf_beta_P(i*step, a, b));
    printf("cdf_q: %.18e\n", gsl_cdf_beta_Q(i*step, a, b));
}
return 0;
}
