#include "Players.hpp"

// changes weapon specs if upgraded
void gunUpgrade(Gun &both)
{
    if(both.weaponUpgrade)
    {
        both.reloadSpeedChange = 0.75;
        both.bulletAmountChange = 1.4;
        both.shotTimeChange = 0.9;
    }
}

// cooldown for shooting so the player cant spam
void shotCooldown(Gun &both, const float delta)
{
    if(both.shotTime > 0.0)
    {
        both.shotTime -= delta;
    }
}

void playersShooting(vector<Gun>&bullets, Gun &bothGun, Player &both, bool pOne, bool pTwo)
{
    int variance = (rand() % 30) - 15;
    bool whichGun;

    // sets up shooting inputs
    if((bothGun.getGunType() == "Rifle" && !bothGun.rifleQuest)|| bothGun.getGunType() == "Sniper" || bothGun.getGunType() == "Shotgun")
    {
        if(pOne)
        {
            whichGun = IsKeyPressed(KEY_E);
        }

        if(pTwo)
        {
            whichGun = IsKeyPressed(KEY_KP_DECIMAL);
        }

        both.isShooting = false;
    }
    else
    {
        if(pOne)
        {
            whichGun = IsKeyDown(KEY_E);
        }

        if(pTwo)
        {
            whichGun = IsKeyDown(KEY_KP_DECIMAL);
        }
    }

    if(whichGun && bothGun.shotTime <= 0.0 && bothGun.bulletAmount > 0 && !both.isReloading)
    {
        // checks direction of shooting and gun to decide how to push back bullets and move them
        if(both.shotRight)
        {
            bothGun.setXSize(15), bothGun.setYSize(10);
            bothGun.setAngle(90);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX() + 50, both.getPosY() - 26, bothGun.getBulletSpeed() / 1.1, -bothGun.getBulletSpeed() / 7, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() + 50, both.getPosY() + 10, bothGun.getBulletSpeed() / 1.1, bothGun.getBulletSpeed() / 7, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + 70, both.getPosY() + variance, bothGun.getBulletSpeed(), 0, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));     
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + 70, both.getPosY() - 8, bothGun.getBulletSpeed(), 0, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }
        else if(both.shotLeft)
        {
            bothGun.setXSize(15), bothGun.setYSize(10);                     
            bothGun.setAngle(-90);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX() - 50, both.getPosY() - 10, -bothGun.getBulletSpeed() / 1.1, -bothGun.getBulletSpeed() / 7, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() - 50, both.getPosY() + 25, -bothGun.getBulletSpeed() / 1.1, bothGun.getBulletSpeed() / 7, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() - 70, both.getPosY() + variance, -bothGun.getBulletSpeed(), 0, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() - 70, both.getPosY() + 8, -bothGun.getBulletSpeed(), 0, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }
        else if(both.shotUp)
        {
            bothGun.setXSize(10), bothGun.setYSize(15);
            bothGun.setAngle(0);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX() + 20, both.getPosY() - 50, bothGun.getBulletSpeed() / 7, -bothGun.getBulletSpeed() / 1.1, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() - 30, both.getPosY() - 45, -bothGun.getBulletSpeed() / 7, -bothGun.getBulletSpeed() / 1.1, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + variance, both.getPosY() - 60, 0, -bothGun.getBulletSpeed(), bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() - 8, both.getPosY() - 60, 0, -bothGun.getBulletSpeed(), bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }
        else if(both.shotDown)
        {
            bothGun.setXSize(10), bothGun.setYSize(15);    
            bothGun.setAngle(180);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX() + 35, both.getPosY() + 40, bothGun.getBulletSpeed() / 7, bothGun.getBulletSpeed() / 1.1, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() - 15, both.getPosY() + 39, -bothGun.getBulletSpeed() / 7, bothGun.getBulletSpeed() / 1.1, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + variance, both.getPosY() + 60, 0, bothGun.getBulletSpeed(), bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + 7, both.getPosY() + 60, 0, bothGun.getBulletSpeed(), bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }
        else if(both.shotRightUp)
        {
            bothGun.setXSize(10), bothGun.setYSize(15); 
            bothGun.setAngle(45);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX(), both.getPosY() - 30, bothGun.getBulletSpeed() / 3, -bothGun.getBulletSpeed() / 1.8, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() + 22, both.getPosY() - 10, bothGun.getBulletSpeed() / 1.8, -bothGun.getBulletSpeed() / 3, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + 26 + variance / 1.41, both.getPosY() - 39 + variance / 1.41, bothGun.getBulletSpeed() / 1.5, -bothGun.getBulletSpeed() / 1.5, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + 26, both.getPosY() - 39, bothGun.getBulletSpeed() / 2, -bothGun.getBulletSpeed() / 2, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }
        else if(both.shotRightDown)
        {
            bothGun.setXSize(10), bothGun.setYSize(15);          
            bothGun.setAngle(135);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX() + 35, both.getPosY() + 14, bothGun.getBulletSpeed() / 1.8, bothGun.getBulletSpeed() / 3, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() + 25, both.getPosY() + 41, bothGun.getBulletSpeed() / 3, bothGun.getBulletSpeed() / 1.8, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + 39 - variance / 1.41, both.getPosY() + 35 + variance / 1.41, bothGun.getBulletSpeed() / 1.41, bothGun.getBulletSpeed() / 1.41, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() + 39, both.getPosY() + 35, bothGun.getBulletSpeed() / 2, bothGun.getBulletSpeed() / 2, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }
        else if(both.shotLeftUp)
        {
            bothGun.setXSize(15), bothGun.setYSize(10);         
            bothGun.setAngle(315);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX() - 20, both.getPosY() - 28, -bothGun.getBulletSpeed() / 3, -bothGun.getBulletSpeed() / 1.8, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() - 31, both.getPosY() - 5, -bothGun.getBulletSpeed() / 1.8, -bothGun.getBulletSpeed() / 3, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() - 33 - variance / 1.41, both.getPosY() - 24 + variance / 1.41, -bothGun.getBulletSpeed() / 1.41, -bothGun.getBulletSpeed() / 1.41, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() - 33, both.getPosY() - 24, -bothGun.getBulletSpeed() / 2, -bothGun.getBulletSpeed() / 2, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }
        else if(both.shotLeftDown)
        {
            bothGun.setXSize(15), bothGun.setYSize(10);             
            bothGun.setAngle(225);

            if(bothGun.getGunType() == "Shotgun")
            {
                bullets.push_back(Gun(both.getPosX() - 5, both.getPosY() + 31, -bothGun.getBulletSpeed() / 3, bothGun.getBulletSpeed() / 1.8, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()-20, bothGun.getDamage(), bothGun.getGunType()));
                bullets.push_back(Gun(both.getPosX() - 21, both.getPosY() + 10, -bothGun.getBulletSpeed() / 1.8, bothGun.getBulletSpeed() / 3, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle()+20, bothGun.getDamage(), bothGun.getGunType()));
            }
            else if(bothGun.getGunType() == "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() - 24 + variance / 1.41, both.getPosY() + 25 + variance / 1.41, -bothGun.getBulletSpeed() / 1.41, bothGun.getBulletSpeed() / 1.41, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }

            if(bothGun.getGunType() != "Minigun")
            {
                bullets.push_back(Gun(both.getPosX() - 21, both.getPosY() + 29, -bothGun.getBulletSpeed() / 2, bothGun.getBulletSpeed() / 2, bothGun.getXSize(), bothGun.getYSize(), bothGun.getAngle(), bothGun.getDamage(), bothGun.getGunType()));
            }
        }

        bothGun.shotTime = bothGun.maxShotTime;
        bothGun.bulletAmount -= 1;
        both.isShooting = true;
    }
    else if(IsKeyUp(KEY_E) || IsKeyReleased(KEY_E))  
    {
        both.isShooting = false;
    }
}

