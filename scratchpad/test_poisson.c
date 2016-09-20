#include <gsl/gsl_randist.h> 
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_errno.h>
#include <stdio.h> 
#include <math.h>
double gsl_ran_poisson_pdf_2(const unsigned int k, const double mu);



double
gsl_ran_poisson_pdf_2 (const unsigned int k, const double mu)
{
  double p;
  double lf = gsl_sf_lnfact (k); 
    
  if (mu < 0)
    GSL_ERROR("Poisson distribution not defined for input", GSL_EDOM);
  else if (mu > 0)
    p = exp (log (mu) * k - lf - mu);
  else
    p = (k==0)?1:0;
    
  return p;
}


int main(){ 
    const gsl_rng_type * T;
    gsl_rng * r;
    
    int x, i;
    double mu = 0;
    double res;
    
    /* create a generator chosen by the
    environment variable GSL_RNG_TYPE */
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    
    x = 0;
    res = gsl_ran_poisson_pdf(x, mu);
    printf("poisson pdf(%d;%.5f)=%.5f\n", x, mu, res); 
    x = 2;
    res = gsl_ran_poisson_pdf(x, mu);
    printf("poisson pdf(%d;%.5f)=%.5f\n", x, mu, res); 
    x = 0;
    res = gsl_ran_poisson_pdf(x, -1);
    printf("poisson pdf(%d;%.5f)=%.5f\n", x, -1., res); 
    
    x = 0;
    res = gsl_ran_poisson_pdf_2(x, mu);
    printf("poisson pdf 2(%d;%.5f)=%.5f\n", x, mu, res); 
    x = 2;
    res = gsl_ran_poisson_pdf_2(x, mu);
    printf("poisson pdf 2(%d;%.5f)=%.5f\n", x, mu, res); 
    x = 0;
    res = gsl_ran_poisson_pdf_2(x, -1);
    printf("poisson pdf 2(%d;%.5f)=%.5f\n", x, -1., res); 
    
    double p, ln_p;
    int k = 0;
    double lf = gsl_sf_lnfact (k); 

    //p = exp (log (mu) * k - lf - mu);
    ln_p = log (mu) * k;// - lf - mu;
    printf("%.5f\n", ln_p);
    
    printf("Poisson random numbers with mu = %.2f\n", mu);
    for (i = 0; i < 5; i++){
        printf("%d\n", gsl_ran_poisson(r, mu));
    }
    
    gsl_rng_free (r);
    
    return 0; 
} 
