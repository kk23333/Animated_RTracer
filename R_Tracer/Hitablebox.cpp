//
// Created by KK on 17/5/10.
//

#include "Hitablebox.h"
const int Hitablebox::MaxElementNumber = 5;

static bool compareX(Hitable * ah,Hitable * bh ){
    return ah->box->start.x()+ah->box->size.x() > bh->box->start.x()+bh->box->size.x();
}

static bool compareY(Hitable * ah,Hitable * bh ){
    return ah->box->start.y()+ah->box->size.y() < bh->box->start.y()+bh->box->size.y();
}

static bool compareZ(Hitable * ah,Hitable * bh ) {
    return ah->box->start.z()+ah->box->size.z()  < bh->box->start.z()+bh->box->size.z();
}

void Hitablebox::split(){
    vector<Hitable *> x_dir[2];
    sort(hitables.begin(),hitables.end(),compareX);
    x_dir[0] = vector<Hitable *>(hitables.begin(),hitables.begin()+(hitables.size()>>1));
    x_dir[1] = vector<Hitable *>(hitables.begin() +
                                  (hitables.size() >> 1), hitables.end());
    for(int x = 0; x < 2; x++){
        vector<Hitable *> y_dir[2];
        sort(x_dir[x].begin(), x_dir[x].end(),compareY);
        y_dir[0] = vector<Hitable *>(x_dir[x].begin(),x_dir[x].begin()+(x_dir[x].size()>>1));
        y_dir[1] = vector<Hitable *>(x_dir[x].begin()+(x_dir[x].size()>>1),x_dir[x].end());
        for(int y = 0; y < 2;y++){
            vector<Hitable *> z_dir[2];
            sort(y_dir[y].begin(), y_dir[y].end(), compareZ);
            z_dir[0] = vector<Hitable *>(y_dir[y].begin(),
                                          y_dir[y].begin() + (y_dir[y].size() >> 1));
            z_dir[1] = vector<Hitable *>(y_dir[y].begin() +
                                          (y_dir[y].size() >> 1), y_dir[y].end());
            for(int z = 0 ; z < 2 ; z += 1)
                children[x * 4 + y * 2 + z] =
                        new Hitablebox(z_dir[z]);
        }
    }
   // hitables.clear();
}

void Hitablebox::fitSize() {
    if (hitables.empty()) return;
    vector<double> nums;
    nums.clear();

    for (int i = 0; i < hitables.size(); i++){
        nums.push_back((hitables[i])->box->start[0]);
    }
    start.e[0] = *min_element(nums.begin(), nums.end()) - EPSILON1;
    nums.clear();
    for (int i = 0; i < hitables.size(); i++){
        nums.push_back((hitables[i])->box->start[0]+hitables[i]->box->size.x());
    }
    size.e[0] =(*max_element(nums.begin(), nums.end())) - start.x() + EPSILON1;//padding
    nums.clear();

    for (int i = 0; i < hitables.size(); i++){
        nums.push_back((hitables[i])->box->start[1]);
    }
    start.e[1] = *min_element(nums.begin(), nums.end()) - EPSILON1;
    nums.clear();
    for (int i = 0; i < hitables.size(); i++){
        nums.push_back((hitables[i])->box->start[1]+hitables[i]->box->size.y());
    }
    size.e[1] =(*max_element(nums.begin(), nums.end())) - start.y() + EPSILON1;//padding
    nums.clear();


    for (int i = 0; i < hitables.size(); i++){
        nums.push_back((hitables[i])->box->start[2]);
    }
    start.e[2] = *min_element(nums.begin(), nums.end()) - EPSILON1;
    nums.clear();
    for (int i = 0; i < hitables.size(); i++){
        nums.push_back((hitables[i])->box->start[2]+hitables[i]->box->size.z());
    }
    size.e[2] =(*max_element(nums.begin(), nums.end())) - start.z() + EPSILON1;//padding
    nums.clear();

}

Hitablebox::Hitablebox(const vector<Hitable *> _ht) {
    hitables = _ht;
    fitSize();
    if (hitables.size() > MaxElementNumber) split();
    else {
        for (int i = 0; i < 8; i++) {
            children[i] = nullptr;
        }
    }
}


double Hitablebox::_intersect(double p0, double p, double s) {
    if (p == 0) return -1;
    return (s - p0) / p;
}

bool Hitablebox::isPassing(const Ray &ray) {
    if (children[0] == nullptr && hitables.empty()) return false;
    if (ray.origin().x() - start.x() > -EPSILON1 &&
        ray.origin().y() - start.y() > -EPSILON1 &&
        ray.origin().z() - start.z() > -EPSILON1 &&
        ray.origin().x() - (start.x() + size.x()) < EPSILON1 &&
        ray.origin().y() - (start.y() + size.y()) < EPSILON1 &&
        ray.origin().z() - (start.z() + size.z()) < EPSILON1)
        return true;
    double mins[3];
    double maxs[3];
    mins[0] = _intersect(ray.origin().x(), ray.direction().x(), start.x());
    maxs[0] = _intersect(ray.origin().x(), ray.direction().x(), start.x() + size.x());
    if (mins[0] > maxs[0]) _swap(mins[0], maxs[0]);
    mins[1] = _intersect(ray.origin().y(), ray.direction().y(), start.y());
    maxs[1] = _intersect(ray.origin().y(), ray.direction().y(), start.y() + size.y());
    if (mins[1] > maxs[1]) _swap(mins[1], maxs[1]);
    mins[2] = _intersect(ray.origin().z(), ray.direction().z(), start.z());
    maxs[2] = _intersect(ray.origin().z(), ray.direction().z(), start.z() + size.z());
    if (mins[2] > maxs[2]) _swap(mins[2], maxs[2]);
    double max_of_mins = *max_element(mins, mins + 3);
    double min_of_maxs = maxs[0];
    if (min_of_maxs == -1 ||
        (maxs[1] != -1 && maxs[1] < min_of_maxs))
        min_of_maxs = maxs[1];
    if (min_of_maxs == -1 ||
        (maxs[2] != -1 && maxs[2] < min_of_maxs))
        min_of_maxs = maxs[2];
    return max_of_mins <= min_of_maxs;
}
