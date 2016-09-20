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
double U, V, X, Y;
double beta;

for (i = 0; i < n; i++)
{
    /*
    This is the classic Joehnk's method. It suffers from long execution time
    when 1/a or 1/b is close to 1, but it works well when a or b is small (see
    NAG library).
    */
    U = gsl_rng_uniform_pos(r);
    V = gsl_rng_uniform_pos(r);
    X = pow(U, 1.0/a);
    Y = pow(V, 1.0/b);
    
    if ((X + Y ) <= 1.0)
    {
        if (X + Y > 0)
        {
            // Joehnk's algorithm
            beta =  X/ (X + Y);
        }
        else
        {
            //if X and Y happen to be numerically zero. Use the logrithm for stability
            double logX = log(U)/a;
            double logY = log(V)/b;
            double logM = logX > logY ? logX: logY;
            logX -= logM;
            logY -= logM;
            
            beta =  exp(logX - log(exp(logX) + exp(logY)));
        }
    }
    printf (" %d\t%4.2f\t%.18e\n", i, beta, U+V);
}
printf ("\n");
gsl_rng_free (r);
return 0;
}
