#ifndef _BG_H_
#define _BG_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
typedef struct{
SDL_Rect pos;
SDL_Surface *images[50];
int anim;
SDL_Rect camera;
}bg;

typedef struct {
    char name[20];
    int score;
} Score;
void init_bg(bg *bg);
void afficher_bg(bg bg,SDL_Surface *screen);
void anim_bg(bg *bg);
void scrolling(bg *bg,int d,int pas);
void animation(bg* bg);
void animation_start(SDL_Surface *screen);
void play_sound( char *sound_file);
void musique(int stage);
void partage_ecran(bg bg1,bg bg2,SDL_Surface *screen);
void garder_image_sur_ecran(bg *bg, SDL_Surface *screen);
void save_score(Score score);
void show_top_scores(SDL_Surface *screen);

#endif