// depending on the weapon the mass will change, mass slows down the player the higher it is
void weaponMass(Gun &gun, Player players)
{
    if(players.isShooting)
    {
        if(gun.getGunType() == "Minigun")
        {
            gun.weaponMass = 0.4;
        }
        else if(gun.getGunType() == "AR")
        {
            gun.weaponMass = 1.1;
        }
    }
    else
    {
        if(gun.getGunType() == "Minigun")
        {
            gun.weaponMass = 0.85;
        }
        else if(gun.getGunType() == "AR")
        {
            gun.weaponMass = 0.95;
        }
        else if(gun.getGunType() == "Shotgun")
        {
            gun.weaponMass = 0.95;
        }
        else if(gun.getGunType() == "Rifle")
        {
            gun.weaponMass = 0.98;
        }
        else if(gun.getGunType() == "Sniper")
        {
            gun.weaponMass = 0.88;
        }
    }

}

// if the player is using a shotgun the damage decreases overtime as the bullet moves
void shotgunDamage(vector<Gun>&bullets, Gun &bothGun)
{
    for(int i = 0; i < bullets.size(); i++)
    {
        if(GetTime() - bullets[i].time < 0.25 && bothGun.getGunType() == "Shotgun")
        {
            bullets[i].setDamage(80);
        }
        else if(GetTime() - bullets[i].time < 0.5 && bothGun.getGunType() == "Shotgun")
        {
            bullets[i].setDamage(50);
        }
        else if(GetTime() - bullets[i].time < 0.75 && bothGun.getGunType() == "Shotgun")
        {
            bullets[i].setDamage(40);
        }
        else if(GetTime() - bullets[i].time < 1 && bothGun.getGunType() == "Shotgun")
        {
            bullets[i].setDamage(20);
        }
        else if(bothGun.getGunType() == "Shotgun")
        {
            bullets[i].setDamage(10);
        }
    }
}

