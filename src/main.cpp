
#include <iostream>
#include <cmath> 
#include "func.h"
#include "vector2.h"
#include "vector3.h"
#include <ncurses.h>

int main() {

	initscr();
	noecho();
	curs_set(0);
	cbreak();
	int width, height;
	getmaxyx(stdscr, height, width);

    float aspect = (float)width / height;
    float pixelAspect = 11.0f / 24.0f;
    char gradient[] = " .:!/r(l1#4H9W8$@";
    int gradientSize = sizeof(gradient) - 2;

    char* screen = new char[width * height + 1];
    screen[width * height] = '\0';


    for (int t = 0; t < 100000; t++){
        vector3 light = norm(vector3(-0.5, 0.5, -1.0));
        vector3 spherePos = vector3(0, 3, 0);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++){
                vector2 uv = vector2(i, j) / vector2(width, height) * 2.0f - 1.0f;
                uv.x *= aspect * pixelAspect;
                vector3 ro = vector3(-6, 0, 0);
                vector3 rd = norm(vector3(2, uv));

                ro = rotateY(ro, 0.25);
				rd = rotateY(rd, 0.25);
				ro = rotateZ(ro, t * 0.01);
				rd = rotateZ(rd, t * 0.01);

                vector3 boxN = 0;
                float diff = 1;
				for (int k = 0; k < 5; k++) {
                    float minIt = 99999;
					vector2 intersection = sphere(ro - spherePos, rd, 1);
					vector3 n = 0;
					float albedo = 1;
					if (intersection.x > 0) {
						vector3 itPoint = ro - spherePos + rd * intersection.x;
						minIt = intersection.x;
						n = norm(itPoint);
					}
					vector3 boxN = 0;
					intersection = box(ro, rd, 1, boxN);
					if (intersection.x > 0 && intersection.x < minIt) {
						minIt = intersection.x;
						n = boxN;
					}
					intersection = plane(ro, rd, vector3(0, 0, -1), 1);
					if (intersection.x > 0 && intersection.x < minIt) {
						minIt = intersection.x;
						n = vector3(0, 0, -1);
						albedo = 0.5;
					}
					if (minIt < 99999) {
						diff *= (dot(n, light) * 0.5 + 0.5) * albedo;
						ro = ro + rd * (minIt - 0.01);
						rd = reflect(rd, n);
					}
					else break;
                }
                int color = (int)(diff * 20);
				color = clamp(color, 0, gradientSize);
				char pixel = gradient[color];
				screen[i + j * width] = pixel;
                
            }
        }
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				mvaddch(j, i, screen[i + j * width]);
				refresh();
			}
		}
    }
    getchar();
    
}
