// Graphics.cc
//

#include "Graphics.hh"
#define LZZ_INLINE inline
Graphics::Graphics ()
    {
        fps=60;
        pxfac=3e-2;
        friction=0.98;
        restwall=1.0;
        restufo=0.45;
        repulwall=0;
        repulufo=300;
        can={19200,10800};
        board={10000,8000};
        base={1000,board.y};
        side=(can-board)*0.5f;
        tlb2={side.x+board.x-base.x,side.y};
        nvect={0,-1};
        nhorz={1,0};
        sforange={250,141,39,60};
        sfpurple={221,48,111,60};
        font1.loadFromFile("resources/font/Roboto/Roboto-Black.ttf");
        name1={can.x*0.5f-board.x*0.5f,side.y*0.7f};
        name2={can.x*0.5f+board.x*0.5f,side.y*0.7f};
        score1={can.x*0.5f-base.x,side.y*0.7f};
        score2={can.x*0.5f+base.x,side.y*0.7f};
        countdown={can.x*0.5f,can.y-side.y*0.7f};
    }
#undef LZZ_INLINE
