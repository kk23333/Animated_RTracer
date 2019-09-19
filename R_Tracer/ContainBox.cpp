//
// Created by KK on 16/10/6.
//

#include "ContainBox.h"


const int ContainBox::MaxElementNumber = 8;

static bool compareX(Triangle * atri,Triangle * btri ){
    double _a[] = {atri->a.x(), atri->b.x(),atri->c.x()};
    double _b[] = {btri->a.x(), btri->b.x(),btri->c.x()};
    return *min_element(_a, _a+3) < *min_element(_b, _b+3);
}

static bool compareY(Triangle * atri,Triangle * btri ){
    double _a[] = {atri->a.y(), atri->b.y(),atri->c.y()};
    double _b[] = {btri->a.y(), btri->b.y(),btri->c.y()};
    return *min_element(_a, _a+3) < *min_element(_b, _b+3);
}

static bool compareZ(Triangle * atri,Triangle * btri ){
    double _a[] = {atri->a.z(), atri->b.z(),atri->c.z()};
    double _b[] = {btri->a.z(), btri->b.z(),btri->c.z()};
    return *min_element(_a, _a+3) < *min_element(_b, _b+3);
}

void ContainBox::split(){
    vector<Triangle *> x_dir[2];
    sort(triangles.begin(),triangles.end(),compareX);
    x_dir[0] = vector<Triangle *>(triangles.begin(),triangles.begin()+(triangles.size()>>1));
    x_dir[1] = vector<Triangle *>(triangles.begin() +
                                  (triangles.size() >> 1), triangles.end());
    for(int x = 0; x < 2; x++){
        vector<Triangle *> y_dir[2];
        sort(x_dir[x].begin(), x_dir[x].end(),compareY);
        y_dir[0] = vector<Triangle *>(x_dir[x].begin(),x_dir[x].begin()+(x_dir[x].size()>>1));
        y_dir[1] = vector<Triangle *>(x_dir[x].begin()+(x_dir[x].size()>>1),x_dir[x].end());
        for(int y = 0; y < 2;y++){
            vector<Triangle *> z_dir[2];
            sort(y_dir[y].begin(), y_dir[y].end(), compareZ);
            z_dir[0] = vector<Triangle *>(y_dir[y].begin(),
                                          y_dir[y].begin() + (y_dir[y].size() >> 1));
            z_dir[1] = vector<Triangle *>(y_dir[y].begin() +
                                          (y_dir[y].size() >> 1), y_dir[y].end());
            for(int z = 0 ; z < 2 ; z += 1)
                children[x * 4 + y * 2 + z] =
                        new ContainBox(z_dir[z]);
        }
    }
    triangles.clear();
}

void ContainBox::fitSize() {
    if (triangles.empty()) return;
    vector<double> nums;
    nums.clear();

    for (int i = 0; i < triangles.size(); i++)
        for (int j = 0; j < 3; j++)
            nums.push_back((*(triangles[i]))[j].x());

    start.e[0] = *min_element(nums.begin(), nums.end()) - EPSILON1;
    size.e[0] = (*max_element(nums.begin(), nums.end())) - start.x() + EPSILON1;//padding
    nums.clear();

    for (int i = 0; i < triangles.size(); i++)
        for (int j = 0; j < 3; j++)
         nums.push_back((*triangles[i])[j].y());

    start.e[1] = *min_element(nums.begin(), nums.end()) - EPSILON1;
    size.e[1] = (*max_element(nums.begin(), nums.end())) - start.y() + EPSILON1;
     nums.clear();

     for (int i = 0; i < triangles.size(); i += 1)
          for (int j = 0; j < 3; j += 1)
               nums.push_back((*triangles[i])[j].z());

     start.e[2] = *min_element(nums.begin(), nums.end()) - EPSILON1;
     size.e[2] = (*max_element(nums.begin(), nums.end())) - start.z() + EPSILON1;
     nums.clear();
}

ContainBox::ContainBox(const vector<Triangle *> _t) {
    triangles = _t;
    fitSize();
    if (triangles.size() > MaxElementNumber) split();
    else {
            for (int i = 0; i < 8; i++) {
            children[i] = nullptr;
            }
    }
}

double ContainBox::_intersect(double p0, double p, double s) {
        if (p == 0) return -1;
        return (s - p0) / p;
}

bool ContainBox::isPassing(const Ray &ray) {
        if (children[0] == nullptr && triangles.empty()) return false;
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
