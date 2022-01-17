/* Copyright (C) 2022 Aaron Alef <aaron.alef@code.berlin>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (e.g., ./LICENSE).
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include <opencv2/opencv.hpp>
#include <iostream>

#include "config.h"

#include "grayify.hpp"

using namespace cv;
using namespace std;

int main (int argc, char * argv[]) {
    google::InitGoogleLogging (argv[0]);
    
    // Read the image file
    Mat image = imread (IMG_IN / "bird.png");
    
    // Check for failure
    if (image.empty ()) {
        cout << "Could not open or find the image" << endl;
        cin.get ();
        return -1;
    }
    cout << "Successfully opened the image with dimension " << image.rows << "x" << image.cols << std::endl;
    
    grayify (image);
    
    String windowName = "The Little Bird";
    namedWindow (windowName);
    imshow (windowName, image);
    while (waitKey (0) != 27);
    destroyWindow (windowName);
}
