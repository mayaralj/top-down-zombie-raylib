#include "Classes.hpp"

void windowBoundry(Player &one, Player &two)
{
    //Prevent them from ever getting past boundaries (X)
    if(one.getPosX() <= 20)
    {
        one.setPosX(one.getPosX() + 1);
    }

    if(two.getPosX() <= 20)
    {
        two.setPosX(two.getPosX() + 1);
    }

    if(one.getPosX() >= 1680)
    {
        one.setPosX(one.getPosX() - 1);
    }

    if(two.getPosX() >= 1680)
    {
        two.setPosX(two.getPosX() - 1);
    }  
    
    //Prevent them from ever getting past boundaries (Y)
    if(one.getPosY() <= 20)
    {
        one.setPosY(one.getPosY() + 1);
    }

    if(two.getPosY() <= 20)
    {
        two.setPosY(two.getPosY() + 1);
    }

    if(one.getPosY() >= 930)
    {
        one.setPosY(one.getPosY() - 1);
    }

    if(two.getPosY() >= 930)
    {
        two.setPosY(two.getPosY() - 1);
    }  
}

void checkPlayerAlive(Player &both, Gun &bothGun)
{
    // removes player from gameplay area if dead
    if(both.getHealth() <= 0)
    {
        both.setAlive(false);
        both.hpPerk = false;
        both.slowPerk = false;
        both.runPerk = false;
        both.reloadPerk = false;
        bothGun.setGunType("Rifle");
        bothGun.weaponUpgrade = false;
        both.setPosX(10000);
    }
}

// chacks if the players collide
bool checkPlayerCollide(Player one, Player two)
{
    return CheckCollisionCircles({one.getPosX(), one.getPosY()}, one.getRadius(), {two.getPosX(), two.getPosY()}, two.getRadius());
}

void playersCollide(Player &one, Player &two)
{
    bool playersCollide = checkPlayerCollide(one, two);

    // sets the player back if they collide
    if(playersCollide)
    {
        if(one.getPosX() < two.getPosX())
        {
            if(one.getPosX() > 20)
            {
                one.setPosX(one.getPosX() - 0.75);

                two.setPosX(two.getPosX() + 0.75);  
            }
        }
        else
        {
            if(one.getPosX() < 1680)
            {
                one.setPosX(one.getPosX() + 0.75);

                two.setPosX(two.getPosX() - 0.75);  
            }            
        }

        if(one.getPosY() < two.getPosY())
        {
            if(one.getPosY() > 20)
            {                
                one.setPosY(one.getPosY() - 0.75);

                two.setPosY(two.getPosY() + 0.75);
            }
        }
        else
        {
            if(one.getPosY() < 930)
            {                
                one.setPosY(one.getPosY() + 0.75);

                two.setPosY(two.getPosY() - 0.75);
            }            
        }

        // sets player two back
        if(two.getPosX() < one.getPosX())
        {
            if(two.getPosX() > 20)
            {
                two.setPosX(two.getPosX() - 0.75);

                one.setPosX(one.getPosX() + 0.75);  
            }
        }
        else
        {
            if(two.getPosX() < 1680)
            {
                two.setPosX(two.getPosX() + 0.75);

                one.setPosX(one.getPosX() - 0.75);  
            }
        }

        if(two.getPosY() < one.getPosY())
        {
            if(two.getPosY() > 20)
            {                
                two.setPosY(two.getPosY() - 0.75);

                one.setPosY(one.getPosY() + 0.75);
            }
        }
        else
        {
            if(two.getPosY() < 930)
            {                
                two.setPosY(two.getPosY() + 0.75);

                one.setPosY(one.getPosY() - 0.75);
            }  
        
        }            
    }
}

void playersRunning(Player &both, const float delta, bool one, bool two)
{
    bool running;

    // player one shift key
    if(one)
    {
        running = IsKeyDown(KEY_LEFT_SHIFT);
    }

    // player two shift key
    if(two)
    {
        running = IsKeyDown(KEY_KP_ENTER);
    }

    // increases speed and decreases stamina over time while sprinting
    if(running && both.getStamina() > 0)
    {
        both.setSpeed(1.7 + both.speedChange);
        both.setStamina(both.getStamina() - delta);
        both.stamTime = GetTime();
    }
    else
    {
        if(both.isFacingLeftDown || both.isFacingRightDown || both.isFacingLeftUp || both.isFacingLeftDown)
        {
            both.setSpeed(1.1 + both.speedChange);  
        }
        else
        {
            both.setSpeed(1.0 + both.speedChange);
        }
    }
}

