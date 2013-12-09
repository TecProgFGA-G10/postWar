#include <iostream>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <iostream>
#include "../../../include/draw.h"
#include "../../../include/video.h"
#include "../../../include/loop.h"
#include "../../../include/gamefeatures.h"


void coleta_ouro(Pais *pais, int valor_coleta_ouro){
    pais->ouro += valor_coleta_ouro;
}

void coleta_minerio(Pais *pais, int valor_coleta_minerio){
    pais->minerio += valor_coleta_minerio;
}

void coleta_comida(Pais *pais, int valor_coleta_comida){
    pais->comida += valor_coleta_comida;
}