// moves the player backwards when shooting (amount depends on gun)
void recoil(Gun &gun, Player &both)
{
    if(both.isShooting)
    {
        if(gun.getGunType() == "Minigun")
        {
            gun.recoil = 0.2;
        }
        else if(gun.getGunType() == "AR")
        {
            gun.recoil = 0.3;
        }
        else if(gun.getGunType() == "Shotgun")
        {
            gun.recoil = 20;
        }
        else if(gun.getGunType() == "Sniper")
        {
            gun.recoil = 12;
        }
        else if(gun.getGunType() == "Rifle")
        {
            gun.recoil = 1 * gun.soloWeaponRecoil;
        }

        // applies recoil based on where the player is facing
        if(both.isFacingRight)  
        {
            both.setPosX(both.getPosX() + gun.recoil);
        }
        else if(both.isFacingLeft)  
        {
            both.setPosX(both.getPosX() - gun.recoil);
        }
        else if(both.isFacingDown)  
        {
            both.setPosY(both.getPosY() + gun.recoil);
        }
        else if(both.isFacingUp)  
        {
            both.setPosY(both.getPosY() - gun.recoil);
        }
        else if(both.isFacingRightUp)
        {
            both.setPosX(both.getPosX() + gun.recoil/1.4);
            both.setPosY(both.getPosY() - gun.recoil/1.4);
        }
        else if(both.isFacingRightDown)
        {
            both.setPosX(both.getPosX() + gun.recoil/1.4);
            both.setPosY(both.getPosY() + gun.recoil/1.4);
        }
        else if(both.isFacingLeftUp)
        {
            both.setPosX(both.getPosX() - gun.recoil/1.4);
            both.setPosY(both.getPosY() - gun.recoil/1.4);
        }
        else if(both.isFacingLeftDown)
        {
            both.setPosX(both.getPosX() - gun.recoil/1.4);
            both.setPosY(both.getPosY() + gun.recoil/1.4);
        }
    }
}

void perks(Player &one, Gun &oneGun, Player &two, Gun &twoGun, bool twoAlive)
{
    DrawText("PERKS: " , 300, 10, 20, WHITE);   

    // applies effects of perks to player one
    if(one.runPerk)
    {
        one.speedChange = 0.3;

        DrawText("SPEED" , 210, 35, 15, RED);        
    }

    if(one.slowPerk)
    {
        DrawText("SLOWMO" , 270, 35, 15, SKYBLUE);               
    }

    if(one.hpPerk)
    {
        one.hpChange = 150;

        DrawText("HP" , 345, 35, 15, GREEN);        
    }

    if(one.reloadPerk)
    {
        oneGun.perkReloadChange = 0.75;

        DrawText("RELOAD" , 380, 35, 15, WHITE);        
    }

    // perks for player two
    if(twoAlive)
    {
        DrawText("PERKS: " , 1300, 10, 20, WHITE);
                         
        if(IsKeyPressed(KEY_J))
        {
            two.runPerk = true;
        }

        if(IsKeyPressed(KEY_K))
        {
            two.hpPerk = true;
        }

        if(IsKeyPressed(KEY_L))
        {
            two.reloadPerk = true;
        }

        if(IsKeyPressed(KEY_O))
        {
            two.slowPerk = true;
        }

        if(two.runPerk)
        {
            two.speedChange = 0.3;

            DrawText("SPEED" , 1220, 35, 15, RED);        
        }

        if(two.slowPerk)
        {
            DrawText("SLOWMO" , 1280, 35, 15, SKYBLUE);        
        }
       
        if(two.hpPerk)
        {
            two.hpChange = 150;

            DrawText("HP" , 1355, 35, 15, GREEN);        
        }

        if(two.reloadPerk)
        {
            twoGun.perkReloadChange = 0.75;

            DrawText("RELOAD" , 1390, 35, 15, WHITE);        
        }
    }
}

