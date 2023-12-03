#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

// Función para convertir una región de la imagen a escala de grises (versión paralela)
void convertirImgAGris(const Mat& entrada, Mat& salida, int filaInicio, int filaFin) {
    #pragma omp parallel for
    for (int r = filaInicio; r < filaFin; r++) {
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
        cout << "Use la sintaxis: ./paralelo imagen_entrada imagen_salida" << endl;
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

    int numHebras;
    cout << "Ingrese el número de hebras a utilizar: ";
    cin >> numHebras;

    // Versión paralela
    int filasPorHebra = imagen.rows / numHebras;

    auto inicioTiempo = high_resolution_clock::now(); // Iniciar el cronómetro

    #pragma omp parallel num_threads(numHebras)
    {
        int idHebra = omp_get_thread_num();
        int filaInicio = idHebra * filasPorHebra;
        int filaFin = (idHebra + 1) * filasPorHebra;
        if (idHebra == numHebras - 1) {
            filaFin = imagen.rows; // La última hebra se encarga de las filas restantes
        }

        convertirImgAGris(imagen, imagenGrises, filaInicio, filaFin);
    }

    auto finTiempo = high_resolution_clock::now(); // Detener el cronómetro
    auto duracion = duration_cast<duration<double>>(finTiempo - inicioTiempo); // Calcular la duración en segundos

    imwrite(rutaImagenSalida, imagenGrises);

    cout << "Tiempo de ejecución total: " << duracion.count() << " segundos" << endl;

    return 0;
}