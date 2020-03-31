/*
 * Types.h
 *
 *  Created on: 16/mar/2020
 *      Author: francescopc
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef struct {
	double x,y,z;
} tfloat3;

typedef struct {
	double u,v,w,d,p;
} tfloat5;

typedef struct {
	double x,y;
} tfloat2;


typedef struct{
  unsigned x,y;
}tuint2;

inline tuint2 TUint2(unsigned v){ tuint2 p={v,v}; return(p); }
inline tuint2 TUint2(unsigned x,unsigned y){ tuint2 p={x,y}; return(p); }
inline bool   operator ==(const tuint2& a,const tuint2& b){ return(a.x==b.x && a.y==b.y); }
inline bool   operator !=(const tuint2& a,const tuint2& b){ return(a.x!=b.x || a.y!=b.y); }
inline bool   operator  <(const tuint2& a,const tuint2& b){ return(a.x<b.x && a.y<b.y); }
inline bool   operator  >(const tuint2& a,const tuint2& b){ return(a.x>b.x && a.y>b.y); }
inline bool   operator <=(const tuint2& a,const tuint2& b){ return(a.x<=b.x && a.y<=b.y); }
inline bool   operator >=(const tuint2& a,const tuint2& b){ return(a.x>=b.x && a.y>=b.y); }
inline tuint2 operator  +(const tuint2& a,const tuint2& b){ return(TUint2(a.x+b.x,a.y+b.y)); }
inline tuint2 operator  -(const tuint2& a,const tuint2& b){ return(TUint2(a.x-b.x,a.y-b.y)); }
inline tuint2 operator  *(const tuint2& a,const tuint2& b){ return(TUint2(a.x*b.x,a.y*b.y)); }
inline tuint2 operator  /(const tuint2& a,const tuint2& b){ return(TUint2(a.x/b.x,a.y/b.y)); }
inline tuint2 operator  +(const tuint2& a,const unsigned& b){ return(TUint2(a.x+b,a.y+b)); }
inline tuint2 operator  -(const tuint2& a,const unsigned& b){ return(TUint2(a.x-b,a.y-b)); }
inline tuint2 operator  *(const tuint2& a,const unsigned& b){ return(TUint2(a.x*b,a.y*b)); }
inline tuint2 operator  /(const tuint2& a,const unsigned& b){ return(TUint2(a.x/b,a.y/b)); }
inline tuint2 MinValues(const tuint2& a,const tuint2& b){ return(TUint2((a.x<=b.x? a.x: b.x),(a.y<=b.y? a.y: b.y))); }
inline tuint2 MaxValues(const tuint2& a,const tuint2& b){ return(TUint2((a.x>=b.x? a.x: b.x),(a.y>=b.y? a.y: b.y))); }
inline unsigned TUint2Get(const tuint2& a,unsigned c){ return(!c? a.x: a.y); }
inline tuint2 TUint2Set(const tuint2& a,unsigned c,unsigned v){ return(TUint2((c? a.x: v),(c!=1? a.y: v))); }

#endif /* TYPES_H_ */
