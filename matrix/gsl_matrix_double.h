/* matrix/gsl_matrix_double.h
 * 
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 Gerard Jungman, Brian Gough
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __GSL_MATRIX_DOUBLE_H__
#define __GSL_MATRIX_DOUBLE_H__

#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector_double.h>

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS

typedef struct gsl_matrix_struct gsl_matrix;

struct gsl_matrix_struct
{
  size_t size1;
  size_t size2;
  size_t tda;
  double * data;
  gsl_block * block;
} ;

gsl_matrix * 
gsl_matrix_alloc (const size_t n1, const size_t n2);

gsl_matrix * 
gsl_matrix_calloc (const size_t n1, const size_t n2);

gsl_matrix * 
gsl_matrix_alloc_from_block (gsl_block * b, 
                                   const size_t offset, 
                                   const size_t n1, 
                                   const size_t n2, 
                                   const size_t d2);

gsl_matrix * 
gsl_matrix_alloc_from_matrix (gsl_matrix * m,
                                    const size_t k1, 
                                    const size_t k2,
                                    const size_t n1, 
                                    const size_t n2);

gsl_vector * 
gsl_vector_alloc_row_from_matrix (gsl_matrix * m,
                                        const size_t i);

gsl_vector * 
gsl_vector_alloc_col_from_matrix (gsl_matrix * m,
                                        const size_t j);

void gsl_matrix_free (gsl_matrix * m);

void gsl_matrix_set_zero (gsl_matrix * m);
void gsl_matrix_set_identity (gsl_matrix * m);
void gsl_matrix_set_all (gsl_matrix * m, double x);

double * gsl_matrix_ptr(const gsl_matrix * m, const size_t i, const size_t j);
double   gsl_matrix_get(const gsl_matrix * m, const size_t i, const size_t j);
void    gsl_matrix_set(gsl_matrix * m, const size_t i, const size_t j, double x);

int gsl_matrix_fread (FILE * stream, gsl_matrix * m) ;
int gsl_matrix_fwrite (FILE * stream, const gsl_matrix * m) ;
int gsl_matrix_fscanf (FILE * stream, gsl_matrix * m);
int gsl_matrix_fprintf (FILE * stream, const gsl_matrix * m, const char * format);
 
int gsl_matrix_memcpy(gsl_matrix * dest, const gsl_matrix * src);
int gsl_matrix_swap(gsl_matrix * m1, const gsl_matrix * m2);

int gsl_matrix_swap_rows(gsl_matrix * m, const size_t i, const size_t j);
int gsl_matrix_swap_columns(gsl_matrix * m, const size_t i, const size_t j);
int gsl_matrix_swap_rowcol(gsl_matrix * m, const size_t i, const size_t j);
int gsl_matrix_transpose (gsl_matrix * m);


gsl_matrix gsl_matrix_submatrix (gsl_matrix * m, size_t i, size_t j, size_t n1, size_t n2);
gsl_vector gsl_matrix_row (gsl_matrix * m, size_t i);
gsl_vector gsl_matrix_column (gsl_matrix * m, size_t j);
gsl_vector gsl_matrix_diagonal (gsl_matrix * m);

double gsl_matrix_max (const gsl_matrix * m);
double gsl_matrix_min (const gsl_matrix * m);
void gsl_matrix_minmax (const gsl_matrix * m, double * min_out, double * max_out);

void gsl_matrix_max_index (const gsl_matrix * m, size_t * imax, size_t *jmax);
void gsl_matrix_min_index (const gsl_matrix * m, size_t * imin, size_t *jmin);
void gsl_matrix_minmax_index (const gsl_matrix * m, size_t * imin, size_t * jmin, size_t * imax, size_t * jmax);

int gsl_matrix_isnull (const gsl_matrix * m);

int gsl_matrix_add (gsl_matrix * a, const gsl_matrix * b);
int gsl_matrix_sub (gsl_matrix * a, const gsl_matrix * b);
int gsl_matrix_mul_elements (gsl_matrix * a, const gsl_matrix * b);
int gsl_matrix_div_elements (gsl_matrix * a, const gsl_matrix * b);
int gsl_matrix_scale (gsl_matrix * a, const double x);
int gsl_matrix_add_constant (gsl_matrix * a, const double x);

/***********************************************************************/
/* The functions below are obsolete                                    */
/***********************************************************************/
int gsl_matrix_get_row(gsl_vector * v, const gsl_matrix * m, const size_t i);
int gsl_matrix_get_col(gsl_vector * v, const gsl_matrix * m, const size_t j);
int gsl_matrix_set_row(gsl_matrix * m, const size_t i, const gsl_vector * v);
int gsl_matrix_set_col(gsl_matrix * m, const size_t j, const gsl_vector * v);

int gsl_vector_view_row_from_matrix (gsl_vector * v, gsl_matrix * m, const size_t i);
int gsl_vector_view_col_from_matrix (gsl_vector * v, gsl_matrix * m, const size_t j);

int gsl_matrix_view_from_vector (gsl_matrix * m, gsl_vector * base, const size_t offset, const size_t n1, const size_t n2, const size_t d2);



extern int gsl_check_range ;

/* inline functions if you are using GCC */

#ifdef HAVE_INLINE
extern inline 
double
gsl_matrix_get(const gsl_matrix * m, const size_t i, const size_t j)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= m->size1)
    {
      GSL_ERROR_RETURN("first index out of range", GSL_EINVAL, 0) ;
    }
  else if (j >= m->size2)
    {
      GSL_ERROR_RETURN("second index out of range", GSL_EINVAL, 0) ;
    }
#endif
  return m->data[i * m->tda + j] ;
} 

extern inline 
void
gsl_matrix_set(gsl_matrix * m, const size_t i, const size_t j, const double x)
{
#ifndef GSL_RANGE_CHECK_OFF
  if (i >= m->size1)
    {
      GSL_ERROR_RETURN_NOTHING("first index out of range", GSL_EINVAL) ;
    }
  else if (j >= m->size2)
    {
      GSL_ERROR_RETURN_NOTHING("second index out of range", GSL_EINVAL) ;
    }
#endif
  m->data[i * m->tda + j] = x ;
}
#endif

__END_DECLS

#endif /* __GSL_MATRIX_DOUBLE_H__ */
