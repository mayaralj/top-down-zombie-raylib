#include "Weapons.hpp"

//  the zombies avoid vertical walls depending on their predetermined direction
void avoidVert(Enemy &zombie, const float delta)
{
    if(zombie.avoidDirection == 1)
    {
        zombie.isFacingDown = true;
        zombie.isFacingUp = false, zombie.isFacingRight = false, zombie.isFacingRightDown = false, zombie.isFacingRightUp = false, zombie.isFacingLeftDown = false, zombie.isFacingLeftUp = false;
        zombie.setPosY(zombie.getPosY() + (zombie.getSpeed() / 1.5));
    }
    else
    {
        zombie.isFacingUp = true;
        zombie.isFacingDown = false, zombie.isFacingRight = false, zombie.isFacingRightDown = false, zombie.isFacingRightUp = false, zombie.isFacingLeftDown = false, zombie.isFacingLeftUp = false;
        zombie.setPosY(zombie.getPosY() - (zombie.getSpeed() / 1.5));
    }

}

//  the zombies avoid horizontal walls depending on their predetermined direction
void avoidHorz(Enemy &zombie, const float delta)
{
    if(zombie.avoidDirection == 1)
    {
        zombie.isFacingRight = true;
        zombie.isFacingUp = false, zombie.isFacingLeft = false, zombie.isFacingRightDown = false, zombie.isFacingRightUp = false, zombie.isFacingLeftDown = false, zombie.isFacingLeftUp = false;
        zombie.setPosX(zombie.getPosX() + (zombie.getSpeed() / 1.5));
    }
    else
    {
        zombie.isFacingLeft = true;
        zombie.isFacingUp = false, zombie.isFacingRight = false, zombie.isFacingRightDown = false, zombie.isFacingRightUp = false, zombie.isFacingLeftDown = false, zombie.isFacingLeftUp = false;
        zombie.setPosX(zombie.getPosX() - (zombie.getSpeed() / 1.5));
    }
}

// chacks id player and zombie collide
bool checkPlayerZombieColl(Player both, Enemy zombies)
{
    return CheckCollisionCircles({both.getPosX(), both.getPosY()}, both.getRadius(), {zombies.getPosX(), zombies.getPosY()}, zombies.getRadius());   
}

void zombieAttack(Player &both, vector <Enemy> &zombies, int waveNum)
{
    float damageMulti;
    
    // damage increases exponentialy dependant on the wave number
    if(waveNum < 40)
    {
        damageMulti = waveNum * 1.25;
    }
    else
    {
        damageMulti = 40 * 1.25;
    }
    
    for(int i = 0; i < zombies.size(); i++)
    {
        zombies[i].zomPlayerColl = checkPlayerZombieColl(both, zombies[i]);
        
        // applies damage to player and starts cooldown for attackign again
        if(zombies[i].zomPlayerColl && !zombies[i].isHitting && GetTime() - zombies[i].attackTime > 3)
        {
            zombies[i].hitTime = GetTime();
            zombies[i].isHitting = true;
            both.healthTime = GetTime();
            both.isHitAtAll = true;
            both.setHealth(both.getHealth() - (15 + damageMulti));
        }
        
        // chacks if cooldowns not over to prevent the zombie from attacking again
        if(GetTime() - zombies[i].hitTime > 2)
        {
            zombies[i].isHitting = false;
        }
    }
}

void playerzomColl(Player &both, vector <Enemy> &zombies)
{
    int zomAmount = zombies.size();

    for(int i = 0; i < zomAmount; i++)
    {
        zombies[i].zomPlayerColl = checkPlayerZombieColl(both, zombies[i]);

        // moves zombie if collides with player
        if(zombies[i].zomPlayerColl)
        {
            if(both.getPosX() < zombies[i].getPosX())
            {
                if(both.getPosX() > 20)
                {
                    zombies[i].setPosX(zombies[i].getPosX() + 1);  
                }
            }
            else
            {
                if(both.getPosX() < 1680)
                {
                    zombies[i].setPosX(zombies[i].getPosX() - 1);
                }
            }
            
            if(both.getPosY() < zombies[i].getPosY())
            {
                if(both.getPosY() > 20)
                {                
                    zombies[i].setPosY(zombies[i].getPosY() + 1);
                }
            }
            else
            {
                if(both.getPosY() < 930)
                {                
                    zombies[i].setPosY(zombies[i].getPosY() - 1);
                }
            }
        }
    }
}

