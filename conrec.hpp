#ifndef CONREC

#define CONREC

int conrec(double **d,
	   int ilb,
	   int iub,
	   int jlb,
	   int jub,
	   double *x,
	   double *y,
	   int nc,
	   double *z);
// d               ! matrix of data to contour
// ilb,iub,jlb,jub ! index bounds of data matrix
// x               ! data matrix column coordinates
// y               ! data matrix row coordinates
// nc              ! number of contour levels
// z               ! contour levels in increasing order

#define xsect(p1,p2) (h[p2]*xh[p1]-h[p1]*xh[p2])/(h[p2]-h[p1])
#define ysect(p1,p2) (h[p2]*yh[p1]-h[p1]*yh[p2])/(h[p2]-h[p1])
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)

#endif
