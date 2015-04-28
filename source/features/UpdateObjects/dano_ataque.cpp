#include <iostream>
#include <string>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../../include/draw.h"
#include "../../../include/video.h"
#include "../../../include/loop.h"
#include "../../../include/gamefeatures.h"
#include "../../../include/sound.h"

Mix_Chunk *efeito_explosao;
int lastdt = SDL_GetTicks();
int totalElapsedTime = 0;
int delay = 200;
string derrotado = "branca";

void dano_ataque(SDL_Surface *screen)
{
	string tipoquartel = "quartel";
	/* inicializa o random */
	srand (time(NULL));

	string cor1 = "azul";
	string cor2 = "vermelho";

	int rand_defensor = rand() % 50 + 30;
	int rand_atacante = rand() % 50 + 40;

	Unit *atacante = hexagonos[hex_selecao->i_before]
								 [hex_selecao->j_before]->unit;
	Unit *defensor = hexagonos[hex_selecao->i]
								 [hex_selecao->j]->unit;

	if (atacante->unit_type == tipoquartel) {
		cout << "Unit não pode atacar" << endl;
		return;
	}

	int dano_no_atacante = ((defensor->attack_points/atacante->deffense_points)+1) *
						   (rand_defensor/2);
	int dano_no_defensor = ((atacante->attack_points/ defensor->deffense_points)+1)*
						   (rand_atacante);
	cout << "dano no atacante:" << dano_no_atacante << endl;
	cout << "dano no defensor:" << dano_no_defensor << endl;
	atacante->health_points -= dano_no_atacante;
	if (atacante->health_points <= 0) {
		atacante->health_points  = 0;
	}
	defensor->health_points -= dano_no_defensor;
	if (defensor->health_points < 0) {
		defensor->health_points  = 0;
	}

	if (defensor->unit_type == tipoquartel && defensor->health_points == 0) {
		cout << "defensor:" << defensor->color << endl;
		derrotado = defensor->color;
		cout << "derrotado:" << derrotado << endl;
	}
	cout << "atacante health_points:" << atacante->health_points << endl;
	cout << "defensor health_points:" << defensor->health_points << endl;

	if (atacante->health_points <= 0) {
		explode_unidade(screen,
						hexagonos[hex_selecao->i_before][hex_selecao->j_before]->x,
						hexagonos[hex_selecao->i_before][hex_selecao->j_before]->y,
						totalElapsedTime, delay, lastdt);
		hexagonos[hex_selecao->i_before][hex_selecao->j_before]->unit = NULL;
		hexagonos[hex_selecao->i_before]
				 [hex_selecao->j_before]->contains_unit = 0;
	}
	else {
		hexagonos[hex_selecao->i_before]
				 [hex_selecao->j_before]->unit->health_points = atacante->health_points;
	}
	if (defensor->health_points <= 0) {
		if (defensor->unit_type.compare("quartel") != 0) {
			if (defensor->unit_type.compare("metralhadora") != 0) {
				play_effect(efeito_explosao);
				explode_unidade(screen,
								hexagonos[hex_selecao->i][hex_selecao->j]->x,
								hexagonos[hex_selecao->i][hex_selecao->j]->y,
								totalElapsedTime, delay, lastdt);
				hexagonos[hex_selecao->i][hex_selecao->j]->unit = NULL;
				hexagonos[hex_selecao->i][hex_selecao->j]->contains_unit = 0;
			}
			else if (defensor->color == "azul") {
				play_effect(efeito_explosao);
				hexagonos[9][12]->unit = NULL;
				hexagonos[9][12]->contains_unit = 0;
				hexagonos[10][12]->unit = NULL;
				hexagonos[10][12]->contains_unit = 0;
				hexagonos[11][12]->unit = NULL;
				hexagonos[11][12]->contains_unit = 0;
				hexagonos[12][12]->unit = NULL;
				hexagonos[12][12]->contains_unit = 0;
				hexagonos[13][12]->unit = NULL;
				hexagonos[13][12]->contains_unit = 0;
			}
			else {
				play_effect(efeito_explosao);
				hexagonos[6][4]->unit = NULL;
				hexagonos[6][4]->contains_unit = 0;
				hexagonos[7][4]->unit = NULL;
				hexagonos[7][4]->contains_unit = 0;
				hexagonos[8][4]->unit = NULL;
				hexagonos[8][4]->contains_unit = 0;
			}
		}
		else if (defensor->color == "azul") {
			play_effect(efeito_explosao);
			hexagonos[7][13]->unit = NULL;
			hexagonos[7][13]->contains_unit = 0;
			hexagonos[7][14]->unit = NULL;
			hexagonos[7][14]->contains_unit = 0;
			hexagonos[8][14]->unit = NULL;
			hexagonos[8][14]->contains_unit = 0;
			hexagonos[9][13]->unit = NULL;
			hexagonos[9][13]->contains_unit = 0;
			hexagonos[9][14]->unit = NULL;
			hexagonos[9][14]->contains_unit = 0;
			hexagonos[10][14]->unit = NULL;
			hexagonos[10][14]->contains_unit = 0;

		}
		else {
			play_effect(efeito_explosao);
			hexagonos[5][1]->unit = NULL;
			hexagonos[5][1]->contains_unit = 0;
			hexagonos[6][1]->unit = NULL;
			hexagonos[6][1]->contains_unit = 0;
			hexagonos[6][2]->contains_unit = 0;
			hexagonos[6][2]->unit = NULL;
			hexagonos[7][1]->contains_unit = 0;
			hexagonos[7][1]->unit = NULL;
			hexagonos[8][1]->contains_unit = 0;
			hexagonos[8][1]->unit = NULL;
			hexagonos[8][2]->contains_unit = 0;
			hexagonos[8][2]->unit = NULL;
			hexagonos[9][1]->contains_unit = 0;
			hexagonos[9][1]->unit = NULL;
		}
	}
	else {
		hexagonos[hex_selecao->i][hex_selecao->j]->unit->health_points = defensor->health_points;
	}
}

void explode_unidade(SDL_Surface *screen,
                     int x,
                     int y,
                     int totalElapsedTime,
                     int delay,
                     int lastdt)
{
	string caminho =
	            "source/GameFeatures/Jogar/Fase1/images/explosao_unidades.png";
	SDL_Surface *explosao = load_Image(caminho, screen);
	int n_sprites = 8;
	int tamanho_sprites = 32;
	int tempo_delay = 50;
	for (int i = 0; i <= 3; i++) {
		SDL_Rect cutBox = {0, 0, 32, 32};

		while (cutBox.x < n_sprites*tamanho_sprites) {
			blit_tela(screen, 1);
			int dt = SDL_GetTicks() - lastdt;
			lastdt = SDL_GetTicks();

			totalElapsedTime += dt;

			if (totalElapsedTime >= delay) {
				totalElapsedTime -= delay;
				cutBox.x += tamanho_sprites;
			}

			SDL_Rect dest = {(Sint16)x, (Sint16)y, 0, 0};
			SDL_BlitSurface(explosao, &cutBox, screen, &dest);
			SDL_Delay(tempo_delay);
			SDL_Flip(screen);
		}
	}
}