// chacks if the zombies collide
int checkZomColl(Enemy zombie, vector <Enemy> zombies, int index, int amount)
{
    for(int i = index +1; i < amount; i++)
    {
        if(CheckCollisionCircles({zombie.getPosX(), zombie.getPosY()}, zombie.getRadius(), {zombies[i].getPosX(), zombies[i].getPosY()}, zombies[i].getRadius()))
        {
            return i;
        }
    }

    return -1;
}

vector <Enemy> zomColl(vector <Enemy> zombies, int zomAmount)
{
    for(int i = 0; i < zomAmount; i++)
    {
        zombies[i].zomColl = -1;

        // checks if zombies collied
        try{zombies[i].zomColl = checkZomColl(zombies[i], zombies , i, zomAmount);}
        catch(...){}

        if(zombies[i].zomColl != -1)
        {
            int j = zombies[i].zomColl;
            
            // moves zombies back based on where their trying to enter the other zombie
            if(zombies[j].getPosX() < zombies[i].getPosX())
            {
                if(zombies[j].getPosX() > 20)
                {
                    zombies[j].setPosX(zombies[j].getPosX() - 1);
                    zombies[i].setPosX(zombies[i].getPosX() + 1);
                }
            }
            else
            {
                if(zombies[j].getPosX() < 1680)
                {
                    zombies[j].setPosX(zombies[j].getPosX() + 1);
                    zombies[i].setPosX(zombies[i].getPosX() - 1);  
                }
            }
            
            if(zombies[j].getPosY() < zombies[i].getPosY())
            {
                if(zombies[j].getPosY() > 20)
                {                
                    zombies[j].setPosY(zombies[j].getPosY() - 1);
                    zombies[i].setPosY(zombies[i].getPosY() + 1);
                }
            }
            else
            {
                if(zombies[j].getPosY() < 930)
                {                
                    zombies[j].setPosY(zombies[j].getPosY() + 1);
                    zombies[i].setPosY(zombies[i].getPosY() - 1);
                }
            }
        }

        zombies[i].zomColl = -1;
    }

    return zombies;
}

vector <Enemy> pushBackZombies(vector <Enemy> zombies, Enemy boss, int regular, int speed, int tank, int waveNum)
{
    float healthMulti;

    // health multiplier based on wave number
    if(waveNum <= 40)
    {
        healthMulti = waveNum * 5;
    }
    else
    {
        healthMulti = (15 * 5) + ((waveNum - 15) * 1.001);
    }


    if(waveNum % 10 != 0)
    {
        // pushes back predetestend amount of regular zombies into the zombies vector
        for(int i = 0; i < regular; i++)
        {
            zombies.push_back(Enemy(25 + healthMulti, 440, 350, 17, .5, false, true));
        }

        // pushes back preditestend amount of speed zombies into the zombies vector
        for(int i = 0; i < speed; i++)
        {
            zombies.push_back(Enemy(15 + healthMulti, 100, 850, 13, 0.85, false, true));
        }

        // pushes back preditestend amount of tank zombies into the zombies vector
        for(int i = 0; i < tank; i++)
        {
            zombies.push_back(Enemy(50 + healthMulti, 1600, 850, 22, .3, false, true));
        }

        // on waves divisible by 5, mini bosses are spawned in
        if(waveNum % 5 == 0)
        {
            for(int i = 0; i < waveNum / 5; i++)
            {
                zombies.push_back(Enemy(300 + healthMulti, 1210, 300, 30, 0.88, false, true));
            }
        }
    }
    else
    {
        for(int i = 0; i < 10; i++)
        {
            zombies.push_back(Enemy(50 + healthMulti, 40.0f + i * 10, 500.0f + i * 10, 17, .5, false, true));
        }
        
        boss.setHealth(boss.getHealth() * (3*(waveNum/10)));

        // pushes back the every 10 wave boss into the zombie vector
        zombies.push_back(boss);
    }
    for(int i = 0; i < zombies.size(); i++)
    {
        zombies[i].originalSpeed = zombies[i].getSpeed();
    }

    return zombies;
}

vector <Enemy> zombiePlacement(vector <Enemy> zombies, int allZom)
{
    int randomPlacement = 0;
    
    // chooses the random placement and avoidance direction for each of the zombies
    for(int i = 1; i < allZom; i++)
    {
        randomPlacement = rand() % 4 + 1;
        
        if(randomPlacement == 1)
        {
            zombies[i].setPosX(440);
            zombies[i].setPosY(350);
            zombies[i].avoidDirection = 2;
        }
        else if(randomPlacement == 2)
        {
            zombies[i].setPosX(100);
            zombies[i].setPosY(850);
            zombies[i].avoidDirection = 2;
        }
        else if(randomPlacement == 3)
        {
            zombies[i].setPosX(1600);
            zombies[i].setPosY(850);
            zombies[i].avoidDirection = 1;
        }
        else
        {
            zombies[i].setPosX(1210);
            zombies[i].setPosY(300);
            zombies[i].avoidDirection = 1;
        }
    }
    return zombies;
}

