//
// Created by KK on 16/9/15.
//

#include "Triangle.h"
using namespace std;

double Triangle::theNearestIntersection(Ray &ray) {
    return _theNearestIntersection(ray);
}

Vec3 Triangle::getNormalVec3(const Vec3 &p) {

    if(!ihn){

        Vec3 A = b - a;
        Vec3 B = c - a;
        return unit_Vector(cross(A,B));
    }
    else{
        Vec3 s = p;
        Vec3 pa = a - s;
        Vec3 pb = b - s;
        Vec3 pc = c -s ;

        Vec3 ab = b - a;
        Vec3 ac = c - a;
        double ss = cross(ab,ac).length();
        double c1 = cross(pb,pc).length()/ss;//a
        double c2 = cross(pa,pc).length()/ss;//b
        return unit_Vector(c1*norm1 + c2*norm2 + (1-c1-c2)*norm3)   ;

    }


}

Vec3 & Triangle::operator [] (int i){
    if(i == 0) return a;
    if(i == 1) return b;
    return c;
}

////????
void line_add( double** mat , int a, int b, double k ) {
    for (int i = 0; i < 6; i++) {
        mat[a][i] += mat[b][i] * k;
    }
}

int work1(double** mat ){
    for (int i =1; i < 3; i++){
        if(fabs(mat[i-1][i-1])<0.00000001)
        {
            int mm;
            for( mm = i;mm < 3;mm++){
                if(fabs(mat[mm - 1][i - 1])> 0.00000001)
                    break;
            }
            line_add(mat,i - 1 ,mm - 1,1);
        }
        if(fabs(mat[i-1][i-1])<0.00000001){
            return 0;
        } else{
            for ( int j = i;j < 3; ++ j)
            {
                line_add(mat,j,i - 1 , -mat[j][i - 1 ] / mat[i - 1 ][i - 1 ]);   //化为上三角矩阵
            } // end for j
        }
    }
    return 1;
}

int work2(double** mat){
    for(int i = 1;i>=0;i--){
        for(int j =i;j>=0;j--){
            if(fabs(mat[i+1][i+1])<0.00000001)
                return 0 ;
            line_add(mat,j,i+1,-mat[j][i+1]/mat[i+1][i+1]);
        }
    }
    return 1;
}

