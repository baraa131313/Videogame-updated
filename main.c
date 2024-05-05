#include "bg.h"

void main()
{
bg bg,bg2,bg3;
init_bg(&bg);
init_bg(&bg2);
init_bg(&bg3);

char nom[30];
printf("Veuillez taper votre nom:");
scanf("%s",nom);
SDL_Init(SDL_INIT_EVERYTHING);
TTF_Init();
SDL_EnableKeyRepeat(60,0);
SDL_Surface *screen =SDL_SetVideoMode(1000,750,32,SDL_SWSURFACE);
int q=0;
animation_start(screen);
if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
musique(1);
SDL_Event event;
int partage = 0;

    SDL_Rect button_rect = { 10, 10, 0, 0 };
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* button_surface = TTF_RenderText_Solid(TTF_OpenFont("font.ttf", 32),"Show Scores",textColor);
	button_rect.w = button_surface->w;
    button_rect.h = button_surface->h;
while(q==0)
{
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                q=1;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.x >= button_rect.x && event.button.x < button_rect.x + button_rect.w &&
                    event.button.y >= button_rect.y && event.button.y < button_rect.y + button_rect.h) {
                    show_top_scores(screen);
                }
                break;
			case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    q=1;
                    break;
                case SDLK_p:
                    if (partage == 1) partage =0;else partage=1;
                    break;
                case SDLK_UP:
                    scrolling(&bg,2,20);
                    break;
                case SDLK_DOWN:
                    scrolling(&bg,2,-20);
                    break;
                case SDLK_LEFT:
                    scrolling(&bg,1,20);
                    scrolling(&bg3,1,20);
                    break;
                case SDLK_RIGHT:
                    scrolling(&bg,1,-20);
                    scrolling(&bg3,1,-20);
                    break;
		case SDLK_z:
                    scrolling(&bg2,2,20);
                    break;
                case SDLK_s:
                    scrolling(&bg2,2,-20);
                    break;
                case SDLK_q:
                    scrolling(&bg2,1,20);
                    break;
                case SDLK_d:
                    scrolling(&bg2,1,-20);
                    break;
                //default:
                    break;
                case SDLK_a:
                    play_sound("musiques/pickupcoin.wav");
                    break;
                case SDLK_b:
                    play_sound("musiques/jump.wav");
                    break;
                case SDLK_c:
                    play_sound("musiques/danger.wav");
                    break;
               
            }
            default:
                break;
        }
    }
animation(&bg);
animation(&bg2);
garder_image_sur_ecran(&bg,screen);
garder_image_sur_ecran(&bg2,screen);
if(partage == 1)
partage_ecran(bg,bg2,screen);
else
afficher_bg(bg,screen);
//afficher_bg(bg3,screen);
//bg3.pos.x=bg.pos.w-bg.camera.x;
SDL_BlitSurface(button_surface, NULL, screen, &button_rect);
SDL_Delay(50);
SDL_Flip(screen);
}

Score score;
strcpy(score.name,nom);
score.score = bg.camera.x;
save_score(score);
SDL_Quit();
}
