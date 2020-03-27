/*
 * InterpolateMLS.h
 *
 *  Created on: 24/mar/2020
 *      Author: francescopc
 */

#ifndef INTERPOLATEMLS_H_
#define INTERPOLATEMLS_H_

#include "Types.h"
#include<iostream>
#include <cmath>
#include <cblas.h>
#include <cstring>
#include <lapacke.h>


class InterpolateMLS {
public:
	unsigned Np;
	unsigned Nc;
	unsigned q;
	double	Mass;
	double	L=1.0;
	double	dx;
	double h;
	tfloat2 *Sol=nullptr;
	InterpolateMLS(unsigned np, unsigned nc, unsigned qcell,double mass,double deltax,double H);
	void AllocateArray();
	void FreeArray();
	void Solve(pos *coord, dat *data, unsigned *BeginCell, unsigned *Partsincell);
	void SolveBox(pos *coord, dat *data, unsigned *BeginCell, unsigned *Partsincell,unsigned i,unsigned j);
	double getKernelWedland(double rr2,double h);
	virtual ~InterpolateMLS();
};

#endif /* INTERPOLATEMLS_H_ */
