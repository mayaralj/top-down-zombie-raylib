#include "MiscFunctions.hpp"


int main()
{
    Window screen;
    Player playerOne(Player(100, 200, 450, 500, 20, 1, true));
    Player playerTwo(Player(100, 200, 9000, 9000, 20, 1, true));
    Gun playerOneGun(Gun(playerOneGun.getPosX(), playerOneGun.getPosY(), 4, 0, playerOneGun.getXSize(), playerOneGun.getYSize(), playerOneGun.getAngle(), 10, "Rifle"));
    Gun playerTwoGun(Gun(playerTwoGun.getPosX(), playerTwoGun.getPosY(), 4, 0, playerTwoGun.getXSize(), playerTwoGun.getYSize(), playerTwoGun.getAngle(), 10, "Rifle"));
    Enemy boss(Enemy(1000, 9000, 100, 100, 0, false, false));
    vector<Enemy> zombies = {}, bossBullets{};
    vector<Gun> playerOneBullets{}, playerTwoBullets{};
    int zomAmount = 5, spdZomAmount = 0, tnkZomAmount = 0, waveCount = 0, allZomAmount = 0;
    bool roundOver = true;

    // Set window screen and fps
    InitWindow(screen.getWidth(), screen.getHeight(), "ATopDownZombieGame");
    SetTargetFPS(60);
    srand(time(NULL));

    // sprites
    Texture2D map = LoadTexture ("map.png");
    Texture2D miniGun = LoadTexture ("MINIGUN.png");
    Texture2D shotGun = LoadTexture ("SHOTGUN.png");
    Texture2D sniper = LoadTexture ("SNIPER.png");
    Texture2D ar = LoadTexture ("AR.png");
    Texture2D rifle = LoadTexture ("RIFLE.png");
    Texture2D bulletOne = LoadTexture ("BULLET.png");

    playerOneGun.bulletAmount = 10;
    playerTwoGun.bulletAmount = 10;

    // pushes back the wave 20 boss into the zombie vector
    zombies.push_back(boss);

    vertBuildMaze(vertWallAmount);
    horzBuildMaze(horzWallAmount);

    menuScreen(screen);
    
    while (WindowShouldClose() == false)
    {
        DrawTexture(map, 0, 0, WHITE);

        int variance = (rand() % 50) - 25;
        int splashRadius = 40 + variance;

        const float dT = GetFrameTime();

        windowBoundry(playerOne, playerTwo);

        // counts the amount of dead zombies
        for(int i = 0; i < allZomAmount; i++)
        {
            if(!zombies[i].isAlive())
            {
                zombies.erase(zombies.begin() + i);
                allZomAmount = zombies.size();
            }
        }

        if(allZomAmount == 0 && waveCount % 10 != 0)
        {
            roundOver = true;
        }

        // ifuser is in the boss battle and the boss is killed then the round is over
        if(waveCount % 10 == 0 && !zombies[zombies.size() - 1].isAlive())
        {
            roundOver = true;
        }

        roundEnd(screen, zombies, boss, bossBullets, roundOver, zombies.size() - 1, waveCount, zomAmount, spdZomAmount, tnkZomAmount, allZomAmount, playerOne, playerTwo);
        
        // ifa boss wave is active then activate boss bullets
        if(waveCount % 10 == 0)
        {
            bossBulletHandiling(playerOne, playerTwo, zombies, bossBullets, screen);
        }

        // Collision check between the 2 players
        playersCollide(playerOne, playerTwo);

        checkPlayerAlive(playerOne, playerOneGun);
        checkPlayerAlive(playerTwo, playerTwoGun);

        playersRunning(playerOne,dT, true, false);
        playersRunning(playerTwo,dT, false, true);

        zombieAttack(playerOne, zombies, waveCount);
        zombieAttack(playerTwo, zombies, waveCount);

        shotgunDamage(playerOneBullets, playerOneGun);
        shotgunDamage(playerTwoBullets, playerTwoGun);

        gunUpgrade(playerOneGun);
        gunUpgrade(playerTwoGun);

        twoPlayer(playerTwo);

        shotCooldown(playerOneGun, dT);
        shotCooldown(playerTwoGun, dT);

        stamRegen(playerOne);
        stamRegen(playerTwo);

        recoil(playerOneGun, playerOne);
        recoil(playerTwoGun, playerTwo);

        healthRegen(playerOne);
        healthRegen(playerTwo);

        reloadTime(playerOneGun, playerOne);
        reloadTime(playerTwoGun , playerTwo);

        playerzomColl(playerOne, zombies);
        playerzomColl(playerTwo, zombies);

        zombies = zomColl(zombies, zombies.size());

        playersMovement(playerOne, playerOneGun, dT, true, false);
        playersMovement(playerTwo, playerTwoGun, dT, false, true);

        weaponMass(playerOneGun, playerOne);
        weaponMass(playerTwoGun, playerTwo);

        weaponStats(playerOneGun, playerOne, waveCount);
        weaponStats(playerTwoGun, playerTwo, waveCount);

        soloQuest(playerOne, playerTwo, playerOneGun, playerTwoGun, waveCount);
        duoQuest(playerOne, playerTwo, waveCount);

        perks(playerOne, playerOneGun, playerTwo, playerTwoGun, playerTwo.twoPlayerMode);

        if(IsKeyPressed(KEY_B))    
        {
            playerOneGun.weaponUpgrade = true;
            playerTwoGun.weaponUpgrade = true;
        }

        zombies = zomMovement(zombies, zombies.size(), playerOne, playerTwo);
        zombies = zombieWallColl(zombies, dT);
      
        if(playerOne.isAlive())
        {
            playersShooting(playerOneBullets, playerOneGun, playerOne, true, false);
            // Reloading
            playersReloading(playerOne, playerOneGun, true, false);
        }
        //PlayerTwo
        if(playerTwo.isAlive())
        {
            playersShooting(playerTwoBullets, playerTwoGun, playerTwo, false, true);
            playersReloading(playerTwo,playerTwoGun, false, true);
        }

        playerOne = playerWallColl(playerOne);
        playerTwo = playerWallColl(playerTwo);

        playerOneBullets = deleteBullets(playerOneBullets, screen);
        playerTwoBullets = deleteBullets(playerTwoBullets, screen);

        BeginDrawing();
            ClearBackground(BLACK);

            if(waveCount % 10 == 0)
            {
                DrawHealthBar(screen.getWidth() / 2 - 275, 45, 500, 20, zombies[zombies.size() - 1].getHealth(), 3000 * (waveCount / 10), RED, MAROON);
            }

            for(int i = 0; i < bossBullets.size(); i++)
            {
                DrawCircle(bossBullets[i].getPosX(), bossBullets[i].getPosY(), bossBullets[i].getRadius(), MAROON);
            }

            for (int i = 0; i < zombies.size(); i++)    
            {
                if(zombies[i].isAlive())
                {
                    DrawCircle(zombies[i].getPosX(), zombies[i].getPosY(), zombies[i].getRadius(), GREEN);
                }
                else
                {
                    zombies[i].setPosX(9000);
                }
            }

            //Placing Perks around the map
            DrawRectanglePro(Rectangle{1210, 730, 10, 30}, Vector2{10 / 2, 30 / 2}, 310, RED);
            DrawRectanglePro(Rectangle{1355, 230, 10, 30}, Vector2{10 / 2, 30 / 2}, 350, DARKGREEN);
            DrawRectanglePro(Rectangle{450, 230, 10, 30}, Vector2{10 / 2, 30 / 2}, 90, WHITE);
            DrawRectanglePro(Rectangle{850, 320, 10, 30}, Vector2{10 / 2, 30 / 2}, 90, SKYBLUE);

            //Placing weapons around the map
            DrawTextureEx(ar,(Vector2) {740, 225}, 90, 0.5, WHITE);
            DrawTextureEx(shotGun,(Vector2) {1530, 115}, 85, 0.5, WHITE);
            DrawTextureEx(sniper,(Vector2) {1310, 650}, 130, 0.5, WHITE);
            DrawTextureEx(miniGun,(Vector2) {130, 480}, 88, 0.5, WHITE);

            perkInput(playerOne, true, false);
            perkInput(playerTwo, false, true);

            weaponInput(playerOne, playerOneGun, true, false);
            weaponInput(playerTwo, playerTwoGun, false, true);

            upgradeInput(playerOne,playerTwo,playerOne,playerOneGun, true, false);
            upgradeInput(playerOne,playerTwo,playerTwo,playerTwoGun, false, true);

            Color mergeColor = {255,220,220,255};

            // Draw players, health bar, stamina bar and reload
            DrawCircle(playerOne.getPosX(), playerOne.getPosY(), playerOne.getRadius() + 3, BLUE);
            DrawCircle(playerOne.getPosX(), playerOne.getPosY(), playerOne.getRadius(), WHITE);

            DrawText(("MONEY: " + to_string(playerOne.money)).c_str(), 10, 10, 20, WHITE);
            DrawText(("KILLS: " + to_string(playerOne.zomKills)).c_str(), 10, 35, 20, WHITE);
            DrawText(("ROUND: " + to_string(waveCount)).c_str(), screen.getWidth() / 2 - 100, 10, 30, WHITE);

            if(playerOneGun.weaponUpgrade)
            {
                DrawText(("Gun: " + (playerOneGun.getGunType())).c_str(), 510, 10, 17, RED);
            }
            else
            {
                DrawText(("Gun: " + (playerOneGun.getGunType())).c_str(), 510, 10, 17, WHITE);
            }

            DrawHealthBar(playerOne.getPosX() - playerOne.getRadius(), playerOne.getPosY() + playerOne.getRadius() + 23, 40, 8, playerOne.getHealth(), 100 + playerOne.hpChange, GREEN, DARKGREEN);
            DrawHealthBar(playerOne.getPosX() - playerOne.getRadius(), playerOne.getPosY() + playerOne.getRadius() + 32, 18, 8, playerOne.getStamina(), 200, BLUE, DARKBLUE);
            DrawHealthBar(playerOne.getPosX() - playerOne.getRadius() + 22, playerOne.getPosY() + playerOne.getRadius() + 32, 18, 8, playerOneGun.bulletAmount, playerOneGun.maxBulletAmount, WHITE, GRAY);


            //Player two
            if(playerTwo.twoPlayerMode)
            {
                DrawCircle(playerTwo.getPosX(), playerTwo.getPosY(), playerTwo.getRadius() + 3, RED);
                DrawCircle(playerTwo.getPosX(), playerTwo.getPosY(), playerTwo.getRadius(), GRAY);
            }

            DrawText(("KILLS: " + to_string(playerTwo.zomKills)).c_str(), 1550, 35, 20, WHITE);
            DrawText(("MONEY: " + to_string(playerTwo.money)).c_str(), 1550, 10, 20, WHITE);

            if(playerTwoGun.weaponUpgrade) 
            {
                DrawText(("Gun: " + (playerTwoGun.getGunType())).c_str(), 1050, 10, 17, RED);
            }
            else
            {
                DrawText(("Gun: " + (playerTwoGun.getGunType())).c_str(), 1050, 10, 17, WHITE);
            }

            DrawHealthBar(playerTwo.getPosX() - playerTwo.getRadius(), playerTwo.getPosY() + playerTwo.getRadius() + 23, 40, 8, playerTwo.getHealth(), 100 + playerTwo.hpChange, GREEN, DARKGREEN);
            DrawHealthBar(playerTwo.getPosX() - playerTwo.getRadius(), playerTwo.getPosY() + playerTwo.getRadius() + 32, 18, 8, playerTwo.getStamina(), 200, BLUE, DARKBLUE);
            DrawHealthBar(playerTwo.getPosX() - playerTwo.getRadius() + 22, playerTwo.getPosY() + playerTwo.getRadius() + 32, 18, 8, playerTwoGun.bulletAmount, playerTwoGun.maxBulletAmount, WHITE, GRAY);
        

            // Drawing the Bullets
            for (int i = 0; i < playerOneBullets.size(); i++)
            {
                playerOneBullets[i].upDatePosition();

                DrawTextureEx(bulletOne, (Vector2) {playerOneBullets[i].getPosX(), playerOneBullets[i].getPosY()}, playerOneBullets[i].getAngle(), 1, WHITE);

                for (float j = 0; j < zombies.size(); j++)
                {
                    if(CheckCollisionCircles({zombies[j].getPosX(), zombies[j].getPosY()}, zombies[j].getRadius(), {playerOneBullets[i].getPosX(), playerOneBullets[i].getPosY()}, 3))
                    {
                        //Aoe dmg
                        if(playerOneGun.weaponUpgrade)
                        {
                            DrawCircle(zombies[j].getPosX(), zombies[j].getPosY(), splashRadius, MAROON);
                            for(int k = 0; k < zombies.size(); k++)
                            {
                                if(CheckCollisionCircles({zombies[j].getPosX(), zombies[j].getPosY()}, splashRadius, {zombies[k].getPosX(), zombies[k].getPosY()}, zombies[k].getRadius()))
                                {
                                    zombies[j].setHealth(zombies[j].getHealth() - playerOneBullets[i].getDamage() / 3);
                                    playerOne.money += playerOneBullets[i].getDamage() / 3;
                                }
                            }
                        }

                        //Cooldown to prevent rapid shot weapons from rapidly slowing down
                        if(playerOne.slowPerk && GetTime() - zombies[j].slowTimeCooldown >= 2.5)
                        {
                            zombies[j].slowTime = GetTime();
                            zombies[j].setSpeed(zombies[j].getSpeed() / 2);
                            zombies[j].slowTimeCooldown = GetTime();
                        }

                        zombies[j].setHealth(zombies[j].getHealth() - playerOneBullets[i].getDamage());
                        
                        if(waveCount <= 5)
                        {
                            playerOne.money += playerOneBullets[i].getDamage() * 2;
                        }
                        else if(waveCount <= 10)
                        {
                            playerOne.money += playerOneBullets[i].getDamage() * 1.5;
                        }
                        else if(waveCount <= 15)
                        {
                            playerOne.money += playerOneBullets[i].getDamage() * 1.2;
                        }
                        else if(waveCount <= 20)
                        {
                            playerOne.money += playerOneBullets[i].getDamage() * 1.1;
                        }
                        else
                        {
                            playerOne.money += playerOneBullets[i].getDamage() * 0.5;
                        }

                        if(zombies[j].getHealth() <= 0 && zombies[j].isAlive())
                        {
                            playerOne.zomKills += 1;
                            playerOne.money += 10;
                            zombies[j].setAlive(false);
                        }

                        if(playerOneGun.getGunType() != "Sniper")
                        {
                            playerOneBullets[i].setPosX(9000);
                        }
                    }

                    if((playerOneBullets[i].getPosX() > screen.getWidth() || playerOneBullets[i].getPosY() > screen.getHeight()) || (playerOneBullets[i].getPosX() < 0 || playerOneBullets[i].getPosY() < 0))
                    {
                        playerOneBullets[i].setPosX(9000);                   
                    }

                    if(playerOneGun.getGunType() != "Sniper")
                    {
                        for (int k = 0; k < vertWallAmount; k++)
                        {
                            if(CheckCollisionCircleRec({playerOneBullets[i].getPosX(), playerOneBullets[i].getPosY()}, 4, vertMaze[k]))
                            {
                                playerOneBullets[i].setPosX(9000);
                            }
                        }

                        for (int k = 0; k < horzWallAmount; k++)
                        {
                            if(CheckCollisionCircleRec({playerOneBullets[i].getPosX(), playerOneBullets[i].getPosY()}, 4, horzMaze[k]))
                            {
                                playerOneBullets[i].setPosX(9000);                            
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < zombies.size(); i++)
            {
                //Checks to see iftime passed to return the speed to the original
                if(playerOne.slowPerk && GetTime() - zombies[i].slowTime >= 2)
                {
                    zombies[i].setSpeed(zombies[i].originalSpeed);
                }
            }

            //Player two
            for (int i = 0; i < playerTwoBullets.size(); i++)
            {
                playerTwoBullets[i].upDatePosition();

                DrawTextureEx(bulletOne, (Vector2) {playerTwoBullets[i].getPosX(), playerTwoBullets[i].getPosY()}, playerTwoBullets[i].getAngle(), 1, WHITE);

                for (float j = 0; j < zombies.size(); j++)
                {
                    if(CheckCollisionCircles({zombies[j].getPosX(), zombies[j].getPosY()}, zombies[j].getRadius(), {playerTwoBullets[i].getPosX(), playerTwoBullets[i].getPosY()}, 3))
                    {
                        //Aoe dmg
                        if(playerTwoGun.weaponUpgrade)
                        {
                            DrawCircle(zombies[j].getPosX(), zombies[j].getPosY(), splashRadius, MAROON);
                            for(int k = 0; k < zombies.size(); k++)
                            {
                                if(CheckCollisionCircles({zombies[j].getPosX(), zombies[j].getPosY()}, splashRadius, {zombies[k].getPosX(), zombies[k].getPosY()}, zombies[k].getRadius()))
                                {
                                    zombies[j].setHealth(zombies[j].getHealth() - playerTwoBullets[i].getDamage() / 3);
                                    playerTwo.money += playerTwoBullets[i].getDamage() / 3;
                                }
                            }
                        }

                        //Cooldown to prevent rapid shot weapons from rapidly slowing down
                        if(playerTwo.slowPerk && GetTime() - zombies[j].slowTimeCooldown >= 2.5)
                        {
                            zombies[j].slowTime = GetTime();
                            zombies[j].setSpeed(zombies[j].getSpeed() / 2);
                            zombies[j].slowTimeCooldown = GetTime();
                        }

                        zombies[j].setHealth(zombies[j].getHealth() - playerTwoBullets[i].getDamage());

                        if(waveCount <= 5)
                        {
                            playerTwo.money += playerTwoBullets[i].getDamage() * 2;
                        }
                        else if(waveCount <= 10)
                        {
                            playerTwo.money += playerTwoBullets[i].getDamage() * 1.5;
                        }
                        else if(waveCount <= 15)
                        {
                            playerTwo.money += playerTwoBullets[i].getDamage() * 1.1;
                        }
                        else if(waveCount <= 20)
                        {
                            playerTwo.money += playerTwoBullets[i].getDamage() * 1;
                        }
                        else
                        {
                            playerTwo.money += playerTwoBullets[i].getDamage() * 0.5;
                        }

                        if(zombies[j].getHealth() <= 0 && zombies[j].isAlive())
                        {
                            playerTwo.zomKills += 1;
                            playerTwo.money += 10;
                            zombies[j].setAlive(false);
                        }

                        if(playerTwoGun.getGunType() != "Sniper")
                        {
                            playerTwoBullets[i].setPosX(9000);
                        }
                    }

                    if((playerTwoBullets[i].getPosX() > screen.getWidth() || playerTwoBullets[i].getPosY() > screen.getHeight()) || (playerTwoBullets[i].getPosX() < 0 || playerTwoBullets[i].getPosY() < 0))
                    {
                        playerTwoBullets[i].setPosX(9000);                   
                    }

                    if(playerTwoGun.getGunType() != "Sniper")
                    {
                        for (int k = 0; k < vertWallAmount; k++)
                        {
                            if(CheckCollisionCircleRec({playerTwoBullets[i].getPosX(), playerTwoBullets[i].getPosY()}, 4, vertMaze[k]))
                            {
                                playerTwoBullets[i].setPosX(9000);
                            }
                        }

                        for (int k = 0; k < horzWallAmount; k++)
                        {
                            if(CheckCollisionCircleRec({playerTwoBullets[i].getPosX(), playerTwoBullets[i].getPosY()}, 4, horzMaze[k]))
                            {
                                playerTwoBullets[i].setPosX(9000);                            
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < zombies.size(); i++)
            {
                //Checks to see iftime passed to return the speed to the original
                if(playerTwo.slowPerk && GetTime() - zombies[i].slowTime >= 2)
                {
                    zombies[i].setSpeed(zombies[i].originalSpeed);
                }
            }

            if(playerOne.isFacingLeft)
            {            
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) {playerOne.getPosX() + playerOne.getRadius() + 50, playerOne.getPosY() - 5}, 90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) {playerOne.getPosX() + playerOne.getRadius() + 50, playerOne.getPosY() - 5}, 90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) {playerOne.getPosX() + playerOne.getRadius() + 50, playerOne.getPosY() - 5}, 90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) {playerOne.getPosX() + playerOne.getRadius() + 50, playerOne.getPosY() - 5}, 90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) {playerOne.getPosX() + playerOne.getRadius() + 50, playerOne.getPosY() - 5}, 90, 0.5, WHITE);
                }

                playerOne.shotRight = true;
                playerOne.shotLeft = false, playerOne.shotUp = false, playerOne.shotDown = false;
                playerOne.shotLeftUp = false, playerOne.shotLeftDown = false, playerOne.shotRightUp = false, playerOne.shotRightDown = false;
            }

            if(playerOne.isFacingRight)
            {
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 50, playerOne.getPosY() + 5}, -90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 50, playerOne.getPosY() + 5}, -90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 50, playerOne.getPosY() + 5}, -90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 50, playerOne.getPosY() + 5}, -90, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 50, playerOne.getPosY() + 5}, -90, 0.5, WHITE);
                }

                playerOne.shotLeft = true;
                playerOne.shotRight = false, playerOne.shotUp = false, playerOne.shotDown = false;
                playerOne.shotLeftUp = false, playerOne.shotLeftDown = false, playerOne.shotRightUp = false, playerOne.shotRightDown = false;
            }

            if(playerOne.isFacingDown)
            {
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 15, playerOne.getPosY() - 65}, +360, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 15, playerOne.getPosY() - 65}, +360, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 15, playerOne.getPosY() - 65}, +360, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 15, playerOne.getPosY() - 65}, +360, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 15, playerOne.getPosY() - 65}, +360, 0.5, WHITE);
                }

                playerOne.shotUp = true;
                playerOne.shotLeft = false, playerOne.shotRight = false, playerOne.shotDown = false;
                playerOne.shotLeftUp = false, playerOne.shotLeftDown = false, playerOne.shotRightUp = false, playerOne.shotRightDown = false;
            }

            if(playerOne.isFacingUp)
            {
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 25, playerOne.getPosY() + 65}, -180, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 25, playerOne.getPosY() + 65}, -180, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 25, playerOne.getPosY() + 65}, -180, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 25, playerOne.getPosY() + 65}, -180, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 25, playerOne.getPosY() + 65}, -180, 0.5, WHITE);
                }

                playerOne.shotDown = true;
                playerOne.shotLeft = false, playerOne.shotRight = false, playerOne.shotUp = false;
                playerOne.shotLeftUp = false, playerOne.shotLeftDown = false, playerOne.shotRightUp = false, playerOne.shotRightDown = false;
            }

            //Dimension 4-8 to give it a rotation feeling
            if(playerOne.isFacingLeftDown)
            {
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 55, playerOne.getPosY() - 50}, + 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 55, playerOne.getPosY() - 50}, + 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 55, playerOne.getPosY() - 50}, + 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 55, playerOne.getPosY() - 50}, + 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 55, playerOne.getPosY() - 50}, + 45, 0.5, WHITE);
                }

                playerOne.shotRightUp = true;
                playerOne.shotLeft = false, playerOne.shotRight = false, playerOne.shotUp = false, playerOne.shotDown = false;
                playerOne.shotLeftUp = false, playerOne.shotLeftDown = false, playerOne.shotRightDown = false;
            }

            if(playerOne.isFacingLeftUp)
            {
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 75, playerOne.getPosY() + 50}, + 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 75, playerOne.getPosY() + 50}, + 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 75, playerOne.getPosY() + 50}, + 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 75, playerOne.getPosY() + 50}, + 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) {playerOne.getPosX() - playerOne.getRadius() + 75, playerOne.getPosY() + 50}, + 135, 0.5, WHITE);
                }

                playerOne.shotRightDown = true;
                playerOne.shotLeft = false, playerOne.shotRight = false, playerOne.shotUp = false, playerOne.shotDown = false;
                playerOne.shotLeftUp = false, playerOne.shotLeftDown = false, playerOne.shotRightUp = false;
            }

            if(playerOne.isFacingRightDown)
            {
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 30, playerOne.getPosY() - 40}, - 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 30, playerOne.getPosY() - 40}, - 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 30, playerOne.getPosY() - 40}, - 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 30, playerOne.getPosY() - 40}, - 45, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) {playerOne.getPosX() - playerOne.getRadius() - 30, playerOne.getPosY() - 40}, - 45, 0.5, WHITE);
                }

                playerOne.shotLeftUp = true;
                playerOne.shotLeft = false, playerOne.shotRight = false, playerOne.shotUp = false, playerOne.shotDown = false;
                playerOne.shotRightUp = false, playerOne.shotLeftDown = false, playerOne.shotRightDown = false;
            }

            if(playerOne.isFacingRightUp)
            {
                if(playerOneGun.getGunType() == "Sniper")
                {
                    DrawTextureEx(sniper,(Vector2) { playerOne.getPosX() - playerOne.getRadius() - 23, playerOne.getPosY() + 52}, - 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Shotgun")
                {
                    DrawTextureEx(shotGun,(Vector2) { playerOne.getPosX() - playerOne.getRadius() - 23, playerOne.getPosY() + 52}, - 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Minigun")
                {
                    DrawTextureEx(miniGun,(Vector2) { playerOne.getPosX() - playerOne.getRadius() - 23, playerOne.getPosY() + 52}, - 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "Rifle")
                {
                    DrawTextureEx(rifle,(Vector2) { playerOne.getPosX() - playerOne.getRadius() - 23, playerOne.getPosY() + 52}, - 135, 0.5, WHITE);
                }
                else if(playerOneGun.getGunType() == "AR")
                {
                    DrawTextureEx(ar,(Vector2) { playerOne.getPosX() - playerOne.getRadius() - 23, playerOne.getPosY() + 52}, - 135, 0.5, WHITE);
                }

                playerOne.shotLeftDown = true;
                playerOne.shotLeft = false, playerOne.shotRight = false, playerOne.shotUp = false, playerOne.shotDown = false;
                playerOne.shotLeftUp = false, playerOne.shotRightUp = false, playerOne.shotRightDown = false;
            }

            //Player Two
            if(playerTwo.twoPlayerMode == true)
            {
                if(playerTwo.isFacingLeft)
                {
                
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) {playerTwo.getPosX() + playerTwo.getRadius() + 50, playerTwo.getPosY() - 5}, 90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) {playerTwo.getPosX() + playerTwo.getRadius() + 50, playerTwo.getPosY() - 5}, 90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) {playerTwo.getPosX() + playerTwo.getRadius() + 50, playerTwo.getPosY() - 5}, 90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) {playerTwo.getPosX() + playerTwo.getRadius() + 50, playerTwo.getPosY() - 5}, 90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) {playerTwo.getPosX() + playerTwo.getRadius() + 50, playerTwo.getPosY() - 5}, 90, 0.5, WHITE);
                    }

                    playerTwo.shotRight = true;
                    playerTwo.shotLeft = false, playerTwo.shotUp = false, playerTwo.shotDown = false;
                    playerTwo.shotLeftUp = false, playerTwo.shotLeftDown = false, playerTwo.shotRightUp = false, playerTwo.shotRightDown = false;
                }

                if(playerTwo.isFacingRight)
                {
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 50, playerTwo.getPosY() + 5}, -90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 50, playerTwo.getPosY() + 5}, -90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 50, playerTwo.getPosY() + 5}, -90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 50, playerTwo.getPosY() + 5}, -90, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 50, playerTwo.getPosY() + 5}, -90, 0.5, WHITE);
                    }

                    playerTwo.shotLeft = true;
                    playerTwo.shotRight = false, playerTwo.shotUp = false, playerTwo.shotDown = false;
                    playerTwo.shotLeftUp = false, playerTwo.shotLeftDown = false, playerTwo.shotRightUp = false, playerTwo.shotRightDown = false;
                }

                if(playerTwo.isFacingDown)
                {
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 15, playerTwo.getPosY() - 65}, +360, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 15, playerTwo.getPosY() - 65}, +360, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 15, playerTwo.getPosY() - 65}, +360, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 15, playerTwo.getPosY() - 65}, +360, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 15, playerTwo.getPosY() - 65}, +360, 0.5, WHITE);
                    }

                    playerTwo.shotUp = true;
                    playerTwo.shotLeft = false, playerTwo.shotRight = false, playerTwo.shotDown = false;
                    playerTwo.shotLeftUp = false, playerTwo.shotLeftDown = false, playerTwo.shotRightUp = false, playerTwo.shotRightDown = false;
                }

                if(playerTwo.isFacingUp)
                {
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 25, playerTwo.getPosY() + 65}, -180, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 25, playerTwo.getPosY() + 65}, -180, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 25, playerTwo.getPosY() + 65}, -180, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 25, playerTwo.getPosY() + 65}, -180, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 25, playerTwo.getPosY() + 65}, -180, 0.5, WHITE);
                    }

                    playerTwo.shotDown = true;
                    playerTwo.shotLeft = false, playerTwo.shotRight = false, playerTwo.shotUp = false;
                    playerTwo.shotLeftUp = false, playerTwo.shotLeftDown = false, playerTwo.shotRightUp = false, playerTwo.shotRightDown = false;
                }

                //Dimension 4-8 to give it a rotation feeling
                if(playerTwo.isFacingLeftDown)
                {
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 55, playerTwo.getPosY() - 50}, + 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 55, playerTwo.getPosY() - 50}, + 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 55, playerTwo.getPosY() - 50}, + 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 55, playerTwo.getPosY() - 50}, + 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 55, playerTwo.getPosY() - 50}, + 45, 0.5, WHITE);
                    }

                    playerTwo.shotRightUp = true;
                    playerTwo.shotLeft = false, playerTwo.shotRight = false, playerTwo.shotUp = false, playerTwo.shotDown = false;
                    playerTwo.shotLeftUp = false, playerTwo.shotLeftDown = false, playerTwo.shotRightDown = false;
                }

                if(playerTwo.isFacingLeftUp)
                {
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 75, playerTwo.getPosY() + 50}, + 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 75, playerTwo.getPosY() + 50}, + 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 75, playerTwo.getPosY() + 50}, + 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 75, playerTwo.getPosY() + 50}, + 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() + 75, playerTwo.getPosY() + 50}, + 135, 0.5, WHITE);
                    }

                    playerTwo.shotRightDown = true;
                    playerTwo.shotLeft = false, playerTwo.shotRight = false, playerTwo.shotUp = false, playerTwo.shotDown = false;
                    playerTwo.shotLeftUp = false, playerTwo.shotLeftDown = false, playerTwo.shotRightUp = false;
                }

                if(playerTwo.isFacingRightDown)
                {
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 30, playerTwo.getPosY() - 40}, - 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 30, playerTwo.getPosY() - 40}, - 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 30, playerTwo.getPosY() - 40}, - 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 30, playerTwo.getPosY() - 40}, - 45, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) {playerTwo.getPosX() - playerTwo.getRadius() - 30, playerTwo.getPosY() - 40}, - 45, 0.5, WHITE);
                    }

                    playerTwo.shotLeftUp = true;
                    playerTwo.shotLeft = false, playerTwo.shotRight = false, playerTwo.shotUp = false, playerTwo.shotDown = false;
                    playerTwo.shotRightUp = false, playerTwo.shotLeftDown = false, playerTwo.shotRightDown = false;
                }

                if(playerTwo.isFacingRightUp)
                {
                    if(playerTwoGun.getGunType() == "Sniper")
                    {
                        DrawTextureEx(sniper,(Vector2) { playerTwo.getPosX() - playerTwo.getRadius() - 23, playerTwo.getPosY() + 52}, - 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Shotgun")
                    {
                        DrawTextureEx(shotGun,(Vector2) { playerTwo.getPosX() - playerTwo.getRadius() - 23, playerTwo.getPosY() + 52}, - 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Minigun")
                    {
                        DrawTextureEx(miniGun,(Vector2) { playerTwo.getPosX() - playerTwo.getRadius() - 23, playerTwo.getPosY() + 52}, - 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "Rifle")
                    {
                        DrawTextureEx(rifle,(Vector2) { playerTwo.getPosX() - playerTwo.getRadius() - 23, playerTwo.getPosY() + 52}, - 135, 0.5, WHITE);
                    }
                    else if(playerTwoGun.getGunType() == "AR")
                    {
                        DrawTextureEx(ar,(Vector2) { playerTwo.getPosX() - playerTwo.getRadius() - 23, playerTwo.getPosY() + 52}, - 135, 0.5, WHITE);
                    }
                    playerTwo.shotLeftDown = true;
                    playerTwo.shotLeft = false, playerTwo.shotRight = false, playerTwo.shotUp = false, playerTwo.shotDown = false;
                    playerTwo.shotLeftUp = false, playerTwo.shotRightUp = false, playerTwo.shotRightDown = false;
                }
            }


            if(!playerOne.isAlive() && (!playerTwo.isAlive() || !playerTwo.twoPlayerMode))
            {
                DrawText("GAME OVER", screen.getWidth() / 2 - 450, screen.getHeight() / 2 - 100, 150, RED);
            }

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(miniGun);
    UnloadTexture(shotGun);
    UnloadTexture(sniper);
    UnloadTexture(rifle);
    UnloadTexture(bulletOne);
    UnloadTexture(ar);
    CloseWindow();
}

//Update log

// -Made Running faster and slightly decreased walking speed
// -Slightly Made zombies slower to prevent rapid attacks
// -Made pistol damage increase as wave increases to make completing quest easier
// -Rebalanced money gain to make it fair
// -Fixed Bullet deletion and made it only delete when its outside the barriers and doesnt count to 99 and doesnt clear
// -Made it so zombies wait 3 seconds before attacking when they spawn to prevent them from instantly killing u if you are in their spawn
// -AR price 7000 -> 5000
// -Improved Bullet hit detection so it doesnt sometimes phase through the sides of a zombie or a wall
// -Fixed playerTwo spawning as an invisible circle at waves 6 and above for no reason and when the game isnt even in 2 player mode to begin with
// -Fixed Not correctly displaying gun type
// -Fixed Rifle quest automatically activating when wave 21 is hit even though both players dont have rifle
// -Buffed the Main boss Health
// -Fixed only needing 250 kills to unlock the weapon upgrade option (250 -> 500)
// -Fixed Diagonal Movement being too slow
// -Fixed health perk option not dissapearing when you unlock it
// -Buffed Minigun's damage and lowered its weight
// -Nerfed OP rifle
// -Tank and regular zombies have more hp now and move slightly faster
// -Fixed zombies getting stuck when avoiding walls
// -Made less zombies spawn on early on but the cap is now greater so more zombies can spawn by high waves
// -speed and tank zombies do not spawn till after boss wave
// -Fixed money not being rewarded correctly


//Issues:

