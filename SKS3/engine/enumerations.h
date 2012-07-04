/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
enum direction { N, S, E, W, SAV, RES, QUI, HLP, NIL };
enum color { RED, GREEN, BLUE, NORMAL };
namespace character
{
    enum player { N, S, E, W};
    enum target { SMALLBUG, LARGEBUG, WORM, PITBULL};
}
namespace targetnoms
{
    enum target { SMALLBUG = 25, LARGEBUG = 50, WORM = 75, PITBULL = 100};
}
namespace weapons
{
    struct weaponlist
    {
        int strength[6]; //some standards
    };
    //D(fist) x(throwing star) |(sword) ©(gun) {}(cannon) ~(laser)
}