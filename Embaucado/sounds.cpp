#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <string>
#include "sounds.h";
#include <iostream>
using namespace std;

void reproducirMusica() {
    const string path = "H:\\Salchy\\UTN\\Cursada 2024\\Prog 1\\Embaucado\\sounds\\cancion.mid";

    char cmd[256];

    sprintf(cmd, "open \"%s\" type sequencer alias music", path.c_str());
    if (mciSendString(cmd, NULL, 0, NULL) != 0) {
        //cout << "Falló la apertura" << endl;
        return;
    }

    if (mciSendString("play music from 0", NULL, 0, NULL) != 0) {
        //cout << "Falló la reproducción del sonido" << endl;
        return;
    }
}
