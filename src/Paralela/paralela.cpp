#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace cv;
using namespace std;

// Función para convertir una región de la imagen a escala de grises (versión paralela)
void convertirImgAGris(const Mat& entrada, Mat& salida, int filaInicial, int filaFinal) {
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

    // Versión paralela
    int numHebras = thread::hardware_concurrency();
    cout << "Cantidad de hebras utilizadas: " << numHebras << endl;

    int filasPorHebra = imagen.rows / numHebras;

    vector<thread> hebras(numHebras);
    auto inicioTiempo = chrono::high_resolution_clock::now(); // Iniciar el cronómetro
    for (int i = 0; i < numHebras; i++) {
        int filaInicial = i * filasPorHebra;
        int filaFinal = (i + 1) * filasPorHebra;
        if (i == numHebras - 1) {
            filaFinal = imagen.rows; // La última hebra se encarga de las filas restantes
        }

        hebras[i] = thread(convertirImgAGris, ref(imagen), ref(imagenGrises), filaInicial, filaFinal);
    }

    for (auto& t : hebras) {
        t.join();
    }
    auto finTiempo = chrono::high_resolution_clock::now(); // Detener el cronómetro
    auto duracion = chrono::duration_cast<chrono::duration<double>>(finTiempo - inicioTiempo); // Calcular la duración en segundos

    imwrite(rutaImagenSalida, imagenGrises);

    cout << fixed << setprecision(5); // Configurar la precisión decimal
    cout << "Tiempo de ejecución total: " << duracion.count() << " segundos" << endl;

    return 0;
}