#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>

using namespace cv;
using namespace std;

// Función para convertir una región de la imagen a escala de grises (versión paralela)
void convertRegionToGrayscale(const Mat& input, Mat& output, int startRow, int endRow) {
    #pragma omp parallel for
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
        cout << "Use la sintaxis: ./paralelo imagen_entrada imagen_salida" << endl;
        return -1;
    }

    string inputImagePath = argv[1];
    string outputImagePath = argv[2];

    Mat image = imread(inputImagePath, IMREAD_COLOR);
    if (image.empty()) {
        cout << "Error al cargar la imagen. Verifique que la imagen esté en el directorio" << endl;
        return -1;
    }

    Mat grayscaleImage = image.clone();

    // Versión paralela
    int numThreads = omp_get_max_threads();
    int rowsPerThread = image.rows / numThreads;

    #pragma omp parallel
    {
        int threadId = omp_get_thread_num();
        int startRow = threadId * rowsPerThread;
        int endRow = (threadId + 1) * rowsPerThread;
        if (threadId == numThreads - 1) {
            endRow = image.rows; // La última hebra se encarga de las filas restantes
        }

        convertRegionToGrayscale(image, grayscaleImage, startRow, endRow);
    }

    imwrite(outputImagePath, grayscaleImage);

    return 0;
}