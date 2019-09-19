//
// Created by KK on 16/10/22.
//

#include "AnimatedXform.h"

AnimatedXform::AnimatedXform(string name){
    Xformname = name;
}

void AnimatedXform::GetTMatrix(double tm){

    A = FindAnimation(this->Xformname,Animation_list);
    if(A->rotations)
    {
        _GetRotation(A, tm, xz);
    } else{
        xz[0] = 1;
        xz[1] = 0;
        xz[2] = 0;
        xz[3] = 0;
    }


    /* concatenate with scaling */
    if(A->scales)
    {
        _GetScale(A, tm, bl);

    } else{
        bl[0] = 1;
        bl[1] = 1;
        bl[2] = 1;

    }


    /* translation */
    if(A->translations)
    {
        _GetTranslation(A, tm, wy);

    }else{
        wy[0]=0;
        wy[1]=0;
        wy[2]=0;
    }

}