// movement inputs for the players
void playersMovement(Player &both, Gun &gun, const float delta, bool one, bool two)
{
    bool moveLeft, moveRight, moveUp, moveDown;

    // setting player one inputs 
    if(one)
    {
        moveLeft = IsKeyDown(KEY_A);
        moveRight = IsKeyDown(KEY_D);
        moveUp = IsKeyDown(KEY_W);
        moveDown = IsKeyDown(KEY_S);
    }

    // sets player two inputs
    if(two)
    {
        moveLeft = IsKeyDown(KEY_LEFT);
        moveRight = IsKeyDown(KEY_RIGHT);
        moveUp = IsKeyDown(KEY_UP);
        moveDown = IsKeyDown(KEY_DOWN);
    }
  
    if (moveLeft && both.getPosX() > 20)
    {
        both.setPosX(both.getPosX() - both.getSpeed() * gun.weaponMass);
        both.isFacingLeft = true;
        both.isFacingRight = false, both.isFacingUp = false, both.isFacingDown = false, both.isFacingLeftDown = false, both.isFacingRightDown = false, both.isFacingLeftUp = false, both.isFacingRightUp = false;
    }

    if (moveRight && both.getPosX() < 1680)
    {
        both.setPosX(both.getPosX() + both.getSpeed() * gun.weaponMass);
        both.isFacingRight = true;
        both.isFacingLeft = false, both.isFacingUp = false, both.isFacingDown = false, both.isFacingLeftDown = false, both.isFacingRightDown = false, both.isFacingLeftUp = false, both.isFacingRightUp = false;
    }

    if (moveUp && both.getPosY() > 20)
    {
        both.setPosY(both.getPosY() - both.getSpeed() * gun.weaponMass);
        both.isFacingUp = true;
        both.isFacingLeft = false, both.isFacingRight = false, both.isFacingDown = false, both.isFacingLeftDown = false, both.isFacingRightDown = false, both.isFacingLeftUp = false, both.isFacingRightUp = false;
    }

    if (moveDown && both.getPosY() < 930)
    {
        both.setPosY(both.getPosY() + both.getSpeed() * gun.weaponMass);
        both.isFacingDown = true;
        both.isFacingLeft = false, both.isFacingUp = false, both.isFacingRight = false, both.isFacingLeftDown = false, both.isFacingRightDown = false, both.isFacingLeftUp = false, both.isFacingRightUp = false;
    }

    if (moveLeft && moveDown)
    {
        both.setPosX(both.getPosX() + (both.getSpeed() / 3) * gun.weaponMass);
        both.setPosY(both.getPosY() - (both.getSpeed() / 3) * gun.weaponMass);
        both.isFacingLeftDown = true;
        both.isFacingLeft = false, both.isFacingUp = false, both.isFacingRight = false, both.isFacingDown = false, both.isFacingRightDown = false, both.isFacingLeftUp = false, both.isFacingRightUp = false;
    }

    if (moveLeft && moveUp)
    {
        both.setPosX(both.getPosX() + (both.getSpeed() / 3) * gun.weaponMass);
        both.setPosY(both.getPosY() + (both.getSpeed() / 3) * gun.weaponMass);
        both.isFacingLeftUp = true;
        both.isFacingLeft = false, both.isFacingUp = false, both.isFacingRight = false, both.isFacingDown = false, both.isFacingLeftDown = false, both.isFacingRightUp = false, both.isFacingRightDown = false;
    }

    if (moveRight && moveDown)
    {
        both.setPosX(both.getPosX() - (both.getSpeed() / 3) * gun.weaponMass);
        both.setPosY(both.getPosY() - (both.getSpeed() / 3) * gun.weaponMass);
        both.isFacingRightDown = true;
        both.isFacingLeft = false, both.isFacingUp = false, both.isFacingRight = false, both.isFacingDown = false, both.isFacingLeftDown = false, both.isFacingLeftUp = false, both.isFacingRightUp = false;
    }

    if (moveRight && moveUp)
    {
        both.setPosX(both.getPosX() - (both.getSpeed() / 3) * gun.weaponMass);
        both.setPosY(both.getPosY() + (both.getSpeed() / 3) * gun.weaponMass);
        both.isFacingRightUp = true;
        both.isFacingLeft = false, both.isFacingUp = false, both.isFacingRight = false, both.isFacingDown = false, both.isFacingLeftDown = false, both.isFacingLeftUp = false, both.isFacingRightDown = false;
    }
}

// regens stamina after a set time
void stamRegen(Player &both)
{
    if (both.getStamina() < 200)
    {
        if (GetTime() - both.stamTime > 1)
        {
            both.setStamina(both.getStamina() + 1);
        }
    }
}

// regens health after a set time
void healthRegen(Player &both)
{
    if (both.getHealth() < 100 + both.hpChange)
    {
        if (GetTime() - both.healthTime > 5)
        {
            both.setHealth(both.getHealth() + 1);
        }
    }   
}

// input to activate two player mode
void twoPlayer(Player &two)
{
    if(IsKeyPressed(KEY_RIGHT_SHIFT) && !two.twoPlayerMode)
    {
        two.twoPlayerMode = true;
        two.setAlive(true);
        two.setPosX(1250);
        two.setPosY(500);
    }
}

// menu player movement for start screen animation
Player menuMovement(Player menu, bool menuMove)
{
    // moves the player in a rectangle to avoid the zombies in the start screen animation
    if(menuMove && menu.getPosY() < 800 && menu.getPosX() <= 200)
    {
        menu.setPosY(menu.getPosY() + menu.getSpeed() * 2);
        menu.isFacingDown = true;
        menu.isFacingLeft = false;
    }

    if(menu.getPosX() < 900 && menu.getPosY() == 800)
    {
        menu.setPosX(menu.getPosX() + menu.getSpeed() * 2);
        menu.isFacingDown = false;
        menu.isFacingRight = true;
    }

    if(menu.getPosX() >= 900 && menu.getPosY() > 400)
    {
        menu.setPosY(menu.getPosY() - menu.getSpeed() * 2);
        menu.isFacingUp = true;
        menu.isFacingRight = false;
    }

    if(menu.getPosX() >= 200 && menu.getPosY() <= 400)
    {
        menu.setPosX(menu.getPosX() - menu.getSpeed() * 2);
        menu.isFacingUp = false;
        menu.isFacingLeft = true;
    }

    return menu;
}