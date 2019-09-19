//
// Created by KK on 16/10/5.
//

#include "Meshhitable.h"


double Meshhitable::closestIntersection(HandlingRay *h) {
    queue<ContainBox *> potential_box;
    potential_box.push(box);

    vector<Triangle *> possible_triangle;
    while (!potential_box.empty()) {
        ContainBox *currentbox = potential_box.front();
        if (currentbox->isPassing(h->ray)) {
            if (currentbox->children[0] != nullptr) {
                for (int i = 0; i < 8; i += 1)
                    potential_box.push(currentbox->children[i]);
            } else
                for (int i = 0; i < currentbox->triangles.size(); i++)
                    possible_triangle.push_back(currentbox->triangles[i]);
        }
        potential_box.pop();
    }
    Triangle *target = nullptr;
    h->ray_t = -1;
    for (int i = 0; i < possible_triangle.size(); i++) {
        double t = possible_triangle[i]->theNearestIntersection(h->ray);
        if (t != -1 && (h->ray_t == -1 ||t < h->ray_t)) { ///
            h->ray_t = t;
            target = possible_triangle[i];
            hitid = possible_triangle[i]->id;
        }
    }
    if (target != nullptr) {
//        if(ALMOST_ZERO(h->ray.N-1)){
//            h->ray.N=this->mtrl->N;
//        }else
//            h->ray.N = 1;

        Vec3 p = h->ray.origin() + h->ray_t * h->ray.direction();
//        if(ALMOST_ZERO(h->ray.N - 1.0)){
            h->normal = Ray(p, target->getNormalVec3(p));
//        }else{
//            h->normal = Ray(p, -target->getNormalVec3(p));
//        }

    }else {hitid = -1;}
        return h->ray_t;
}

