/* Author:  G. Jungman
 * RCS:     $Id$
 */
#ifndef GSL_SF_FERMI_DIRAC_H_
#define GSL_SF_FERMI_DIRAC_H_


/* Complete Fermi-Dirac Integrals:
 *
 *  F_j(x)   := 1/Gamma[j+1] Integral[ t^j /(Exp[t-x] + 1), {t,0,Infinity}]
 *
 *
 * Incomplete Fermi-Dirac Integrals:
 *
 *  F_j(x,b) := 1/Gamma[j+1] Integral[ t^j /(Exp[t-x] + 1), {t,b,Infinity}]
 */


/* Complete integral F_{-1}(x) = e^x / (1 + e^x)
 *
 * exceptions: GSL_EUNDRFLW
 */
int     gsl_sf_fermi_dirac_m1_impl(double x, double * result);
int     gsl_sf_fermi_dirac_m1_e(double x, double * result);
double  gsl_sf_fermi_dirac_m1(double x);


/* Complete integral F_0(x) = ln(1 + e^x)
 *
 * exceptions: GSL_EUNDRFLW
 */
int     gsl_sf_fermi_dirac_0_impl(double x, double * result);
int     gsl_sf_fermi_dirac_0_e(double x, double * result);
double  gsl_sf_fermi_dirac_0(double x);


/* Complete integral F_1(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int     gsl_sf_fermi_dirac_1_impl(double x, double * result);
int     gsl_sf_fermi_dirac_1_e(double x, double * result);
double  gsl_sf_fermi_dirac_1(double x);


/* Complete integral F_2(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int     gsl_sf_fermi_dirac_2_impl(double x, double * result);
int     gsl_sf_fermi_dirac_2_e(double x, double * result);
double  gsl_sf_fermi_dirac_2(double x);


/* Complete integral F_j(x)
 * for integer j
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int     gsl_sf_fermi_dirac_int_impl(int j, double x, double * result);
int     gsl_sf_fermi_dirac_int_e(int j, double x, double * result);
double  gsl_sf_fermi_dirac_int(int j, double x);


/* Complete integral F_{-1/2}(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int     gsl_sf_fermi_dirac_mhalf_impl(double x, double * result);
int     gsl_sf_fermi_dirac_mhalf_e(double x, double * result);
double  gsl_sf_fermi_dirac_mhalf(double x);


/* Complete integral F_{1/2}(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int     gsl_sf_fermi_dirac_half_impl(double x, double * result);
int     gsl_sf_fermi_dirac_half_e(double x, double * result);
double  gsl_sf_fermi_dirac_half(double x);


/* Complete integral F_{3/2}(x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EOVRFLW
 */
int     gsl_sf_fermi_dirac_3half_impl(double x, double * result);
int     gsl_sf_fermi_dirac_3half_e(double x, double * result);
double  gsl_sf_fermi_dirac_3half(double x);


/* Incomplete integral F_0(x,b) = ln(1 + e^(b-x)) - (b-x)
 *
 * exceptions: GSL_EUNDRFLW, GSL_EDOM
 */
int     gsl_sf_fermi_dirac_inc_0_impl(double x, double b, double * result);
int     gsl_sf_fermi_dirac_inc_0_e(double x, double b, double * result);
double  gsl_sf_fermi_dirac_inc_0(double x, double b);


#endif /* !GSL_SF_FERMI_DIRAC_H_ */
