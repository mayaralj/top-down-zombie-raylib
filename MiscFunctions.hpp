#include "Zombies.hpp"

const int vertWallAmount = 24;
Rectangle vertMaze[vertWallAmount];

// stores the coordinates for all of the vertical walls
float vertWallArray [vertWallAmount][24] =  {{0.85, 8.47}, {0.85, 8}, {2.85, 8.47}, {2.85, 8}, {6.25, 4.45}, {6.25, 5.45}, {6.25, 6.45}, {6.25, 7.45}, {6.25, 8.40}, {11.30, 8.35}, {11.50, 8.35}, {11.70, 8.25}, {12.70, 6.25}, {12.50, 6.25}, {18.50, 5.20}, {18.50, 4.20}, {18.50, 3.20}, {18.50, 2.80}, {15.20, 2.80}, {15.20, 3.50}, {27.2, 4}, {27.2, 3}, {32, 2.1}, {32.1, 3.1}};

const int horzWallAmount = 34;
Rectangle horzMaze[horzWallAmount];

//stores the coordinates for horizontal walls
float horzWallArray [horzWallAmount][34] =  {{1, 8}, {1.8, 8}, {1, 9.47}, {1.8, 9.47}, {14, 4.45}, {13, 4.45}, {12, 4.45}, {11, 4.45}, {10, 4.45}, {9, 4.45}, {8, 4.45}, {7, 4.45}, {6.1, 4.45}, {6.25, 9.35}, {8.30, 9.35}, {9.30, 9.35}, {10.30, 9.35}, {12.70, 6.20}, {13.70, 6.20}, {14.70, 6.20}, {15.70, 6.20}, {16.70, 6.20}, {17.60, 6.20}, {17.50, 2.8}, {17.2, 2.8}, {15.20, 2.8}, {30, 4.8}, {28, 5}, {27.2, 5}, {28.5, 2.3}, {29.4, 2.2}, {30.2, 2.1}, {31, 2.1}, {31, 4.6}};

// takes the coordinats of the horizontal walls and translates it to the actual position of the wall
Rectangle horzBuildWall(float x, float y)
{
   return Rectangle{x * 50, (y * 50) - 5, 50, 10};
}

// draws two rectangle to represent health bar
void DrawHealthBar(int posX, int posY, int width, int height, int currentHealth, int maxHealth, Color barColor, Color backgroundColor)
{
    int barWidth;

    if(maxHealth != 0)
    {
        barWidth = (width * currentHealth) / maxHealth;
    }
    else
    {
        barWidth = 0;
    }

    DrawRectangle(posX, posY, width, height, backgroundColor);

    DrawRectangle(posX, posY, barWidth, height, barColor);
}

// sets the size for the horizontal walls
void horzBuildMaze(int size)
{
    for(int i = 0; i < size; i++)
    {
        horzMaze[i] = horzBuildWall(horzWallArray[i][0], horzWallArray[i][1]);
    }
}

// sets rectangle to grid position
Rectangle vertBuildWall(float x, float y)
{
    return Rectangle{(x * 50 - 5) ,( y * 50), 10, 50};
}

// sets size for vertical walls
void vertBuildMaze(int size)
{
    for(int i = 0; i < size; i++)
    {
        vertMaze[i] = vertBuildWall(vertWallArray[i][0], vertWallArray[i][1]);
    }
}

bool checkPlayerWallCollision(Player both)
{
    // checking collision for any player hitting any vertical wall
    for(int i = 0; i < vertWallAmount; i++)
    {
        if(CheckCollisionCircleRec(Vector2{both.getPosX(), both.getPosY()}, both.getRadius() - 1, vertMaze[i]))
        {
            return true;
        }
    }

    // checking collision for any player hitting any horizontal wall
    for(int i = 0; i < horzWallAmount; i++)
    {
        if(CheckCollisionCircleRec(Vector2{both.getPosX(), both.getPosY()}, both.getRadius() - 1, horzMaze[i]))
        {
            return true;
        }
    }

    return false;
}

// pushing back any player if they hit the wall
Player playerWallColl(Player both)
{
    // checks if either player hits wall
    bool bothWallColl = checkPlayerWallCollision(both);

    if(bothWallColl)
    {
        if(both.isFacingRight)
        {
            both.setPosX(both.getPosX() - both.getSpeed() * 2);
            bothWallColl = false;
        }
        else if(both.isFacingLeft)
        {
            both.setPosX(both.getPosX() + both.getSpeed() * 2);
            bothWallColl = false;
        }
        else if(both.isFacingUp)
        {
            both.setPosY(both.getPosY() + both.getSpeed() * 2);
            bothWallColl = false;
        }
        else if(both.isFacingDown)
        {
            both.setPosY(both.getPosY() - both.getSpeed() * 2);
            bothWallColl = false;
        }
        else if(both.isFacingLeftDown)
        {
            both.setPosX(both.getPosX() + (both.getSpeed()) * 2);
            both.setPosY(both.getPosY() - (both.getSpeed()) * 2);
            bothWallColl = false;
        }
        else if(both.isFacingLeftUp)
        {
            both.setPosX(both.getPosX() + (both.getSpeed()) * 2);
            both.setPosY(both.getPosY() + 1.0 * 2);
            bothWallColl = false;
        }
        else if(both.isFacingRightDown)
        {
            both.setPosX(both.getPosX() - (both.getSpeed()) * 2);
            both.setPosY(both.getPosY() - (both.getSpeed()) * 2);
            bothWallColl = false;
        }
        else if(both.isFacingRightUp)
        {
            both.setPosX(both.getPosX() - (both.getSpeed()) * 2);
            both.setPosY(both.getPosY() + (both.getSpeed()) * 2);
            bothWallColl = false;
        }
    }

    return both;
}

