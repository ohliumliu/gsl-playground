#include <gsl/gsl_math.h> 
#include <stdio.h> 

int main(){ 
    double x= 0.5; 
    double res = gsl_cdf_ugaussian_Pinv(x); 
    printf("icdf(%f)=%f\n",x,res); 
    return 0; 
} 