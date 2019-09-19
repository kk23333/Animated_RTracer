//
// Created by KK on 16/10/22.
//

#include "StaticXform.h"
StaticXform::StaticXform(double s[3],double r[4],double t[3])
{
/* m = translation * rotation * scale */
   // double drot[4];

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            m[i][j]=(i==j);
    for(int i =0;i<3;i++){
        bl[i] = s[i];
    };
    for(int i =0;i<4;i++){
        xz[i] = r[i];
    }
    for(int i =0;i<3;i++){
        wy[i] =t[i];
    }

//    Rotation3 RR = {1,0,0,0};
//    Quaternion q;
//    if(r != nullptr){
//        RR.x=r[0];
//        RR.y=r[1];
//        RR.z=r[2];
//        RR.angle=r[3];
//        FromAngleAxis(&q, RR.angle, RR.x, RR.y, RR.z);
//        double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
//
//        /* calculate coefficients */
//        x2 = q.x + q.x;
//        y2 = q.y + q.y;
//        z2 = q.z + q.z;
//
//        xx = q.x * x2;   xy = q.x * y2;   xz = q.x * z2;
//        yy = q.y * y2;   yz = q.y * z2;   zz = q.z * z2;
//        wx = q.w * x2;   wy = q.w * y2;   wz = q.w * z2;
//
//        m[0][0] = 1.0 - (yy + zz);
//        m[0][1] = xy - wz;
//        m[0][2] = xz + wy;
//        m[0][3] = 0.0;
//
//        m[1][0] = xy + wz;
//        m[1][1] = 1.0 - (xx + zz);
//        m[1][2] = yz - wx;
//        m[1][3] = 0.0;
//
//        m[2][0] = xz - wy;
//        m[2][1] = yz + wx;
//        m[2][2] = 1.0 - (xx + yy);
//        m[2][3] = 0.0;
//
//        m[3][0] = 0;
//        m[3][1] = 0;
//        m[3][2] = 0;
//        m[3][3] = 1;
//        QuatToMatrix(&q, m); /* Also sets bottom row to 0 0 0 1 */

//    }
//
//
//    if(s!= nullptr){
//        m[0][0] *= s[0]; m[0][1] *= s[0]; m[0][2] *= s[0];
//        m[1][0] *= s[1]; m[1][1] *= s[1]; m[1][2] *= s[1];
//        m[2][0] *= s[2]; m[2][1] *= s[2]; m[2][2] *= s[2];
//    }
//
//
//
//
//
//
//
//    if(t!= nullptr){
//        m[0][3] = t[0];
//        m[1][3] = t[1];
//        m[2][3] = t[2];
//    }

/* translation */



}