// changes the stats of the gun depending on what gun the player has
void weaponStats(Gun &gun, Player &both, int &waveNum)
{     
    if(gun.getGunType() == "Rifle")             
    {
        gun.maxBulletAmount = 12 * gun.bulletAmountChange * gun.soloBulletAmount;
        gun.maxShotTime = 0.7 * gun.shotTimeChange * gun.soloShotSpeed;
        gun.maxReloadTime = 1 * gun.perkReloadChange * gun.reloadSpeedChange * gun.soloReloadSpeed;
        if(waveNum <= 20)
        {
            gun.setDamage((20 + waveNum) * both.questDamage * gun.soloDamage);
        }
        else
        {
            gun.setDamage((100) * both.questDamage * gun.soloDamage);
        }
        gun.setSpeed(8,8);         
    }
    else if(gun.getGunType() == "Minigun")   
    {
        gun.maxBulletAmount = 120 * gun.bulletAmountChange;
        gun.maxShotTime = 0.08 * gun.shotTimeChange;
        gun.maxReloadTime = 4 * gun.perkReloadChange * gun.reloadSpeedChange;
        gun.setDamage(20 * both.questDamage);
        gun.setSpeed(10,10);        
    }
    else if(gun.getGunType() == "AR")
    {
        gun.maxBulletAmount = 40 * gun.bulletAmountChange;
        gun.maxShotTime = 0.15 * gun.shotTimeChange;
        gun.maxReloadTime = 1.5 * gun.perkReloadChange * gun.reloadSpeedChange;
        gun.setDamage(14 * both.questDamage);
        gun.setSpeed(11, 11);
    }
    else if(gun.getGunType() == "Shotgun")
    {
        gun.maxBulletAmount = 8 * gun.bulletAmountChange;
        gun.maxShotTime = 0.8 * gun.shotTimeChange;
        gun.maxReloadTime = 2.5 * gun.perkReloadChange * gun.reloadSpeedChange;
        gun.setDamage(80 * both.questDamage);
        gun.setSpeed(6,6); 
    }
    else if(gun.getGunType() == "Sniper")
    {
        gun.maxBulletAmount = 3 * gun.bulletAmountChange;
        gun.maxShotTime = 2 * gun.shotTimeChange;
        gun.maxReloadTime = 2.5 * gun.perkReloadChange * gun.reloadSpeedChange;
        gun.setDamage(34 * both.questDamage);
        gun.setSpeed(15,15);        
    }
}

// if the player reloads this makes it so it takes time
void reloadTime(Gun &bothGun , Player &both)
{
    if(GetTime() - bothGun.reloadTime > bothGun.maxReloadTime && both.isReloading)
    {
        bothGun.bulletAmount = bothGun.maxBulletAmount;

        both.isReloading = false;
    }
}

void playersReloading(Player &both, Gun &bothGun, bool one, bool two)
{
    bool reloadKey;

    // reload key for player one
    if(one)
    {
        reloadKey = IsKeyPressed(KEY_R);
    }

    // reload keu for player two
    if(two)
    {
        reloadKey = IsKeyPressed(KEY_RIGHT_CONTROL);
    }

    // if the reload key is pressed and the player isn't already reloading then start reload time and reload
    if(reloadKey && !both.isReloading && bothGun.bulletAmount != bothGun.maxBulletAmount)
    {
        bothGun.reloadTime = GetTime();

        both.isShooting = false;
        both.isReloading = true;
    }
}

