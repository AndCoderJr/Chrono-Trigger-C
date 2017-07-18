/*
 * Player.c
 *
 *  Created on: 13 de jul de 2017
 *      Author: Anderson
 */


#include "Player.h"
#include "Stage.h"
#include "Monster.h"
#include <string.h>


#define SPEED 2
#define TROCA 6
#define STAGE_VEL 1
#define MARGEM_ERRO 10
//
//int accel = 1;

int setupSprite(PlayerConf* conf,SDL_Rect* spriteRect)
{

	char* path;
	variacaoSprite = 0;
	variacaoRigth = 0;
	if(!strcmp(conf->name,"crono") && conf->start != 1){
		path = "Resourcers/cronoNormal1.png";
		conf->pathSprite = malloc(sizeof(char) * 40);

		conf->up = conf->down = conf->left = conf->rigth = 0;
		spriteRect->x = 400;
		spriteRect->y = 500;

		up = down = left = right = 0;
	}

	*conf->surface = IMG_Load(path);
	conf->start = 1;
	conf->state = 1;
	conf->ready = 0;
	if(!*conf->surface)
		return 0;
	*conf->tex = SDL_CreateTextureFromSurface(*conf->render, *conf->surface);
	if(!*conf->tex)
		return 0;
	SDL_QueryTexture(*conf->tex, NULL, NULL, &spriteRect->w, &spriteRect->h);
	spriteRect->w *= 3;
	spriteRect->h *= 3;
	SDL_FreeSurface(*conf->surface);
	conf->battleState = 0;

	conf->battle = (PlayerBattle*) malloc(sizeof(PlayerBattle) * 50);
	conf->battle->hp = 100;
	conf->battle->mp = 120;
	conf->battle->atk = 15;
	conf->battle->def = 20;

	return 1;
}

void changeSprite(PlayerConf* conf,SDL_Rect* sprite_rect,int reset)
{	/*

		1 - front
		2 - left        <---- PADRÃO
		3 - right
		4 - back
 */

	if(reset){
		if(!strcmp(conf->name,"crono")){
			switch(conf->state){
			case 1: *conf->surface = IMG_Load("Resourcers/cronoNormal1.png");break;
			case 2: *conf->surface = IMG_Load("Resourcers/cronoNormalLeft1.png");break;
			case 3: *conf->surface = IMG_Load("Resourcers/cronoNormalRight1.png");break;
			case 4: *conf->surface = IMG_Load("Resourcers/cronoNormalDown1.png");break;
			}
		}
	}else{


		if(conf->up)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkFront",conf->numSprite, ".png");

		if(conf->left)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkLeft",conf->numSprite, ".png");

		if(conf->rigth)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkRight",conf->numSprite, ".png");

		if(conf->down || conf->flag == 2)
			sprintf(conf->pathSprite, "%s%d%s", "Resourcers/cronoWalkDown", conf->numSprite, ".png");

		//battle mode

		if(conf->battleState && conf->state && conf->ready)
			sprintf(conf->pathSprite, "%s%d%s","Resourcers/battle",conf->numSprite,".png");

		else if(conf->battleState && conf->state == 2 && conf->ready)
			sprintf(conf->pathSprite,"%s%d%s","Resourcers/battleLeft",conf->numSprite,".png");


		*conf->surface = IMG_Load(conf->pathSprite);
	}

	if(!*conf->surface)
		SDL_Log("erro aqui ó %s", SDL_GetError());

	*conf->tex = SDL_CreateTextureFromSurface(*conf->render, *conf->surface );
	if(!*conf->tex)
	{
		SDL_Log("%s", SDL_GetError());
	}
	SDL_QueryTexture(*conf->tex, NULL, NULL, &sprite_rect->w, &sprite_rect->h);
	sprite_rect->w *= 3;
	sprite_rect->h *= 3;
	SDL_FreeSurface(*conf->surface);
}

