# project_rect

Simple [openFrameworks](https://openframeworks.cc/) app to project adjustable rectangles

## Configuration

Update the following in `src/ofApp.h`:
```
#define PROJECTION_SCREEN_OFFSET 1920

#define PROJECTION_SCREEN_WIDTH 1280
#define PROJECTION_SCREEN_HEIGHT 800
```
According to your projection resolution. The app assumes you are using a double sided display, and the projection screen is your secondary display. Change `PROJECTION_SCREEN_OFFSET` to be the width of your **main** display.

## How to use

To run:
```
make && make run
```

Press 0/1/2/3 to switch the active rectangle.

Press Enter to start adding vertices. Click the left mouse button to add a vertex. If four vertices are already present, clicking will replace the last vertex with a new one in the current location.

You can drag existing vertices to change their position. To do so, you must be **out** of adding vertices mode.

Press h/s/b to enter Hue/Saturation/Brightness mode. Then press UP/DOWN to change the corresponding HSB value of the active rectangle

#### HSB Definition

* **Hue** refers to the 'color' in the rainbow sense, moving from red through yellow through; green through blue through purple through red, looping around again.
* **Saturation** refers to the intensity of the color. high saturation means intense color,low saturation means washed out or black and white.    
* **Brightness** refers to how light or dark the color is. high brightness means a bright color, low brightness is dark. if the brightness is 0 the resulting color will be black, regardless of the values for hue or saturation.
