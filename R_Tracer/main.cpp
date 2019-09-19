#include <iostream>
#include <fstream>
#include "parse.h"

using namespace std;


Scene *world = new Scene();
AnimationList *Animation_list;
Camera* ccam;
double curtm;

int main() {
    curtm = 0;
    double interval;
    Vec3 zz(0.000001, 0.000001, 0.000001);
    FILE *f = fopen("/Users/kk/ClionProjects/RTracer/kitchen/kitchen.aff", "r");
    parse *parse1 = new parse();
    parse1->viParseFile(f);
    interval = (world->endtime - world->startime) / (world->numoframes);

    ofstream dataFile;

    dataFile.open("/Users/kk/ClionProjects/RTracer/kitchen/ceshi.ppm", ios::trunc);
    if (!dataFile) {
        cout << "error open" << endl;
        exit(0);
    }

    dataFile << "P3\n" << world->width << " " << world->height << "\n255\n";

//    double worldtime = world.startime;

    //   Camera cc = *ccam;
//

    vector<Triangle *> tmp;

    int hitablesize = world->hitableList.size();
    for (int i = 0; i < hitablesize; i++) {
        world->hitableList[i]->GetPosition(curtm);
    };

    int samplenum = 3 ;
//    double max1,max2,max3=0;

    ccam->GetCameraPosition(curtm, Animation_list);
 //   Hitablebox *hbvh = new Hitablebox(world->hitableList);
    //world-> hitbvh = hbvh;
//    vector<Hitable *> h = world->hitableList;
    vector<RayWithCoef *> views;
    for (int j = world->height - 1; j >= 0; j--) {
        for (int i = 0; i < world->width; i++) {
            Vec3 color(0, 0, 0);
            for (int s = 0; s < samplenum; s++) {
//                if(i == 125 && j==133 ){
//                if(i == 90 && j==40 ){
//                    int cuddlyk = 10;
//                }
                float u = float(i + drand48()) / float(800);
                float v = float(j + drand48()) / float(600);

                Vec3 threh(1, 1, 1);
//                views.push_back(
//                        new RayWithCoef(ccam->get_ray((double) i / world->width, (double) j / world->height), threh));
                views.push_back(new RayWithCoef(ccam->get_ray(u, v), threh));

                while (!views.empty()) {
                    RayWithCoef *view = views.back();
                    views.pop_back();
       //             Vec3 viewp = view->first.A;
//                    Vec3 viewd = view->first.B;
//                    Vec3 qaz = view->second;

//                RayWithCoef view_refract(view);
                    if (view->second < zz) {
                        delete view;
                        continue;
                    }
                    RayWithCoef *view_reflect = new RayWithCoef(view->first,view->second);
                    RayWithCoef *view_refract = new RayWithCoef(view->first,view->second);
                    color += world->shade(view, view_reflect, view_refract, world->ambient_light);

                    if (!isAlmostSame(view->first.A, view_reflect->first.origin()))
                        views.push_back(view_reflect);
                    else
                        delete view_reflect;
                    if (!isAlmostSame(view->first.A, view_refract->first.origin()))
                        views.push_back(view_refract);
                    else
                        delete view_refract;
                }
            }

//

//            inline double clamp(double x) {
//                return x < 0 ? 0 : (x > 1 ? 1 : x);
//            }
//            inline int gamma(double x) {
//                return int(pow(clamp(x), 1/2.2) * 255 + 0.5);
//            }
            int ir = int(255.99 * (color[0])/samplenum);
            int ig = int(255.99 * (color[1])/samplenum);
            int ib = int(255.99 * (color[2])/samplenum );


             if (ir == 0 && ig == 0 && ib == 0) {
                    ir = int(255.99 * world->backcolor[0]);
                    ig = int(255.99 * world->backcolor[1]);
                    ib = int(255.99 * world->backcolor[2]);
                }

                if (i == j)
                    cout << ir << endl;
                dataFile << ir << " " << ig << " " << ib << "\n";
            }
        }



    dataFile.close();
    delete parse1;
}