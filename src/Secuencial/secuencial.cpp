#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

// Función para convertir una región de la imagen a escala de grises (versión secuencial)
void convertirRegionAGrises(const Mat& entrada, Mat& salida, int filaInicial, int filaFinal) {
    for (int r = filaInicial; r < filaFinal; r++) {
        for (int c = 0; c < entrada.cols; c++) {
            Vec3b& pixel = salida.at<Vec3b>(r, c);
            int valorGris = (pixel[0] + pixel[1] + pixel[2]) / 3;
            pixel[0] = valorGris;
            pixel[1] = valorGris;
            pixel[2] = valorGris;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Use la sintaxis: ./secuencial imagen_entrada imagen_salida" << endl;
        return -1;
    }

    string rutaImagenEntrada = argv[1];
    string rutaImagenSalida = argv[2];

    Mat imagen = imread(rutaImagenEntrada, IMREAD_COLOR);
    if (imagen.empty()) {
        cout << "Error al cargar la imagen. Verifique que la imagen esté en el directorio" << endl;
        return -1;
    }

    Mat imagenGrises = imagen.clone();

    // Versión secuencial
    auto inicio = high_resolution_clock::now(); // Iniciar el cronómetro

    convertirRegionAGrises(imagen, imagenGrises, 0, imagen.rows);

    auto fin = high_resolution_clock::now(); // Detener el cronómetro
    auto duracion = duration_cast<duration<double>>(fin - inicio); // Calcular la duración en segundos

    imwrite(rutaImagenSalida, imagenGrises);

    cout << "Tiempo de ejecución total: " << duracion.count() << " segundos" << endl;

    return 0;
}