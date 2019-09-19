#include "Ufo.hh"
#include "Flag.hh"


Ufo::Ufo()
{
}

Ufo::Ufo(int team, int id): team(team), id(id)
{
    setup();
}

void Ufo::setup()
{
    gfx=Graphics();
    owning=false;
    color=gfx.sforange;
    pos.x=gfx.base.x*0.5;
    pos.y=2500;
    field={0,gfx.base.x};
    if (team) {
        color=gfx.sfpurple;
        pos.x+=gfx.board.x-gfx.base.x;
        field+=sc2vc(gfx.board.x-gfx.base.x);

    }
    if (id) pos.y=5500;
    spawn=pos;
    mag=0;
    aim={5000,4000};
    motorposleft=pos+rotate(vdir(pos-aim),-0.5)*size*1.1f;
    motorposright=pos+rotate(vdir(pos-aim),0.5)*size*1.1f;
    motorleft=create_circ(gfx.side+motorposleft,motorsize,
                          sf::Color(240,30,20,mag*2.2),
                          sf::Color(150,50,30,mag*1.5),15);
    motorright=create_circ(gfx.side+motorposright,motorsize,
                           sf::Color(240,30,20,mag*2.2),
                           sf::Color(150,50,30,mag*1.5),15);
    shape=create_circ(gfx.side+pos,size,color);
}

std::vector<float> Ufo::getData()
{
    float given_owner=0;
    if (owning) given_owner=1;
    return std::vector<float> {pos.x,pos.y,vel.x,vel.y,given_owner};
}

void Ufo::setData(float dt, float _mag, float aimx, float aimy)
{
    mag=_mag;
    aim={aimx,aimy};
    clip(mag,0.f,100.f);
    acc=vdir(aim-pos)*mag*gfx.pxfac;
    vel=gfx.friction*vel+acc*dt;
    pos=pos+vel*dt;
    motorposleft=pos+rotate(vdir(pos-aim),-0.5)*size*1.1f;
    motorposright=pos+rotate(vdir(pos-aim),0.5)*size*1.1f;
    collided=false;
    collwall();
    collflag();
    detectScore();
}

void Ufo::draw(sf::RenderWindow &window)
{
    shape.setPosition(gfx.side+pos-sc2vc(size));
    motorleft.setPosition(gfx.side+motorposleft-sc2vc(motorsize));
    motorright.setPosition(gfx.side+motorposright-sc2vc(motorsize));
    motorleft.setFillColor(sf::Color(240,30,20,mag*2.2));
    motorright.setFillColor(sf::Color(240,30,20,mag*2.2));
    motorleft.setOutlineColor(sf::Color(150,50,30,mag*1.5));
    motorright.setOutlineColor(sf::Color(150,50,30,mag*1.5));
    window.draw(motorleft);
    window.draw(motorright);
    window.draw(shape);
}

void Ufo::collwall()
{
    // Compute new velocity vector if colliding with wall:
    //     M(angle) = [ cos(angle) -sin(angle)
    //                  sin(angle)  cos(angle) ]
    //     v_new = M(angle) * v_old * wall_restitution
    // Wall collisions are elastic, they increase ufos speed.
    int fac;
    float ang;
    sf::Vector2f nvec;
    bool coll=false;
    if (pos.x+size>gfx.board.x) {nvec=gfx.nvect; fac=-1; coll=true;}
    if (pos.x-size<0)           {nvec=gfx.nvect; fac= 1; coll=true;}
    if (pos.y+size>gfx.board.y) {nvec=gfx.nhorz; fac=-1; coll=true;}
    if (pos.y-size<0)           {nvec=gfx.nhorz; fac= 1; coll=true;}
    if (coll) {
        ang=angvec2(vel,nvec);
        vel=rotate(vel,fac*2*ang)*gfx.restwall;
    }
}

void Ufo::collufos(Ufo *othufo)
{
    // Compute new velocity vector if colliding with ufo:
    //     difference = x_ufo2 - x_ufo1
    //     direction = vector_director(difference)
    //     v_ufo1_new = - direction * norm(v_ufo2_old) * ufo_restitution
    //     (+) tiny repulsion force (like opposite magnet)
    // Ufos collisions are solid, they decrease ufos speed.
    if (collided) return;
    sf::Vector2f r=othufo->pos-pos;
    if (norm(r)<2*size) {
        // Detection flag owner tackling
        if (team != othufo->team) {
            if (owning && norm(vel) <= norm(othufo->vel)) {
                owning=false;
                enemy_flag->spawn();
            }
            else if (othufo->owning && norm(vel) >= norm(othufo->vel)) {
                othufo->owning=false;
                flag->spawn();
            }
        }
        // Apply collision
        sf::Vector2f v1=vel, v2=othufo->vel;
        vel=gfx.restufo*norm(v2)*vdir(v2) - gfx.repulufo*vdir(r);
        othufo->vel=gfx.restufo*norm(v1)*vdir(v1) + gfx.repulufo*vdir(r);
        othufo->collided=true;
    }
}

void Ufo::collflag()
{
    // Detection enemy flag capture
    if (owning) return;
    if (norm(enemy_flag->pos-pos)<enemy_flag->size+size) {
        owning=true;
        enemy_flag->owned=true;
        enemy_flag->given_pos={-1,-1};
        flag_rot={0,size};
    }
}

void Ufo::detectScore()
{
    // Detection bringing flag back to base
    if (!owning) return;
    flag_rot = rotate(flag_rot, flag_rot_speed);
    enemy_flag->pos=pos+flag_rot;
    if (enemy_flag->pos.x > field.x && enemy_flag->pos.x < field.y) {
        owning=false;
        enemy_flag->spawn();
        flag->score++;
        score->setString(toString<int>(flag->score));
    }
}
