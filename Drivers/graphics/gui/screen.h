#ifndef  screens_INC
#define  screens_INC

#include "widgets.h"

enum {screen_boot, screen_main, screen_settings};

typedef struct screen_t screen_t;
typedef enum{ screen_Idle=0, screen_Erase, screen_Erased } screenRefreshType;

struct screen_t
{
	struct screen_t *next_screen;
	widget_t *widgets;
	widget_t *current_widget;
	uint8_t enabled;
	screenRefreshType refresh;
	int (*processInput)(struct screen_t *scr, RE_Rotation_t input, RE_State_t *);
	void (*update)(screen_t *scr);
	// void (*draw)(screen_t *scr);
	uint8_t (*draw)(screen_t *scr);
	void (*onExit)(screen_t *scr);
	void (*onEnter)(screen_t *scr);
	uint8_t index;
	void (*init)(screen_t *scr);
	void (*create)(screen_t *scr);
	uint8_t backup_combo_scroll;
	uint8_t backup_combo_index;
};


void default_init(screen_t *scr);
void screen_addWidget(widget_t *widget, screen_t *scr);
widget_t * screen_tabToWidget(screen_t * scr, uint8_t tab);
int default_screenProcessInput(screen_t * scr, RE_Rotation_t input, RE_State_t *state);
uint8_t default_screenDraw(screen_t *scr);
void default_screenUpdate(screen_t *scr);

#endif   /* ----- #ifndef screens_INC  ----- */