void roundEnd(Window screen, vector <Enemy> &zombies, Enemy &boss, vector <Enemy> &bossBullets, bool &roundEnd, int bossNum, int &waveNum, int &regZom, int &spdZom, int &tnkZom, int &allZom, Player &one, Player &two)
{
    if(roundEnd)
    {
        // if the round ends the wave number increases
        waveNum++;
        
        if(waveNum % 10 != 0)
        {
            bossBullets.clear();

            // when the round ends the number of all the different zombies increases for the next round but has a cap
            // if(regZom < 12)
            // {
            //     regZom += 2;
            // }
            if(regZom < 40)
            {
                regZom += 1;
            }
            
            // if the wave number is under 11 specialized zombies do not spawn
            if(waveNum < 11)
            {
                spdZom = 0;
                tnkZom = 0;
            }
            else
            {
                // overtime after round 11 more and more specialized zombies are spawned in
                if(spdZom < 8)
                {
                    spdZom += 1;
                }
                
                if(tnkZom < 10)
                {
                    tnkZom += 1;
                }
            }

            if(!one.isAlive() && two.isAlive())
            {
                one.setPosX(screen.getWidth() / 2);
                one.setPosY(screen.getHeight() / 2);
                one.setAlive(true);
            }

            if(!two.isAlive() && two.twoPlayerMode && one.isAlive())
            {
                two.setPosX(screen.getWidth() / 2);
                two.setPosY(screen.getHeight() / 2);
                two.setAlive(true);
            }
            
            zombies.clear();

            zombies = pushBackZombies(zombies, boss, regZom, spdZom, tnkZom, waveNum);
            for(int i = 0; i < zombies.size(); i++)
            {
                zombies[i].attackTime = GetTime();
            }

            allZom = zombies.size() - 1;

            zombies = zombiePlacement(zombies, allZom);
        }
        // if boss wave is active
        else
        {
            // pushes back 10 regular zombies for boss fight
            zombies = pushBackZombies(zombies, boss, regZom, spdZom, tnkZom, waveNum);
            
            for(int i = 0; i < allZom; i++)
            {
                zombies[i].setAlive(false);
            }

            // pushes back bossbullets
            for(int i = 0; i < 12; i++)
            {
                bossBullets.push_back(Enemy(1, screen.getWidth() / 2, screen.getHeight() / 2, 25, 2, false, true));
            }

            // sets boss position and state of living
            zombies[zombies.size() - 1].setAlive(true);
            zombies[zombies.size() - 1].setPosX(screen.getWidth() / 2);
            zombies[zombies.size() - 1].setPosY(screen.getHeight() / 2);
        }

        roundEnd = false;
    }
}

bool distance(Enemy zombie, Player one, Player two)
{
    // checks distance between players and enemys
    if(sqrt(pow(zombie.getPosX() - one.getPosX(), 2) + pow(zombie.getPosY() - one.getPosY(), 2)) < sqrt(pow(zombie.getPosX() - two.getPosX(), 2) + pow(zombie.getPosY() - two.getPosY(), 2)))
    {
        // if player one is closer returns true
        return true;
    }

    // if player two is closer returns false
    return false;
}

