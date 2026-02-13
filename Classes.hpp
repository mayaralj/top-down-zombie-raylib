#include <raylib.h>
#include <iostream>
#include "math.h"
#include <vector>
#include "string"
#include <bits/stdc++.h>
using namespace std;

class Window
{
    protected:
        float hei = 950;
        float wid = 1700;

    public:
        void setHeight(float height)
        {
            hei = height;
        }
        void setWidth(float width)
        {
            wid = width;
        }
        float getHeight()
        {
            return hei;
        }
        float getWidth()
        {
            return wid;
        }
};

class Enemy{
    protected:
        float x, y, rad, spd;
        int hp;
        bool col, exist, harm;

    public:
        bool isFacingLeft = false, isFacingRight = false, isFacingUp = false, isFacingDown = false;
        bool isFacingLeftUp = false, isFacingLeftDown = false, isFacingRightUp = false, isFacingRightDown = false;
        bool zomPlayerColl = false, avoidingWall = false, avoidingVert = false, avoidingHorz = false, isHitting = false, isSlowedCooldown;
        int zomColl, avoidDirection = false;
        double hitTime = 0, wallMoveTime, slowTime = 0, slowTimeCooldown = 0, attackTime = 0;
        float originalSpeed = 0;

        void setHealth(int health)
        {
            hp = health;
        }
        void setPosX(float posX)
        {
            x = posX;
        }
        void setPosY(float posY)
        {
            y = posY;
        }
        void setRadius(float radius)
        {
            rad = radius;
        }
        void setSpeed(float speed)
        {
            spd = speed;
        }
        void setCollision(bool collision)
        {
            col = collision;
        }
        void setAlive(bool alive)
        {
            exist = alive;
        }
        int getHealth()
        {
            return hp;
        }
        float getPosX()
        {
            return x;
        }
        float getPosY()
        {
            return y;
        }
        float getRadius()
        {
            return rad;
        }
        float getSpeed()
        {
            return spd;
        }
        bool getCollision()
        {
            return col;
        }
        bool isAlive()
        {
            return exist;
        }

        Enemy(int health, float posX, float posY, float radius, float speed, bool collision, bool alive)
        {
            setHealth(health);
            setPosX(posX);
            setPosY(posY);
            setRadius(radius);
            setSpeed(speed);
            setCollision(collision);
            setAlive(alive);
        }
};

class Player{
    protected:
        float x = 400, y = 400, spd;
        int rad = 20, hp, stm;
        bool col = false, exist = false, hit = false;

    public:
        //Variables
        double stamTime = 0, healthTime = 0;
        int money = 99999, zomKills = 0;
        float speedChange = 0, hpChange = 0, questDamage = 1;
        bool isFacingLeft = false, isFacingRight = false, isFacingUp = false, isFacingDown = false;
        bool isFacingLeftUp = false, isFacingLeftDown = false, isFacingRightUp = false, isFacingRightDown = false;
        bool twoPlayerMode = false, isShooting = false, isReloading = false;
        bool shotLeft, shotRight, shotUp, shotDown, shotLeftUp, shotLeftDown, shotRightUp, shotRightDown;
        bool hpPerk = false, reloadPerk = false, runPerk = false, slowPerk = false, bossHit = false, isHitAtAll = false;

        void setHealth(int health)
        {
            hp = health;
        }
        void setStamina(float stamina)
        {
            stm = stamina;
        }
        void setSpeed(float speed)
        {
            spd = speed;
        }
        void setRadius(int radius)
        {
            rad = radius;
        }
        void setPosX(float posX)
        {
            x = posX;
        }
        void setPosY(float posY)
        {
            y = posY;
        }
        void setAlive(bool alive)
        {
            exist = alive;
        }
        int getHealth()
        {
            return hp;
        }
        float getStamina()
        {
            return stm;
        }
        float getSpeed()
        {
            return spd;
        }
        int getRadius()
        {
            return rad;
        }
        float getPosX()
        {
            return x;
        }
        float getPosY()
        {
            return y;
        }
        bool isAlive()
        {
            return exist;
        }

        Player(int health, float stamina, float posX, float posY, int radius, float speed, bool alive)
        {
            setHealth(health);
            setStamina(stamina);
            setPosX(posX);
            setPosY(posY);
            setRadius(radius);
            setSpeed(speed);
            setAlive(alive);
        }
};  

class Gun
{   
    private:
        float x, y;
        float xSpeed, ySpeed, xSize, ySize, ang , dmg;
        string gType;

    public:
        double time = 0, shotTime = 0, maxShotTime = 0, reloadTime = 0, maxReloadTime = 0;
        bool weaponUpgrade = false, rifleQuest = false;
        float bulletAmount = maxBulletAmount, maxBulletAmount;
        float reloadSpeedChange = 1, bulletAmountChange = 1, shotTimeChange = 1, perkReloadChange = 1, recoil = 0, weaponMass = 1;
        float soloDamage = 1, soloShotSpeed = 1, soloReloadSpeed = 1, soloBulletAmount = 1, soloWeaponMass = 1, soloWeaponRecoil = 1;
        
        void upDatePosition()
        {
            x += xSpeed;
            y += ySpeed;
        }
        void setDamage(float damage)
        {
            dmg = damage;
        }
        void setPosX(float posX)
        {
            x = posX;
        }
        void setPosY(float posY)
        {
            y = posY;
        }
        void setXSize(float hSize)
        {
            xSize = hSize;
        }
        void setYSize(float vSize)
        {
            ySize = vSize;
        }    
        void setAngle(float angle)
        {
            ang = angle;
        }
        void setSpeed(float speed, float vSpeed)
        {
            xSpeed = speed;
            this -> ySpeed = vSpeed;
        }
        void setGunType(string type)
        {
            gType = type;
        }
        float getAngle()
        {
            return ang;
        }
        float getPosX()
        {
            return x;
        }
        float getXSize()
        {
            return xSize;
        }
        float getYSize()
        {
            return ySize;
        }
        float getPosY()
        {
            return y;
        }    
        float getBulletSpeed()
        {
            return xSpeed;
        }
        float getDamage()
        {
            return dmg;
        }
        string getGunType()
        {
            return gType;
        }
        Gun(float posX = 0, float posY = 0, float xSpeed = 0, float ySpeed = 0, float xSize = 0, float ySize = 0, float ang = 0, float damage = 0, string type = " ")
        {
            setPosX(posX);
            setPosY(posY);
            setSpeed(xSpeed,ySpeed);
            setXSize(xSize);
            setYSize(ySize);
            setDamage(damage);
            setGunType(type);
            setAngle(ang);
            this -> time = GetTime();
        }
};