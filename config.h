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
static const unsigned int baralpha = 0xff;
static const unsigned int borderalpha = 0xff;
static const char *fonts[]          = { "Terminus:size=9" };
static const char col_gray1[]       = "#002b36";
static const char col_gray2[]       = "#073642";
static const char col_gray3[]       = "#93a1a1";
static const char col_gray4[]       = "#eee8d5";
static const char col_cyan[]        = "#002b36";
static const char *colors[][3]      = {
/*                                                       fg         bg         border   */
                                          [SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
                                          [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
                                      };
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};
/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

/* Rules for specific applications */
static const Rule rules[] = {
  /* class          instance    title       tags mask     isfloating   monitor */
    {"Gimp",        NULL,       NULL,       0,            1,           -1 },
    {"Uget-gtk",    NULL,       NULL,       1 << 7,       0,           -1 },
    {"qBittorrent", NULL,       NULL,       1 << 6,       0,           -1 },
    {"Alacritty",       NULL,       "Floating",       0,            1,           -1 },
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
static const char *termcmd[]     = { "alacritty", NULL };
static const char *ranger[]      = { "alacritty", "-e", "ranger" , NULL };
static const char *qutebrowser[] = { "qutebrowser" ,  NULL };
static const char *nemo[]        = { "nemo", NULL };
static const char *scrot[]       = { "scrot", NULL };
static const char *codium[]      = { "codium", NULL };
static const char *power[]       = { "/home/rohan/.config/.bin/power", NULL };
static const char *launch[]      = { "/home/rohan/.config/.bin/launch" , NULL };

static Key keys[] = {
    /* modifier                     key         function        argument */
    { Mod1Mask,                     XK_q,       killclient,     {0} },
    { MODKEY,                       XK_l,       spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_p,       spawn,          {.v = power } },
    { MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,       spawn,          {.v = qutebrowser } },
    { MODKEY,                       XK_f,       spawn,          {.v = nemo } },
    { MODKEY,                       XK_k,       spawn,          {.v = codium } },
    { MODKEY,                       XK_o,       spawn,          {.v = ranger } },
    { MODKEY,                       XK_s,       spawn,          {.v = scrot } },
    { MODKEY,                       XK_i,       spawn,          {.v = launch } },
    { MODKEY,                       XK_Left,    shiftview,      {.i = -1 } },
    { MODKEY,                       XK_Right,   shiftview,      {.i = +1 } },
    { MODKEY,                       XK_Tab,     focusstack,     {.i = +1 } },
    // { MODKEY,                       XK_Up,      incnmaster,     {.i = +1 } },
    // { MODKEY,                       XK_Down,    incnmaster,     {.i = -1 } },
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

