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


	void PreSort(tfloat3 *coord);

	CellDiv(unsigned nc, unsigned np,double l,double xmin);
	void SortPosition(tfloat3 *vec);
	void SortVariables(tfloat5 *vec);
	int CountPeriodicPart(unsigned q);
	void AllocateArray();
	void OuterLoop(tfloat3* coord, tfloat3 *coord1, tfloat5* data, tfloat5* data1, unsigned q);
	unsigned InnerLoop(tuint2 inn, tuint2 out, tfloat2 delta,tfloat3* coord, tfloat3 *coord1, tfloat5* data, tfloat5* data1,unsigned n);
	void AllocateArrays();
	void FreeArrays();
	void ChangeNp(unsigned np);
	void ChangeNc(unsigned nc){Nc=nc;};
	void ChangexMin(double xmin){xMin=xmin;};
	virtual ~CellDiv();
};

#endif /* CELLDIV_H_ */