void Meshhitable:: GetPosition(double ct) {
    current.clear();
    stack<Xform *> tmps;
    int ssize = transform.size();
    if (ssize == 0) {
        box = new ContainBox(record);
        current = record;
        return;
    }
    double t[4][4];
    double zzz[3][3];
    double tzzz[3][3];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t[i][j] = (i == j);

    double t_[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t_[i][j] = (i == j);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            zzz[i][j] = (i == j);


    while(!transform.empty()){
        tmps.push(transform.top());
        transform.top()->GetTMatrix(ct);
        transform.pop();
    }




    Rotation3 RR = {1, 0, 0, 0};
    Quaternion q;
    double ss[3] = {1, 1, 1};
    double tt[3] = {0, 0, 0};

//    tmps.top()->GetTMatrix(ct);
    if (tmps.top()->wy) {
        tt[0] = tmps.top()->wy[0];
        tt[1] = tmps.top()->wy[1];
        tt[2] = tmps.top()->wy[2];
    }
    if (tmps.top()->xz) {

        RR.x = tmps.top()->xz[0];
        RR.y = tmps.top()->xz[1];
        RR.z = tmps.top()->xz[2];
        RR.angle = tmps.top()->xz[3];
        FromAngleAxis(&q, RR.angle, RR.x, RR.y, RR.z);
        double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

        /* calculate coefficients */
        x2 = q.x + q.x;
        y2 = q.y + q.y;
        z2 = q.z + q.z;

        xx = q.x * x2;
        xy = q.x * y2;
        xz = q.x * z2;
        yy = q.y * y2;
        yz = q.y * z2;
        zz = q.z * z2;
        wx = q.w * x2;
        wy = q.w * y2;
        wz = q.w * z2;

        t[0][0] = 1.0 - (yy + zz);
        t[0][1] = xy - wz;
        t[0][2] = xz + wy;
        t[0][3] = tt[0];

        t[1][0] = xy + wz;
        t[1][1] = 1.0 - (xx + zz);
        t[1][2] = yz - wx;
        t[1][3] = tt[1];

        t[2][0] = xz - wy;
        t[2][1] = yz + wx;
        t[2][2] = 1.0 - (xx + yy);
        t[2][3] = tt[2];

        t[3][0] = 0;
        t[3][1] = 0;
        t[3][2] = 0;
        t[3][3] = 1;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                zzz[i][j] = t[i][j];
    }
    if (tmps.top()->bl) {
        ss[0] = tmps.top()->bl[0];
        ss[1] = tmps.top()->bl[1];
        ss[2] = tmps.top()->bl[2];
        t[0][0] *= ss[0];
        t[0][1] *= ss[0];
        t[0][2] *= ss[0];

        t[1][0] *= ss[1];
        t[1][1] *= ss[1];
        t[1][2] *= ss[1];

        t[2][0] *= ss[2];
        t[2][1] *= ss[2];
        t[2][2] *= ss[2];
    }

    transform.push(tmps.top());

    tmps.pop();

    while (!tmps.empty()) {
//        if (tmps.top()->wy) {
            tt[0] = tmps.top()->wy[0];
            tt[1] = tmps.top()->wy[1];
            tt[2] = tmps.top()->wy[2];
//        }

        //           tmps.top()->GetTMatrix(ct);
//            if (tmps.top()->xz) {
                RR.x = tmps.top()->xz[0];
                RR.y = tmps.top()->xz[1];
                RR.z = tmps.top()->xz[2];
                RR.angle = tmps.top()->xz[3];
                FromAngleAxis(&q, RR.angle, RR.x, RR.y, RR.z);
                double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
                double tp[4][4];


                /* calculate coefficients */
                x2 = q.x + q.x;
                y2 = q.y + q.y;
                z2 = q.z + q.z;

                xx = q.x * x2;
                xy = q.x * y2;
                xz = q.x * z2;
                yy = q.y * y2;
                yz = q.y * z2;
                zz = q.z * z2;
                wx = q.w * x2;
                wy = q.w * y2;
                wz = q.w * z2;

                tp[0][0] = 1.0 - (yy + zz);
                tp[0][1] = xy - wz;
                tp[0][2] = xz + wy;
                tp[0][3] = tt[0];

                tp[1][0] = xy + wz;
                tp[1][1] = 1.0 - (xx + zz);
                tp[1][2] = yz - wx;
                  tp[1][3]= tt[1];

                tp[2][0] = xz - wy;
                tp[2][1] = yz + wx;
                tp[2][2] = 1.0 - (xx + yy);
                tp[2][3] = tt[2];

                tp[3][0] = 0;
                tp[3][1] = 0;
                tp[3][2] = 0;
                tp[3][3] = 1;

        tzzz[0][0] = zzz[0][0] * tp[0][0] + zzz[0][1] * tp[1][0] + zzz[0][2] * tp[2][0] ;
        tzzz[0][1] = zzz[0][0] * tp[0][1] + zzz[0][1] * tp[1][1] + zzz[0][2] * tp[2][1] ;
        tzzz[0][2] = zzz[0][0] * tp[0][2] + zzz[0][1] * tp[1][2] + zzz[0][2] * tp[2][2] ;


        tzzz[1][0] = zzz[1][0] * tp[0][0] + zzz[1][1] * tp[1][0] + zzz[1][2] * tp[2][0];
        tzzz[1][1] = zzz[1][0] * tp[0][1] + zzz[1][1] * tp[1][1] + zzz[1][2] * tp[2][1];
        tzzz[1][2] = zzz[1][0] * tp[0][2] + zzz[1][1] * tp[1][2] + zzz[1][2] * tp[2][2];


        tzzz[2][0] = zzz[2][0] * tp[0][0] + zzz[2][1] * tp[1][0] + zzz[2][2] * tp[2][0];
        tzzz[2][1] = zzz[2][0] * tp[0][1] + zzz[2][1] * tp[1][1] + zzz[2][2] * tp[2][1];
        tzzz[2][2] = zzz[2][0] * tp[0][2] + zzz[2][1] * tp[1][2] + zzz[2][2] * tp[2][2];


                if (tmps.top()->bl) {
                    ss[0] = tmps.top()->bl[0];
                    ss[1] = tmps.top()->bl[1];
                    ss[2] = tmps.top()->bl[2];

                    tp[0][0] *= ss[0];
                    tp[0][1] *= ss[0];
                    tp[0][2] *= ss[0];

                    tp[1][0] *= ss[1];
                    tp[1][1] *= ss[1];
                    tp[1][2] *= ss[1];

                    tp[2][0] *= ss[2];
                    tp[2][1] *= ss[2];
                    tp[2][2] *= ss[2];
//                }

                t_[0][0] = t[0][0] * tp[0][0] + t[0][1] * tp[1][0] + t[0][2] * tp[2][0] + t[0][3] * tp[3][0];
                t_[0][1] = t[0][0] * tp[0][1] + t[0][1] * tp[1][1] + t[0][2] * tp[2][1] + t[0][3] * tp[3][1];
                t_[0][2] = t[0][0] * tp[0][2] + t[0][1] * tp[1][2] + t[0][2] * tp[2][2] + t[0][3] * tp[3][2];
                t_[0][3] = t[0][0] * tp[0][3] + t[0][1] * tp[1][3] + t[0][2] * tp[2][3] + t[0][3] * tp[3][3];

                t_[1][0] = t[1][0] * tp[0][0] + t[1][1] * tp[1][0] + t[1][2] * tp[2][0]+ t[1][3] * tp[3][0];
                t_[1][1] = t[1][0] * tp[0][1] + t[1][1] * tp[1][1] + t[1][2] * tp[2][1]+ t[1][3] * tp[3][1];
                t_[1][2] = t[1][0] * tp[0][2] + t[1][1] * tp[1][2] + t[1][2] * tp[2][2]+ t[1][3] * tp[3][2];
                t_[1][3] = t[1][0] * tp[0][3] + t[1][1] * tp[1][3] + t[1][2] * tp[2][3]+ t[1][3] * tp[3][3];

                t_[2][0] = t[2][0] * tp[0][0] + t[2][1] * tp[1][0] + t[2][2] * tp[2][0]+ t[2][3] * tp[3][0];
                t_[2][1] = t[2][0] * tp[0][1] + t[2][1] * tp[1][1] + t[2][2] * tp[2][1]+ t[2][3] * tp[3][1];
                t_[2][2] = t[2][0] * tp[0][2] + t[2][1] * tp[1][2] + t[2][2] * tp[2][2]+ t[2][3] * tp[3][2];
                t_[2][3] = t[2][0] * tp[0][3] + t[2][1] * tp[1][3] + t[2][2] * tp[2][3]+ t[2][3] * tp[3][3];

                t_[3][0] = t[3][0] * tp[0][0] + t[3][1] * tp[1][0] + t[3][2] * tp[2][0]+ t[3][3] * tp[3][0];
                t_[3][1] = t[3][0] * tp[0][1] + t[3][1] * tp[1][1] + t[3][2] * tp[2][1]+ t[3][3] * tp[3][1];
                t_[3][2] = t[3][0] * tp[0][2] + t[3][1] * tp[1][2] + t[3][2] * tp[2][2]+ t[3][3] * tp[3][2];
                t_[3][3] = t[3][0] * tp[0][3] + t[3][1] * tp[1][3] + t[3][2] * tp[2][3]+ t[3][3] * tp[3][3];

            }


            for (int ii = 0; ii < 4; ii++) {
                for (int kk = 0; kk < 4 ;kk++) {
                    t[ii][kk] = t_[ii][kk];
                }
            }
            for (int ii = 0; ii < 3; ii++) {
                for (int kk = 0; kk < 3 ;kk++) {
                    zzz[ii][kk] = tzzz[ii][kk];
                }
             }

            transform.push(tmps.top());

            tmps.pop();
        }



        for (int qq = 0; qq < record.size(); qq++) {
            if (!record[qq]->ihn) {
                Vec3d tmpt1 = {0, 0, 0};
                Vec3d tmpt2 = {0, 0, 0};
                Vec3d tmpt3 = {0, 0, 0};

                Vec3d tmpt1_ = {0, 0, 0};
                Vec3d tmpt2_ = {0, 0, 0};
                Vec3d tmpt3_ = {0, 0, 0};


                for (int j = 0; j < 3; j++) {
                    tmpt1[j] = record[qq]->a[j];
                    tmpt2[j] = record[qq]->b[j];
                    tmpt3[j] = record[qq]->c[j];
                }


                for (int k = 0; k < 3; k++) {
                    tmpt1_[k] = tmpt1[0] * t[k][0] + tmpt1[1] * t[k][1] +
                                tmpt1[2] * t[k][2] + t[k][3];
                }


                for (int k = 0; k < 3; k++) {
                    tmpt2_[k] = tmpt2[0] * t[k][0] + tmpt2[1] * t[k][1] +
                                tmpt2[2] * t[k][2] + t[k][3];
                }

                for (int k = 0; k < 3; k++) {
                    tmpt3_[k] = tmpt3[0] * t[k][0] + tmpt3[1] * t[k][1] +
                                tmpt3[2] * t[k][2] + t[k][3];
                }
                for (int k = 0; k < 3; k++) {
                    tmpt2[k] = tmpt2_[k];
                }
                for (int k = 0; k < 3; k++) {
                    tmpt1[k] = tmpt1_[k];
                }
                for (int k = 0; k < 3; k++) {
                    tmpt3[k] = tmpt3_[k];
                }


                Triangle *n = new Triangle(Vec3(tmpt1_[0], tmpt1_[1], tmpt1_[2]), Vec3(tmpt2_[0], tmpt2_[1], tmpt2_[2]),
                                           Vec3(tmpt3_[0], tmpt3_[1], tmpt3_[2]), qq);
                current.push_back(n);

            } else {
                Vec3d tmpt1 = {0, 0, 0};
                Vec3d tmpt2 = {0, 0, 0};
                Vec3d tmpt3 = {0, 0, 0};

                Vec3d tmpt1_ = {0, 0, 0};
                Vec3d tmpt2_ = {0, 0, 0};
                Vec3d tmpt3_ = {0, 0, 0};

                Vec3d tmptn1 = {0, 0, 0};
                Vec3d tmptn2 = {0, 0, 0};
                Vec3d tmptn3 = {0, 0, 0};

                Vec3d tmptn1_ = {0, 0, 0};
                Vec3d tmptn2_ = {0, 0, 0};
                Vec3d tmptn3_ = {0, 0, 0};


                for (int j = 0; j < 3; j++) {
                    tmpt1[j] = record[qq]->a[j];
                    tmpt2[j] = record[qq]->b[j];
                    tmpt3[j] = record[qq]->c[j];
                }

                for (int j = 0; j < 3; j++) {
                    tmptn1[j] = record[qq]->norm1[j];
                    tmptn2[j] = record[qq]->norm2[j];
                    tmptn3[j] = record[qq]->norm3[j];
                }

                for (int k = 0; k < 3; k++) {
                    tmpt1_[k] = tmpt1[0] * t[k][0] + tmpt1[1] * t[k][1] +
                                tmpt1[2] * t[k][2] + t[k][3];
                }

                for (int k = 0; k < 3; k++) {
                    tmptn1_[k] = tmptn1[0] * zzz[k][0] + tmptn1[1] * zzz[k][1] +
                                 tmptn1[2] * zzz[k][2] ;
                }


                for (int k = 0; k < 3; k++) {
                    tmpt2_[k] = tmpt2[0] * t[k][0] + tmpt2[1] * t[k][1] +
                                tmpt2[2] * t[k][2] + t[k][3];
                }

                for (int k = 0; k < 3; k++) {
                    tmptn2_[k] = tmptn2[0] * zzz[k][0] + tmptn2[1] * zzz[k][1] +
                                 tmptn2[2] * zzz[k][2] ;
                }

                for (int k = 0; k < 3; k++) {
                    tmpt3_[k] = tmpt3[0] * t[k][0] + tmpt3[1] * t[k][1] +
                                tmpt3[2] * t[k][2] + t[k][3];
                }

                for (int k = 0; k < 3; k++) {
                    tmptn3_[k] = tmptn3[0] * zzz[k][0] + tmptn3[1] * zzz[k][1] +
                                 tmptn3[2] * zzz[k][2] ;
                }
                Triangle *n = new Triangle(Vec3(tmpt1_[0], tmpt1_[1], tmpt1_[2]), Vec3(tmpt2_[0], tmpt2_[1], tmpt2_[2]),
                                           Vec3(tmpt3_[0], tmpt3_[1], tmpt3_[2]),
                                           Vec3(tmptn1_[0], tmptn1_[1], tmptn1_[2]),
                                           Vec3(tmptn2_[0], tmptn2_[1], tmptn2_[2]),
                                           Vec3(tmptn3_[0], tmptn3_[1], tmptn3_[2]), qq);
                current.push_back(n);

            }
        }
        box = new ContainBox(current);
}

Meshhitable::Meshhitable() {};
