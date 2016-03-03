#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Structures.h"


static double extents[][2] = { { 49.262161, -123.250812 }, { 49.263114,
		-123.248334 }, { 49.261765, -123.247403 }, { 49.260998, -123.249801 } };

static int TRI[][3] = { { 2, 3, 4 }, { 2, 4, 1 } };

static double screen[][2] = { { 0, 0 }, { 800, 0 }, { 800, 480 }, { 0, 480 } };

#if !defined(Point2D)
typedef struct {
	double x, y;
} Point2D;

#endif

typedef struct {
	double x, y, z;
} Vector3;

typedef struct {
	Point2D bary;
	double x, y;
} Vertex;

typedef struct {
	// Vertex *v1,*v2,*v3;
	Vertex v1, v2, v3;
	double bary_normalize, dot00, dot01, dot11;
	Point2D e0, e1, centroid;
} Triangle;

typedef struct {
	int numv, numt;
	Vertex* vertices;
	Triangle* T;
	Point2D *centroids;
} Delaunay;

Vector3 vec3(double x, double y, double z) {
	Vector3 v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}

double dotv(Vertex v1, Vertex v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

double dotp(Point2D p1, Point2D p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

double crossp(Point2D p1, Point2D p2) {
	return p1.x * p2.y - p2.x * p1.y;
}

double crossv(Vertex v1, Vertex v2) {
	return v1.x * v2.y - v2.x * v1.y;
}

Vertex vsubv(Vertex v1, Vertex v2) {
	Vertex v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return v;
}

Point2D vsubp(Vertex v1, Vertex v2) {
	Point2D p;
	p.x = v1.x - v2.x;
	p.y = v1.y - v2.y;
	return p;
}

Point2D psubp(Point2D p1, Point2D p2) {
	Point2D p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

double normsqv(Vertex v) {
	return dotv(v, v);
}

double normsqp(Point2D p) {
	return dotp(p, p);
}

double normp(Point2D p) {
	return sqrt(dotp(p, p));
}

Point2D point(double x, double y) {
	Point2D p;
	p.x = x;
	p.y = y;
	return p;
}

Vertex vtx(double x, double y, Point2D b) {
	Vertex v;
	v.x = x;
	v.y = y;
	v.bary = b;
	return v;
}

Point2D v2p(Vertex v) {
	return point(v.x, v.y);
}

Vertex Vert(double x, double y, double bx, double by) {
	Vertex v;
	v.x = x;
	v.y = y;
	v.bary.x = bx;
	v.bary.y = by;

	return v;
}

Point2D computeCentroid(Triangle T) {
	double xavg = (T.v1.x + T.v2.x + T.v3.x) / 3;
	double yavg = (T.v1.y + T.v2.y + T.v3.y) / 3;
	// double zavg = (T.v1->z + T.v2->z + T.v3->z)/3;

	return point(xavg, yavg);
}

// Triangle makeTri(Vertex* v1, Vertex* v2, Vertex* v3){
// 	Triangle T;
// 	T.v1 = *v1;
// 	T.v2 = *v2;
// 	T.v3 = *v3;
//
// 	T.e0 = vsubp(*v2,*v1);
// 	T.e1 = vsubp(*v3,*v1);
//
// 	T.dot00 = dotp(T.e0,T.e0);
// 	T.dot01 = dotp(T.e0,T.e1);
// 	T.dot11 = dotp(T.e1,T.e1);
//
// 	T.bary_normalize = 1/(T.dot00*T.dot01 - T.dot01*T.dot01);
//
// 	T.centroid = computeCentroid(T);
// 	return T;
// }

Triangle makeTri(Vertex v1, Vertex v2, Vertex v3) {
	Triangle T;
	T.v1 = v1;
	T.v2 = v2;
	T.v3 = v3;

	T.e0 = vsubp(v2, v1);
	T.e1 = vsubp(v3, v1);

	T.dot00 = dotp(T.e0, T.e0);
	T.dot01 = dotp(T.e0, T.e1);
	T.dot11 = dotp(T.e1, T.e1);

	T.bary_normalize = 1 / (T.dot00 * T.dot01 - T.dot01 * T.dot01);

	T.centroid = computeCentroid(T);
	return T;
}

Vector3 barycentric(Triangle T, Point2D q) {
	// Point e2 = psubp(q, v2p(*(T.v1)));
	Point2D e2 = psubp(q, v2p(T.v1));

	double dot20 = dotp(e2, T.e0);
	double dot21 = dotp(e2, T.e1);

	double v = (T.dot11 * dot20 - T.dot01 * dot21) * T.bary_normalize;
	double w = (T.dot00 * dot21 - T.dot01 * dot20) * T.bary_normalize;
	double u = 1.f - v - w;

	return vec3(u, v, w);
}

Vector3 barycentric2(Triangle T, Point2D q) {
	double area = .5 * (crossp(vsubp(T.v2, T.v1), vsubp(T.v3, T.v1)));
	double area23q = .5 * (crossp(psubp(v2p(T.v2), q), psubp(v2p(T.v3), q)));
	double area13q = .5 * (crossp(psubp(v2p(T.v3), q), psubp(v2p(T.v1), q)));

	double bx = area13q / area;
	double bz = area23q / area;
	// printf("%f\n", );
	double by = 1.0 - bx - bz;

	return vec3(bx, by, bz);
}

int centroidLessThan(Triangle t1, Triangle t2, Point2D p) {
	double dist1 = normsqp(psubp(t1.centroid, p));
	double dist2 = normsqp(psubp(t2.centroid, p));

	return (dist1 < dist2) ? 1 : 0;
}

int centroidGreaterThan(Triangle t1, Triangle t2, Point2D p) {
	double dist1 = normsqp(psubp(t1.centroid, p));
	double dist2 = normsqp(psubp(t2.centroid, p));

	return (dist1 > dist2) ? 1 : 0;
}

int centroidEqualTo(Triangle t1, Triangle t2, Point2D p, double eps) {
	double dist1 = normsqp(psubp(t1.centroid, p));
	double dist2 = normsqp(psubp(t2.centroid, p));

	return (fabs(dist1 - dist2) < eps) ? 1 : 0;
}

int findMin(double *numbers, int size) {
	int i, min = numbers[0];
	for (i = 1; i < size; i++)
		(numbers[i] < numbers[min]) ? min = i : 1;
	return min;
}

double showMin(double *numbers, int size) {
	int i, min = 1e6;
	for (i = 0; i < size; i++)
		(numbers[i] < min) ? min = numbers[i] : 1;
	return min;
}

Triangle nearestneighbour(Delaunay d, Point2D q) {
	int i;
	// printf("test: %.10f %.10f\n", q.x,q.y);
	double neighbours[d.numt];
	for (i = 0; i < d.numt; i++) {
		// printf("centroid: %.10f %.10f\n", d.T[i].centroid.x,d.T[i].centroid.y);
		neighbours[i] = normp(psubp(d.T[i].centroid, q));
		// printf("neighbours[i]: %.10f\n", neighbours[i]);
	}

	// printf("%d\n", findMin(neighbours,d.numt));
	return d.T[findMin(neighbours, d.numt)];
}

Delaunay DelaunayTriangulation(double vs[][2], double bary[][2], int tris[][3],
		int vsize, int bsize, int tsize) {
	assert(vsize == bsize);
	Delaunay d;
	Triangle tri;
	int i;
	d.numv = vsize;
	d.numt = tsize;
	d.vertices = malloc(sizeof(Vertex) * vsize);
	d.centroids = malloc(sizeof(int) * tsize);
	d.T = malloc(sizeof(Triangle) * tsize);

	int one, two, three;
	for (i = 0; i < vsize; i++) {
		d.vertices[i] = vtx(vs[i][0], vs[i][1], point(bary[i][0], bary[i][1]));
		// printf("%f %f\n", vs[i][0],vs[i][1]);
	}
	for (i = 0; i < tsize; i++) {

		one = tris[i][0] - 1;
		two = tris[i][1] - 1;
		three = tris[i][2] - 1;

		Vertex v1 = vtx(vs[one][0], vs[one][1],
				point(bary[one][0], bary[one][1]));
		Vertex v2 = vtx(vs[two][0], vs[two][1],
				point(bary[two][0], bary[two][1]));
		Vertex v3 = vtx(vs[three][0], vs[three][1],
				point(bary[three][0], bary[three][1]));
		tri = makeTri(v1, v2, v3);
		d.T[i] = tri;
		d.centroids[i] = (tri.centroid);
	}

	return d;
}

Delaunay CopyDelaunayTriangulation(Vertex* vs, Triangle* ts, int vsize,
		int tsize) {
	Delaunay d;
	int i;
	d.vertices = malloc(sizeof(Vertex) * vsize);
	d.T = malloc(sizeof(Triangle) * tsize);
	for (i = 0; i < vsize; i++)
		d.vertices[i] = vs[i];
	for (i = 0; i < tsize; i++)
		d.T[i] = ts[i];

	return d;
}

double dot3(Vector3 v1, Vector3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Point2D toScreen(Triangle tt, Vector3 b) {
	return point(dot3(b, vec3(tt.v2.bary.x, tt.v3.bary.x, tt.v1.bary.x)),
			dot3(b, vec3(tt.v2.bary.y, tt.v3.bary.y, tt.v1.bary.y)));
}

void computePixel(double lat, double lon, int * latPix, int * lonPix){
	Delaunay del_all = DelaunayTriangulation(extents,screen,TRI,4,4,2);
	Point2D q = point(lat,lon);
	Triangle tt = nearestneighbour(del_all,q);
	Vector3 vvv = barycentric2(tt,q);
	Point2D pixel = toScreen(tt,vvv);
	printf("%f %f\n", pixel.x, pixel.y);

	*latPix = (int) pixel.x;
	*lonPix = (int) pixel.y;

	printf("Lat: %d, Long %d \n", *latPix, *lonPix);
}