vector <Enemy> checkZomWall(vector <Enemy> zombies)
{
    // checks if any of the zombies have hit a verticle wall
    for(int i = 0; i < vertWallAmount; i++)
    {
        for(int j = 0; j < zombies.size(); j++)
        {
            if(CheckCollisionCircleRec(Vector2{zombies[j].getPosX(), zombies[j].getPosY()}, zombies[j].getRadius() - 1, vertMaze[i]))
            {
                zombies[j].setCollision(true);
                zombies[j].avoidingVert = true;
                zombies[j].avoidingHorz = false;
            }
        }
        
    }

    // checking collision for player one hitting any horizontal wall
    for(int i = 0; i < horzWallAmount; i++)
    {
        for(int j = 0; j < zombies.size(); j++)
        {
            if(CheckCollisionCircleRec(Vector2{zombies[j].getPosX(), zombies[j].getPosY()}, zombies[j].getRadius() - 1, horzMaze[i]))
            {
                zombies[j].setCollision(true);
                zombies[j].avoidingHorz = true;
                zombies[j].avoidingVert = false;
            }
        }
    }

    return zombies;
}

vector <Enemy> zombieWallColl(vector <Enemy> zombies, int dT)
{
    zombies = checkZomWall(zombies);

    for(int i = 0; i < zombies.size(); i++)
    {
        // sees if the zombie has been avoiding the wall for the alloted time
        if(GetTime() - zombies[i].wallMoveTime > 1 || zombies[i].getPosX() < 20 || zombies[i].getPosX() > 1680 || zombies[i].getPosY() < 20 || zombies[i].getPosY() > 930)
        {
            zombies[i].avoidingWall = false;
        }

        // makes the zombie move in a predetermined direction to avoid the wall
        else
        {
            zombies[i].avoidingWall = true;
            if(zombies[i].avoidingHorz)
            {
                avoidHorz(zombies[i], dT);
            }
            else if(zombies[i].avoidingVert)
            {
                avoidVert(zombies[i], dT);
            }
        }

        // if the zombie collides with the wall push them out
        if(zombies[i].getCollision() == true)
        { 
            if(zombies[i].isFacingRight)
            {
                zombies[i].setPosX(zombies[i].getPosX() - zombies[i].getSpeed() * 1.41);
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }
    
            if(zombies[i].isFacingLeft)
            {
                zombies[i].setPosX(zombies[i].getPosX() - zombies[i].getSpeed() * 1.41);
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }

            if(zombies[i].isFacingDown)
            {
                zombies[i].setPosY(zombies[i].getPosY() + zombies[i].getSpeed() * 1.41);
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }

            if(zombies[i].isFacingUp)
            {
                zombies[i].setPosY(zombies[i].getPosY() - zombies[i].getSpeed() * 1.41);
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }

            if(zombies[i].isFacingRightUp)
            {
                zombies[i].setPosX(zombies[i].getPosX() - zombies[i].getSpeed());
                zombies[i].setPosY(zombies[i].getPosY() - zombies[i].getSpeed());
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }

            if(zombies[i].isFacingRightDown)
            {
                zombies[i].setPosX(zombies[i].getPosX() - zombies[i].getSpeed());
                zombies[i].setPosY(zombies[i].getPosY() + zombies[i].getSpeed());
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }

            if(zombies[i].isFacingLeftUp)
            {
                zombies[i].setPosX(zombies[i].getPosX() + zombies[i].getSpeed());
                zombies[i].setPosY(zombies[i].getPosY() - zombies[i].getSpeed());
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }

            if(zombies[i].isFacingLeftDown)
            {
                zombies[i].setPosX(zombies[i].getPosX() + zombies[i].getSpeed());
                zombies[i].setPosY(zombies[i].getPosY() + zombies[i].getSpeed());
                zombies[i].wallMoveTime = GetTime();
                zombies[i].avoidingWall = true;
            }

            
        }
        
        zombies[i].setCollision(false);
    }

    return zombies;
}

void menuScreen(Window screen)
{
    Player menuPlayer(Player(20, 200, 200, 500, 20, 1.5, true));
    Player menuPlayerTwo(Player(20, 200, 9000, 9000, 20, 1.5, true));
    Gun menuBullet(Gun(menuPlayer.getPosX() + menuPlayer.getRadius() + 5, menuPlayer.getPosY() - 5, 4, 0, 15, 10, 0, 0, " "));
    vector <Enemy> menuZombies{};
    bool start = false, menu = false, menuBulletMoving = true, menuBulletColl = false, menuPlayerMove = false;
    
    // pushes back the menu zombies into the vector for the animation
    for(int i = 0; i < 5; i++)
    {
        menuZombies.push_back(Enemy(100, screen.getWidth() / 2, screen.getHeight() / 2, 17, .5, false, true));
    }

    while(WindowShouldClose() == false && !start)
    {
        // sets up the rectangle for the bullet zombie collision
        Rectangle bulletRectangle = {menuBullet.getPosX(), menuBullet.getPosY(), 15, 10};
        
        // starts the game
        if(IsKeyPressed(KEY_S))
        {
            start = true;
        }

        // chacks the collision between the zombie and the zombie
        for(int i = 0; i < 5; i++)
        {
            if(CheckCollisionCircleRec(Vector2{menuZombies[i].getPosX(), menuZombies[i].getPosY()}, menuZombies[i].getRadius() - 1, bulletRectangle))
            {
                menuBulletColl = true;
                menuPlayerMove = true;
            }
        }

        // chacks the position of the zombie then shoots id it is in the right position
        if(menuPlayer.getPosX() == 200 && menuPlayer.getPosY() == 500)
        {
            menuBulletMoving = true;
            menuPlayer.isFacingLeft = true;
        }
        
        menuPlayer = menuMovement(menuPlayer, menuPlayerMove);

        // updates the position of the bullet to make it move if activated
        if(menuBulletMoving)
        {
            menuBullet.upDatePosition();
        }
        else
        {
            menuBullet.setPosX(9000);
        }

        // allows the player to open and close the menu with M
        if(IsKeyPressed(KEY_M))
        {
            if(!menu)
            {
                menu = true;
            }
            else
            {
                menu = false;
            }
        }
        
        // puts the vector of menu zombies through the movement and zombie collision vector allowing them to move but stopping them from going through each other
        menuZombies = zomMovement(menuZombies, 5, menuPlayer, menuPlayerTwo);

        // collision for menu zombies
        menuZombies = zomColl(menuZombies, 5);

        BeginDrawing();
        ClearBackground(BLACK);

            // if user is on the start screen the menu animation will play and the start screen options will be displayed
            if(!menu)
            {
                DrawText("ATopDownZombieGame", 100, 30, 80, GREEN);
                DrawText("S - Start", 100, 100, 30, GREEN);
                DrawText("M - Menu", 300, 100, 30, GREEN);
                DrawCircle(menuPlayer.getPosX(), menuPlayer.getPosY(), menuPlayer.getRadius(), WHITE);

                for(int i = 0; i < 5; i++)
                {
                    DrawCircle(menuZombies[i].getPosX(), menuZombies[i].getPosY(), menuZombies[i].getRadius(), GREEN);
                }

                menuPlayer = drawPlayerGun(menuPlayer);

                if(menuBulletMoving && !menuBulletColl)
                {
                    DrawRectangle(menuBullet.getPosX(), menuBullet.getPosY(), 15, 10, BLUE);
                }
            }

            // if the user is in the menu the options will be displayed
            if(menu)
            {
                DrawText("PLAYER ONE", 100, 100, 30, GREEN);
                DrawText("W - up", 100, 150, 20, GREEN);
                DrawText("A - Left", 100, 170, 20, GREEN);
                DrawText("S - Down", 100, 190, 20, GREEN);
                DrawText("D - Right", 100, 210, 20, GREEN);
                DrawText("LShift - Sprint", 100, 230, 20, GREEN);
                DrawText("E - Shoot", 100, 250, 20, GREEN);
                DrawText("R - Reload", 100, 270, 20, GREEN);
                DrawText("Q - Buy", 100, 290, 20, GREEN);

                DrawText("PLAYER TWO", 100, 330, 30, GREEN);
                DrawText("RShift - Enable", 100, 380, 20, GREEN);
                DrawText("Arrow Up - up", 100, 400, 20, GREEN);
                DrawText("Arrow Left - Left", 100, 420, 20, GREEN);
                DrawText("Arrow Down - Down", 100, 440, 20, GREEN);
                DrawText("Arrow Right - Right", 100, 460, 20, GREEN);
                DrawText("Numpad Enter - Sprint", 100, 480, 20, GREEN);
                DrawText("Numpad Del - Shoot", 100, 500, 20, GREEN);
                DrawText("Numpad + - Buy", 100, 520, 20, GREEN);

                DrawText("Quest 1:", 700, 100, 30, YELLOW);
                DrawText("Requirements: Make It Past Two Bosses Without switching Weapons", 700, 150, 20, YELLOW);
                DrawText("Rewards: OP Rifle", 700, 180, 20, YELLOW);

                DrawText("Quest 2:", 700, 330, 30, YELLOW);
                DrawText("Requirements: Survive Past The Boss Without Taking Damage", 700, 380, 20, YELLOW);
                DrawText("Rewards: 1.5x Permanent Damage", 700, 410, 20, YELLOW);

            }

        EndDrawing();
    }
}