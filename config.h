/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 9;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int vertpad            = 9;        /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = {
                                        "Meslo LG S:size=9",
                                        "FontAwesome 5 Free:style=Regular:size=8",
                                        "FontAwesome 5 Free:style=Solid:size=8",
                                        "FontAwesome 5 Brands:style=Regular:size=8",
                                        "MaterialIcons:size=8",
                                      };
static const char dmenufont[]       = "Meslo LG S:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_black[]       = "#000000";
static const char col_accent[]      = "#0a88d6";
static const unsigned int baralpha  = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray2 },
	[SchemeSel]  = { col_gray4, col_accent,  col_accent },
};
static const unsigned int alphas[][3]      = {
       /*               fg      bg        border     */
       [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
       [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	{ "Lxappearance",     NULL,       NULL,       0,            1,           -1 },
	{ "Pavucontrol",      NULL,       NULL,       0,            1,           -1 },

	{ "URxvt",            NULL,       "urxvt",    1,            0,           -1 },
	{ "URxvt",            NULL,       "spt",      1 << 6,       0,           -1 },

	{ "Brave",            NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Chromium",         NULL,       NULL,       1 << 1,       0,           -1 },
	{ "firefox",          NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Google-Chrome",    NULL,       NULL,       1 << 1,       0,           -1 },

	{ "discord",          NULL,       NULL,       1 << 2,       0,           -1 },
	{ "TelegramDesktop",  NULL,       NULL,       1 << 2,       0,           -1 },

	{ "Nautilus",         NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Thunar",           NULL,       NULL,       1 << 3,       0,           -1 },

	{ "code-oss",         NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Sublime_text",     NULL,       NULL,       1 << 4,       0,           -1 },

	{ "vlc",              NULL,       NULL,       1 << 5,       0,           -1 },

	{ "Spotify",          NULL,       NULL,       1 << 6,       0,           -1 },

	{ "Lutris",           NULL,       NULL,       1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *scrshotcmd[] = { "scrshot", NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XK_Print,  spawn,          {.v = scrshotcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },

    { 0, XF86XK_AudioMute,                     spawn,          SHCMD("pamixer -t; pkill -RTMIN+4 dwmblocks") },
    { 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("pamixer --allow-boost -i 3; pkill -RTMIN+4 dwmblocks") },
    { 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("pamixer --allow-boost -d 3; pkill -RTMIN+4 dwmblocks") },
    { 0, XF86XK_AudioPrev,                     spawn,          SHCMD("playerctl previous; pkill -RTMIN+5 dwmblocks") },
    { 0, XF86XK_AudioNext,                     spawn,          SHCMD("playerctl next; pkill -RTMIN+5 dwmblocks") },
    { 0, XF86XK_AudioPause,                    spawn,          SHCMD("playerctl play-pause") },
    { 0, XF86XK_AudioPlay,                     spawn,          SHCMD("playerctl play-pause") },
    { 0, XF86XK_MonBrightnessUp,               spawn,          SHCMD("xbacklight -inc 15") },
    { 0, XF86XK_MonBrightnessDown,             spawn,          SHCMD("xbacklight -dec 15") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

