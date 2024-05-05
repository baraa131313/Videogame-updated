#include "bg.h"
void init_bg(bg *bg) 
{
char ch[50]; 
for(int i=1;i<31;i++)
{
sprintf(ch,"backgrounds/%d.jpg",i);
bg->images[i-1] = IMG_Load(ch);
}
bg->pos.w=bg->images[1]->w;
bg->pos.h=bg->images[1]->h;
bg->camera.x=0;
bg->camera.y=0;
bg->camera.w=bg->images[1]->w;
bg->camera.h=bg->images[1]->h;
bg->anim=0;
bg->pos.x=0;
bg->pos.y=0;
}
void scrolling(bg *bg,int d,int pas)
{
if(d==1) bg->camera.x-=pas;
if(d==2) bg->camera.y-=pas;
}
void garder_image_sur_ecran(bg *bg, SDL_Surface *screen)
{
 
if(bg->camera.x<0) bg->camera.x=0;
if(bg->camera.y<0) bg->camera.y=0;
if(bg->camera.x>bg->camera.w-screen->w) bg->camera.x=bg->camera.w-screen->w;
if(bg->camera.y>bg->camera.h-screen->h) bg->camera.y=bg->camera.h-screen->h;
}
void afficher_bg(bg bg,SDL_Surface *screen)
{
SDL_BlitSurface(bg.images[bg.anim],&bg.camera,screen,&bg.pos);
SDL_Delay(50);

}
void animation(bg* bg)
{
bg->anim++;
if(bg->anim==31)bg->anim=0;
}

void animation_start(SDL_Surface *screen)
{
SDL_Surface *image;
image= IMG_Load("backgrounds/1.jpg");
SDL_Rect pos;pos.x=screen->w+1000;pos.y=0;
SDL_Delay(500);
while(pos.x>10)
{
SDL_BlitSurface(image,NULL,screen,&pos);
pos.x-=10;
SDL_Flip(screen);
}
}
void play_sound(char *sound_file)
{
Mix_Chunk *sound = Mix_LoadWAV(sound_file);
    if (sound == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
    Mix_PlayChannel(-1, sound, 0);
}  
void musique(int stage)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Music *musique; 
    char nom_musique[40];
	sprintf(nom_musique,"musiques/%d.mp3",stage); 
	musique = Mix_LoadMUS(nom_musique); 
    Mix_PlayMusic(musique, -1);
	Mix_VolumeMusic(128);
}

void partage_ecran(bg bg1,bg bg2,SDL_Surface *screen)
{
SDL_BlitSurface(bg1.images[bg1.anim],&bg1.camera,screen,NULL);
bg2.pos.x=screen->w/2;
SDL_BlitSurface(bg2.images[bg2.anim],&bg2.camera,screen,&bg2.pos);
}


void save_score(Score score) {
    FILE *fp;
    fp = fopen("score.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    fprintf(fp, "%s %d\n", score.name, score.score);
    fclose(fp);
}

void show_top_scores(SDL_Surface *screen) {
    TTF_Font *font;
    SDL_Color textColor = {255, 255, 255}; 
    SDL_Surface *textSurface;
    SDL_Rect textPos;
    char scoreStr[30];
    Score scores[100] = {0};
    int i, j;
    FILE *fp;

    // Load the font
    font = TTF_OpenFont("font.ttf", 28);
    if (font == NULL) {
        printf("Error opening font\n");
        return;
    }

    // Read the scores from the file
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (i = 0; i < 100; i++) {
        if (fscanf(fp, "%s %d", scores[i].name, &scores[i].score) == EOF) {
            break;
        }
    }
    fclose(fp);
    // Sort the scores in descending order
    for (i = 0; i < 99; i++) {
        for (j = i+1; j < 100; j++) {
            if (scores[j].score > scores[i].score) {
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // Display the top 3 scores on screen
    for (i = 0; i < 3; i++) {
        sprintf(scoreStr, "%d. %s: %d", i+1, scores[i].name, scores[i].score);
        textSurface = TTF_RenderText_Solid(font, scoreStr, textColor);
        textPos.x = (screen->w - textSurface->w) / 2;
        textPos.y = 50 + i * 50;
        SDL_BlitSurface(textSurface, NULL, screen, &textPos);
        SDL_FreeSurface(textSurface);
    }
SDL_Flip(screen);SDL_Delay(1500);
    TTF_CloseFont(font);
}


