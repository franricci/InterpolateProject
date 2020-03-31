/*
 * CellDiv.cpp
 *
 *  Created on: 22/mar/2020
 *      Author: francescopc
 */

#include "CellDiv.h"

CellDiv::CellDiv(unsigned nc, unsigned np,double l,double xmin) {
	Nc=nc;
	Np=np;
	L=l;
	dx=L/Nc;
	xMin=xmin;
}

void CellDiv::AllocateArrays(){
	CellPartTemp	= new unsigned[Np];
	PartsincellTemp	= new unsigned[Nc*Nc];
	BeginCellTemp	= new unsigned[Nc*Nc];
	SortPartTemp	= new unsigned[Np];

}

void CellDiv::FreeArrays(){
	delete [] CellPartTemp; 	CellPartTemp=NULL;
	delete [] PartsincellTemp; 	PartsincellTemp=NULL;
	delete [] BeginCellTemp;   	BeginCellTemp=NULL;
	delete [] SortPartTemp;		SortPartTemp=NULL;


}


void CellDiv::PreSort(tfloat3 *coord){
	memset(PartsincellTemp,0,sizeof(unsigned)*Nc*Nc);
	for (unsigned p=0; p<Np; p++){
			double x=coord[p].x-xMin;
			double z=coord[p].z-xMin;
			unsigned i= floor(x/dx);
			unsigned j= floor(z/dx);

			unsigned index=i+j*Nc;
			CellPartTemp[p]=index;
			PartsincellTemp[index]++;
	}

	for(unsigned n=0; n<Nc*Nc; n++){
		std::cout<< PartsincellTemp[n]<<std::endl;
	}



	BeginCellTemp[0]=0;
		for (unsigned n=0; n<Nc*Nc-1; n++){
			BeginCellTemp[n+1]=BeginCellTemp[n]+PartsincellTemp[n];
		}
		memset(PartsincellTemp,0,sizeof(unsigned)*Nc*Nc);
		for (unsigned p=0; p<Np; p++){
			unsigned box=CellPartTemp[p];
			SortPartTemp[BeginCellTemp[box]+PartsincellTemp[box]]=p;
			PartsincellTemp[box]++;
		}


}

void CellDiv::SortPosition(tfloat3 *vec){
	tfloat3 *SortedVector = new tfloat3[Np];
	for (unsigned p=0; p<Np; p++) SortedVector[p]=vec[SortPartTemp[p]];
	memcpy(vec,SortedVector,sizeof(tfloat3)*Np);
}

void CellDiv::SortVariables(tfloat5 *vec){
	tfloat5 *SortedVector = new tfloat5[Np];
	for (unsigned p=0; p<Np; p++) SortedVector[p]=vec[SortPartTemp[p]];
	memcpy(vec,SortedVector,sizeof(tfloat5)*Np);
}

int CellDiv::CountPeriodicPart(unsigned q){
	tuint2 lim[3];
		double del[3];
		tfloat2 delta;
		unsigned n=0;

		lim[0] = TUint2(0,q); lim[1] = TUint2(Nc-q,Nc); lim[2] = TUint2(0,Nc);

		del[0] =L; del[1]=-L; del[2]=0.0;

		for (unsigned i=0; i< 3; i++)
			for (unsigned j=0; j<3; j++){

				if(i==2 && j==2) break;

				for (unsigned k=lim[i].x; k < lim[i].y; k++)
					for (unsigned m=lim[j].x; m<lim[j].y; m++){

						unsigned pmin=BeginCellTemp[i+j*Nc];
						unsigned pmax=pmin+PartsincellTemp[i+j*Nc];

						for (unsigned p=pmin; p<pmax; p++)n++;
					}

		   }

		return n;
}


void CellDiv::OuterLoop(tfloat3* coord, tfloat3 *coord1, tfloat5* data, tfloat5* data1, unsigned q){
	tuint2 lim[3];
	double del[3];
	tfloat2 delta;
	unsigned n=0;

	lim[0] = TUint2(0,q); lim[1] = TUint2(Nc-q,Nc); lim[2] = TUint2(0,Nc);

	del[0] =L; del[1]=-L; del[2]=0.0;

	for (unsigned i=0; i< 3; i++)
		for (unsigned j=0; j<3; j++){
			delta.x=del[i];
			delta.y=del[j];
			n=InnerLoop(lim[i],lim[j],delta,coord, coord1, data, data1, n);
		}
}

unsigned CellDiv::InnerLoop(tuint2 out, tuint2 inn, tfloat2 delta,tfloat3* coord, tfloat3 *coord1, tfloat5* data, tfloat5* data1,unsigned n){
	for (unsigned i=out.x; i < out.y; i++)
		for (unsigned j=inn.x; j<inn.y; j++){

			unsigned pmin=BeginCellTemp[i+j*Nc];
			unsigned pmax=pmin+PartsincellTemp[i+j*Nc];

			for (unsigned p=pmin; p<pmax; p++){
			coord[n].x=coord1[p].x+delta.x;
			coord[n].z=coord1[p].z+delta.y;
			data[n]=data1[p];
			n++;
			}

		}
	return n;
}

void CellDiv::ChangeNp(unsigned np){
	Np=np;
}
CellDiv::~CellDiv() {
	// TODO Auto-generated destructor stub
}