// draws a red rectangle facing the direction of the menuplayer
Player drawPlayerGun(Player both)
{
    if(both.isAlive())
    {
        if(both.isFacingLeft)
        {
            DrawRectangle(both.getPosX() + both.getRadius() + 5, both.getPosY() - 5, 15, 10, RED);
    
            both.shotRight = true;
            both.shotLeft = false, both.shotUp = false, both.shotDown = false;
            both.shotLeftUp = false, both.shotLeftDown = false, both.shotRightUp = false, both.shotRightDown = false;
        }

        if(both.isFacingRight)
        {
            DrawRectangle(both.getPosX() - both.getRadius() - 19, both.getPosY() - 5, 15, 10, RED);

            both.shotLeft = true;
            both.shotRight = false, both.shotUp = false, both.shotDown = false;
            both.shotLeftUp = false, both.shotLeftDown = false, both.shotRightUp = false, both.shotRightDown = false;
        }

        if(both.isFacingDown)
        {
            DrawRectangle(both.getPosX() - both.getRadius() + 15, both.getPosY() - 39, 10, 15, RED);

            both.shotUp = true;
            both.shotLeft = false, both.shotRight = false, both.shotDown = false;
            both.shotLeftUp = false, both.shotLeftDown = false, both.shotRightUp = false, both.shotRightDown = false;
        }

        if(both.isFacingUp)
        {
            DrawRectangle(both.getPosX() - both.getRadius() + 15, both.getPosY() + 24, 10, 15, RED);

            both.shotDown = true;
            both.shotLeft = false, both.shotRight = false, both.shotUp = false;
            both.shotLeftUp = false, both.shotLeftDown = false, both.shotRightUp = false, both.shotRightDown = false;
        }

        // Dimension 4-8 to give it a rotation feeling
        if(both.isFacingLeftDown)
        {
            DrawRectanglePro(Rectangle{both.getPosX() - both.getRadius() + 40, both.getPosY() - 26, 10, 15}, Vector2{5, 7.5}, 45, RED);
            
            both.shotRightUp = true;
            both.shotLeft = false, both.shotRight = false, both.shotUp = false, both.shotDown = false;
            both.shotLeftUp = false, both.shotLeftDown = false, both.shotRightDown = false;
        }

        if(both.isFacingLeftUp)
        {
            DrawRectanglePro(Rectangle{both.getPosX() - both.getRadius() + 40, both.getPosY() + 25, 15, 10}, Vector2{7.5, 5}, 45, RED);
            
            both.shotRightDown = true;
            both.shotLeft = false, both.shotRight = false, both.shotUp = false, both.shotDown = false;
            both.shotLeftUp = false, both.shotLeftDown = false, both.shotRightUp = false;
        }

        if(both.isFacingRightDown)
        {
            DrawRectanglePro(Rectangle{both.getPosX() - both.getRadius() - 4, both.getPosY() - 24, 15, 10}, Vector2{7.5, 5}, 45, RED);
            
            both.shotLeftUp = true;
            both.shotLeft = false, both.shotRight = false, both.shotUp = false, both.shotDown = false;
            both.shotRightUp = false, both.shotLeftDown = false, both.shotRightDown = false;
        }

        if(both.isFacingRightUp)
        {
            DrawRectanglePro(Rectangle{both.getPosX() - both.getRadius() - 4, both.getPosY() + 25, 10, 15}, Vector2{5, 7.5}, 45, RED);
            
            both.shotLeftDown = true;
            both.shotLeft = false, both.shotRight = false, both.shotUp = false, both.shotDown = false;
            both.shotLeftUp = false, both.shotRightUp = false, both.shotRightDown = false;
        }
    }

    return both;
}

// if the boss bullet hits either players then apply damage to them and return the bullet to the boss
void bossBulletPlayerColl(vector <Enemy> &bossBullets, vector <Enemy> zombies, Player &one, Player &two)
{
    for(int i = 0; i < bossBullets.size(); i++)
    {
        if(CheckCollisionCircles({one.getPosX(), one.getPosY()}, one.getRadius(), {bossBullets[i].getPosX(), bossBullets[i].getPosY()}, bossBullets[i].getRadius()))
        {
            one.bossHit = true;
        }

        if(CheckCollisionCircles({two.getPosX(), two.getPosY()}, two.getRadius(), {bossBullets[i].getPosX(), bossBullets[i].getPosY()}, bossBullets[i].getRadius()))
        {
            two.bossHit = true;
        }

        if(one.bossHit == true)
        {
            one.setHealth(one.getHealth() - 25);
            one.healthTime = GetTime();
            one.isHitAtAll = true;
            bossBullets[i].setPosX(zombies[zombies.size() - 1].getPosX());
            bossBullets[i].setPosY(zombies[zombies.size() - 1].getPosY());
            one.bossHit = false;
        }

        if(two.bossHit == true)
        {
            two.setHealth(two.getHealth() - 25);
            one.isHitAtAll = true;
            two.healthTime = GetTime();
            bossBullets[i].setPosX(zombies[zombies.size() - 1].getPosX());
            bossBullets[i].setPosY(zombies[zombies.size() - 1].getPosY());
            two.bossHit = false;
        }
    }
}

