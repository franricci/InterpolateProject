/*
 * CellDiv.h
 *
 *  Created on: 22/mar/2020
 *      Author: francescopc
 */

#ifndef CELLDIV_H_
#define CELLDIV_H_

#include<cstring>
#include<cmath>
#include<iostream>
#include "Types.h"


class CellDiv {
public:
	unsigned 	Nc;
	unsigned 	Np;
	double 		L;
	double 	 	dx;
	double	 	xMin;
	unsigned 	*CellPartTemp=NULL;
	unsigned 	*PartsincellTemp=NULL;
	unsigned 	*BeginCellTemp=NULL;
	unsigned 	*SortPartTemp=NULL;


	void PreSort(pos *coord);

	CellDiv(unsigned nc, unsigned np,double l,double xmin);
	void SortPosition(pos *vec);
	void SortVariables(dat *vec);
	int CountPeriodicPart(unsigned q);
	void AllocateArray();
	void CopyPeriodicParticles(pos* coord, pos *coord1, dat* data, dat* data1, unsigned q);
	void AllocateArrays();
	void FreeArrays();
	void ChangeNp(unsigned np);
	void ChangeNc(unsigned nc){Nc=nc;};
	void ChangexMin(double xmin){xMin=xmin;};
	virtual ~CellDiv();
};

#endif /* CELLDIV_H_ */
