/// TODO adjust scaled_i and scaled_j to use a center point w/ diameter

/// @file mand.cpp
/// @author Bryce Forrest <5006464939>
/// @date 07/06/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Generate .ppm file of Mandelbrot set

#include <iostream>
#include <complex>
#include <fstream>

using Complex = std::complex<double>;

// global constants
const unsigned int MAX_HEIGHT = 800;
const unsigned int MAX_WIDTH = 800;
const unsigned int COLOR_SIZE = 255;
const unsigned int MAX_ITER = 50;

// rgb pixel struct
struct pixel_t {
    unsigned char red;      // value of r
    unsigned char green;    // value of g
    unsigned char blue;     // value of b
};

// two-dimensional array of pixels (image struct)
struct image_t {
    unsigned int height = MAX_HEIGHT;       // number of vertical pixels
    unsigned int width = MAX_WIDTH;         // number of horizontal pixels
    unsigned int max_color = 255;          // maximum color value

    pixel_t image[MAX_HEIGHT][MAX_WIDTH];   // 2d array of pixels
};

double resize (unsigned int input, unsigned int input_max,
               double output_min, double output_max);
unsigned int mandelbrot (Complex c);
void read_file(std::ifstream& infile, pixel_t palette[], 
               double& top, double& bottom, double& left, double& right);
void write_pixel (std::ofstream& outfile, pixel_t pixel);
void write_image (std::ofstream& outfile, image_t output);

int main () {
    std::ifstream infile;           // input file stream
    std::ofstream outfile;          // output file stream
    image_t output;                 // image struct to be printed
    pixel_t palette[COLOR_SIZE];    // color palette
    double top;                     // top coordinate
    double bottom;                  // bottom coordinate
    double left;                    // leftmost coordinate
    double right;                   // rightmost coordinate

    infile.open("palette.txt");     // open input file stream
    outfile.open("image.ppm");      // open output file stream

    // take in coordinates and color palette
    read_file(infile, palette, top, bottom, left, right);

    // iterate through each pixel of image, rescaling the value of i and j to
    // the coordinate values from the input file
    // plug values into mandelbrot function and use the number of iterations to
    // map to a color to be printed in that corresponding pixel.           
    for (int i = 0; i < output.height; ++i) {
        for (int j = 0; j < output.width; ++j) {
            double scaled_i = resize(i, output.height, bottom, top);
            double scaled_j = resize(j, output.width, left, right);

            Complex c(scaled_j, scaled_i);
            unsigned int iterations = mandelbrot(c);
            int color = static_cast<int>(resize(iterations, MAX_ITER, 0, 255));
            output.image[i][j] = palette[color];
        }
    }

    write_image(outfile, output);       // print image struct to output file

    infile.close();                     // close input file stream
    outfile.close();                    // close output file stream

    return EXIT_SUCCESS;
}

/// @brief resize
///
/// Resizes a value in an unsigned range to a decimal output range
/// @param input        the value to be scaled
/// @param input_max    the uppermost value of input range
/// @param output_min   the minimum value of output range
/// @param output_max   the uppermost value of output range
/// @return             the scaled output
double resize (unsigned int input, unsigned int input_max,
               double output_min, double output_max) {
    double scaling_factor = (output_max - output_min) / input_max;
    return (input * scaling_factor) + output_min;
}

/// @brief mandelbrot
///
/// Calculates whether complex number c is bounded over z = z^2 + c
/// @param c    complex value c to be checked
/// @return     the number of iterations before escaping (if at all)
unsigned int mandelbrot (Complex c) {
    Complex z(0, 0);
    unsigned int i = 0;

    while (i < MAX_ITER && std::abs(z) <= 2) {
        z = z*z + c;
        ++i;
    }

    return i;
}

/// @brief read_file
///
/// Takes coordinates and color palette from input file
/// @param infile   input file stream
/// @param palette  color palette
/// @param top      top coordinate
/// @param bottom   bottom coordinate
/// @param left     leftmost coordinate
/// @param right    rightmost coordinate
void read_file(std::ifstream& infile, pixel_t palette[], 
               double& top, double& bottom, double& left, double& right) {
    int digit;      // integer to hold number input before casting to char

    infile >> top >> bottom >> left >> right;

    for (int i = 0; i < COLOR_SIZE; ++i) {
        infile >> digit;
        palette[i].red = static_cast<int>(digit);
        infile >> digit;
        palette[i].green = static_cast<int>(digit);
        infile >> digit;
        palette[i].blue = static_cast<int>(digit);
    }
}

/// @brief write_pixel
///
/// Writes a single pixel to output file stream
///
/// @param outfile  output file stream
/// @param pixel    pixel_t to be printed.
void write_pixel (std::ofstream& outfile, pixel_t pixel) {
    outfile << static_cast<int>(pixel.red) << " "
            << static_cast<int>(pixel.green) << " "
            << static_cast<int>(pixel.blue) << " ";
}

/// @brief write_image
///
/// Writes the image_t array to output file stream
///
/// @param outfile  output file stream
/// @param output   image_t containing array of pixel_t to be printed.
void write_image (std::ofstream& outfile, image_t output) {
    outfile << "P3" << std::endl;
    outfile << output.width << " "
            << output.height << " "
            << output.max_color << std::endl;

    for (int i = 0; i < output.height; ++i) {
        for (int j = 0; j < output.width; ++j) {
            write_pixel(outfile, output.image[i][j]);
        }
    }
}
