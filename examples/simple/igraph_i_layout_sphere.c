/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2006  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#include <igraph.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int igraph_i_layout_sphere_2d(igraph_matrix_t *coords, real_t *x, real_t *y,
			      real_t *r);
int igraph_i_layout_sphere_3d(igraph_matrix_t *coords, real_t *x, real_t *y,
			      real_t *z, real_t *r);

int main () {
  long int i; 
  igraph_matrix_t m;
  real_t x, y, z, r;

  srand(time(0));

  /* 2D */
  igraph_matrix_init(&m, 1000, 2);
  for (i=0; i<igraph_matrix_nrow(&m); i++) {
    MATRIX(m,i,0)=rand()/(double)RAND_MAX;
    MATRIX(m,i,1)=rand()/(double)RAND_MAX;
  }
  igraph_i_layout_sphere_2d(&m, &x, &y, &r);
  
  for (i=0; i<igraph_matrix_nrow(&m); i++) {
    real_t dist=sqrt((MATRIX(m,i,0)-x)*(MATRIX(m,i,0)-x) + 
		     (MATRIX(m,i,1)-y)*(MATRIX(m,i,1)-y));
    if (dist > r) {
      printf("x: %f y: %f r: %f\n", x, y, r);
      printf("x: %f y: %f dist: %f (%li)\n", 
	     MATRIX(m,i,0), MATRIX(m,i,1), dist, i);
      return 1;
    }
  }
  igraph_matrix_destroy(&m);

  /* 3D */
  igraph_matrix_init(&m, 1000, 3);
  for (i=0; i<igraph_matrix_nrow(&m); i++) {
    MATRIX(m,i,0)=rand()/(double)RAND_MAX;
    MATRIX(m,i,1)=rand()/(double)RAND_MAX;
    MATRIX(m,i,2)=rand()/(double)RAND_MAX;
  }
  igraph_i_layout_sphere_3d(&m, &x, &y, &z, &r);
  
  for (i=0; i<igraph_matrix_nrow(&m); i++) {
    real_t dist=sqrt((MATRIX(m,i,0)-x)*(MATRIX(m,i,0)-x) + 
		     (MATRIX(m,i,1)-y)*(MATRIX(m,i,1)-y) +
		     (MATRIX(m,i,2)-z)*(MATRIX(m,i,2)-z));
    if (dist > r) {
      printf("x: %f y: %f z: %f r: %f\n", x, y, z, r);
      printf("x: %f y: %f z: %f dist: %f (%li)\n", 
	     MATRIX(m,i,0), MATRIX(m,i,1), MATRIX(m,i,2), dist, i);
      return 1;
    }
  }
  igraph_matrix_destroy(&m);

  

  return 0;
}