vector <Enemy> zomMovement(vector <Enemy> &zombies, int zomAmount, Player one, Player two)
{
    for(int i = 0; i < zomAmount; i++)
    {
        // checks distance bbetween players and all zombies
        if(distance(zombies[i], one, two) && !zombies[i].avoidingWall)
        {
            // if closer to player one move towards them
            if(zombies[i].isAlive() && zombies[i].getPosX() < one.getPosX()){
                zombies[i].setPosX(zombies[i].getPosX() + zombies[i].getSpeed());
                zombies[i].isFacingRight = true;
                zombies[i].isFacingLeft = false;
            }
            else if(zombies[i].isAlive() && zombies[i].getPosX() > one.getPosX())
            {
                zombies[i].setPosX(zombies[i].getPosX() - zombies[i].getSpeed());
                zombies[i].isFacingLeft = true;
                zombies[i].isFacingRight = false;
            }

            if(zombies[i].isAlive() && zombies[i].getPosY() < one.getPosY())
            {
                zombies[i].setPosY(zombies[i].getPosY() + zombies[i].getSpeed());
                zombies[i].isFacingUp = true;
                zombies[i].isFacingDown = false;
            }
            else if(zombies[i].isAlive() && zombies[i].getPosY() > one.getPosY())
            {
                zombies[i].setPosY(zombies[i].getPosY() - zombies[i].getSpeed());
                zombies[i].isFacingDown = true;
                zombies[i].isFacingUp = false;
            }
        }
        else if(!zombies[i].avoidingWall)
        {
            // if closer to player two move towards them
            if(zombies[i].isAlive() && zombies[i].getPosX() < two.getPosX())
            {
                zombies[i].setPosX(zombies[i].getPosX() + zombies[i].getSpeed());
                zombies[i].isFacingRight = true;
                zombies[i].isFacingLeft = false, zombies[i].isFacingUp = false, zombies[i].isFacingDown = false, zombies[i].isFacingLeftDown = false, zombies[i].isFacingRightDown = false, zombies[i].isFacingLeftUp = false, zombies[i].isFacingRightUp = false;
            }
            else if(zombies[i].isAlive() && zombies[i].getPosX() > two.getPosX())
            {
                zombies[i].setPosX(zombies[i].getPosX() - zombies[i].getSpeed());
                zombies[i].isFacingLeft = true;
                zombies[i].isFacingRight = false, zombies[i].isFacingUp = false, zombies[i].isFacingDown = false, zombies[i].isFacingLeftDown = false, zombies[i].isFacingRightDown = false, zombies[i].isFacingLeftUp = false, zombies[i].isFacingRightUp = false;
            }

            if(zombies[i].isAlive() && zombies[i].getPosY() < two.getPosY())
            {
                zombies[i].setPosY(zombies[i].getPosY() + zombies[i].getSpeed());
                zombies[i].isFacingUp = true;
                zombies[i].isFacingRight = false, zombies[i].isFacingLeft = false, zombies[i].isFacingDown = false, zombies[i].isFacingLeftDown = false, zombies[i].isFacingRightDown = false, zombies[i].isFacingLeftUp = false, zombies[i].isFacingRightUp = false;
            }
            else if(zombies[i].isAlive() && zombies[i].getPosY() > two.getPosY())
            {
                zombies[i].setPosY(zombies[i].getPosY() - zombies[i].getSpeed());
                zombies[i].isFacingDown = true;
                zombies[i].isFacingRight = false, zombies[i].isFacingLeft = false, zombies[i].isFacingUp = false, zombies[i].isFacingLeftDown = false, zombies[i].isFacingRightDown = false, zombies[i].isFacingLeftUp = false, zombies[i].isFacingRightUp = false;
            }
        }

        // if two facing options are true then the real one is applied
        if(zombies[i].isFacingRight && zombies[i].isFacingDown)
        {
            zombies[i].isFacingRight = false;
            zombies[i].isFacingDown = false;
            zombies[i].isFacingRightDown = true;
        }
        else if(zombies[i].isFacingRight && zombies[i].isFacingUp)
        {
            zombies[i].isFacingRight = false;
            zombies[i].isFacingUp = false;
            zombies[i].isFacingRightUp = true;
        }
        else if(zombies[i].isFacingLeft && zombies[i].isFacingDown)
        {
            zombies[i].isFacingLeft = false;
            zombies[i].isFacingUp = false;
            zombies[i].isFacingLeftDown = true;
        }
        else if(zombies[i].isFacingLeft && zombies[i].isFacingUp)
        {
            zombies[i].isFacingLeft = false;
            zombies[i].isFacingUp = false;
            zombies[i].isFacingLeftUp = true;
        }

        // if on the same x or y coordinate make facing any diagnol false due to it not being possible
        if(one.getPosX() == zombies[i].getPosX() || two.getPosX() == zombies[i].getPosX())
        {
            zombies[i].isFacingLeftDown = false;
            zombies[i].isFacingRightDown = false;
            zombies[i].isFacingLeftUp = false;
            zombies[i].isFacingRightUp = false;
        }
        else if(one.getPosY() == zombies[i].getPosY() || two.getPosY() == zombies[i].getPosY())
        {
            zombies[i].isFacingLeftDown = false;
            zombies[i].isFacingRightDown = false;
            zombies[i].isFacingLeftUp = false;
            zombies[i].isFacingRightUp = false;
        }
    }

    return zombies;
}

