/* See LICENSE file for copyright and license details. */
#include "../dwm-dwl-theme.h"
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */


static const char *fonts[]          = { 
	DWM_BAR_FONT,
	//"Font Awesome 6 Free Solid:size=10"
};
static const char dmenufont[]       = DWM_BAR_FONT;

//static const char col_gray1[]       = DWM_COLOR(NORAML_BACKGROUND_COLOR); //background
//static const char col_gray2[]       = DWM_COLOR(NORMAL_COLOR); //border norm
//static const char col_gray3[]       = DWM_COLOR(NORMAL_FONT_COLOR);
//static const char col_gray4[]       = DWM_COLOR(SELECTED_FONT_COLOR);
//static const char col_cyan1[]       = DWM_COLOR(SELECTED_BACKGROUND_COLOR); //bar sel
//static const char col_cyan2[]       = DWM_COLOR(SELECTED_COLOR); //border sel
//static const char col_hilgh[]       = "#4E7390";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { DWM_COLOR(NORMAL_FONT_COLOR),   DWM_COLOR(NORAML_BACKGROUND_COLOR),   DWM_COLOR(NORMAL_WINDOW_COLOR)   },
	[SchemeSel]  = { DWM_COLOR(SELECTED_FONT_COLOR), DWM_COLOR(SELECTED_BACKGROUND_COLOR), DWM_COLOR(SELECTED_WINDOW_COLOR) },
};

/* tagging */
#define MAX_TAGNAME_LEN 24		/* excludes TAG_PREPEND */
#define TAG_PREPEND "[%1i%s]"		/* formatted as 2 chars */
#define MAX_TAGLEN 24			/* altogether */
static char tags[][MAX_TAGLEN] = { "[1]", "[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Arandr",   NULL,       NULL,       0,            1,           -1 },
	{ "Blueman-manager",NULL, NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	//{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dwm-dmenu-all", "-m", dmenumon, 
        "-fn", dmenufont,   //font
        "-nb", DWM_COLOR(NORAML_BACKGROUND_COLOR),   // not selected back color
        "-nf", DWM_COLOR(NORMAL_FONT_COLOR),   // not selected font color
        "-sb", DWM_COLOR(SELECTED_BACKGROUND_COLOR),    // selected     back color
        "-sf", DWM_COLOR(SELECTED_FONT_COLOR),   // selected     font color
                            //fzf highlight
        "-nhb", DWM_COLOR(NORAML_BACKGROUND_HIGHLIGHT_COLOR),  // not selected back color
        "-nhf", DWM_COLOR(NORMAL_FONT_HIGHLIGHT_COLOR),  // not selected font color
        "-shb", DWM_COLOR(SELECTED_BACKGROUND_HIGHLIGHT_COLOR),   // selected     back color
        "-shf", DWM_COLOR(SELECTED_FONT_HIGHLIGHT_COLOR),  // selected     font color
        NULL };

static const char *termcmd[]  = { "alacritty", NULL };

static const char *mute_volume_cmd   []    = { "pactl",   "set-sink-mute",   "@DEFAULT_SINK@",        "toggle",   NULL };
static const char *down_volume_cmd   []    = { "pactl",   "set-sink-volume", "@DEFAULT_SINK@",        "-5%",      NULL };
static const char *up_volume_cmd     []    = { "pactl",   "set-sink-volume", "@DEFAULT_SINK@",        "+5%",      NULL };
static const char *mute_mic_cmd      []    = { "pactl",   "set-source-mute", "@DEFAULT_SOURCE@",      "toggle",   NULL };

static const char *down_backlight_cmd[]    = { "brightnessctl",   "set",    "5-%",   NULL };
static const char *up_backlight_cmd  []    = { "brightnessctl",   "set",    "5+%",   NULL };


static const char *print_dunst_volume_cmd  []    = { "print_dunst_volume",   NULL };
static const char *flameshot_cmd[]    = { "flameshot", "gui",   NULL };


static const char *test_cmd[]    = { "/home/delete/.dwm/tags_presets/firefox", NULL };
//      XF86AudioMute,         
//      XF86AudioLowerVolume,  
//      XF86AudioRaiseVolume,  
//      XF86AudioMicMute,      
//                               
//      XF86MonBrightnessDown, 
//      XF86MonBrightnessUp,   
//      XF86Display,           
//      XF86WLAN,              
//                               
//      XF86Messenger,         
//      XF86Go,                
//      Cancel,                
//      XF86Favorites,         
//                               
//      Print,                 
static int cursor_warp        = 1;        /*  */
void
cursor_warp_toggle(const Arg *arg) {
        cursor_warp = !cursor_warp;
}
void
volume(const Arg *arg) {
	Arg a = {.v = print_dunst_volume_cmd};
    spawn(arg);
    spawn(&a);
}
#include "movestack.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{      0,    XF86XK_AudioMute,             volume,         {.v = mute_volume_cmd} },
	{      0,    XF86XK_AudioLowerVolume,      volume,         {.v = down_volume_cmd} },
	{      0,    XF86XK_AudioRaiseVolume,      volume,         {.v = up_volume_cmd} },
	{      0,    XF86XK_AudioMicMute,          spawn,          {.v = mute_mic_cmd       } },
                                                                                
	{      0,    XF86XK_MonBrightnessDown,     spawn,          {.v = down_backlight_cmd } },
	{      0,    XF86XK_MonBrightnessUp,       spawn,          {.v = up_backlight_cmd   } },

	{      0,    XK_Print,                     spawn,          {.v = flameshot_cmd   } },
	{ MODKEY,                       XK_r,      nametag,        {0} },
    //{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = test_cmd   } },
	{ MODKEY|ShiftMask,             XK_r,      run_tag_prog,   {0} },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
//	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
//	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_w,      cursor_warp_toggle,     {0} },
//	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
//	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
//	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	//{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
