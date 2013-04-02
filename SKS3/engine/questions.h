/*****************************************************************
 Super Key Seeker Version 3
 Copyright © 2012 phyrrus9 <phyrrus9@gmail.com>
 This software is free, it may be customized, redistributed
 or used in any way that suits your needs. This software is
 open source, meaning that it MUST be distributed along with
 its source code or have provisions to recieve the source code
 if desired. This program, though it is free and open source
 is still copyright © the following names and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com> 2012
 MOD Technologies LLC <http:modtech.co> 2012
 This program source code MUST be distributed with this comment
 block intact as a reference to users who would actually like
 to follow the rules. Please do not be a jerk and take credit
 for a program you did not write. This code for the most part
 was written by the following people and companies:
 Ethan Laur (phyrrus9) <phyrrus9@gmail.com>
 Dereck Wonnacott <dereck@gmail.com>
 GNU Project (for ncurses which we all so dearly love)
 All third party lisencing by the above authors is transmitted
 with the source code of this program to its new author, who
 may add his or her name to this block for the works they did
 It is greatly appreciated if any work you do on the program
 is reported back to the original authors (copyright section)
 so that we can incorporate your features into the game as a
 public release. We thank you for reading this file.
 If you want to know how many lines of code are in this project,
 you can just cd into the source directory and run the following
 find . -type f -print0 | xargs -0 cat | wc -l
 =================================================================
 File: questions.h
 Description: Holds structures and databases for the mystery boxes
 Authors: phyrrus9 <phyrrus9@gmail.com>
 *****************************************************************/
#ifndef SKS3_questions_h
#define SKS3_questions_h

namespace question
{
    
    struct bonus
    {
        int health;
        int lives;
        int score;
        int attack;
    };

#define q_complete "Complete the statement:"
#define q_answerme "Answer me this:"
#define q_boolean  "True (1) or false (0):"
    
    const static int question_count = 7;

    static char instructions[question_count][50] =
    {
        q_complete,
        q_boolean,
        q_answerme,
        q_answerme,
        q_answerme,
        q_answerme,
        q_answerme
    };

    static char questions[question_count][80] =
    {
        "Hello, ",
        "Division by zero is possible",
        "What is the square root an empty return value",
        "What has a foot, but no legs",
        "Poor people have it. Rich people need it. If you eat it you die.",
        "What comes down but never goes up",
        "Mary’s father has 5 daughters: Nana, Nene, Nini, Nono. Who is the fifth?"
    };

    static char answers[question_count][20] =
    {
        "World",
        "1",
        "i",
        "a snail",
        "nothing",
        "rain",
        "Mary"
    };
    
    static bonus gains[question_count] =
    {
        { 0,     1,    150,   0 },
        { 50,    0,    300,   0 },
        { 100,   2,    5000,  2 },
        { 250,   2,    7000,  4 },
        { 500,   4,    9000,  8 },
        { 50,    2,    500,   0 },
        { 100,   0,    900,   1 }
    };
    
}

#endif