void bossBulletHandiling(Player &one, Player &two, vector <Enemy> zombies, vector <Enemy> &bossBullets, Window screen)
{
    bossBulletPlayerColl(bossBullets, zombies, one, two);

    // if the boss bullets leave the screen then reset them to original position
    for(int i = 0; i < bossBullets.size(); i++)
    {
        if(bossBullets[i].getPosX() > screen.getWidth() || bossBullets[i].getPosY() > screen.getHeight() || bossBullets[i].getPosY() < 0 || bossBullets[i].getPosX() < 0)
        {
            bossBullets[i].setPosX(zombies[zombies.size() - 1].getPosX());
            bossBullets[i].setPosY(zombies[zombies.size() - 1].getPosY());
        }
    }

    // moves boss bullets based on predetermined path
    bossBullets[0].setPosX(bossBullets[0].getPosX() + bossBullets[0].getSpeed());
    bossBullets[1].setPosX(bossBullets[1].getPosX() - bossBullets[1].getSpeed());
    bossBullets[2].setPosY(bossBullets[2].getPosY() + bossBullets[2].getSpeed());
    bossBullets[3].setPosY(bossBullets[3].getPosY() - bossBullets[3].getSpeed());
    bossBullets[4].setPosX(bossBullets[4].getPosX() - bossBullets[4].getSpeed());
    bossBullets[4].setPosY(bossBullets[4].getPosY() - bossBullets[4].getSpeed());
    bossBullets[5].setPosX(bossBullets[5].getPosX() + bossBullets[5].getSpeed());
    bossBullets[5].setPosY(bossBullets[5].getPosY() + bossBullets[5].getSpeed());
    bossBullets[6].setPosX(bossBullets[6].getPosX() - bossBullets[6].getSpeed());
    bossBullets[6].setPosY(bossBullets[6].getPosY() + bossBullets[6].getSpeed());
    bossBullets[7].setPosX(bossBullets[7].getPosX() + bossBullets[7].getSpeed());
    bossBullets[7].setPosY(bossBullets[7].getPosY() - bossBullets[7].getSpeed());
    bossBullets[8].setPosX(bossBullets[8].getPosX() - bossBullets[8].getSpeed());
    bossBullets[8].setPosY(bossBullets[8].getPosY() - bossBullets[8].getSpeed() + 1);
    bossBullets[9].setPosX(bossBullets[9].getPosX() + bossBullets[9].getSpeed());
    bossBullets[9].setPosY(bossBullets[9].getPosY() + bossBullets[9].getSpeed() + 1);
    bossBullets[10].setPosX(bossBullets[10].getPosX() - bossBullets[10].getSpeed() + 1);
    bossBullets[10].setPosY(bossBullets[10].getPosY() + bossBullets[10].getSpeed());
    bossBullets[11].setPosX(bossBullets[11].getPosX() + bossBullets[11].getSpeed());
    bossBullets[11].setPosY(bossBullets[11].getPosY() - bossBullets[11].getSpeed() + 1); 
    bossBullets[8].setPosX(bossBullets[8].getPosX() - bossBullets[8].getSpeed());
    bossBullets[8].setPosY(bossBullets[8].getPosY() - bossBullets[8].getSpeed() + 1);
    bossBullets[5].setPosX(bossBullets[5].getPosX() + bossBullets[5].getSpeed());
    bossBullets[5].setPosY(bossBullets[5].getPosY() + bossBullets[5].getSpeed() + 1);
    bossBullets[6].setPosX(bossBullets[6].getPosX() - bossBullets[6].getSpeed() + 1);
    bossBullets[6].setPosY(bossBullets[6].getPosY() + bossBullets[6].getSpeed());
    bossBullets[7].setPosX(bossBullets[7].getPosX() + bossBullets[7].getSpeed());
    bossBullets[7].setPosY(bossBullets[7].getPosY() - bossBullets[7].getSpeed() + 1);
    bossBullets[8].setPosX(bossBullets[8].getPosX() - bossBullets[8].getSpeed());
    bossBullets[8].setPosY(bossBullets[8].getPosY() + bossBullets[8].getSpeed() / 2);
    bossBullets[9].setPosX(bossBullets[9].getPosX() - bossBullets[9].getSpeed());
    bossBullets[9].setPosY(bossBullets[9].getPosY() - bossBullets[9].getSpeed() / 2);
    bossBullets[10].setPosX(bossBullets[10].getPosX() - bossBullets[10].getSpeed());
    bossBullets[10].setPosY(bossBullets[10].getPosY() + bossBullets[10].getSpeed() - 1.9);
    bossBullets[11].setPosX(bossBullets[11].getPosX() - bossBullets[11].getSpeed());
    bossBullets[11].setPosY(bossBullets[11].getPosY() + bossBullets[11].getSpeed() - 1.85);
}