#include <stdio.h>
#include "../3rd-party/fenster/fenster.h"

#define W 1024
#define H 600

#define WHITE 0xffffff
#define RED 0xff0000
#define BLUE 0x0000ff

#define FPS 60

void draw_rect(struct fenster* f, int x, int y, int w, int h, uint32_t colour) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			fenster_pixel(f, i+x, j+y) = colour;
		}
	}
}

uint_fast8_t main(int argc, char** argv) {
	uint32_t buf1[W*H] = {0};
	struct fenster f = {
		.title = "Game Window",
		.width = W,
		.height = H,
		.buf=buf1
	};
	fenster_open(&f);
	
	draw_rect(&f, 0, 0, W, H, RED);	
	draw_rect(&f, 0, 0, 64, 64, WHITE);	
	draw_rect(&f, 64, 64, 128, 256, BLUE);	

	int64_t now, prev = 0;

	while (fenster_loop(&f) == 0) {
		now = fenster_time();
		fenster_sleep(1000 / FPS);
		float dt = (now - prev) / 1000.f;
		prev = now;
	}
	fenster_close(&f);

	return 0;
}
