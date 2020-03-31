/*
 * InterpolateMLS.cpp
 *
 *  Created on: 24/mar/2020
 *      Author: francescopc
 */

#include "InterpolateMLS.h"
#include <cblas.h>

InterpolateMLS::InterpolateMLS(unsigned np, unsigned nc, unsigned qcell,double mass,double deltax,double H) {
	Np=np;
	Nc=nc;
	q=qcell;
	Mass=mass;
	dx=deltax;
	h=H;
	// TODO Auto-generated constructor stub

}

void InterpolateMLS::AllocateArray(){
	Sol = new tfloat2[Nc*Nc];
}

void InterpolateMLS::FreeArray(){
	delete [] Sol; Sol=nullptr;
}
void InterpolateMLS::Solve(tfloat3 *coord, tfloat5 *data, unsigned *BeginCell, unsigned *Partsincell){
	for(unsigned i=0; i<Nc; i++)
		for(unsigned j=0; j<Nc; j++){
			SolveBox(coord,data,BeginCell,Partsincell,i,j);
		}
}

void InterpolateMLS::SolveBox(tfloat3 *coord, tfloat5 *data, unsigned *BeginCell, unsigned *Partsincell,unsigned i,unsigned j){
	unsigned i_1=i+q;
	unsigned j_1=j+q;
	double x1=i*dx;
	double z1=j*dx;
	double C[36]={0.0};
	double *B=new double[12];
	memset(B,0,sizeof(double)*12);
	int ipiv[6]={0};
	lapack_int info;


	for (unsigned m=i_1-q; m<i_1+q-1;m++)
		for(unsigned n=j_1-q;n<j_1+q-1;n++){

			unsigned index=m+n*(Nc+2*q);
			unsigned pmin=BeginCell[index];
			unsigned pmax=pmin+Partsincell[index];

			for(unsigned p=pmin; p<pmax; p++){

				double	x2=coord[p].x;
				double	z2=coord[p].z;


				double 	rhop=data[p].d;
				double  vol=Mass/rhop;
				double 	u=data[p].u;
				double 	v=data[p].w;

				double ddx=x1-x2;
				double ddz=z1-z2;

				double rr2=ddx*ddx+ddz*ddz;

				if (rr2 < 4*h*h && rr2>10e-6){
					double w=getKernelWedland(rr2,h);

					double A[] = {1,ddx,ddz,ddx*ddx*0.5,ddx*ddz,ddz*ddz*0.5};
					double alpha=w*vol;

					cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,6,6,1,alpha,A,6,A,1,1.0,C,6);

					double alpha1=u*alpha;
					double alpha2=v*alpha;

					cblas_daxpy(6,alpha1,A,1,&B[0],2);
					cblas_daxpy(6,alpha2,A,1,&B[1],2);



				}


			}
		}

	info=LAPACKE_dgesv(LAPACK_ROW_MAJOR,6,2,C,6,ipiv,B,2);
	Sol[i+Nc*j].x=B[0];
	Sol[i+Nc*j].y=B[1];
	delete [] B; B=nullptr;
}

double InterpolateMLS::getKernelWedland(double rr2,double h){
	double qq=sqrt(rr2)/h;
	double qq1=(1.0-0.5*qq);
	double qq2=qq1*qq1;
	double Awen=0.557/(h*h);
	double w=Awen*(2*qq+1)*qq2*qq2;
	return w;

}
InterpolateMLS::~InterpolateMLS() {
	// TODO Auto-generated destructor stub
}

