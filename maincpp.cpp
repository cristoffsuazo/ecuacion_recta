#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <sstream> 

// Variables 
float p1x = 0.0f, p1y = 0.0f;
float p2x = 0.0f, p2y = 0.0f;
float pendiente = 0.0f;
std::string formula; // Para almacenar la fórmula de la pendiente

// Función para mostrar texto en pantalla
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y); // Posición del texto
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c); // Dibuja cada carácter
    }
}

// Función para calcular la pendiente y generar la fórmula
void calcularPendiente() {
    if (p2x - p1x != 0) { // Evitar división por cero
        pendiente = (p2y - p1y) / (p2x - p1x);
        std::cout << "La pendiente de la recta es: " << pendiente << std::endl;

        // Convertir la fórmula a texto para mostrarla
        std::ostringstream ss;
        ss << "Pendiente (m) = (" << p2y << " - " << p1y << ") / (" << p2x << " - " << p1x << ")";
        formula = ss.str();
    }
    else {
        std::cout << "La recta es vertical, la pendiente es indefinida (infinita)." << std::endl;
        formula = "Pendiente indefinida (Recta vertical)";
        pendiente = INFINITY; // Infinita
    }
}

// Función para dibujar los ejes del plano cartesiano
void dibujarEjes() {
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco para los ejes
    glBegin(GL_LINES);
    // Eje X
    glVertex2f(-10.0f, 0.0f);
    glVertex2f(10.0f, 0.0f);
    // Eje Y
    glVertex2f(0.0f, -10.0f);
    glVertex2f(0.0f, 10.0f);
    glEnd();
}

// Función para dibujar un punto
void dibujarPunto(float x, float y) {
    glPointSize(6.0); // Tamaño del punto
    glColor3f(0.0f, 1.0f, 0.0f); // Color verde para los puntos
    glBegin(GL_POINTS);
    glVertex2f(x, y); // Dibuja el punto en las coordenadas dadas
    glEnd();
}

// Función para mostrar los valores de los puntos en pantalla
void mostrarCoordenadas(float x, float y) {
    std::ostringstream ss;
    ss << "(" << x << ", " << y << ")"; // Convertir las coordenadas a string
    renderBitmapString(x + 0.2f, y + 0.2f, GLUT_BITMAP_HELVETICA_12, ss.str().c_str()); // Mostrar cerca del punto
}

// Función de dibujo principal
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar los ejes del plano cartesiano
    dibujarEjes();

    // Dibujar los puntos en las coordenadas dadas
    dibujarPunto(p1x, p1y);
    dibujarPunto(p2x, p2y);

    // Mostrar los valores de los puntos cerca de ellos
    mostrarCoordenadas(p1x, p1y);
    mostrarCoordenadas(p2x, p2y);

    // Configurar el color de la línea (roja) y dibujar la recta
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(p1x, p1y);
    glVertex2f(p2x, p2y);
    glEnd();

    // Mostrar la fórmula de la pendiente en la parte superior de la pantalla
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco para el texto
    renderBitmapString(-9.5f, 9.0f, GLUT_BITMAP_HELVETICA_18, formula.c_str());

    // Actualizar la ventana
    glutSwapBuffers();
}

// Inicialización de OpenGL
void init() {
    // Color de fondo (negro)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Configurar la proyección ortográfica
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0); // Coordenadas del sistema (-10, 10)
}

// Función para manejar el teclado y recibir los puntos
void teclado(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q') {
        exit(0); // Salir del programa si se presiona 'q'
    }
}

// Función principal
int main(int argc, char** argv) {
    // Pedir las coordenadas de los puntos
    std::cout << "Ingrese las coordenadas del primer punto (p1x, p1y): ";
    std::cin >> p1x >> p1y;
    std::cout << "Ingrese las coordenadas del segundo punto (p2x, p2y): ";
    std::cin >> p2x >> p2y;

    // Calcular la pendiente y la fórmula
    calcularPendiente();

    // Inicializar GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Plano Cartesiano con Recta, Pendiente y Puntos");

    // Inicialización de OpenGL
    init();

    // Registrar las funciones de callback
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);

    // Iniciar el loop principal de GLUT
    glutMainLoop();

    return 0;
}