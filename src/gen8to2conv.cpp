/*!
 * Gen8to2conv
 * References:
 * http://dlib.net/dlib/pixel.h.html#rgb_pixel
 * https://www.nongnu.org/pngpp/doc/0.2.9/
 * https://stackoverflow.com/questions/299267/image-scaling-and-rotating-in-c-c
 * Note: consider bilinear-image-scaling for resizing
 */

#include "../png++/png.hpp"
#include <string>
#include <cmath>

using namespace std;

void pan(png::image<png::rgb_pixel> &image, png::image<png::rgb_pixel> &new_image, 
	int x1, int y1, int x2, int y2, int rounding, int pan_x, int pan_y, int pr) {
	int max_height = image.get_height(); int max_width = image.get_width(); int shade = 1;

	// pan
	if (pan_x!=0 || pan_y!=0) {
		for (png::uint_32 y = y1; y < max_height && y < y2; y++) {
		    for (png::uint_32 x = x1; x < max_width && x < x2; x++) {
		    	if (x+pan_x>=0 && x+pan_x<max_width && y+pan_y>=0 && y+pan_y<max_height) {
			        new_image[y][x].red = image[y+pan_y][x+pan_x].red*shade;
			        new_image[y][x].green = image[y+pan_y][x+pan_x].green*shade;
			        new_image[y][x].blue = image[y+pan_y][x+pan_x].blue*shade;	    		
		    	}
		    	else if (x+pan_x>=0 && x+pan_x<max_width) {
			        new_image[y][x].red = image[y][x+pan_x].red*shade;
			        new_image[y][x].green = image[y][x+pan_x].green*shade;
			        new_image[y][x].blue = image[y][x+pan_x].blue*shade;	    		
		    	}
		    	else if (y+pan_y>=0 && y+pan_y<max_height) {
			        new_image[y][x].red = image[y+pan_y][x].red*shade;
			        new_image[y][x].green = image[y+pan_y][x].green*shade;
			        new_image[y][x].blue = image[y+pan_y][x].blue*shade;
		    	}
		    }
		}
	}	
}

void zoom(png::image<png::rgb_pixel> &image, png::image<png::rgb_pixel> &new_image, 
	int x1, int y1, int x2, int y2, int rounding, float zoom_x, float zoom_y, int pan_x, int pan_y) {
	int max_height = image.get_height(); int max_width = image.get_width();
	zoom_x = 1/zoom_x; zoom_y = 1/zoom_y;	

	// zoom
	if (zoom_x!=1 || zoom_y!=1) {
		for (png::uint_32 y = y1; y < max_height && y < y2; y++) {
		    for (png::uint_32 x = x1; x < max_width && x < x2; x++) {
		    	if (x*zoom_x<max_width && y*zoom_y<max_height) {
			    	new_image[y][x].red = image[(y*zoom_y)+pan_y][(x*zoom_x)+pan_x].red;
			    	new_image[y][x].green = image[(y*zoom_y)+pan_y][(x*zoom_x)+pan_x].green;
			    	new_image[y][x].blue = image[(y*zoom_y)+pan_y][(x*zoom_x)+pan_x].blue;
		    	}
		    }
		}
	}	
}

float euc_dist(float x1, float x2, float y1, float y2) {
	// euclidean distance for oval shape

	return sqrt(pow(x2-x1,2)+(pow(y2-y1,2)*2.4));
}

void mouth_adj(png::image<png::rgb_pixel> &mouth, png::image<png::rgb_pixel> &new_image, 
	int x1, int y1, int x2, int y2) {
	int max_height = new_image.get_height(); int max_width = new_image.get_width();
	float x_center = ((float)x1+(float)x2)/2; float y_center = ((float)y1+(float)y2)/2;
	int shade = 1;
	float red_diff = (float) new_image[3170][2500].red / (float) mouth[3170][2500].red;
	float green_diff = (float) new_image[3170][2500].green / (float) mouth[3170][2500].green;
	float blue_diff = (float) new_image[3170][2500].blue / (float) mouth[3170][2500].blue;

	for (png::uint_32 y = y1; y < max_height && y < y2; y++) {
	    for (png::uint_32 x = x1; x < max_width && x < x2; x++) {
	    	if (euc_dist((float)x, x_center, (float)y, y_center) < 320) {
		    	new_image[y][x].red = mouth[(y)][(x)].red*red_diff;
		    	new_image[y][x].green = mouth[(y)][(x)].green*green_diff;
		    	new_image[y][x].blue = mouth[(y)][(x)].blue*blue_diff;
		    	//printf("%f %f %f\n",red_diff,green_diff,blue_diff);
		    	//printf("%f %f %f %f %f\n",euc_dist((float)x, x_center, (float)y, y_center),(float)x, x_center, (float)y, y_center);
	    	}
	    	//printf("%f\n",euc_dist((float)x, x_center, (float)y, y_center));
	    }
	}
}

