#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832
#endif

float A = 0.0;
float B = 0.0;
float C = 0.0;

const float R = 20; //major axis of the torus
const float r = 10; //minor axis;
const int screenWidth = 100, screenHeight = 40;
const float increment = 0.06; //smaller --> more densly plotting points

const float distToObj = 120;
const float distToScreen = 40; // calculated with: (screenWidth * distToObj)/(1.5 * 2*(R+r)))) to keep the viewport 1.5x the width of the max 2D projection

float zBuffer[100*40];
char buffer[100*40];

void sigint_handler(int sig);
void calculatePoint(float x, float y, float z, char ch);

int main() {
    signal(SIGINT, sigint_handler); //set up sigint handler for cleaner program quits on C-c
    printf("\e[?25l"); //hide cursor

    while (1) {
        memset(buffer, ' ', screenHeight*screenWidth); //clear the frame and z buffers
        memset(zBuffer, 0, screenHeight*screenWidth * sizeof(float)); //need to account for 4-byte length of floats

        //precompute trig
        float cosA = cos(A), cosB = cos(B), cosC = cos(C);
        float sinA = sin(A), sinB = sin(B), sinC = sin(C);

        for (float theta = 0; theta <= 2*M_PI; theta += increment) { //these angle loops construct the torus

            float costheta = cos(theta), sintheta = sin(theta);

            for (float phi = 0; phi <= 2*M_PI; phi += increment) {

                float cosphi = cos(phi), sinphi = sin(phi);

                //------torus construction math------
                float x = (R + r*costheta)*cosphi; //the unrotated xyz coords of of the torus
                float y = r*sintheta;
                float z = (R + r*costheta)*sinphi;

                //---------3D rotation math----------
                float xr = x*(cosB*cosC) + y*(sinA*sinB*cosC + cosA*sinC) + z*(sinA*sinC - cosA*sinB*cosC); 
                float yr = x*(-cosB*sinC) + y*(cosA*cosC - sinA*sinB*sinC) + z*(cosA*sinB*sinC + sinA*cosC);
                float zr = x*(sinB) - y*(sinA*cosB) + z*(cosA*cosB);


                //----------2D projection math---------------------
                zr = zr + distToObj; //first push the z component back so the object is in front of camera
                float ooz = 1/zr; //calculate 1/z for projection below

                int xp = (int)((screenWidth/2) + distToScreen*xr*ooz*2); //cast to int because these are the 2D grid values. x needs to be doubled due to aspect ratio
                int yp = (int)((screenHeight/2) - distToScreen*yr*ooz); //y is negative since higher terminal row numbers = lower down the screen

                //----------illluminance math---------------------

                float xn = costheta*cosphi;
                float yn = sintheta;
                float zn = costheta*sinphi;

                float I = xn*(sinC*cosB + sinB) + yn*(sinC*sinB*sinA + cosC*cosA - cosB*sinA) + zn*(sinC*sinB*cosA - cosC*sinA - cosB*cosA);

                //----------rendering logic----------------------
                int idx = xp + screenWidth * yp; //this is "row-major ordering", or, a way to encode 2D data in 1D memory per known row-length

                if (idx >= 0 && idx < screenHeight*screenWidth) {
                    if (I > 0) { //"backface culling" -- only render faces that are pointing to us
                        if (ooz > zBuffer[idx]) { //"z-sorting" : ensures we only render the frontmost of many potentially-overlaid points
                            zBuffer[idx] = ooz;

                            int luminance_index = I*8; //maps the 0-sqrt(2) illuminance to a 0-11 index
                            
                            buffer[idx] = ".,-~:;=!*#$@"[luminance_index];
                        }
                    } 
                }
            }
        }

        printf("\e[H"); // move cursor to home position, this mitigates screen flicker by making the terminal overwrite last frame instead of scrolling last frame out of view
        for (int idx = 0; idx < screenHeight*screenWidth; idx++) {
            putchar(idx % screenWidth ? buffer[idx] : '\n'); //this un-encodes 1D data to 2D pixels. If index is multiple of screenwidth, means we need a newline
        }

        usleep(50000);

        A += 0.07;
        B += 0.05;
        C += 0.03;
    }

    sigint_handler(SIGINT);
    return 0;
}

void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)");
    printf("\e[2J\e[H\e[?25h");
    exit(0);
}