// quest for both players to complete to indefinetly increase damage
void duoQuest(Player &one, Player &two, int roundCount)
{
    static float questTime = 0;

    if(!one.isHitAtAll && !two.isHitAtAll && roundCount == 11)
    {
        one.questDamage = 1.5;
        two.questDamage = 1.5;
        questTime = GetTime();
        one.isHitAtAll = true;
        two.isHitAtAll = true;
    }

    if(GetTime() - questTime <= 3)
    {
        DrawText("1.5X DMG TO PLAYERS", 570, 475, 50, WHITE);
    }
}

// quest for each individual player
void soloQuest(Player &one, Player &two, Gun &oneGun, Gun &twoGun, int roundCount)
{
    static float rifleTime = 0;
    static bool preventTimeLoop = true;

    if(oneGun.getGunType() == "Rifle" && twoGun.getGunType() == "Rifle" && roundCount >= 21 && preventTimeLoop)
    {
        oneGun.soloDamage = 4;
        oneGun.soloBulletAmount = 7;
        oneGun.soloReloadSpeed = 0.7;
        oneGun.bulletAmount = oneGun.maxBulletAmount * oneGun.soloBulletAmount;
        oneGun.soloShotSpeed = 0.15;
        oneGun.soloWeaponMass = 1;
        oneGun.soloWeaponRecoil = 0.2;
        oneGun.rifleQuest = true;
        preventTimeLoop = false;
        rifleTime = GetTime();
    }

    if(oneGun.getGunType() == "Rifle" && GetTime() - rifleTime <= 3)
    {
        DrawText("Your Rifle feels an unknown presence...", one.getPosX() - 150, one.getPosY() - 80, 15, WHITE);
    }


    if(twoGun.getGunType() == "Rifle" && oneGun.getGunType() == "Rifle" && roundCount == 21 && preventTimeLoop)
    {
        twoGun.soloDamage = 4;
        twoGun.soloBulletAmount = 7;
        twoGun.bulletAmount = twoGun.maxBulletAmount * twoGun.soloBulletAmount;
        twoGun.soloReloadSpeed = 0.7;
        twoGun.soloShotSpeed = 0.15;
        twoGun.weaponMass = 1;
        twoGun.soloWeaponRecoil = 0.2;
        twoGun.rifleQuest = true;
        preventTimeLoop = false;
        rifleTime = GetTime();
    }

    if(twoGun.getGunType() == "Rifle" && GetTime() - rifleTime <= 3)
    {
        DrawText("Your Rifle feels an unknown presence...", two.getPosX() - 150, two.getPosY() - 80, 15, WHITE);
    }
}