int makeunit(double** _mat) // 单位化
{

    for ( int i = 0 ;i < 3; ++ i)
    {
        double u =  _mat[i][i];
        if (fabs(u) < 0.00000001 ){
            return 0 ;
        } else{
            for ( int j = 0 ;j < 6; ++ j)
            {

                double tmp;
                tmp = _mat[i][j] /u;
                _mat[i][j] = tmp;
            }
        }

    }
    return 1;
}
void InverseMatrix(double **A,double **B)
{
    int i,j;
    double **a =new double*[3];


    for(i=0;i<3;i++)
   {
       a[i]=new double[2*3];
   }
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            a[i][j]=A[i][j];  //复制A到a，避免改变A的值

    for(i=0;i<3;i++)
        for(j=3;j<6;j++)
            a[i][j]=(j==i+3);


    if(work1(a)){
        if(work2(a)){
            if(makeunit(a))//单位化
            {
                for(i=0;i<3;i++)
                    for(j=0;j<3;j++)
                        B[i][j]=a[i][j+3];  //取出求逆结果
            }else {
                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++) {
                        B[i][j] = 0;
                    }
                }
            }
        }else {
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    B[i][j] = 0;
                }
            }
        }
    } else{
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                    B[i][j]=0;
            }
        }
    }
    for(i=0;i<3;i++)
    {
        delete [] a[i];
    }
    delete [] a;

}
//
//void printstep(double **C) // 显示求的过程
//{
//
//    for ( int i = 0 ;i < 3; ++ i)
//    {
//        for ( int j = 0 ;j <6; ++ j)
//        {
//            if (fabs(C[i][j]) < 0.000001 )
//                C[i][j] = 0 ;
//            cout << C[i][j] << " " ;
//            if (j == 2 )
//                cout << " | " ;
//        }
//        cout << endl;
//    }
//    cout << endl;
//}
//
double Triangle::_theNearestIntersection(Ray &ray, int test_count) {
    if(test_count > 2) return -1;
    double tmpA[3][3]=
    {
            {ray.B.x(),a.x()-b.x(),a.x()-c.x()},{ray.B.y(),a.y()-b.y(),a.y()-c.y()},{ray.B.z(),a.z()-b.z(),a.z()-c.z()}
    };
    double **  matA = (double**)calloc(3,sizeof(double*));

    for(int i = 0; i < 3; i++){
        matA[i] = (double*)calloc(3,sizeof(double));
    }


    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            matA[i][j]=tmpA[i][j];

    double **matA2;

    matA2 = (double**)calloc(3, sizeof(double*));
    for(int i = 0; i < 3; i++){
        matA2[i] = (double*)calloc(3, sizeof(double));
    }


//    double  **matA2;

    InverseMatrix(matA,matA2);
    for(int kkk=0;kkk<3;kkk++){
        free(matA[kkk]);
    }
    free(matA);

    double matb[3]={
            a.x() - ray.A.x(),
            a.y() - ray.A.y(),
            a.z() - ray.A.z()
    };
    double result[3] = {

          matA2[0][0]* matb[0]+matA2[0][1]* matb[1]+matA2[0][2]* matb[2],
          matA2[1][0]* matb[0]+matA2[1][1]* matb[1]+matA2[1][2]* matb[2],
          matA2[2][0]* matb[0]+matA2[2][1]* matb[1]+matA2[2][2]* matb[2]
    };



    double t = result[0];
    double beta = result[1];
    double gama = result [2];

    for(int kk=0;kk<3;kk++){
        free(matA2[kk]);
    }
    free(matA2);

    if(ALMOST_ZERO(t)){
        ray.A += ray.B*EPSILON1;
        return this->_theNearestIntersection(ray,test_count+1);
    }
    if(t <=0.01||beta < 0||beta > 1|| gama < 0||gama > 1||beta + gama > 1)
        return -1;
    return t;
}
Triangle::Triangle(Vec3 aa, Vec3 bb,Vec3 cc,Vec3 naa,Vec3 nbb ,Vec3 ncc,Vec2d o, Vec2d oo,  Vec2d ooo,int tid){

    a = aa;
    b = bb;
    c = cc;

    norm1 = naa;
    norm2 = nbb;
    norm3 = ncc;

    a_t[0] = o[0];
    a_t[1] = o[1];

    b_t[0] = oo[0];
    b_t[1] = oo[1];

    c_t[0] = ooo[0];
    c_t[1] = ooo[1];

    ihn = true;

    id = tid;

}



Triangle::Triangle(Vec3 aa, Vec3 bb , Vec3 cc , Vec2d o , Vec2d oo, Vec2d ooo , int tid){

    a = aa;
    b = bb;
    c = cc;


    a_t[0] = o[0];
    a_t[1] = o[1];

    b_t[0] = oo[0];
    b_t[1] = oo[1];

    c_t[0] = ooo[0];
    c_t[1] = ooo[1];

    id = tid;
}





//
//double Triangle:: theNearestIntersection(Ray &ray){
//    double t,u,v;
//
//    //E1
//    Vec3 E1 = b-a;
//    //E2
//    Vec3 E2 = c-a;
//    //p
//    Vec3 p =cross(ray.direction(),E2);
//
//    //determinant
//    double det = dot(E1,p);
//
//    Vec3 T;
//    if(det>0){
//        T = ray.origin() -a;
//    }else{
//        T = a -ray.origin();
//        det = -det;
//    }
//
//    if(det<0.00001f)
//        return -1;
//
//    u = dot(T,p);
//    if(u<0||u>det)
//        return -1;
//
//    Vec3 Q = cross(T,E1);
//
//    v = dot(ray.direction(),Q);
//    if(v<0|| u+v>det)
//        return -1;
//
//    t = dot(E2,Q);
//
//    double fInvDet =  1.0 / det;
//    t *= fInvDet;
//    return t;
//
//}