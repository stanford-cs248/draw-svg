# Stanford CS248 Assignment 1: A Simple SVG Rasterizer

![Teaser](misc/teaser.png)

## Overview

In this project, you will implement a simple software rasterizer that draws points, lines, triangles, and bitmap images. When you are done, you will have a viewer that supports basic features of the [Scalable Vector Graphics](https://en.wikipedia.org/wiki/Scalable_Vector_Graphics) (SVG) format that is now widely used on the internet.

## Due date
The assignment is due Jan 20th at 11:59:59 PM.

## Submission instruction
Zip your assignment directory (please delete the `build` directory to reduce the file size), and upload your zipped file to [Gradescope](https://www.gradescope.com/). Please also include a brief writeup (can be a few lines), including all the SUNET ids of the members on your team, the tasks you completed and comments and/or considerations you want to let us know (optional). **One team only needs one submission, please tag your teammates in your submission**. 

## Getting started

We will be distributing assignments with git. You can find the repository for this assignment at https://github.com/stanford-cs248/draw-svg.git. If you are unfamiliar with git, here is what you need to do to get the starter code:

```
$ git clone https://github.com/stanford-cs248/draw-svg.git
```

If you are using Windows, you can use [TortoiseGit](https://tortoisegit.org/). After installing it, right-click on the directory of your choice and click `Git Clone...` to perform the same operation (put `https://github.com/stanford-cs248/draw-svg.git` inside of `URL` box).
This will create a folder with all the source files.

### Build Instructions

In order to ease the process of running on different platforms, we will be using [CMake](http://www.cmake.org/) for our assignments. You will need a CMake installation of version 2.8+ to build the code for this assignment. The project can be run by SSH'ing to rice.stanford.edu with your SUNet ID, password, and two-step authentication using MobaXterm (remember to turn on X11 forwarding). It should also be relatively easy to build the assignment and work locally on your OSX or 64-bit version of Linux or Windows.

#### OS X/Linux Build Instructions

If you are working on OS X and do not have CMake installed, we recommend installing it through [Homebrew](http://brew.sh/): `$ brew install cmake`.  Note that the following command assumes you've already installed the Homebrew package manager available at: <http://brew.sh/>. You may also need the freetype package `$ brew install freetype`.

**Note: if you are working on new MAC M1, please rename `draw-svg/src/reference/libdrawsvgref_osx_M1.a` to `draw-svg/src/reference/libdrawsvgref_osx.a` to replace the old file.**

If you are working on Linux, you should be able to install dependencies with your system's package manager as needed (you may need cmake and freetype, and possibly others).

##### To install freetype on Linux:

```
$ sudo apt-get install libfreetype6
$ sudo apt-get install libfreetype6-dev
```

##### To install other possible dependencies (RandR, etc) on Linux:

```
$ sudo apt-get install libglu1-mesa-dev
$ sudo apt-get install xorg-dev
```

##### To build your code for this assignment on OS X or Linux:

```
$ cd draw-svg && mkdir build && cd build
$ cmake ..
$ make
```

These 3 steps (1) create an out-of-source build directory, (2) configure the project using CMake, and (3) compile the project. If all goes well, you should see an executable `drawsvg` in the build directory. As you work, simply typing `make` in the build directory will recompile the project.

#### Windows Build Instructions

You need to install the latest version of [CMake](http://www.cmake.org/) and [Visual Studio Community 2022](https://www.visualstudio.com/) (We have tested windows build with 2022). Make sure you install **Desktop development with C++** in Visual Studio. You can find the installation instructions [here](https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=vs-2017). Already have Visual Studio installed and don't have that workload/aren't sure? See how to modify workloads [here](https://docs.microsoft.com/en-us/visualstudio/install/modify-visual-studio?view=vs-2017#modify-workloads). 

After installing CMake and Visual Studio, let's start with building in CMake. Replace `SOURCE_DIR` to the cloned directory (`draw-svg/` in our case, NOT `src/`), and `BUILD_DIR` to `draw-svg/build`.
<!-- 
![Sample locations](misc/cmake_initial_setup.png?raw=true)
 -->
Then, press `Configure` button, select **Visual Studio 17 2022** for generator and **x64** for platform, and you should see `Configuring done` message. Then, press `Generate` button and you should see `Generating done`.

<!-- ![Sample locations](misc/cmake_final_setup.png?raw=true)
 -->
This should create a `build` directory with a Visual Studio solution file in it named `drawsvg.sln`. You can double-click this file to open the solution in Visual Studio.

Note: to avoid the linking error when building x64 (e.g. LNK4272: library machine type 'x86' conflicts with target machine type 'x64', LNK1104: cannot open file freetype.lib.), please make the following changes to your draw-svg project properties (right click `drawsvg` project in the Solution Explorer sidebar to open Properties).
```
Properties -> Linker -> Input -> edit -> change freetype.lib to freetype_win64.lib
```

If you plan on using Visual Studio to debug your program, you must change `drawsvg` project in the Solution Explorer sidebar as the startup project by right-clicking on it and selecting `Set as StartUp Project`. 

For setting the commandline arguments to the project, right-click `drawsvg` project again, select `Properties`, go into the `Debugging` tab, and set the value in `Command Arguments`. If you want to run the program with the basic svg folder, you can set this command argument to `..\..\svg\basic`. After setting all these, you can hit F5\press `Local Windows Debugger` button to build your program and run it with the debugger.

You should also change the build mode to `Release` from `Debug` occasionally by clicking the Solution Configurations drop down menu on the top menu bar, which will make your program run faster. Note that you will have to edit the Linker and set `Command Arguments` again if you change the build mode. Note that your application must run properly in both debug and release build.

### Using the Mini-SVG Viewer App

When you have successfully built your code, you will get an executable named **drawsvg**. The **drawsvg** executable takes exactly one argument from the command line. You may load a single SVG file by specifying its path. For example, to load the example file `svg/basic/test1.svg`:

```
./drawsvg ../svg/basic/test1.svg
```

When you first run the application, you will see a picture of a flower made of a bunch of blue points. The starter code that you must modify is drawing these points. Now press the R key to toggle display to the staff's reference solution to this assignment.

While looking at the reference solution, hold down your primary mouse button (left button) and drag the cursor to pan the view. Cursor location will be printed as a debugging utility to console when you click with your primary mouse button. You can also use scroll wheel to zoom the view. (You can always hit SPACE to reset the viewport to the default view conditions). You can also compare the output of your implementation with that of the reference implementation. To toggle the diff view, press 'D'. We have also provided you with a "pixel-inspector" view to examine pixel-level details of the currently displayed implementation more clearly. The pixel inspector is toggled with the 'Z' key.

For convenience, `drawsvg` can also accept a path to a directory that contains multiple SVG files. To load files from `svg/basic`:

```
./drawsvg ../svg/basic
```

The application will load up to nine files from that path and each file will be loaded into a tab. You can switch to a specific tab using keys 1 through 9.

### Summary of Viewer Controls

A table of all the keyboard controls in the **draw** application is provided below.

| Command                                  |  Key  |
| ---------------------------------------- | :---: |
| Go to tab                                | 1 ~ 9 |
| Switch to sw renderer                    |   S   |
| Toggle sw renderer impl (student soln/ref soln) |   R   |
| Regenerate mipmaps for current tab (student soln) |   ;   |
| Regenerate mipmaps for current tab (ref soln) |   '   |
| Increase samples per pixel               |   =   |
| Decrease samples per pixel               |   -   |
| Toggle text overlay                      |   `   |
| Toggle pixel inspector view              |   Z   |
| Toggle image diff view                   |   D   |
| Normalize image diff view while pressed  | SHIFT |
| Reset viewport to default position       | SPACE |

### Grading

The assignment is divided into seven basic tasks and seven advanced tasks, which are described below in the order the course staff suggests you to attempt them.  Finishing the basic tasks will result in a grade of 92 points (out of 100 max) on the assignment. In general the staff views scores in the low 90's as very solid student work, and you can think of that level of effort as corresponding to a solid A- letter grade in the course.  For students that have more time and really want to learn more graphics, you can earn extra points by tackling the advanced tasks. The final grade for this assigment will be clamped at 100 pts. (And yes, we can always make exceptions for truly great work! ;-))

Draw-svg is made by humans, and will be graded by humans (the staff) looking at your results. We are not asking for a pixel-perfect recreation of the reference solution. Floating-point arithmetic on different architectures may lead to subtle inconsistencies that may make your solution a few pixels different than the reference. You should instead aim to have the bigger picture down: lines are in the general same area and thickness, no gaps in triangle fills, etc. It should be clear that if we held the two images together side by side, there shouldn't be a major difference to the human eye (we're looking for eye-level differences, not pixel-level differences). If you are unsure about grading, feel free to ask on the class discussion board.

### Friendly Advice from your TAs 

- As always, start early. There is a lot to implement in this assignment, so don't fall behind!
- Open `draw-svg/CS248/docs/html/index.html` with a browser to see documentation of many utility classes, **especially the ones related to vectors and matrices**.
- Be careful with memory allocation, as frequent heap allocations can severely degrade performance.
- Be careful with types (e.g. float, double, int, uint8_t), casting, and using the right functions for each type. Take note of the `uint8_to_float` and `float_to_uint8` functions in `texture.cpp`, which you may find helpful for later tasks.
- While C has many pitfalls, C++ introduces even more wonderful ways to shoot yourself in the foot. Later assignments will require you to use C++ classes and objects, so take the time to learn the new features C++ introduces. 
- Currently, `draw-svg` does not support rendering `<circle>` svg elements (which is different from `<ellipse>`).

#### Getting Acquainted with the Starter Code

Before you start, here are some basic information on the structure of the starter code.

Most of your work will be constrained to implementing part of the class `SoftwareRendererImp` in `software_renderer.h` and `software_renderer.cpp`. The most important method is `draw_svg` which (not surprisingly) accepts an SVG object to draw. An SVG file defines its canvas (which defines a 2D coordinate space), and specifies a list of shape elements (such as points, lines, triangles, and images) that should be drawn on that canvas. Each shape element has a number of style parameters (e.g., color) as well as a modeling transform used to determine the element's position on the canvas. You can find the definition of the SVG class (and all the associated `SVGElements`) in `svg.h`. Notice that one type of `SVGElement` is a group that itself contains child elements. Therefore, you should think of an SVG file as defining a tree of shape elements. (Interior nodes of the tree are groups, and leaves are shapes.)

Another important method on the `SoftwareRendererImp` class is `set_render_target()`, which provides your code a buffer corresponding to the output image (it also provides width and height of the buffer in pixels, which are stored locally as `target_w` and `target_h`). This buffer is often called the "render target" in many applications, since it is the "target" of rendering commands. **We use the term pixel here on purpose because the values in this buffer are the values that will be displayed on screen.** Pixel values are stored in row-major format, and each pixel is an 8-bit RGBA value (32 bits in total). Your implementation needs to fill in the contents of this buffer when it is asked to draw an SVG file.

`set_render_target()` is called whenever the user resizes the application window.

#### A Simple Example: Drawing Points

You are given starter code that already implements drawing of 2D points. To see how this works, begin by taking a look at `draw_svg()` in `software_renderer.cpp`. The method accepts an SVG file, and draws all elements in the SVG file via a sequence of calls to `draw_element()`. For each element `draw_element()` inspects the type of the element, and then calls the appropriate draw function. In the case of points, that function is `draw_point()`.

The position of each point is defined in a local coordinate frame, so `draw_point()` first transforms the input point into its screen-space position (see Vector2D `p_screen = transform(p)`). This transform is set at the beginning of `draw_svg()`. In the starter code, this transform converts from the svg canvas' coordinate system to screen coordinates. You will need to handle more complex transforms to support more complex SVG files and implement mouse viewing controls later in the assignment.

The function `rasterize_point()` is responsible for actually drawing the point. In this assignment we define screen space for an output image of size `(target_w, target_h)` as follows:

- `(0, 0)` corresponds to the top-left of the output image
- `(target_w, target_h)` corresponds to the bottom-right of the output image
- **Please assume that screen sample positions are located at half-integer coordinates in screen space. That is, the top-left sample point is at coordinate (0.5, 0.5), and the bottom-right sample point is at coordinate (target_w-0.5, target_h-0.5).**

![Sample locations](misc/coord_1spp.png?raw=true)

To rasterize points, we adopt the following rule: a point covers at most one screen sample: the closest sample to the point in screen space. This is implemented as follows, assuming (x, y) is the screen-space location of a point.

```
int sx = (int) floor(x);
int sy = (int) floor(y);
```

Of course, the code should not attempt to modify the render target buffer at invalid pixel locations.

```
if ( sx < 0 || sx >= target_w ) return;
if ( sy < 0 || sy >= target_h ) return;
```

If the points happen to be on screen, we fill in the pixel with the RGBA color associated with the point.

```
  render_target[4 * (sx + sy * target_w)    ] = (uint8_t) (color.r * 255);
  render_target[4 * (sx + sy * target_w) + 1] = (uint8_t) (color.g * 255);
  render_target[4 * (sx + sy * target_w) + 2] = (uint8_t) (color.b * 255);
  render_target[4 * (sx + sy * target_w) + 3] = (uint8_t) (color.a * 255);
```

At this time the starter code does not correctly handle transparent points. In order to handle transparent points, you should call `fill_pixel()`, which handles alpha blending for you.

**Now that you understand the basics of drawing elements, let's get to work actually drawing more interesting elements than points!**


#### Task 0: Warm Up: Drawing Lines (5 pts)

In this task you will add line drawing functionality by implementing the function `rasterize_line()` in `software_renderer.cpp` instead of calling a reference solution.

We discussed a few ways to think about rasterizing a line. (Recall we talked about possible rules for what samples are considered to be "covered" by the line, and we discussed algorithms for efficiently determining what samples meet that criteria. Since line drawing is very well documented on the web, you may consult the web and use any algorithm you wish. However, your solution should:

- Handle non-integer vertex coordinates passed to `rasterize_line()`.
- Handle lines of any slope.
- Perform work proportional to the length of the line (methods that perform work for every pixel on screen or for all samples in the bounding box of the line are not acceptable solutions).

We encourage you to start with an implementation of [Bresenham's algorithm](http://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html). When you are done, your solution should be able to correctly render `basic/test2.svg`.

**Note: If you compare your initial Bresenham results with the reference implementation, you will notice that the reference solution generates smooth lines. For example, you can modify your Bresenham implementation to perform [Xiaolin Wu's line algorithm](https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm) which counts as extra credit. Otherwise, you may want to comment out your implementation and proceed with the `rasterize_line_helper()` for the following tasks to minimize the difference on the boundary when compared to reference.** 

#### Task 1: Drawing Triangles (20 pts)

In this task, you will implement `rasterize_triangle()` in `software_renderer.cpp`.

Your implementation should:

- Sample triangle coverage using the methods discussed in class. There is an exact solution to the problem of sampling triangle coverage. The position of screen sample points--at half-integer coordinates in screen space--was described above.
- To receive full credit in Task 1 your implementation should assume that a sample point on a triangle edge is covered by the triangle. Your implementation **DOES NOT** need to respect the triangle "edge rules" to avoid "double counting" as discussed in class. (but we encourage you to try!)
- Your implementation should use an algorithm that is more work efficient than simply testing all samples on screen. To receive full credit it should at least constrain coverage tests to samples that lie within a screen-space bounding box of the triangle. However, you are free to explore more efficient implementations such as the incremental tile-based method described in class, or this [hierarchical rasterizer](https://www.cs.cmu.edu/afs/cs/academic/class/15869-f11/www/readings/abrash09_lrbrast.pdf). (You will likely find that for scenes with relatively small triangles, a simple bounding box based rasterizer is about as fast as more sophisticated techniques.)
- When a triangle covers a sample, you should write the triangle's color to the location corresponding to this sample in `render_target`.

**Be careful! Note that the vertices may be in counter-clockwise or clockwise order when passed in. Using the cross-product to check orientation may be helpful.**

Once you have successfully implemented triangle drawing, you will able to draw a large number of examples. When loading an SVG, the provided code triangulates convex polyhedra into a list of triangles for you, so by implementing support for rasterizing triangles, the viewer now supports drawing any of these shapes as well. (When parsing the SVG, we convert rectangles and polygons specified in the file into lists of triangles.)

When you are done, you should be able to draw `basic/test3.svg`, `basic/test4.svg`, and `basic/test5.svg`.

#### Task 2: Anti-Aliasing Using Supersampling (20 pts)

In this task, you will extend your rasterizer to anti-alias triangle edges via supersampling. In response to the user changing the screen sampling rate (the '=' and '-' keys), the application will call `set_sample_rate()` . The parameter `sample_rate` defines the sampling rate in each dimension, so a value of 2 would correspond to a sample density of 4 samples per pixel. In this case, the samples lying within the top-left pixel of the screen would be located at locations (0.25, 0.25), (0.75, 0.25), (0.25, 0.75), and (0.75, 0.75).

![Sample locations](misc/coord_4spp.png?raw=true)

It's reasonable to think of supersampled rendering as rendering an image that is `sample_rate` times larger than the actual output image in each dimension, then resampling the larger rendered output down to the screen sampling rate after rendering is complete. To help you out, here is a sketch of an implementation. **Note: If you implemented your triangle rasterizer in terms of sampling coverage in screen-space coordinates (and not in terms of pixels), then the code changes to support supersampling should be fairly simple for triangles:**

- When rasterizing primitives such as triangles, rather than directly updating `render_target`, your rasterization should update the contents of a larger buffer (perhaps call it `supersample_target`) that holds the per-super-sample results. Yes, you will have to allocate/free this buffer yourself. Question for you to think about: when is the right time to perform this allocation in the code?
- After rendering is complete, your implementation must resample the supersampled results buffer to obtain sample values for the render target. This is often called "resolving" the supersample buffer into the render target. Please implement resampling using a simple unit-area box filter.
  Note that the function `SoftwareRendererImp::resolve()` is called by `draw_svg()` after the SVG file has been drawn. Thus it's a very convenient place to perform resampling.

When you are done, try increasing the supersampling rate in the viewer, and bask in the glory of having much smoother triangle edges.

Also observe that after enabling supersampled rendering, something might have gone very wrong with the rasterization of points and lines. (They probably appear to get thinner!) **Please modify your implementation of `fill_pixel()` which get called in rasterizing points and lines so that supersampled rendering of these primitives preserves their thickness across different supersampling rates.** (Note that the line helper function calls your `fill_pixel()`. 

**Hint: Consider having separate functions `fill_pixel()` for filling a "pixel" and `fill_sample()` for filling a "sample."**
A solution that does not anti-alias points and lines is acceptable.)

#### Task 3: Implementing Modeling and Viewing Transforms (12 pts)

##### Part 1: Modeling Transforms (6 pts)

It is common (and often very useful) to describe objects and shapes in their own local coordinate spaces and then build up more complicated objects by positioning many individual components in a single coordinate space. In this task you will extend the renderer to properly interpret the hierarchy of modeling transforms expressed in SVG files.

Recall that an SVG object consists of a hierarchy of shape elements. Each element in an SVG is associated with a modeling transform (see `SVGElement.transform` in `svg.h`) that defines the relationship between the object's local coordinate space and the parent element's coordinate space. At present, the implementation of `draw_element()`ignores these modeling transforms, so the only SVG objects your renderer has been able to correctly draw were objects that contained only identity modeling transforms.

Please modify `draw_svg()` and `draw_element()` to implement the hierarchy of transforms specified in the SVG object. (You can do this in no more than a few lines of code.)

When you are done, you should be able to draw `basic/test6.svg` and `basic/test7.svg`.

**Hint: If there is an SVGElement which is not in a group, the modeling transform should be the relationship between its local coordinate space and the canvas space. If it is in a group, the modeling transform should be the relationship between its local coordinate space and its parent element's local coordinate space. Look at how the transformation matrix in software renderer is applied, and think about how you can modify this to take into account each SVGElement's transform.**

##### Part 2: Viewing Transform (6 pts)

Notice the staff reference solution supports image pan and zoom behavior (drag the mouse to pan, use the scroll wheel to zoom). To implement this functionality in your solution, you will need to implement `ViewportImp::set_viewbox()` in `viewport.cpp`.

A viewport defines a region of the SVG canvas that is visible in the app. When the application initially launches, the entire canvas is in view. For example, if the SVG canvas is of size 400x300, then the viewport will initially be centered on the center of the canvas, and have a vertical field of view that spans the entire canvas. Specifically, the member values of the `Viewport` class will be: `x=200, y=150, span=150`.

When user actions require the viewport be changed, the application will call `update_viewbox()` with the appropriate parameters. Given this change in view parameters, you should implement `set_viewbox()` to compute a transform `canvas_to_norm` based on the new view parameters. This transform should map the SVG canvas coordinate space to a normalized space where the top left of the viewport region maps to (0,0) and the bottom right maps to (1, 1). For example, for the values `x=200,y=150, span=10`, then SVG canvas coordinate (190, 140) transforms to normalized coordinate (0, 0) and canvas coordinate (210, 160) transforms to (1, 1).

Once you have correctly implemented `set_viewbox()`, your solution will respond to mouse controls in the same way as the reference implementation.

#### Task 4: Drawing Scaled Images (20 pts)

In this task, you will implement `rasterize_image()` in `software_renderer.cpp`.

To keep things very simple, we are going to constrain this problem to rasterizing image elements that are positioned on the SVG canvas via translations and scaling, **but not rotations**. Therefore, `rasterize_image()` should render the specified image into an axis-aligned rectangle on screen whose top-level coordinate is `(x0, y0)` and whose bottom-right coordinate is `(x1, y1)`. Your implementation should adhere to the following specification:

- The image element should cover all screen samples inside the specified rectangle.
- For each image, texture space spans a [0-1]^2 domain as described in class. That is, given the example above, the mapping from screen-space to texture-space is as follows: `(x0, y0)` in screen space maps to image texture coordinate `(0, 0)` and `(x1, y1)` maps to `(1, 1)`.
- You may wish to look at the implementation of input texture images in `texture.h/.cpp`. The class `Sampler2D` provides skeleton of methods for nearest-neighbor (`sampler_nearest()`), bilinear (`sampler_bilinear()`), and trilinear filtering (`sample_trilinear()`). In this task, for each covered sample, the color of the image at the specified sample location should be computed using **bilinear filtering** of the input texture. Therefore you should implement `Sampler2D::sampler_bilinear()` in `texture.cpp` and call it from `rasterize_image()`. (However, we recommend first implementing `Sampler2D::sampler_nearest()` -- as nearest neighbor filtering is simpler and will be given partial credit.)
- As discussed in class, please assume that image pixels correspond to samples at half-integer coordinates in texture space.
- The `Texture` struct stored in the `Sampler2D` class maintains multiple image buffers corresponding to a mipmap hierarchy. In this task, you will sample from level 0 of the hierarchy: `Texture::mipmap[0]`.
- You should clamp the border (edge) pixels to the nearest valid image pixel as in GL_CLAMP_TO_EDGE.

When you are done, you should be able to draw the test svgs in `/image`. (Note you need to finish advanced task to support `/image/04_cross_rotate.svg`)

#### Task 5: Alpha Compositing (10 pts)

Up until this point your were invoking a reference solution to properly draw semi-transparent elements. Therefore, your job is to implement your own [Simple Alpha Blending](http://www.w3.org/TR/SVGTiny12/painting.html#CompositingSimpleAlpha) in the SVG specification.

While the application will always clear the render target buffer to the canvas color at the beginning of a frame to opaque white ((255,255,255,255) in RGBA) before drawing any SVG element, your transparency implementation should make no assumptions about the state of the target at the beginning of a frame.

Once you finished, you should be able to correctly draw the test svgs in `/alpha`.

#### Task 6: Draw Something!!! (5 pts)

Now that you have implemented a few basic features of the SVG format, it is time to get creative and draw something!

You can create an SVG file in popular design tools like Adobe Illustrator or Inkscape and export SVG files, or use a variety of editors online. Since an SVG file is just an XML file, you could even use a text editor or write a script to generate the text!

Be aware that our starter code and your renderer implementation only support a **subset** of the features defined in the SVG specification (check svg.cpp), and applications like Adobe Illustrator or Inkscape may not always encode shapes with the primitives we support. (You may need to convert complicated paths to the basic primitives in these tools. This [Path to Polygon Converter](https://betravis.github.io/shape-tools/path-to-polygon/) might be of use.)

If you're using InkScape, and you save your drawing in InkScape as an `InkScape` svg or `Plain` svg, the entire drawing will appear black in DrawSVG.
To work around this, you should instead save it as an `Optimized SVG`. In the resulting dialog, be sure to select `Convert CSS attributes to XML attributes`, and *deselect* `Shorten color values`.

If you're using Illustrator, and you get errors with opening your generated SVG file in DrawSVG, make sure your `<svg>` tag contains a `width` and `height` field, with set values. Look at the test case SVGs in the `svg/` folder for reference. 

Naive editing of the test SVG by changing colors, duplicating or deleting elements may result in point deductions.

Please name this file `task6.svg`.

### Going Further: Advanced Tasks

#### Drawing Smooth Lines with Line Width

- (1 pts) If you compare your initial Bresenham results with the reference implementation, you will notice that the reference solution generates smooth lines. For example, you could modify your Bresenham implementation to perform [Xiaolin Wu's line algorithm](https://en.wikipedia.org/wiki/Xiaolin_Wu's_line_algorithm). 
- (1 pts) Add support for specifying a line width.

#### Implementing Triangle Edge Rules (1 pts)

This extra credit task aims to extend your implementation of triangle rasterization. In some cases, samples lie on the edge of a triangle, then the triangle edge rules are used to determine whether the sample should be treated as inside the triangle or not.

Here, we introduce two different types of edges one triangle may have.
- A top edge is an edge containing vertices with the highest Y values on screen, that is exactly horizontal and is above the other edges.
- A left edge is an edge that is not exactly horizontal and is on the left side of the triangle. Given a triangle with consistent counter-clockwise windings, left edges are always oriented downwards. A triangle can have one or two left edges.

If a sample lies on the top edge or the left edge of a triangle, then it should be treated as inside the triangle. Otherwise it should not.

Detailed description can be found [here](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage-rules).


#### Advanced Supersampling 

- (1 pts) Implement [Morphological anti-aliasing](https://dl.acm.org/citation.cfm?id=1572787) (MLAA), rather than supersampling. It's shocking how well this works. MLAA is a technique used throughout the gaming community to avoid the high cost of supersampling but still avoid objectionable image artifacts caused by aliasing. (More advanced versions of MLAA are described [here](http://www.iryoku.com/mlaa/).)
- (1 pts) Implement [jittered sampling](http://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf) to improve image quality when supersampling.
- (1 pts) Implement higher quality resampling filters than a box filter and analyze their impact on image quality. For example, try a truncated Gaussian filter. You need to do analysis in your writeup to receive the credit. 

#### Anti-Aliasing Image Elements Using Trilinear Filtering (1 pts)

In this task you will improve your anti-aliasing of image elements by adding trilinear filtering. This will involve generating mipmaps for image elements at SVG load time and then modifying your sampling code from Task 4 to implement trilinear filtering using the mipmap. Your implementation is only required to work for images that have power-of-two dimensions in each direction.

- To generate mipmaps, you need to modify code in `Sampler2DImp::generate_mips()` in `texture.cpp`. Code for allocating all the appropriate buffers for each level of the mipmap hierarchy is given to you. However, you will need to populate the contents of these buffers from the original texture data in level 0. **Your implementation can assume that all input texture images have power of two dimensions. (But it should not assume inputs images are square.)**
- Then modify your implementation of `rasterize_image()` from Task 4 to perform trilinear filtered sampling from the mipmap. Your implementation will first need to compute the appropriate level at which to sample from the mip-hierarchy. Recall from class that as image elements shrink on screen, to avoid aliasing the rasterizer should sample from increasingly high (increasing prefiltered) levels of the hierarchy.

The program only stores a single set of mipmaps for each image, so the `rasterize_image()` routine (both your implementation and the reference solution) will use whichever mipmaps have been generated most recently using the `'` and `;` keys. Be sure you are testing with your own mipmaps and not the reference ones.

At this point, zooming in and out of your image should produce nicely filtered results! To test this functionality, try zooming out on svgs in `/image`.

#### Image Elements With Rotation (1 pts)

In this task you will improve your image rendering to render image elements that are rotated. Note that the key difference is that you can not assume the uv coordinates are axis-aligned with the screen space coordinates. How can we compute the uv coordinates with the transformation of the image element? 
You should be able to render `/image/04_cross_rotate.svg` after completing this step.

#### Implement More Advanced SVG Shape Element (1 pts)

We have provided you with a couple of examples of subdividing complex, smooth complex shapes into much simpler triangles in `/subdiv`. (Subdivision is something you will dig into in great detail in Assignment 2). You can see subdivision in action as you step though the test files we provided.

In addition to what you have implemented already, the [SVG Basic Shapes](http://www.w3.org/TR/SVG/shapes.html) also include circles and ellipses. We may support these features by converting them to triangulated polygons. But if we zoom in on the edges, there will be a point at which the approximation breaks down and the image no longer will look like a smooth curve. Triangulating more finely can be costly as a large number of triangles may be necessary to get a good approximation. Is there a better way to sample these shapes? For example, implement `draw_ellipse` in `software_renderer.cpp` and test on `basic/test8.svg`

#### Parallelizing the SVG Rasterizer (1 pts)

So far your rasterization program has been running single-threaded (on one core of your CPU). In this task you will parallelize the program - most likely by modifying `SoftwareRendererImp` class. You can use whatever threading library you wish, for example you can use [POSIX Threads/pthreads](https://en.wikipedia.org/wiki/POSIX_Threads) as we already included this library for you (Or C++ style std::thread). 
<!-- You can set `CS248_BUILD_THREADED` flag to `ON` in your cmake file to see a reference solution in action (and performance number whenever you invoke a render function). Note that the reference solution is implemented with a simple screen tiling scheme to assign different tiles of the image to different cores.-->
Your implementation should be noticably faster than the reference solution in order to receive an extra credit for this task. Note that very ambitious students might consider further parallelizing the renderer using SIMD vector instructions---testing multiple sample points against the triangle in parallel. You might want to see [ISPC](https://ispc.github.io/) as a language for writing SIMD code.  More hints on rasterizer performance and parallelization can be found here [here](https://software.intel.com/en-us/articles/rasterization-on-larrabee). 

### Resources and Notes

- [Rasterization Rules in Direct3D 11](https://msdn.microsoft.com/en-us/library/windows/desktop/cc627092(v=vs.85).aspx)
- [Rasterization in OpenGL 4.0](https://www.opengl.org/registry/doc/glspec40.core.20100311.pdf#page=156)
- [Bryce Summer's C++ Programming Guide](https://github.com/Bryce-Summers/Writings/blob/master/Programming%20Guides/C_plus_plus_guide.pdf)
- [NeHe OpenGL Tutorials Lessons 01~05](http://nehe.gamedev.net/tutorial/lessons_01__05/22004/)

### Acknowledgement

CS248 course staff would like to thank Keenan Crane and his course assistants for their contributions to this assignment.