void perkInput(Player &both, bool one, bool two) 
{
    bool inputs;

    // player one key for buying perks
    if(one) 
    {
        inputs = IsKeyPressed(KEY_Q);
    }

    // player two key for buying perks
    if(two) 
    {
        inputs = IsKeyPressed(KEY_KP_ADD);
    }

    // option to buy speed perk
    if(both.getPosX() <= 1220 && both.getPosX() >= 1150 && both.getPosY() >= 700 && both.getPosY() <= 770 && both.money >= 5000 && !both.runPerk) 
    {
        DrawText("Purchase Speed Perk? (5000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);
        if(inputs) 
        {
            both.runPerk = true;
            both.money -= 5000;
        }
    }
    else if(both.getPosX() <= 1220 && both.getPosX() >= 1150 && both.getPosY() >= 700 && both.getPosY() <= 800 && both.money < 5000 && !both.runPerk) 
    {
        DrawText("Purchase Speed Perk? (5000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }

    // option to buy health perk
    if(both.getPosX() <= 1380 && both.getPosX() >= 1295 && both.getPosY() >= 200 && both.getPosY() <= 270 && both.money >= 7000 && !both.hpPerk) 
    {
        DrawText("Purchase Health Perk? (7000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);
        if(inputs) 
        {
            both.hpPerk = true;
            both.money -= 7000;
        }
    }
    else if(both.getPosX() <= 1380 && both.getPosX() >= 1295 && both.getPosY() >= 200 && both.getPosY() <= 270 && both.money < 7000 && !both.hpPerk) 
    {
        DrawText("Purchase Health Perk? (7000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }

    //option to buy reload perk
    if(both.getPosX() <= 500 && both.getPosX() >= 395 &&both.getPosY() >= 210 && both.getPosY() <= 270 &&both.money >= 5500 && !both.reloadPerk) 
    {
        DrawText("Purchase Reload Perk? (5500)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);

        if(inputs) 
        {
            both.reloadPerk = true;
            both.money -= 5500;
        }
    }
    else if(both.getPosX() <= 500 && both.getPosX() >= 395 &&both.getPosY() >= 210 && both.getPosY() <= 270 &&both.money < 5500 && !both.reloadPerk) 
    {
        DrawText("Purchase Reload Perk? (5500)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }

    // option to buy slowmo perk
    if(both.getPosX() <= 880 && both.getPosX() >= 800 && both.getPosY() >= 300 && both.getPosY() <= 360 && both.money >= 9000 && !both.slowPerk) 
    {
        DrawText("Purchase Slowmo Perk? (9000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);

        if(inputs) 
        {
            both.slowPerk = true;
            both.money -= 9000;
        }
    }
    else if(both.getPosX() <= 880 && both.getPosX() >= 800 &&both.getPosY() >= 300 && both.getPosY() <= 360 &&both.money < 9000 && !both.slowPerk) 
    {
        DrawText("Purchase Slowmo Perk? (9000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }
}

void weaponInput(Player &both, Gun &bothGun, bool one, bool two)
{
    bool inputs;

    // player one key to buy weapons
    if(one)
    {
        inputs = IsKeyPressed(KEY_Q);
    }

    // player two key to buy weapons
    if(two)
    {
        inputs = IsKeyPressed(KEY_KP_ADD);
    }

    // option to buy AR
    if(both.getPosX() <= 760 && both.getPosX() >= 700 && both.getPosY() >= 220 && both.getPosY() <= 260 && both.money >= 5000 && bothGun.getGunType() != "AR") 
    {
        DrawText("Purchase AR? (5000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);
        
        if(inputs) 
        {
            bothGun.weaponUpgrade = false;
            bothGun.setGunType("AR");
            bothGun.maxBulletAmount = 40;
            bothGun.bulletAmount = 40;

            both.money -= 5000;
        }
    }
    else if(both.getPosX() <= 760 && both.getPosX() >= 700 && both.getPosY() >= 220 && both.getPosY() <= 260 && both.money < 5000 && bothGun.getGunType() != "AR") 
    {
        DrawText("Purchase AR? (5000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }

    // option to buy shotgun
    if(both.getPosX() <= 1570 && both.getPosX() >= 1490 && both.getPosY() >= 110 && both.getPosY() <= 150 && both.money >= 10000 && bothGun.getGunType() != "Shotgun") 
    {
        DrawText("Purchase Shotgun? (10000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);
        
        if(inputs) 
        {
            bothGun.weaponUpgrade = false;
            bothGun.setGunType("Shotgun");
            bothGun.maxBulletAmount = 8;
            bothGun.bulletAmount = 8;
            
            both.money -= 10000;
        }
    }
    else if(both.getPosX() <= 1570 && both.getPosX() >= 1490 && both.getPosY() >= 110 && both.getPosY() <= 150 && both.money < 10000 && bothGun.getGunType() != "Shotgun") 
    {
        DrawText("Purchase Shotgun? (10000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }

    // option to buy sniper
    if(both.getPosX() <= 1350 && both.getPosX() >= 1260 && both.getPosY() >= 590 && both.getPosY() <= 670 && both.money >= 12000 && bothGun.getGunType() != "Sniper") 
    {
        DrawText("Purchase Sniper? (12000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);
       
        if(inputs) 
        {
            bothGun.weaponUpgrade = false;
            bothGun.setGunType("Sniper");
            bothGun.maxBulletAmount = 3;
            bothGun.bulletAmount = 3;
            
            both.money -= 12000;
        }
    }
    else if(both.getPosX() <= 1350 && both.getPosX() >= 1260 && both.getPosY() >= 590 && both.getPosY() <= 670 && both.money < 12000 && bothGun.getGunType() != "Sniper") 
    {
        DrawText("Purchase Sniper? (12000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }

    // option to buy minigun
    if(both.getPosX() <= 170 && both.getPosX() >= 90 && both.getPosY() >= 470 && both.getPosY() <= 540 && both.money >= 14000 && bothGun.getGunType() != "Minigun") 
    {
        DrawText("Purchase Minigun? (14000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, WHITE);
        if(inputs) 
        {
            bothGun.weaponUpgrade = false;
            bothGun.maxBulletAmount = 140;
            bothGun.bulletAmount = 140;
            bothGun.setGunType("Minigun");

            both.money -= 14000;
        }
    }
    else if(both.getPosX() <= 170 && both.getPosX() >= 90 && both.getPosY() >= 470 && both.getPosY() <= 540 && both.money < 14000 && bothGun.getGunType() != "Minigun") 
    {
        DrawText("Purchase Minigun? (14000)", both.getPosX() - both.getRadius() - 20, both.getPosY() + both.getRadius() + 40, 15, RED);
    }
}

void upgradeInput(Player &one, Player &two, Player &both, Gun &bothGun, bool oneInput, bool twoInput)
{
    Color semiTransparentColor = {255, 50, 50, 64};
    bool inputs;

    // player one input for weapon upgrade
    if(oneInput)
    {
        inputs = IsKeyPressed(KEY_Q);
    }

    // player two input for weapon upgrade
    if(twoInput)
    {
        inputs = IsKeyPressed(KEY_KP_ADD);
    }

    //Drawing Weapon Upgrade Area
    if(one.zomKills + two.zomKills >= 500)
    {
        DrawRectanglePro(Rectangle{1690, 475, 20, 100}, Vector2{20 / 2, 100 / 2}, 0, semiTransparentColor);
        
        if(both.getPosX() <= 1700 && both.getPosX() >= 1575 && both.getPosY() >= 400 && both.getPosY() <= 525 && both.money >= 24000 && !bothGun.weaponUpgrade)
        {
            DrawText("Purchase Weapon \nUpgrade? (24000)", both.getPosX() - both.getRadius() - 150, both.getPosY() + both.getRadius() + 40, 15, WHITE);
            
            if(inputs) 
            {
                bothGun.weaponUpgrade = true;
                
                both.money -= 24000;
            }
        }
        else if(both.getPosX() <= 1700 && both.getPosX() >= 1575 &&both.getPosY() >= 400 && both.getPosY() <= 525 &&both.money < 24000 && !bothGun.weaponUpgrade)
        {
            DrawText("Purchase Weapon Upgrade Perk? (24000)", both.getPosX() - both.getRadius() - 150, both.getPosY() + both.getRadius() + 40, 15, RED);
        }
    }
}

// vector <Gun> deleteBullets(vector <Gun> bothBullets, Window screen)
// {
//     int checkBulletAmount = 0;

//     if(bothBullets.size() > 99)
//     {
//         for(int i = 0; i < bothBullets.size(); i++)
//         {
//             if(bothBullets[i].getPosX() > screen.getWidth() || bothBullets[i].getPosX() < 0 || bothBullets[i].getPosY() > screen.getHeight() || bothBullets[i].getPosY() < 0)
//             {
//                 checkBulletAmount += 1;
//             }
//         }

//         if(checkBulletAmount == 99)
//         {
//             bothBullets.clear();
//         }
//     }

//     return bothBullets;
// }

vector <Gun> deleteBullets(vector <Gun> bothBullets, Window screen)
{
    for(int i = 0; i < bothBullets.size(); i++)
    {
        if(bothBullets[i].getPosX() > screen.getWidth() || bothBullets[i].getPosX() < 0 || bothBullets[i].getPosY() > screen.getHeight() || bothBullets[i].getPosY() < 0)
        {
            bothBullets.erase(bothBullets.begin() + i);
        }
    }
    return bothBullets;
}