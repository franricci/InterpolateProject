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


void CellDiv::PreSort(pos *coord){
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

void CellDiv::SortPosition(pos *vec){
	pos *SortedVector = new pos[Np];
	for (unsigned p=0; p<Np; p++) SortedVector[p]=vec[SortPartTemp[p]];
	memcpy(vec,SortedVector,sizeof(pos)*Np);
}

void CellDiv::SortVariables(dat *vec){
	dat *SortedVector = new dat[Np];
	for (unsigned p=0; p<Np; p++) SortedVector[p]=vec[SortPartTemp[p]];
	memcpy(vec,SortedVector,sizeof(dat)*Np);
}

int CellDiv::CountPeriodicPart(unsigned q){
	unsigned sum=0;
	for (unsigned i=0; i<q; i++)
		for(unsigned j=0; j<Nc; j++) {
			unsigned index=i+j*Nc;
			unsigned index1=(Nc-1)-i+j*Nc;
			sum +=PartsincellTemp[index];
			sum +=PartsincellTemp[index1];
		}
	for (unsigned j=0; j<q; j++)
			for(unsigned i=0; i<Nc; i++) {
				unsigned index=i+j*Nc;
				unsigned index1=i+(Nc-1-j)*Nc;
				sum +=PartsincellTemp[index];
				sum +=PartsincellTemp[index1];
			}
	for (unsigned i=0; i<q; i++)
			for(unsigned j=0; j<q; j++) {
					unsigned index=i+j*Nc;
					unsigned index1=(Nc-1)-i+j*Nc;
					sum +=PartsincellTemp[index];
					sum +=PartsincellTemp[index1];
			}
	for (unsigned i=0; i<q; i++)
				for(unsigned j=Nc-q; j<Nc; j++) {
						unsigned index=i+j*Nc;
						unsigned index1=(Nc-1)-i+j*Nc;
						sum +=PartsincellTemp[index];
						sum +=PartsincellTemp[index1];
				}
	return sum;
}

void CellDiv::CopyPeriodicParticles(pos* coord, pos *coord1, dat* data, dat* data1, unsigned q){
	memcpy(coord,coord1,sizeof(pos)*Np);
	memcpy(data,data1,sizeof(dat)*Np);
	unsigned n=0;
	for (unsigned i=0; i<q; i++)
			for(unsigned j=0; j<Nc; j++) {
				unsigned index=i+j*Nc;
				unsigned index1=(Nc-1)-i+j*Nc;
				unsigned pmin=BeginCellTemp[index];
				unsigned pmax=pmin+PartsincellTemp[index];
				unsigned pmin1=BeginCellTemp[index1];
				unsigned pmax1=pmin1+PartsincellTemp[index1];

				for (unsigned p=pmin; p<pmax; p++){
					coord[Np+n].x=coord1[p].x+L;
					coord[Np+n].z=coord1[p].z;
					data[Np+n]=data1[p];
					n++;
				}

				for (unsigned p=pmin1; p<pmax1; p++){
					coord[Np+n].x=coord1[p].x-L;
					coord[Np+n].z=coord1[p].z;
					data[Np+n]=data1[p];
					n++;
				}

			}
		for (unsigned j=0; j<q; j++)
				for(unsigned i=0; i<Nc; i++) {
					unsigned index=i+j*Nc;
					unsigned index1=i+(Nc-1-j)*Nc;
					unsigned pmin=BeginCellTemp[index];
					unsigned pmax=pmin+PartsincellTemp[index];
					unsigned pmin1=BeginCellTemp[index1];
					unsigned pmax1=pmin1+PartsincellTemp[index1];


					for (unsigned p=pmin; p<pmax; p++){
						coord[Np+n].x=coord1[p].x;
						coord[Np+n].z=coord1[p].z+L;
						data[Np+n]=data1[p];
						n++;
					}

					for (unsigned p=pmin1; p<pmax1; p++){
						coord[Np+n].x=coord1[p].x;
						coord[Np+n].z=coord1[p].z-L;
						data[Np+n]=data1[p];
						n++;
					}
				}
		for (unsigned i=0; i<q; i++)
					for(unsigned j=0; j<q; j++) {
						unsigned index=i+j*Nc;
						unsigned index1=(Nc-1)-i+j*Nc;
						unsigned pmin=BeginCellTemp[index];
						unsigned pmax=pmin+PartsincellTemp[index];
						unsigned pmin1=BeginCellTemp[index1];
						unsigned pmax1=pmin1+PartsincellTemp[index1];

						for (unsigned p=pmin; p<pmax; p++){
							coord[Np+n].x=coord1[p].x+L;
							coord[Np+n].z=coord1[p].z+L;
							data[Np+n]=data1[p];
							n++;
						}

						for (unsigned p=pmin1; p<pmax1; p++){
							coord[Np+n].x=coord1[p].x-L;
							coord[Np+n].z=coord1[p].z+L;
							data[Np+n]=data1[p];
							n++;
						}

					}
		for (unsigned i=0; i<q; i++)
							for(unsigned j=Nc-q; j<Nc; j++) {
								unsigned index=i+j*Nc;
								unsigned index1=(Nc-1)-i+j*Nc;
								unsigned pmin=BeginCellTemp[index];
								unsigned pmax=pmin+PartsincellTemp[index];
								unsigned pmin1=BeginCellTemp[index1];
								unsigned pmax1=pmin1+PartsincellTemp[index1];

								for (unsigned p=pmin; p<pmax; p++){
									coord[Np+n].x=coord1[p].x+L;
									coord[Np+n].z=coord1[p].z-L;
									data[Np+n]=data1[p];
									n++;
								}

								for (unsigned p=pmin1; p<pmax1; p++){
									coord[Np+n].x=coord1[p].x-L;
									coord[Np+n].z=coord1[p].z-L;
									data[Np+n]=data1[p];
									n++;
								}

							}
}

void CellDiv::ChangeNp(unsigned np){
	Np=np;
}
CellDiv::~CellDiv() {
	// TODO Auto-generated destructor stub
}

