#include "esfera_utils.h"
#include <math.h>

void CalculaVolume (float R, float *volume){
    *volume = 4.0/3.0 * PI * pow(R, 3);
}
void CalculaArea (float R, float *area){
    *area = 4.0 * PI * pow(R, 2);
}