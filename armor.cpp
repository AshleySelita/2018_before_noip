#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#define PI 3.14159265
int dp, bg, wid;
double angle, dep1, dep2, accu1, accu2;
std::string ss, s1, s2;
int main() {
    std::cin >> s1 >> s2 >> ss;
    std::cin >> dp >> angle >> bg >> wid;
    if(!wid) {printf("We didn't penetrate their armor!"); return 0;}
    dep1 = dp * 1.25; dep2 = dp * 0.75;
    int mul(1);
    if(wid * 2 < bg) mul = 2;
    if(wid * 3 < bg) mul = 3;
    if(ss[0] == 'A') {
        switch(ss[2]) {
            case '\0':{
                angle -= 5.0*mul; break;
            }
            default:{
                angle -= 2.0*mul; break;
            }
        }
        if(angle < 0) angle = 0;
        if(angle >= 70) {printf("We didn't penetrate their armor!"); return 0;}
    }
    if(ss[2] == 'A' && angle >= 85) {printf("We didn't penetrate their armor!"); return 0;}
    accu1 = dep1 * cos(angle * PI / 180.0); accu2 = dep2 * cos(angle * PI / 180.0);
    if(accu1 >= wid && accu2 >= wid) {printf("Penetration!");}
    else if(accu1 >= wid && accu2 < wid) {printf("Server is important~");}
    else printf("We didn't penetrate their armor!");
    return 0;
}