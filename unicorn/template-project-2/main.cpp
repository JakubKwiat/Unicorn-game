#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define LEVEL_HEIGHT 385
#define BACKGROUND_WIDTH 6400
#define BACKGROUND_HEIGHT 4000
struct player {

};
// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
SDL_Rect DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	return dest;
};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	int t1, t2, jumptime, quit, rc, control, jump, dashtime, loop, jump_number, play, death,starreset_1,starreset_2,starreset_3,reset_1,reset_2,reset_3,explosiontimer;
	double delta, worldTime, distance, move, speed, power, xgracz, yplayer, colision,points;
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* eti;
	SDL_Surface* obstacle_1bmp;
	SDL_Surface* obstacle_2bmp;
	SDL_Surface* obstacle_3bmp;
	SDL_Surface* obstacle_1_rightbmp;
	SDL_Surface* obstacle_2_rightbmp;
	SDL_Surface* obstacle_3_rightbmp;
	SDL_Surface* platform_200x45bmp;
	SDL_Surface* platform_300x45bmp;
	SDL_Surface* platform_400x80bmp;
	SDL_Surface* platform_600x50bmp;
	SDL_Surface* platform_200x45_rightbmp;
	SDL_Surface* platform_300x45_rightbmp;
	SDL_Surface* platform_400x80_rightbmp;
	SDL_Surface* platform_600x50_rightbmp;
	SDL_Surface* stalagtite_100x315bmp;
	SDL_Surface* background;
	SDL_Surface* menu;
	SDL_Surface* one_life;
	SDL_Surface* two_lives;
	SDL_Surface* heart;
	SDL_Surface* star;
	SDL_Surface* dolphin;
	SDL_Surface* explosion;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect player;
	SDL_Rect platform_start_upper;
	SDL_Rect platform_start_right;
	SDL_Rect platform_1_upper;
	SDL_Rect platform_1_right;
	SDL_Rect platform_2_upper;
	SDL_Rect platform_2_right;
	SDL_Rect platform_3_upper;
	SDL_Rect platform_3_right;
	SDL_Rect platform_4_upper;
	SDL_Rect platform_4_right;
	SDL_Rect platform_5_upper;
	SDL_Rect platform_5_right;
	SDL_Rect platform_6_upper;
	SDL_Rect platform_6_right;
	SDL_Rect platform_7_upper;
	SDL_Rect platform_7_right;
	SDL_Rect platform_8_upper;
	SDL_Rect platform_8_right;
	SDL_Rect platform_9_upper;
	SDL_Rect platform_9_right;
	SDL_Rect platform_10_upper;
	SDL_Rect platform_10_right;
	SDL_Rect platform_11_upper;
	SDL_Rect platform_11_right;
	SDL_Rect platform_12_upper;
	SDL_Rect platform_12_right;
	SDL_Rect platform_13_upper;
	SDL_Rect platform_13_right;
	SDL_Rect platform_14_upper;
	SDL_Rect platform_14_right;
	SDL_Rect stalagtite_1;
	SDL_Rect stalagtite_2;
	SDL_Rect obstacle_1_upper;
	SDL_Rect obstacle_1_right;
	SDL_Rect obstacle_2_upper;
	SDL_Rect obstacle_2_right;
	SDL_Rect obstacle_3_upper;
	SDL_Rect obstacle_3_right;
	SDL_Rect obstacle_4_upper;
	SDL_Rect obstacle_4_right;
	SDL_Rect star_1;
	SDL_Rect star_2;
	SDL_Rect star_3;
	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// tryb pe³noekranowy / fullscreen mode
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	eti = SDL_LoadBMP("./eti.bmp");
	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	background = SDL_LoadBMP("./background.bmp");
	if (background == NULL) {
		printf("SDL_LoadBMP(background.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	obstacle_1bmp = SDL_LoadBMP("./przeszkoda_1.bmp");
	if (obstacle_1bmp == NULL) {
		printf("SDL_LoadBMP(przeszkoda_1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	obstacle_1_rightbmp = SDL_LoadBMP("./przeszkoda_1_prawy.bmp");
	if (obstacle_1_rightbmp == NULL) {
		printf("SDL_LoadBMP(przeszkoda_1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	obstacle_2bmp = SDL_LoadBMP("./przeszkoda_2.bmp");
	if (obstacle_2bmp == NULL) {
		printf("SDL_LoadBMP(przeszkoda_2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	obstacle_2_rightbmp = SDL_LoadBMP("./przeszkoda_2_prawy.bmp");
	if (obstacle_2_rightbmp == NULL) {
		printf("SDL_LoadBMP(przeszkoda_2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	obstacle_3bmp = SDL_LoadBMP("./przeszkoda_3.bmp");
	if (obstacle_3bmp == NULL) {
		printf("SDL_LoadBMP(przeszkoda_3.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	obstacle_3_rightbmp = SDL_LoadBMP("./przeszkoda_3_prawy.bmp");
	if (obstacle_3_rightbmp == NULL) {
		printf("SDL_LoadBMP(przeszkoda_3.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_200x45bmp = SDL_LoadBMP("./platforma_200x45.bmp");
	if (platform_200x45bmp == NULL) {
		printf("SDL_LoadBMP(platforma_200x45.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_200x45_rightbmp = SDL_LoadBMP("./platforma_200x45_prawy.bmp");
	if (platform_200x45_rightbmp == NULL) {
		printf("SDL_LoadBMP(platforma_200x45.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_300x45bmp = SDL_LoadBMP("./platforma_300x45.bmp");
	if (platform_300x45bmp == NULL) {
		printf("SDL_LoadBMP(platforma_300x45.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_300x45_rightbmp = SDL_LoadBMP("./platforma_300x45_prawy.bmp");
	if (platform_300x45_rightbmp == NULL) {
		printf("SDL_LoadBMP(platforma_300x45.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_400x80bmp = SDL_LoadBMP("./platforma_400x80.bmp");
	if (platform_400x80bmp == NULL) {
		printf("SDL_LoadBMP(platforma_400x80.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_400x80_rightbmp = SDL_LoadBMP("./platforma_400x80_prawy.bmp");
	if (platform_400x80_rightbmp == NULL) {
		printf("SDL_LoadBMP(platforma_400x80.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_600x50bmp = SDL_LoadBMP("./platforma_600x50.bmp");
	if (platform_600x50bmp == NULL) {
		printf("SDL_LoadBMP(platforma_600x50.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	platform_600x50_rightbmp = SDL_LoadBMP("./platforma_600x50_prawy.bmp");
	if (platform_600x50_rightbmp == NULL) {
		printf("SDL_LoadBMP(platforma_600x50.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	stalagtite_100x315bmp = SDL_LoadBMP("./stalaktyt.bmp");
	if (stalagtite_100x315bmp == NULL) {
		printf("SDL_LoadBMP(stalaktyt.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	menu = SDL_LoadBMP("./menu.bmp");
	if (menu == NULL) {
		printf("SDL_LoadBMP(menu.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	one_life = SDL_LoadBMP("./1zycie.bmp");
	if (one_life == NULL) {
		printf("SDL_LoadBMP(1zycie.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	two_lives = SDL_LoadBMP("./2zycia.bmp");
	if (two_lives == NULL) {
		printf("SDL_LoadBMP(2zycia.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	heart = SDL_LoadBMP("./zycie.bmp");
	if (heart == NULL) {
		printf("SDL_LoadBMP(zycie.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	star = SDL_LoadBMP("./gwiazda.bmp");
	if (star == NULL) {
		printf("SDL_LoadBMP(gwiazda.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	dolphin = SDL_LoadBMP("./delfin.bmp");
	if (dolphin == NULL) {
		printf("SDL_LoadBMP(delfin.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	explosion = SDL_LoadBMP("./wybuch.bmp");
	if (explosion == NULL) {
		printf("SDL_LoadBMP(wybuch.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();
	quit = 0;
	worldTime = 0;
	jumptime = 0;
	move = 0;
	control = 0;
	jump = 0;
	speed = 0.01;
	dashtime = 0;
	loop = 0;
	power = 0.2;
	yplayer = 0;
	jump_number = 0;
	colision = 0;
	play = 0;
	death = 0;
	points = 0;
	reset_1 = 0;
	reset_2 = 0;
	reset_3 = 0;
	starreset_1 = 0;
	starreset_2 = 0;
	starreset_3 = 0;
	distance = 0;
	speed = 0.03;
	explosiontimer = 0;
	while (!quit) {
		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna³ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		delta = (t2 - t1) * 0.001;
		t1 = t2;
		worldTime += delta;
		
		if ((death == 1)&&(play==0)) {
			DrawSurface(screen, two_lives, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}
		if ((death == 2)&&(play==0)) {
			DrawSurface(screen, one_life, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}
		if ((play == 0)&&(death==0)) {
			DrawSurface(screen, menu, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}
		if (play == 1) {
			//Zapêtlanie siê planszy
			if (move < 0) {
				move = BACKGROUND_WIDTH - SCREEN_WIDTH;
			}
			if (move > BACKGROUND_WIDTH - SCREEN_WIDTH) {
				move = 0;
			}
			//obsluga dasha
			if (dashtime >= 1 && dashtime <= 200) {
				move = move + 0.5;
				dashtime++;
			}
			if (dashtime > 300) {
				dashtime = 0;
			}
			// obsluga skoku
			if (jump == 1) {
				power = power + 0.003;
			}
			if ((jumptime >= 1) && (jumptime <= 500)) {
				if ((jumptime < 150) && (jump == 0)) {
					jumptime = 150;
				}
				if (jumptime >= 150) {
					yplayer = yplayer + power;
				}
				if (dashtime > 0) {
					jumptime = 0;
				}
				jumptime++;
			}
			if (jumptime > 500) {
				power = 0;
				jumptime = 0;
				jump = 0;
			}
			//xgracz = player.x;
			if (SDL_HasIntersection(&player, &platform_start_right)) colision = 1, yplayer = 0, move = 0;
			if (SDL_HasIntersection(&player, &platform_start_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_1_right)) 
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer=0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_1_upper))jump_number = 0;;
			if (SDL_HasIntersection(&player, &platform_2_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_2_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_3_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_3_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_4_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_4_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_5_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_5_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_6_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_6_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_7_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_7_upper)) jump_number=0;
			if (SDL_HasIntersection(&player, &platform_8_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_8_upper)) jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_9_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_9_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_10_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_10_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_11_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_11_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_12_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_12_upper)) jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_13_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_13_upper)) jump_number = 0;
			if (SDL_HasIntersection(&player, &platform_14_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &platform_14_upper)) jump_number = 0;
			if (SDL_HasIntersection(&player, &stalagtite_1))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &stalagtite_2))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &obstacle_1_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &obstacle_1_upper)) jump_number = 0;
			if (SDL_HasIntersection(&player, &obstacle_2_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &obstacle_2_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &obstacle_3_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &obstacle_3_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &obstacle_4_right))
			{
				colision = 1;
				if (explosiontimer == 100) {
					yplayer = 0, move = 0;
				}
			}
			if (SDL_HasIntersection(&player, &obstacle_4_upper))jump_number = 0;
			if (SDL_HasIntersection(&player, &star_1)) {
				if (dashtime == 0) {
					colision = 1, yplayer = 0, move = 0;
				}
				if ((dashtime != 0)&&(reset_1==0)) {
					points = points + 100;
					starreset_1 = distance;
					reset_1 = 1;
				}
			};
			if (SDL_HasIntersection(&player, &star_2)) {
				if (dashtime == 0) {
					colision = 1, yplayer = 0, move = 0;
				}
				if ((dashtime != 0) && (reset_2 == 0)) {
					points = points + 100;
					starreset_2 = distance;
					reset_2 = 1;
				}
			};
			if (SDL_HasIntersection(&player, &star_3)) {
				if (dashtime == 0) {
					colision = 1, yplayer = 0, move = 0;
				}
				if ((dashtime != 0) && (reset_3 == 0)) {
					points = points + 100;
					starreset_3 = distance;
					reset_3 = 1;
				}
			};

			if ((!SDL_HasIntersection(&player, &platform_start_upper)) && (!SDL_HasIntersection(&player, &platform_1_upper)) && (!SDL_HasIntersection(&player, &platform_2_upper)) && (!SDL_HasIntersection(&player, &platform_3_upper)) && (!SDL_HasIntersection(&player, &platform_4_upper)) && (!SDL_HasIntersection(&player, &platform_5_upper)) && (!SDL_HasIntersection(&player, &platform_6_upper)) && (!SDL_HasIntersection(&player, &platform_7_upper)) && (!SDL_HasIntersection(&player, &platform_8_upper)) && (!SDL_HasIntersection(&player, &platform_9_upper)) && (!SDL_HasIntersection(&player, &platform_10_upper)) && (!SDL_HasIntersection(&player, &platform_11_upper)) && (!SDL_HasIntersection(&player, &platform_12_upper)) && (!SDL_HasIntersection(&player, &platform_13_upper)) && (!SDL_HasIntersection(&player, &platform_14_upper)) && (jump == 0) && (jumptime == 0) && (control % 2 == 1) && (!SDL_HasIntersection(&player, &obstacle_1_upper)) && (!SDL_HasIntersection(&player, &obstacle_2_upper)) && (!SDL_HasIntersection(&player, &obstacle_3_upper)) && (!SDL_HasIntersection(&player, &obstacle_4_upper))) {
				yplayer = yplayer - 0.1;
			}
			DrawSurface(screen, background, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			if (colision == 0) {
				player = DrawSurface(screen, eti, 45, 272.5+45-100 );//317.5
			
			}
			if ((colision == 1)&&(explosiontimer<=100)) {
					DrawSurface(screen, explosion, 45, 272.5 + 45-100);
			}
			stalagtite_1 = DrawSurface(screen, stalagtite_100x315bmp, 200 - move, LEVEL_HEIGHT - 500 + yplayer-100);//stalaktyt_1
			stalagtite_2 = DrawSurface(screen, stalagtite_100x315bmp, 2250 - move, LEVEL_HEIGHT - 500 + yplayer-100);//stalaktyt_2
			platform_start_right = DrawSurface(screen, platform_200x45_rightbmp, 100 - move, LEVEL_HEIGHT + 5+yplayer-100);//platforn_start
			platform_start_upper = DrawSurface(screen, platform_200x45bmp, 100 - move, LEVEL_HEIGHT + yplayer-100);//platform_start
			platform_1_upper = DrawSurface(screen, platform_300x45bmp, 400 - move, LEVEL_HEIGHT - 22.5 + yplayer-100); //platform_1
			platform_1_right = DrawSurface(screen, platform_300x45_rightbmp, 400 - move, LEVEL_HEIGHT - 20 + yplayer-100); //platform_1
			obstacle_1_upper = DrawSurface(screen, obstacle_1bmp, 480 - move, LEVEL_HEIGHT - 80 + yplayer-100); //przeszkoda_1;
			obstacle_1_right = DrawSurface(screen, obstacle_1_rightbmp, 480 - move, LEVEL_HEIGHT - 75 + yplayer-100); //przeszkoda_1;
			platform_2_upper = DrawSurface(screen, platform_200x45bmp, 700 - move, LEVEL_HEIGHT - 200 + yplayer-100); //platform_2
			platform_2_right = DrawSurface(screen, platform_200x45_rightbmp, 700 - move, LEVEL_HEIGHT - 195 + yplayer-100); //platform_2
			platform_3_upper = DrawSurface(screen, platform_600x50bmp, 1200 - move, LEVEL_HEIGHT - 400 + yplayer-100); //platform_3
			platform_3_right = DrawSurface(screen, platform_600x50_rightbmp, 1200 - move, LEVEL_HEIGHT - 395 + yplayer-100); //platform_3
			star_1 = DrawSurface(screen, star, 1300 - move, LEVEL_HEIGHT - 480 + yplayer-100);
			platform_4_upper = DrawSurface(screen, platform_400x80bmp, 1600 - move, LEVEL_HEIGHT - 250 + yplayer-100); //platform_4
			platform_4_right = DrawSurface(screen, platform_400x80_rightbmp, 1600 - move, LEVEL_HEIGHT - 245 + yplayer-100); //platform_4
			platform_5_upper = DrawSurface(screen, platform_200x45bmp, 2000 - move, LEVEL_HEIGHT - 100 + yplayer-100); //platform_5
			platform_5_right = DrawSurface(screen, platform_200x45_rightbmp, 2000 - move, LEVEL_HEIGHT - 95 + yplayer - 100); //platform_5
			obstacle_2_upper = DrawSurface(screen, obstacle_1bmp, 2040 - move, LEVEL_HEIGHT - 157.5 + yplayer - 100);
			obstacle_2_right = DrawSurface(screen, obstacle_1_rightbmp, 2040 - move, LEVEL_HEIGHT - 152.5 + yplayer - 100);//przeszkoda_2
			platform_6_upper = DrawSurface(screen, platform_300x45bmp, 2250 - move, LEVEL_HEIGHT - 22.5 + yplayer - 100); //platform_6
			platform_6_right = DrawSurface(screen, platform_300x45_rightbmp, 2250 - move, LEVEL_HEIGHT - 20 + yplayer - 100); //platform_6
			platform_7_upper = DrawSurface(screen, platform_600x50bmp, 2800 - move, LEVEL_HEIGHT - 170 + yplayer - 100);//platform_7
			platform_7_right = DrawSurface(screen, platform_600x50_rightbmp, 2800 - move, LEVEL_HEIGHT - 165 + yplayer - 100);//platform_7
			obstacle_3_upper = DrawSurface(screen, obstacle_3bmp, 2800 - move, LEVEL_HEIGHT - 225 + yplayer - 100);//przeszkoda_3
			obstacle_3_right = DrawSurface(screen, obstacle_3_rightbmp, 2800 - move, LEVEL_HEIGHT - 220 + yplayer - 100);//przeszkoda_3
			platform_8_upper = DrawSurface(screen, platform_400x80bmp, 3200 - move, LEVEL_HEIGHT - 300 + yplayer - 100); //platform_8
			platform_8_right = DrawSurface(screen, platform_400x80_rightbmp, 3200 - move, LEVEL_HEIGHT - 295 + yplayer - 100); //platform_8
			star_2 = DrawSurface(screen, star, 3200 - move, LEVEL_HEIGHT - 400 + yplayer - 100);
			platform_9_upper = DrawSurface(screen, platform_300x45bmp, 3500 - move, LEVEL_HEIGHT - 420 + yplayer - 100); //platform_9
			platform_9_right = DrawSurface(screen, platform_300x45_rightbmp, 3500 - move, LEVEL_HEIGHT - 415 + yplayer - 100); //platform_9
			platform_10_upper = DrawSurface(screen, platform_200x45bmp, 3800 - move, LEVEL_HEIGHT - 310 + yplayer - 100); //platform_10
			platform_10_right = DrawSurface(screen, platform_200x45_rightbmp, 3800 - move, LEVEL_HEIGHT - 305 + yplayer - 100); //platform_10
			platform_11_upper = DrawSurface(screen, platform_600x50bmp, 4300 - move, LEVEL_HEIGHT - 100 + yplayer - 100); //platform_11
			platform_11_right = DrawSurface(screen, platform_600x50_rightbmp, 4300 - move, LEVEL_HEIGHT - 95 + yplayer - 100); //platform_11
			obstacle_4_upper = DrawSurface(screen, obstacle_3bmp, 4400 - move, LEVEL_HEIGHT - 155 + yplayer - 100);//przeszkoda_4
			obstacle_4_right = DrawSurface(screen, obstacle_3_rightbmp, 4400 - move, LEVEL_HEIGHT - 150 + yplayer - 100);//przeszkoda_4
			platform_12_upper = DrawSurface(screen, platform_300x45bmp, 4800 - move, LEVEL_HEIGHT - 22.5 + yplayer - 100);//platform_12
			platform_12_right = DrawSurface(screen, platform_300x45_rightbmp, 4800 - move, LEVEL_HEIGHT - 20 + yplayer - 100);//platform_12
			platform_13_upper = DrawSurface(screen, platform_400x80bmp, 5200 - move, LEVEL_HEIGHT - 200 + yplayer - 100);//platform_13
			platform_13_right = DrawSurface(screen, platform_400x80_rightbmp, 5200 - move, LEVEL_HEIGHT - 195 + yplayer - 100);//platform_13
			star_3 = DrawSurface(screen, star, 5200 - move, LEVEL_HEIGHT - 295 + yplayer - 100);
			platform_14_upper = DrawSurface(screen, platform_300x45bmp, 5650 - move, LEVEL_HEIGHT - 145 + yplayer - 100); //platform_14
			platform_14_right = DrawSurface(screen, platform_300x45_rightbmp, 5650 - move, LEVEL_HEIGHT - 140 + yplayer - 100); //platform_14
			DrawSurface(screen, platform_300x45bmp, 6160 - move, LEVEL_HEIGHT - 22.5 + yplayer - 100);//tylko obrazek do zapetlenia
			DrawSurface(screen, platform_200x45bmp, 5860 - move, LEVEL_HEIGHT + yplayer - 100);//
			DrawSurface(screen, stalagtite_100x315bmp, 5960 - move, LEVEL_HEIGHT - 500 + yplayer - 100);//
			DrawSurface(screen, obstacle_1bmp, 6240 - move, LEVEL_HEIGHT - 80 + yplayer - 100);// tylko obrazek do zapetlenia
			//liczba zyc graficznie
			if (death == 0) {
				DrawSurface(screen, heart, 615 , 415);
				DrawSurface(screen, heart, 565 , 415);
				DrawSurface(screen, heart, 515 , 415);
			}
			if (death == 1) {
				DrawSurface(screen, heart, 615 , 415);
				DrawSurface(screen, heart, 565, 415);
			}
			if (death == 2) {
				DrawSurface(screen, heart, 615, 415);
			}
			if ((yplayer < -500)||(explosiontimer==150)) {
				death++;
				play = 0;
				colision = 0;
				explosiontimer = 0;
				if (death > 2) {
					death = 0;
				}
			}
			if (points < 200) {
				DrawSurface(screen, dolphin, 50, 415);
			}
			if (points >200 && points<400) {
				DrawSurface(screen, dolphin, 50, 415);
				DrawSurface(screen, dolphin, 100, 415);
			}
			if (points > 400 && points<800 ) {
				DrawSurface(screen, dolphin, 50, 415);
				DrawSurface(screen, dolphin, 100, 415);
				DrawSurface(screen, dolphin, 150, 415);
			}
			if (points>800 && points < 1200 ) {
				DrawSurface(screen, dolphin, 50, 415);
				DrawSurface(screen, dolphin, 100, 415);
				DrawSurface(screen, dolphin, 150, 415);
				DrawSurface(screen, dolphin, 200, 415);
			}
			if (points >1200 && points <1800) {
				DrawSurface(screen, dolphin, 50, 415);
				DrawSurface(screen, dolphin, 100, 415);
				DrawSurface(screen, dolphin, 150, 415);
				DrawSurface(screen, dolphin, 200, 415);
				DrawSurface(screen, dolphin, 250, 415);
			}
			if (points >1800 && points < 2400) {
				DrawSurface(screen, dolphin, 50, 415);
				DrawSurface(screen, dolphin, 100, 415);
				DrawSurface(screen, dolphin, 150, 415);
				DrawSurface(screen, dolphin, 200, 415);
				DrawSurface(screen, dolphin, 250, 415);
				DrawSurface(screen, dolphin, 300, 415);
			}
			if (points > 2400) {
				DrawSurface(screen, dolphin, 50, 415);
				DrawSurface(screen, dolphin, 100, 415);
				DrawSurface(screen, dolphin, 150, 415);
				DrawSurface(screen, dolphin, 200, 415);
				DrawSurface(screen, dolphin, 250, 415);
				DrawSurface(screen, dolphin, 300, 415);
				DrawSurface(screen, dolphin, 350, 415);
			}
			//resetowanie sie gwiazdy
			if (distance - starreset_1 > 400) {
				reset_1 = 0;
			}
			if (distance - starreset_2 > 400) {
				reset_2 = 0;
			}
			if (distance - starreset_3 > 400) {
				reset_3 = 0;
			}
			// tekst informacyjny / info text
			DrawRectangle(screen, 0, 440, 4 * SCREEN_WIDTH, 40, czerwony, niebieski);
			//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
			sprintf(text, "czas trwania = %.1lf s , sterowanie strzalkami ,d - zmiana sterowania", worldTime);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 448, text, charset);
			//	      "Esc - exit, \030 - faster, \031 - slower"
			sprintf(text, "punkty = %.1lf s, z - skok, x - dash, n - nowa gra ",points);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 464, text, charset);
		}
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
				else if (event.key.keysym.sym == SDLK_n) {
					worldTime = 0;
					move = 0;
					yplayer = 0;
					colision = 0;
					speed = 0;
					control = 0;
				}
				else if (event.key.keysym.sym == SDLK_d) {
					control++;
				}
				else if (event.key.keysym.sym == SDLK_p) {
					if (play==0) {
						play = 1;
						colision = 0;
						move = 0;
						worldTime = 0;
						yplayer = 0;
						control = 0;
						speed = 0;
					}
				}
				else if (event.key.keysym.sym == SDLK_UP) {
					if (control % 2 == 0) {
						yplayer = yplayer + 10;
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					if (control % 2 == 0) {
						yplayer = yplayer - 10;
					}
					
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					if (control % 2 == 0) {
						move = move + 10;
						points = points + 5;
						distance = distance + 10;
					}
				}
				else if (event.key.keysym.sym == SDLK_LEFT) {
					if (control % 2 == 0) {
						points = points -5;
						move = move - 10;
						distance = distance - 10;
					}
				}
				else if (event.key.keysym.sym == SDLK_z) {
					if (control % 2 == 1) {
						if (jump_number < 2) {
							jump = 1;
							jumptime = 1;
							jump_number++;
						}
					}
				}
				else if (event.key.keysym.sym == SDLK_x) {
					if (control % 2 == 1) {
						dashtime = 1;
					}
				}
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_z) {
					jump = 0;
				}
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
		// automatyczny bieg w prawo
		if (control % 2 == 1) {
			if (loop % 100 == 0) {
				speed = speed + 0.005;
			}
			move = move + speed;
			points = points + speed/10;
			distance = distance + speed;
		}
		loop++;
		if (colision == 1) {
			explosiontimer++;
		}
	};

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};
