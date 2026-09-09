/*
 * Pico y placa — estilo laboratorio (80 columnas).
 *
 * Regla academica clasica (Quito, la que se ensenaba en ejercicios):
 *   Lunes      -> digitos 1 y 2
 *   Martes     -> digitos 3 y 4
 *   Miercoles  -> digitos 5 y 6
 *   Jueves     -> digitos 7 y 8
 *   Viernes    -> digitos 9 y 0
 *   Sabado/Domingo -> sin restriccion
 * Horario restringido: 07:00-09:00 y 16:00-19:00 (hora entera).
 *
 * Colores: secuencias ANSI (Windows 10+, Linux, macOS).
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cstring>

using namespace std;

const int ANCHO = 80;

#ifdef _WIN32
#include <windows.h>
static void habilitar_ansi()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    if (GetConsoleMode(h, &modo))
        SetConsoleMode(h, modo | 0x0004);
}
#else
static void habilitar_ansi() {}
#endif

namespace col {
    const char *reset    = "\033[0m";
    const char *negrita  = "\033[1m";
    const char *rojo     = "\033[1;31m";
    const char *verde    = "\033[1;32m";
    const char *amarillo = "\033[1;33m";
    const char *azul     = "\033[1;34m";
    const char *magenta  = "\033[1;35m";
    const char *cian     = "\033[1;36m";
    const char *blanco   = "\033[1;37m";
}

static void limpiar_pantalla()
{
    cout << "\033[2J\033[H" << flush;
}

static string repetir(char c, int n)
{
    return string(n < 0 ? 0 : n, c);
}

static void centrar(const string &texto, const char *color = col::blanco)
{
    int pad = (ANCHO - (int)texto.size()) / 2;
    if (pad < 0) pad = 0;
    cout << repetir(' ', pad) << color << texto << col::reset << "\n";
}

static void linea_caja(char izq, char medio, char der)
{
    cout << col::cian << izq << repetir(medio, ANCHO - 2) << der << col::reset << "\n";
}

static void fila_caja(const string &texto, const char *color = col::blanco)
{
    cout << col::cian << "|" << col::reset;
    int inner = ANCHO - 2;
    int pad = (inner - (int)texto.size()) / 2;
    if (pad < 0) pad = 0;
    cout << repetir(' ', pad) << color << texto << col::reset;
    int used = pad + (int)texto.size();
    if (used > inner) used = inner;
    cout << repetir(' ', inner - used);
    cout << col::cian << "|" << col::reset << "\n";
}

static void caja_titulo()
{
    linea_caja('+', '-', '+');
    fila_caja("P I C O   Y   P L A C A", col::amarillo);
    linea_caja('+', '-', '+');
}

static void esperar_enter(const string &aviso = "Pulse ENTER para volver al menu...")
{
    cout << "\n";
    centrar(aviso, col::amarillo);
    string dummy;
    getline(cin, dummy);
}

static string minusculas(string s)
{
    for (size_t i = 0; i < s.size(); ++i)
        s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

static string recortar(string s)
{
    size_t a = 0;
    while (a < s.size() && isspace((unsigned char)s[a])) a++;
    size_t b = s.size();
    while (b > a && isspace((unsigned char)s[b - 1])) b--;
    return s.substr(a, b - a);
}

static int parsear_dia(string entrada)
{
    entrada = minusculas(recortar(entrada));
    if (entrada.empty()) return 0;

    if (entrada == "1" || entrada == "lunes" || entrada == "lun" || entrada == "monday")
        return 1;
    if (entrada == "2" || entrada == "martes" || entrada == "mar" || entrada == "tuesday")
        return 2;
    if (entrada == "3" || entrada == "miercoles" || entrada == "miércoles"
        || entrada == "mie" || entrada == "mié" || entrada == "wednesday")
        return 3;
    if (entrada == "4" || entrada == "jueves" || entrada == "jue" || entrada == "thursday")
        return 4;
    if (entrada == "5" || entrada == "viernes" || entrada == "vie" || entrada == "friday")
        return 5;
    if (entrada == "6" || entrada == "sabado" || entrada == "sábado"
        || entrada == "sab" || entrada == "saturday")
        return 6;
    if (entrada == "7" || entrada == "domingo" || entrada == "dom" || entrada == "sunday")
        return 7;

    size_t sp = entrada.find(' ');
    if (sp != string::npos)
        return parsear_dia(entrada.substr(0, sp));
    return 0;
}

static const char *nombre_dia(int d)
{
    switch (d) {
        case 1: return "lunes";
        case 2: return "martes";
        case 3: return "miercoles";
        case 4: return "jueves";
        case 5: return "viernes";
        case 6: return "sabado";
        case 7: return "domingo";
        default: return "?";
    }
}

static int ultimo_digito(const string &placa)
{
    for (int i = (int)placa.size() - 1; i >= 0; --i) {
        if (isdigit((unsigned char)placa[i]))
            return placa[i] - '0';
    }
    return -1;
}

static bool hora_restringida(int hora)
{
    return (hora >= 7 && hora <= 9) || (hora >= 16 && hora <= 19);
}

static bool digito_restringido(int dia, int digito)
{
    switch (dia) {
        case 1: return digito == 1 || digito == 2;
        case 2: return digito == 3 || digito == 4;
        case 3: return digito == 5 || digito == 6;
        case 4: return digito == 7 || digito == 8;
        case 5: return digito == 9 || digito == 0;
        default: return false;
    }
}

static void mostrar_reglas()
{
    limpiar_pantalla();
    caja_titulo();
    cout << "\n";
    centrar("REGLAS DEL EJERCICIO", col::magenta);
    cout << "\n";
    linea_caja('+', '-', '+');
    fila_caja("Lunes       placas terminadas en 1 y 2");
    fila_caja("Martes      placas terminadas en 3 y 4");
    fila_caja("Miercoles   placas terminadas en 5 y 6");
    fila_caja("Jueves      placas terminadas en 7 y 8");
    fila_caja("Viernes     placas terminadas en 9 y 0");
    fila_caja("Sabado y domingo    sin restriccion");
    linea_caja('+', '-', '+');
    cout << "\n";
    centrar("Horario restringido: 07:00-09:00 y 16:00-19:00", col::amarillo);
    centrar("Fuera de ese horario se puede circular siempre.", col::blanco);
    cout << "\n";
    centrar("Esta es la regla clasica de laboratorio (Quito de esa epoca),", col::cian);
    centrar("no la normativa vigente de cada ciudad.", col::cian);
    esperar_enter();
}

static void marco_resultado(const string &linea1, const string &linea2, const char *color)
{
    linea_caja('+', '-', '+');
    fila_caja(linea1, color);
    if (!linea2.empty()) fila_caja(linea2, color);
    linea_caja('+', '-', '+');
}

static void consultar()
{
    limpiar_pantalla();
    caja_titulo();
    cout << "\n";
    centrar("CONSULTAR CIRCULACION", col::magenta);
    cout << "\n";

    string placa;
    cout << col::cian << "  Placa del vehiculo: " << col::reset;
    getline(cin, placa);
    placa = recortar(placa);

    int digito = ultimo_digito(placa);
    while (placa.empty() || digito < 0) {
        cout << col::rojo << "  No encontre un digito en la placa. Intente de nuevo: " << col::reset;
        getline(cin, placa);
        placa = recortar(placa);
        digito = ultimo_digito(placa);
    }

    cout << col::cian << "  Dia (lunes..domingo, o 1..7): " << col::reset;
    string sdia;
    getline(cin, sdia);
    int dia = parsear_dia(sdia);
    while (dia == 0) {
        cout << col::rojo << "  Dia no reconocido. Ej: lunes  |  viernes  |  3: " << col::reset;
        getline(cin, sdia);
        dia = parsear_dia(sdia);
    }

    cout << col::cian << "  Hora (0-23): " << col::reset;
    string shora;
    getline(cin, shora);
    char *fin = 0;
    long hora = strtol(recortar(shora).c_str(), &fin, 10);
    while (shora.empty() || hora < 0 || hora > 23) {
        cout << col::rojo << "  Hora invalida. Un entero entre 0 y 23: " << col::reset;
        getline(cin, shora);
        hora = strtol(recortar(shora).c_str(), &fin, 10);
    }

    cout << "\n";
    linea_caja('+', '-', '+');
    cout << "\n";
    centrar(string("Placa: ") + placa + "   ultimo digito: " + char('0' + digito), col::blanco);
    centrar(string("Dia: ") + nombre_dia(dia) + "   hora: " + to_string((int)hora) + ":00", col::blanco);
    cout << "\n";

    bool pico = hora_restringida((int)hora);
    bool restringe_dia = digito_restringido(dia, digito);

    if (dia >= 6) {
        marco_resultado("PUEDE CIRCULAR",
                        "Fin de semana: no hay pico y placa",
                        col::verde);
    } else if (!pico) {
        marco_resultado("PUEDE CIRCULAR",
                        "Fuera del horario restringido",
                        col::verde);
    } else if (pico && restringe_dia) {
        string det = string("El ") + nombre_dia(dia)
                   + " no circulan las placas terminadas en "
                   + char('0' + digito);
        marco_resultado("NO PUEDE CIRCULAR", det, col::rojo);
    } else {
        string det = string("El ") + nombre_dia(dia)
                   + " restringe otros digitos, no el "
                   + char('0' + digito);
        marco_resultado("PUEDE CIRCULAR", det, col::verde);
    }

    esperar_enter();
}

static int leer_opcion()
{
    cout << col::cian << "  Elija una opcion (1-3): " << col::reset;
    string s;
    getline(cin, s);
    s = recortar(s);
    if (s == "1" || s == "2" || s == "3")
        return s[0] - '0';
    return 0;
}

static void mostrar_menu()
{
    limpiar_pantalla();
    caja_titulo();
    cout << "\n";
    centrar("Ejercicio de consola — logica corregida", col::blanco);
    cout << "\n";
    linea_caja('+', '-', '+');
    fila_caja("");
    fila_caja("1.  Consultar si puede circular", col::amarillo);
    fila_caja("2.  Ver reglas de pico y placa", col::amarillo);
    fila_caja("3.  Salir", col::amarillo);
    fila_caja("");
    linea_caja('+', '-', '+');
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    habilitar_ansi();

    bool seguir = true;
    while (seguir) {
        mostrar_menu();
        int op = leer_opcion();
        switch (op) {
            case 1:
                consultar();
                break;
            case 2:
                mostrar_reglas();
                break;
            case 3:
                seguir = false;
                break;
            default:
                cout << "\n";
                centrar("Opcion no valida. Use 1, 2 o 3.", col::rojo);
                esperar_enter("Pulse ENTER para intentar de nuevo...");
                break;
        }
    }

    limpiar_pantalla();
    caja_titulo();
    cout << "\n";
    centrar("Gracias por usar el programa", col::magenta);
    cout << "\n";
    cout << col::reset;
    return 0;
}