void copy_image(png::image<png::rgb_pixel> &image, png::image<png::rgb_pixel> &new_image, 
	int max_height, int max_width, int y1, int x1, int y2, int x2, string direction) {
	for (png::uint_32 y = 0; y < max_height; ++y) {
	    for (png::uint_32 x = 0; x < max_width; ++x) {
	    	if (direction == "old->new") {
	    		new_image[y][x] = image[y][x];
	    	}
	    	if (direction == "new->old") {
	    		image[y][x] = new_image[y][x];
	    	}
	    }
	}
}

void rgb_adj(png::image<png::rgb_pixel> &image, png::image<png::rgb_pixel> &new_image,
	int max_height, int max_width, float red_adj, float green_adj, float blue_adj) {
	// adjust rgb for orig image to match new image

	for (png::uint_32 y = 0; y < max_height; y++) {
	    for (png::uint_32 x = 0; x < max_width; x++) {
	    	new_image[y][x].red = image[y][x].red*red_adj;
	    	new_image[y][x].green = image[y][x].green*green_adj;
	    	new_image[y][x].blue = image[y][x].blue*blue_adj;
	    }
	}	
}

int main() {
	png::image<png::rgb_pixel> gen8head("input/gen8textures/g8fbasefacemapd_1001.png");
	int mh = gen8head.get_height(); // max height
	int mw = gen8head.get_width(); // max width
	png::image<png::rgb_pixel> gen2newhead(mh, mw);
	png::image<png::rgb_pixel> gen2head("input/gen2textures/v5breeheadm.png");
	png::image<png::rgb_pixel> gen2limbs("input/gen2textures/v5breelimbsm.png");
	png::image<png::rgb_pixel> gen2newlimbs(mh, mw);	
	png::image<png::rgb_pixel> gen2torso("input/gen2textures/v5breetorsom.png");
	png::image<png::rgb_pixel> gen2newtorso(mh, mw);
	png::image<png::rgb_pixel> gen2eyes("input/gen2textures/v5breeeyes7m.png");
	int mh2 = gen2eyes.get_height();
	int mw2 = gen2eyes.get_width();
	png::image<png::rgb_pixel> gen2neweyes(mh2, mw2);
	png::image<png::rgb_pixel> gen2mouth("input/gen2textures/v5breeinmouthm.png");
	png::image<png::rgb_pixel> gen2newmouth(mh2, mw2);

	// color balance between gen8 and gen2
	float red_adj = (float) gen8head[1500][2000].red / (float) gen2torso[2600][1950].red;
	float green_adj = (float) gen8head[1500][2000].green / (float) gen2torso[2600][1950].green;
	float blue_adj = (float) gen8head[1500][2000].blue / (float) gen2torso[2600][1950].blue;

	// update face texture
	// copy forehead and move up
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "old->new");
	pan(gen8head, gen2newhead, 0, 0, mw, mh-3000, 0, 0, 500, 0);
	// stretch forehead vertically
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	zoom(gen8head, gen2newhead, 0, 0, mw, mh-2300, 0, 1, 1.64, 0, 0);
	// stretch forehead horizontally
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	zoom(gen8head, gen2newhead, 0, 0, mw, mh-2300, 0, 1.1, 1, 0, 0);
	// shift forehead left
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	pan(gen8head, gen2newhead, 0, 0, mw, mh-2300, 0, 200, 0, 0);
	// shift face below forehead down
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	pan(gen8head, gen2newhead, 0, 1800, mw, mh, 0, 0, -40, 1);
	// stretch mouth
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	zoom(gen8head, gen2newhead, 1000, 2840, mw-1000, mh, 0, 1.1, 1.1, 175, 250);
	// shrink right eye
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	zoom(gen8head, gen2newhead, 1000, 2000, mw-2092, mh-1532, 0, 0.95, 1, -125, 0);	
	// shrink left eye
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	zoom(gen8head, gen2newhead, 2092, 2000, mw-1000, mh-1532, 0, 0.95, 1, -100, -10);
	// adjust mouth
	copy_image(gen8head, gen2newhead, mh, mw, 0, 0, mh, mw, "new->old");
	mouth_adj(gen2head, gen2newhead, 1724, 2917, 2378, 3323);
	gen2newhead.write("output/headm.png");

	// update limbs texture
	rgb_adj(gen2limbs, gen2newlimbs, mh, mw, red_adj, green_adj, blue_adj);
	gen2newlimbs.write("output/limbsm.png");

	// update torso texture
	rgb_adj(gen2torso, gen2newtorso, mh, mw, red_adj, green_adj, blue_adj);
	gen2newtorso.write("output/torsom.png");

	// update torso texture
	rgb_adj(gen2eyes, gen2neweyes, mh2, mw2, 1, 1, 1);
	gen2neweyes.write("output/eyesm.png");

	// update mouth texture
	rgb_adj(gen2mouth, gen2newmouth, mh2, mw2, 1, 1, 1);
	gen2newmouth.write("output/mouthm.png");

	printf("completed\n");

	return 0;
}