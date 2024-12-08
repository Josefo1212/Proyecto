#ifndef PERMISOS_H
#define PERMISOS_H

#include <string>

using namespace std;

// Función para verificar si un usuario tiene permiso para una opción
bool tienePermiso(const string& rol, int opcion);

#endif // PERMISOS_H
