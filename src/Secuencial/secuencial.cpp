#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Función para convertir una región de la imagen a escala de grises (versión secuencial)
void convertRegionToGrayscale(const Mat& input, Mat& output, int startRow, int endRow) {
    for (int r = startRow; r < endRow; r++) {
        for (int c = 0; c < input.cols; c++) {
            Vec3b& pixel = output.at<Vec3b>(r, c);
            int grayValue = (pixel[0] + pixel[1] + pixel[2]) / 3;
            pixel[0] = grayValue;
            pixel[1] = grayValue;
            pixel[2] = grayValue;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Uso: ./secuencial imagen_entrada imagen_salida" << endl;
        return -1;
    }

    string inputImagePath = argv[1];
    string outputImagePath = argv[2];

    Mat image = imread(inputImagePath, IMREAD_COLOR);
    if (image.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    Mat grayscaleImage = image.clone();

    // Versión secuencial
    convertRegionToGrayscale(image, grayscaleImage, 0, image.rows);

    imwrite(outputImagePath, grayscaleImage);

    return 0;
}