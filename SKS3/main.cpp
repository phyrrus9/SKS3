/*
 * Super Key Seeker Version 3
 * Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 * This software is free, it may be customized, redistributed, blah blah blah...
 */
#include "main.h"
bool server_mode = false;
bool client_mode = false;
bool multiplayer = false;
bool game_initialized = false;
extern int client_port;
extern int server_port;
/*int main(int argc, const char * argv[])
{
    if (argc > 1)
        client("localhost", 1501);
    else
        server(1501);
    
}*/ //for testing server/client socket connections
int main(int argc, const char * argv[])
{
    environment_init();
    clear();
    displaylauncher();
    cout << ">";
    int selection;
    cin >> selection;
    extern int playernum;
    extern char * hostname;
    if (selection == 1)
    {
        //numargs = 1;
        //strcpy(array[0], argv[0]);
    }
    if (selection == 2)
    {
        multiplayer = true;
        cout << "Which player are you? (1/2) ";
        int player;
        cin >> player;
        playernum = player;
        strcpy(hostname, "localhost");
    }
    if (selection == 3)
    {
        cout << "This game uses TCP ports 5101-5103. Please make sure to patch them through"
             << " your firewall if you wish for this to actually work." << endl
             << "This game uses networking before the screen refreshes, so playing over "
             << "an internet connection may be slow." << endl;
        multiplayer = true;
        cout << "Which player are you? (1/2) ";
        int player;
        cin >> player;
        playernum = player;
        cout << "Please enter the server host: ";
        char * host = new char[255];
        cin >> host;
        strcpy(hostname, host);
        delete host;
    }
    if (selection == 4)
    {
        sks4200();
        exit(EXIT_SUCCESS);
    }
    if (selection == 5)
    {
        ofstream sksfastboot(".sksfastboot", ios::out | ios::trunc);
        sksfastboot << "Hello World!";
        sksfastboot.close();
        exit(EXIT_SUCCESS);
    }
    if (selection == 6)
    {
        system("rm .sksfastboot");
        exit(EXIT_SUCCESS);
    }
    if (selection >= 7 || selection <= 0)
        exit(EXIT_SUCCESS);
    showhelp();
    game(argc, argv);
}
void game(int argc, const char * argv[])
{
    game_initialized = true;
    //if (argc > 1)
      //  single = true; // i have no freaking clue
    //if (argc > 1)
   // {
        //if (atoi(argv[1]) == 0)
            //server_mode = true;
        //if (argc > 2)
            //if (/*atoi(argv[1]) == 1*/)
    //            multiplayer /*client_mode*/ = true;
   // }
    srand(time(0));
    //if (!single)
        populate();
    /*else
    {
        ifstream f("1.map");
        //i have no idea what i'm doing with this
        //so i will just stop here....continue it 
        //if you feel like it....
    }*/
    /*if (server_mode)
        server(portnum); //start it
    if (client_mode)
        client((char *)argv[2], portnum);*/
    extern int playernum;
    if (multiplayer)
    {
        //if (argc > 2)
          //  strcpy(hostname, argv[2]);
        //playernum = atoi(argv[1]);
        if (playernum == 1) //player 1
        {
            server_port = portnum;
            server(server_port);
            cout << "When ready press any key" << endl;
            //getch_();
            client_port = portnum + 1;
            //client("localhost", portnum + 1);
        }
        if (playernum == 2) //player 2
        {
            server_port = portnum + 1;
            server(server_port);
            cout << "When ready press any key" << endl;
            //getch_();
            client_port = portnum;
            //client("localhost", portnum);
        }
    }
    //sleep(5);
    cout << "dun" << endl;
    //cin >> ws;
    bool run = true;
    while (run)
    {
        if (!env.showmap)
            env.view = (char *)&env.map;
        else
            env.view = (char *)&env.grid;
        clear();
        if (env.kills >= env.kills_needed)
        {
            env.levels_completed++;
            env.position = 0;
            env.score += env.kills;
            populate();
            continue;
        }
        
        if (env.levels_completed > 0) //level 2
            env.weapons[1] = true; //enable the throwing star
        if (env.levels_completed > 4) //level 5
            env.weapons[2] = true; //enable the sword
        if (env.levels_completed > 9) //level 10
            env.weapons[3] = true; //enable the gun
        if (env.levels_completed > 24) //level 25
            env.weapons[4] = true; //enable the canon
        if (env.levels_completed > 49) //level 50
            env.weapons[5] = true; //enable the laser
        
        display();
        if (env.health <= 0)
        {
            if (env.lives <= 0)
            {
                cout << "You are dead..." << endl;
                run = false;
            }
            else
            {
                env.lives -= 1;
                env.health = 100;
            }
        }
        if (run)
        {
            showmap();
            char a = getch_();
            bool turning = false, moving = false;
            direction t;
            if (a == '1')
                setselectedweapon(0);
            if (a == '2')
                setselectedweapon(1);
            if (a == '3')
                setselectedweapon(2);
            if (a == '4')
                setselectedweapon(3);
            if (a == '5')
                setselectedweapon(4);
            if (a == '6')
                setselectedweapon(5);
            /*if (a == 'g')
            {
                server(5100);
                cout << env.socket_message << endl;
            }*/ //old debug command... DO NOT ENABLE THIS IF YOU DONT KNOW WHAT YOUR DOING!
            if (a == 'w')
            {
                t = N;
                moving = true;
            }
            if (a == 'a')
            {
                t = E;
                moving = true;
            }
            if (a == 's')
            {
                t = S;
                moving = true;
            }
            if (a == 'd')
            {
                t = W;
                moving = true;
            }
            if (a == 'i')
            {
                turning = true;
                t = N;
            }
            if (a == 'j')
            {
                turning = true;
                t = E;
            }
            if (a == 'k')
            {
                turning = true;
                t = S;
            }
            if (a == 'l')
            {
                turning = true;
                t = W;
            }
            if (a == 'e')
                attack();
            if (a == 'E')
                increment_attack();
            if (a == 'S')
            {
                t = SAV;
                _move;
            }
            if (a == 'R')
            {
                t = RES;
                _move;
            }
            if (a == 'Q')
            {
                t = QUI;
                _move;
            }
            if (a == 'H')
            {
                t = HLP;
                _move;
            }
            if (a == 'N')
                execl(argv[0], argv[0]);
            if (a == '/')
            {
                cout << ">";
                string command1, command2;
                cin >> command1 >> command2;
                enginecmd(command1, command2);
                t = NIL;
            }
            if (turning)
                turn(t);
            else
                if (moving)
                    move(t);
                else
                    continue;
        }
    }
    return;
}
void displaylauncher(void)
{
    cout << "#######################################################" << endl
         << "#Welcome  to  Super  Key  Seeker  3  ©  2012  phyrrus9#" << endl
         << "#This game has several modes to select, but if for you#" << endl
         << "#want to play the older games, there is a downloader  #" << endl
         << "#in this menu, it requires internet to work. Thanks :)#" << endl
         << "#Please select an option from the list below to start #" << endl
         << "#1. Single player (local) game                        #" << endl
         << "#2. Miltiplayer (local) game                          #" << endl
         << "#3. Multiplayer (online) game                         #" << endl
         << "#4. Install and launch SKS4200                        #" << endl
         << "#5. Enable fastboot                                   #" << endl
         << "#6. Disable fastboot                                  #" << endl
         << "#7. Exit                                              #" << endl
         << "#######################################################" << endl;
}
void sks4200(void)
{
    printf("Downloading installer...\n");
    system("curl -s http://student.eup.k12.mi.us/~ss14bouchaj/MUD/sks4200.pkg -o sksinstall.pkg");
    printf("Installing...\n");
    system("sudo installer -pkg sksinstall.pkg -target /");
    printf("Cleaning up...\n");
    system("rm sksinstall.pkg");
    printf("Lanching...\n");
    system("sks4200");
}
