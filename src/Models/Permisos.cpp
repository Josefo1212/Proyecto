#include "permisos.h"

bool tienePermiso(const string& rol, int opcion) {
    if (rol == "admin") {
        return true; 
    } else if (rol == "manager") {
        return (opcion >= 1 || opcion <= 13  || opcion == 15 || opcion == 16); 
    } else if (rol == "empleado") {
        return (opcion == 4 || opcion == 12 || opcion == 13 || opcion == 15 || opcion == 16 ); 
    }
    return false;
}
