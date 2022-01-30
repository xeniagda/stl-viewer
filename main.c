#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "stl.h"
#include "render.h"

#define lenof(arr) (sizeof(arr))/(sizeof((arr)[0]))
char *BRIGHTNESS[] = {
    " ",
    "\033[38;5;232m█",
    "\033[38;5;233m█",
    "\033[38;5;234m█",
    "\033[38;5;235m█",
    "\033[38;5;236m█",
    "\033[38;5;237m█",
    "\033[38;5;238m█",
    "\033[38;5;239m█",
    "\033[38;5;240m█",
    "\033[38;5;241m█",
    "\033[38;5;242m█",
    "\033[38;5;243m█",
    "\033[38;5;244m█",
    "\033[38;5;245m█",
    "\033[38;5;246m█",
    "\033[38;5;247m█",
    "\033[38;5;248m█",
    "\033[38;5;249m█",
    "\033[38;5;250m█",
    "\033[38;5;251m█",
    "\033[38;5;252m█",
    "\033[38;5;253m█",
    "\033[38;5;254m█",
    "\033[38;5;255m█",
};

int HEIGHT = 50;
int WIDTH = 70;

void display(Scene *scene) {
    char output_buf[50000];
    int i = 0;

    for (float ry = 0; ry < HEIGHT; ry++) {
        for (float rx = 0; rx < WIDTH; rx++) {
            float vy = -(2 * (ry / HEIGHT) - 1);
            float vx = 0.7 * (2 * (rx / WIDTH) - 1);

            Ray r = Scene_get_ray(scene, vx, vy);
            Triangle *coll = Scene_cast_ray(scene, &r);

            float brightness = Scene_get_brightness(scene, coll, &r);

            char *b;
            if (brightness >= 1) {
                b = BRIGHTNESS[lenof(BRIGHTNESS)-1];
            } else if (brightness < 0) {
                b = BRIGHTNESS[0];
            } else {
                b = BRIGHTNESS[(int) (brightness * lenof(BRIGHTNESS))];
            }
            strcpy(output_buf + i, b);
            i += strlen(b);
        }
        output_buf[i++] = '\n';
    }
    output_buf[i] = 0;
    printf("%s", output_buf);
}

int main(int argc, char *argv[]) {
    char *path = "test_model.stl";
    if (argc == 2) {
        path = argv[1];
    }

    FILE *test_file = fopen(path, "r");
    if (test_file == NULL) {
        puts("file not found :<");
        return 1;
    }

    fseek(test_file, 0, SEEK_END);
    long f_size = ftell(test_file);
    fseek(test_file, 0, SEEK_SET);

    char *data = malloc(f_size);
    fread(data, f_size, 1, test_file);

    fclose(test_file);

    STL_Object stl;
    int err;
    if ((err = STL_read(data, f_size, &stl))) {
        dbg_print_stl_error(err);
    }


    clock_t start = clock();

    for (int i = 0; ; i++ ) {
        clock_t cur = clock();

        float time_delta = ((float) (cur - start)) / CLOCKS_PER_SEC;

        float f = (float) time_delta * 6.28 / 10;
        float r = 234;

        Scene scene = {
            .obj = stl,
            .light_source = { 100, 100, 62 }, // { r * sin(f+1), r * cos(f+1), 50  },
            .camera_origin = { -r * sin(f), -r * cos(f), 62 },
            .camera_map = {
                .col1 = { cos(f), sin(f), 0 },
                .col2 = { -sin(f), cos(f), 0 },
                .col3 = { 0, 0, 1 },
            },
            .camera_fov = 0.69,
        };
        Scene_presort(&scene);

        printf("\033[1;1H");
        display(&scene);

        printf("\033[38;5;244m%.1f FPS | %s | %d tris  \n", i / time_delta, path, stl.n_tris);

        if (time_delta > 10) {
            return 100;
        }
    }
}

