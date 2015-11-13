#include <allegro.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void init();
void deinit();
void reset();
void Buffer();
void MovePlayer();
void AnimationMovePlayer();
void Function();
void calc();

BITMAP *PlayerImage;
BITMAP *BufferImage;
BITMAP *BackGroundImage;
BITMAP *Click;
BITMAP *SkillBar;

int Mouse_x;
int Mouse_y;
int Direcao;
int DirecaoVal=1;
int rotate;
int zoom=1;
int SpriteVal;
int Backposs_x;
int Backposs_y;
double angx;
double angy;
double angax;
double angay;
double tg;
double trix, triy;
int op=0;
bool press=true;

struct Player
{
    double x;
    double y;
    int Val;
};
Player ObjPlayer;

int main()
{
	init();

	reset();

	install_int(Buffer, 20);

    install_int(MovePlayer, 7);

    install_int(AnimationMovePlayer, 300);

    install_int(Function, 80);

    while (!key[KEY_ESC])
    {
		/* put your code here */
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

void reset()
{
     BufferImage = create_bitmap(1280, 720);

     PlayerImage = load_bitmap("animation/human/Front1.bmp", NULL);

     BackGroundImage = load_bitmap("texture/BackGround.bmp", NULL);

     Click = load_bitmap("animation/Click.bmp", NULL);

     SkillBar = load_bitmap("animation/SkillBar.bmp", NULL);

     ObjPlayer.y=360-90;
     ObjPlayer.x=640-20;

     Mouse_y=(int)ObjPlayer.y+90;
     Mouse_x=(int)ObjPlayer.x+20;

     Backposs_x=Mouse_y;
     Backposs_y=Mouse_x;

     install_mouse();
     enable_hardware_cursor();

     select_mouse_cursor(MOUSE_CURSOR_ARROW);

}
END_OF_FUNCTION(reset);

LOCK_FUNCTION(reset);

void calc()
{
     triy=ObjPlayer.y+90-Mouse_y;
     trix=ObjPlayer.x+20-Mouse_x;
     tg=triy/trix;
     angy=(atan(tg) * 180 / PI)/100;
     angx=0.9-angy;
     angay=((atan(tg) * 180 / PI)/100)*-1;
     angax=(0.9-angay)*-1;
}

void Buffer()
{

     pivot_scaled_sprite(BufferImage, BackGroundImage, (int)ObjPlayer.x+20, (int)ObjPlayer.y+90, (int)ObjPlayer.x+20, (int)ObjPlayer.y+90, itofix(rotate), itofix(zoom));
     rotate_scaled_sprite(BufferImage, PlayerImage, (int)ObjPlayer.x, (int)ObjPlayer.y, 0, itofix(zoom));
     draw_sprite(BufferImage, SkillBar, 335, 650);
     if(press==true)
     {
         textprintf_ex(BufferImage, font, 10, 10, makecol(225, 225, 225), -1, "Rotacao: %d", rotate);
         textprintf_ex(BufferImage, font, 10, 30, makecol(225, 225, 225), -1, "Zoom: %d", zoom);
         textprintf_ex(BufferImage, font, 10, 50, makecol(225, 225, 225), -1, "X: %d", mouse_x);
         textprintf_ex(BufferImage, font, 10, 70, makecol(225, 225, 225), -1, "Y: %d", mouse_y);
         textprintf_ex(BufferImage, font, 10, 90, makecol(225, 225, 225), -1, "AngY: %d", angy);
         textprintf_ex(BufferImage, font, 10, 110, makecol(225, 225, 225), -1, "AngX: %d", angx);
     }
     show_mouse(screen);
     draw_sprite(screen, BufferImage, 0, 0);
     clear_bitmap(BufferImage);

}
END_OF_FUNCTION(Buffer);

LOCK_FUNCTION(Buffer);

void MovePlayer()
{

     if(mouse_b & 1)
     {
         Mouse_y=mouse_y;
         Mouse_x=mouse_x;
         calc();
     }

     if(ObjPlayer.x+20>Mouse_x && ObjPlayer.y+90>Mouse_y)
     {
         ObjPlayer.y-=angy;
         ObjPlayer.x-=angx;
         Direcao=4;
     }
     if(ObjPlayer.x+20<Mouse_x && ObjPlayer.y+90<Mouse_y)
     {
         ObjPlayer.y+=angy;
         ObjPlayer.x+=angx;
         Direcao=3;
     }
     if(ObjPlayer.x+20<Mouse_x && ObjPlayer.y+90>Mouse_y)
     {
         ObjPlayer.y-=angay;
         ObjPlayer.x-=angax;
         Direcao=3;
     }
     if(ObjPlayer.x+20>Mouse_x && ObjPlayer.y+90<Mouse_y)
     {
         ObjPlayer.y+=angay;
         ObjPlayer.x+=angax;
         Direcao=4;
     }

     if(mouse_b & 2)
     {
         if(mouse_y<ObjPlayer.y)
             rotate=mouse_x/5;
         if(mouse_y>ObjPlayer.x)
             rotate=(mouse_x*-1)/5;
     }

}
END_OF_FUNCTION(MovePlayer);

LOCK_FUNCTION(MovePlayer);

void AnimationMovePlayer()
{
    if(Direcao==1)
    {
        if(DirecaoVal==1)
        {
            PlayerImage = load_bitmap("animation/human/Front1.bmp", NULL);
            DirecaoVal=2;
        }
        else
            if(DirecaoVal==2)
            {
                PlayerImage = load_bitmap("animation/human/Front2.bmp", NULL);
                DirecaoVal=3;
            }
            else
                if(DirecaoVal==3)
                {
                    PlayerImage = load_bitmap("animation/human/Front3.bmp", NULL);
                    DirecaoVal=4;
                }
                else
                    if(DirecaoVal==4)
                    {
                        PlayerImage = load_bitmap("animation/human/Front4.bmp", NULL);
                        DirecaoVal=1;
                    }
    }
    if(Direcao==2)
    {
        if(DirecaoVal==1)
        {
            PlayerImage = load_bitmap("animation/human/Back1.bmp", NULL);
            DirecaoVal=2;
        }
        else
            if(DirecaoVal==2)
            {
                PlayerImage = load_bitmap("animation/human/Back2.bmp", NULL);
                DirecaoVal=3;
            }
            else
                if(DirecaoVal==3)
                {
                    PlayerImage = load_bitmap("animation/human/Back3.bmp", NULL);
                    DirecaoVal=4;
                }
                else
                    if(DirecaoVal==4)
                    {
                        PlayerImage = load_bitmap("animation/human/Back4.bmp", NULL);
                        DirecaoVal=1;
                    }
    }
    if(Direcao==3)
    {
        if(DirecaoVal==1)
        {
            PlayerImage = load_bitmap("animation/human/Right1.bmp", NULL);
            DirecaoVal=2;
        }
        else
            if(DirecaoVal==2)
            {
                PlayerImage = load_bitmap("animation/human/Right2.bmp", NULL);
                DirecaoVal=3;
            }
            else
                if(DirecaoVal==3)
                {
                    PlayerImage = load_bitmap("animation/human/Right3.bmp", NULL);
                    DirecaoVal=4;
                }
                else
                    if(DirecaoVal==4)
                    {
                        PlayerImage = load_bitmap("animation/human/Right4.bmp", NULL);
                        DirecaoVal=1;
                    }
    }
    if(Direcao==4)
    {
        if(DirecaoVal==1)
        {
            PlayerImage = load_bitmap("animation/human/Left1.bmp", NULL);
            DirecaoVal=2;
        }
        else
            if(DirecaoVal==2)
            {
                PlayerImage = load_bitmap("animation/human/Left2.bmp", NULL);
                DirecaoVal=3;
            }
            else
                if(DirecaoVal==3)
                {
                    PlayerImage = load_bitmap("animation/human/Left3.bmp", NULL);
                    DirecaoVal=4;
                }
                else
                    if(DirecaoVal==4)
                    {
                        PlayerImage = load_bitmap("animation/human/Left4.bmp", NULL);
                        DirecaoVal=1;
                    }
    }
}

END_OF_FUNCTION(AnimationMovePlayer);

LOCK_FUNCTION(AnimationMovePlayer);

void Function()
{
     if(key[KEY_PGUP])
     {
         if(zoom<=10)
         {
             zoom+=1;
         }
     }

     if(key[KEY_PGDN])
     {
         if(zoom>1)
         {
             zoom-=1;
         }

     }

     if(key[KEY_F3])
     {
         if(press==false)
         {
             press=true;
         }
         else
         {
             press=false;
         }
     }
}
END_OF_FUNCTION(Function);

LOCK_FUNCTION(Function);
