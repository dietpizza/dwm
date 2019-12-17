/* appearance */
static const unsigned int borderpx  = 1;
static const unsigned int snap      = 32;
static const unsigned int gappih    = 10;
static const unsigned int gappiv    = 10;
static const unsigned int gappoh    = 10;
static const unsigned int gappov    = 10;
static const int smartgaps          = 0;
static const int showbar            = 1; 
static const int topbar             = 1; 
static const int horizpadbar        = 1;
static const int vertpadbar         = 1;
static const char *fonts[]          = { "xos4 Terminus:size=9" };
static const char col_gray1[]       = "#002b36";
static const char col_gray2[]       = "#073642";
static const char col_gray3[]       = "#839496";
static const char col_gray4[]       = "#eee8d5";
static const char col_cyan[]        = "#268bd2";
static const char *colors[][3]      = {
/*                                                       fg         bg         border   */
                                          [SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
                                          [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
                                      };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

/* Rules for specific applications */
static const Rule rules[] = {
  {"Gimp",        NULL,       NULL,       0,            1,           -1 },
  {"Uget-gtk",    NULL,       NULL,       1<<7,         0,           -1 },
  {"qBittorrent", NULL,       NULL,       1<<6,         0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "T",      tile },    /* first entry is default */
    { "N",      NULL },    /* no layout function means floating behavior */
    { "M",      monocle },
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

/* Shiftview function */
void shiftview(const Arg *arg) {
    Arg shifted;

    if(arg->i > 0) // left circular shift
        shifted.ui = (selmon->tagset[selmon->seltags] << arg->i)
           | (selmon->tagset[selmon->seltags] >> (LENGTH(tags) - arg->i));

    else // right circular shift
        shifted.ui = selmon->tagset[selmon->seltags] >> (- arg->i)
           | selmon->tagset[selmon->seltags] << (LENGTH(tags) + arg->i);

    view(&shifted);
}

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "dmenu_run", NULL };
static const char *termcmd[]     = { "st", NULL };
static const char *chromiumcmd[] = { "chromium","--force-dark-mode",  NULL };
static const char *nemocmd[]     = { "nemo", NULL };
static const char *codecmd[]     = { "code", NULL };
static const char *powercmd[]    = { "/home/rohan/.bin/power", NULL };
static const char *rangercmd[]   = { "st", "-e", "ranger" , NULL };
static const char *launchcmd[]   = { "/home/rohan/.bin/launch" , NULL };

static Key keys[] = {
    /* modifier                     key         function        argument */
    { Mod1Mask,                     XK_q,       killclient,     {0} },
    { MODKEY,                       XK_l,       spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_p,       spawn,          {.v = powercmd } },
    { MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,       spawn,          {.v = chromiumcmd } },
    { MODKEY,                       XK_f,       spawn,          {.v = nemocmd } },
    { MODKEY,                       XK_k,       spawn,          {.v = codecmd } },
    { MODKEY,                       XK_o,       spawn,          {.v = rangercmd } },
    { MODKEY,                       XK_i,       spawn,          {.v = launchcmd } },
    { MODKEY|ShiftMask,             XK_t,       setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_f,       setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_Left,    shiftview,      {.i = -1 } },
    { MODKEY,                       XK_Right,   shiftview,      {.i = +1 } },
    { MODKEY,                       XK_Tab,     focusstack,     {.i = +1 } },
    //{ MODKEY,                       XK_Up,      incnmaster,     {.i = +1 } },
    //{ MODKEY,                       XK_Down,    incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_comma,   setmfact,       {.f = -0.01} },
    { MODKEY,                       XK_period,  setmfact,       {.f = +0.01} },
    { MODKEY,                       XK_m,       zoom,           {0} },
    { MODKEY|ShiftMask,	            XK_q,       quit,           {0} },
    TAGKEYS(                        XK_1,                       0)
    TAGKEYS(                        XK_2,                       1)
    TAGKEYS(                        XK_3,                       2)
    TAGKEYS(                        XK_4,                       3)
    TAGKEYS(                        XK_5,                       4)
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
};
/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

