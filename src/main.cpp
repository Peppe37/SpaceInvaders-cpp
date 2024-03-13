#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

const std::string CSV_PATH = "./assets/settings.csv";
const std::string FONT_PATH = "./assets/fonts/Retrograde-Font/Retrograde-Regular.otf";

// sprites
const std::string PLAYER_SPRITE_PATH = "./assets/sprites/player.png";
const std::string ENEMY_SPRITE_PATH = "./assets/sprites/enemy.png";
const std::string BULLET_SPRITE_PATH = "./assets/sprites/bullet.png";
const std::string EXPLOSION_SPRITE_PATH = "./assets/sprites/explosion.png";
const std::string POWER_UP_SPRITE_PATH = "./assets/sprites/power_up.png";
const std::string HEART_SPRITE_PATH = "./assets/sprites/heart.png";
const std::string BASE_SHIELD_SPRITE_PATH = "./assets/sprites/base_shield.png";
const std::string FULL_SHIELD_SPRITE_PATH = "./assets/sprites/full_shield.png";
const std::string INDICATOR_SHIELD_SPRITE_PATH = "./assets/sprites/indicator_shield.png";
const std::string PLANET_SPRITE_PATH = "./assets/sprites/planet.png";

// sounds
const std::string MENU_CLICK_SOUND_PATH = "./assets/sounds/menu.wav";
const std::string BULLET_SOUND_PATH = "./assets/sounds/bullet.wav";
const std::string EXPLOSION_SOUND_PATH = "./assets/sounds/explosion.wav";
const std::string SHIELD_SOUND_PATH = "./assets/sounds/shield.wav";

const int MAX_DIFFICULTY = 10;
const int MAX_LIFES = 5;
const int MAX_SHIELDS = 3;
const std::vector<std::pair<int, std::string>> colorThemeBinding = {
    {0, "Default"},
    {1, "Yellow"},
    {2, "Green"},
    {3, "Cyan"},
    {4, "Red"}};
int score = 0, difficulty = 1, colorTheme = 0;
bool music = true, sounds = true, lifeSystem = true;
sf::RenderWindow window(sf::VideoMode(1024, 768), "Space Invaders");
sf::Font font;

enum class GameState
{
    MAIN_MENU,
    SETTINGS_MENU,
    GAME
};

GameState showMainMenu();
GameState showSettingsMenu();
GameState playGame();

void saveCsvSettings()
{
    std::ofstream file(CSV_PATH);
    file << "score," << score << std::endl;
    file << "difficulty," << difficulty << std::endl;
    file << "colorTheme," << colorTheme << std::endl;
    file << "music," << (music ? "true" : "false") << std::endl;
    file << "sounds," << (sounds ? "true" : "false") << std::endl;
    file << "lifeSystem," << (lifeSystem ? "true" : "false") << std::endl;
    file.close();
}

GameState showMainMenu()
{
    sf::Text scoreLabel("Score: " + std::to_string(score), font);
    scoreLabel.setPosition(window.getSize().x / 2 - scoreLabel.getGlobalBounds().width / 2, window.getSize().y / 4);

    sf::Text newGameButton("New Game", font);
    newGameButton.setPosition(window.getSize().x / 2 - newGameButton.getGlobalBounds().width / 2, window.getSize().y / 2);

    sf::Text settingsButton("Settings", font);
    settingsButton.setPosition(window.getSize().x / 2 - settingsButton.getGlobalBounds().width / 2, window.getSize().y / 2 + 40);

    sf::Text exitButton("Exit", font);
    exitButton.setPosition(window.getSize().x / 2 - exitButton.getGlobalBounds().width / 2, window.getSize().y / 2 + 80);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (newGameButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    return GameState::GAME;
                }
                if (settingsButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    return GameState::SETTINGS_MENU;
                }
                if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(scoreLabel);
        window.draw(newGameButton);
        window.draw(settingsButton);
        window.draw(exitButton);
        window.display();
    }
    return GameState::MAIN_MENU;
}

GameState showSettingsMenu()
{
    sf::Text musicButton(music ? "Music: true" : "Music: false", font);
    musicButton.setPosition(window.getSize().x / 2 - musicButton.getGlobalBounds().width / 2, window.getSize().y / 4);

    sf::Text soundsButton(sounds ? "Sounds: true" : "Sounds: false", font);
    soundsButton.setPosition(window.getSize().x / 2 - soundsButton.getGlobalBounds().width / 2, window.getSize().y / 4 + 40);

    sf::Text lifeSystemButton(lifeSystem ? "Lyfe System: true" : "Lyfe System: false", font);
    lifeSystemButton.setPosition(window.getSize().x / 2 - lifeSystemButton.getGlobalBounds().width / 2, window.getSize().y / 4 + 80);

    sf::Text colorThemeButton("Color Theme: " + colorThemeBinding[colorTheme].second, font);
    colorThemeButton.setPosition(window.getSize().x / 2 - colorThemeButton.getGlobalBounds().width / 2, window.getSize().y / 4 + 120);

    sf::Text difficultyStartButton("Difficulty Start: " + std::to_string(difficulty), font);
    difficultyStartButton.setPosition(window.getSize().x / 2 - difficultyStartButton.getGlobalBounds().width / 2, window.getSize().y / 4 + 160);

    sf::Text resetScoreButton("Reset Score", font);
    resetScoreButton.setPosition(window.getSize().x / 2 - resetScoreButton.getGlobalBounds().width / 2, window.getSize().y / 4 + 200);

    sf::Text backButton("Back", font);
    backButton.setPosition(window.getSize().x / 2 - backButton.getGlobalBounds().width / 2, window.getSize().y / 4 + 280);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (musicButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    music = !music;
                    musicButton.setString(music ? "Music: true" : "Music: false");
                }
                if (soundsButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    sounds = !sounds;
                    soundsButton.setString(sounds ? "Sounds: true" : "Sounds: false");
                }
                if (lifeSystemButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    lifeSystem = !lifeSystem;
                    lifeSystemButton.setString(lifeSystem ? "Lyfe System: true" : "Lyfe System: false");
                }
                if (colorThemeButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    colorTheme = (colorTheme < colorThemeBinding.size() - 1) ? colorTheme + 1 : 0;
                    colorThemeButton.setString("Color Theme: " + colorThemeBinding[colorTheme].second);
                }
                if (difficultyStartButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    difficulty = difficulty < MAX_DIFFICULTY ? difficulty + 1 : 1;
                    difficultyStartButton.setString("Difficulty Start: " + std::to_string(difficulty));
                }
                if (resetScoreButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    score = 0;
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (backButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    {
                        saveCsvSettings();
                        return GameState::MAIN_MENU;
                    }
                }
            }
        }

        window.clear();
        window.draw(musicButton);
        window.draw(soundsButton);
        window.draw(lifeSystemButton);
        window.draw(colorThemeButton);
        window.draw(difficultyStartButton);
        window.draw(resetScoreButton);
        window.draw(backButton);
        window.display();
    }
    return GameState::SETTINGS_MENU;
}

GameState playGame()
{
    sf::Color color;
    int scale = 2;
    int margin = 32 * scale;
    int curDifficulty = difficulty;
    int curScore = 0;
    bool powerUpActive = false;
    int powerUpBulletRate = 4;
    int powerUpScoreBoost = 1;
    int powerUpBulletSpeed = 1;
    int powerUpEnemySpeed = 1;
    int powerUpShield = false;
    int spawnRate = 2500 / curDifficulty;
    float enemySpeed = 0.05 * curDifficulty;
    float bulletSpeed = -0.05;
    int bulletRate = spawnRate / powerUpBulletRate;
    int scoreIncrement = 100;
    int lifes = lifeSystem ? 3 : 1;
    int shields = 0;

    sf::Texture playerTexture;
    playerTexture.loadFromFile(PLAYER_SPRITE_PATH);
    sf::Sprite player(playerTexture);
    player.setScale(scale, scale);
    player.setPosition(player.getGlobalBounds().width + margin, window.getSize().y - player.getGlobalBounds().height - margin);

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile(ENEMY_SPRITE_PATH);
    std::vector<sf::Sprite> enemies;
    sf::Clock enemySpawnClock;

    sf::Texture powerUpTexture;
    powerUpTexture.loadFromFile(POWER_UP_SPRITE_PATH);
    std::vector<sf::Sprite> powerUps;
    sf::Clock powerUpClock;

    sf::Texture lifeTexture;
    lifeTexture.loadFromFile(HEART_SPRITE_PATH);
    std::vector<sf::Sprite> lifesSprites;
    for (int i = 0; i < lifes; i++)
    {
        sf::Sprite life(lifeTexture);
        life.setPosition(margin + i * (life.getGlobalBounds().width + 10), margin);
        lifesSprites.push_back(life);
    }

    sf::Text scoreLabel;
    scoreLabel.setFont(font);
    scoreLabel.setString("Score: 0");
    scoreLabel.setPosition(window.getSize().x - scoreLabel.getGlobalBounds().width - margin, margin);

    sf::Text powerUpLabel;
    powerUpLabel.setFont(font);
    powerUpLabel.setString("");
    powerUpLabel.setFillColor(sf::Color::Cyan);
    powerUpLabel.setPosition(window.getSize().x / 2 - powerUpLabel.getGlobalBounds().width / 2, margin);

    sf::Text difficultyLabel;
    difficultyLabel.setFont(font);
    difficultyLabel.setFillColor(sf::Color::Red);
    difficultyLabel.setString(std::to_string(curDifficulty));
    difficultyLabel.setPosition(margin, window.getSize().y - margin - difficultyLabel.getGlobalBounds().height);

    sf::Texture bulletTexture;
    bulletTexture.loadFromFile(BULLET_SPRITE_PATH);
    std::vector<sf::Sprite> bullets;
    sf::Clock bulletSpawnClock;

    sf::Texture baseShieldTexture;
    baseShieldTexture.loadFromFile(BASE_SHIELD_SPRITE_PATH);
    sf::Texture fullShieldTexture;
    fullShieldTexture.loadFromFile(FULL_SHIELD_SPRITE_PATH);
    std::vector<sf::Sprite> shieldsSprites;
    sf::Texture indicatorShieldTexture;
    indicatorShieldTexture.loadFromFile(INDICATOR_SHIELD_SPRITE_PATH);
    std::vector<sf::Sprite> shieldsIndicators;

    sf::Texture explosionTexture;
    explosionTexture.loadFromFile(EXPLOSION_SPRITE_PATH);
    std::vector<std::pair<sf::Clock, sf::Sprite>> explosions;

    sf::SoundBuffer bulletSoundBuffer;
    bulletSoundBuffer.loadFromFile(BULLET_SOUND_PATH);
    sf::Sound bulletSound;
    bulletSound.setBuffer(bulletSoundBuffer);

    sf::SoundBuffer explosionSoundBuffer;
    explosionSoundBuffer.loadFromFile(EXPLOSION_SOUND_PATH);
    sf::Sound explosionSound;
    explosionSound.setBuffer(explosionSoundBuffer);

    sf::SoundBuffer shieldSoundBuffer;
    shieldSoundBuffer.loadFromFile(SHIELD_SOUND_PATH);
    sf::Sound shieldSound;
    shieldSound.setBuffer(shieldSoundBuffer);

    // colored sprites with colorTheme
    switch (colorTheme)
    {
    case 0:
        color = sf::Color::White;
        break;
    case 1:
        color = sf::Color::Yellow;
        break;
    case 2:
        color = sf::Color::Green;
        break;
    case 3:
        color = sf::Color::Cyan;
        break;
    case 4:
        color = sf::Color::Red;
        break;
    }
    player.setColor(color);
    scoreLabel.setFillColor(color);
    if (colorTheme != 0)
    {
        difficultyLabel.setFillColor(color);
        powerUpLabel.setFillColor(color);
    }
    for (auto &s : shieldsSprites)
    {
        s.setColor(color);
    }
    for (auto &l : lifesSprites)
    {
        l.setColor(color);
    }

    while (window.isOpen())
    {
        window.clear(sf::Color(0, 0, 25));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            bulletRate = spawnRate / powerUpBulletRate;
            if (curScore % 2500 == 0 && curScore != 0)
            {
                curDifficulty = curDifficulty < MAX_DIFFICULTY ? (curScore / 2500) + 1 : 10;
                spawnRate = 2500 / curDifficulty;
                enemySpeed = 0.05 * curDifficulty;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    player.move(-margin, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    player.move(margin, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    if (bulletSpawnClock.getElapsedTime().asMilliseconds() >= bulletRate)
                    {
                        sf::Sprite bullet(bulletTexture);
                        bullet.setPosition(player.getPosition().x + (player.getGlobalBounds().width / 4), player.getPosition().y - (bullet.getGlobalBounds().height / 2));
                        bullet.setScale(scale, scale);
                        bullets.push_back(bullet);
                        bulletSpawnClock.restart();
                        if (sounds)
                        {
                            bulletSound.play();
                        }
                    }
                }

                // margin is margin and player cant go out of the window with margin inner pixels
                if (player.getPosition().x < margin)
                {
                    player.setPosition(margin, player.getPosition().y);
                }
                if (player.getPosition().x > window.getSize().x - margin - player.getGlobalBounds().width)
                {
                    player.setPosition(window.getSize().x - margin - player.getGlobalBounds().width, player.getPosition().y);
                }
            }
        }

        if (enemySpawnClock.getElapsedTime().asMilliseconds() >= spawnRate)
        {
            sf::Sprite enemy(enemyTexture);
            // random spawn position between margin and window width-margin, steps of margin
            enemy.setPosition(margin + rand() % (window.getSize().x - (margin * 3)), margin);
            // enemy.setPosition(margin + rand() % (window.getSize().x - (margin * 3)), margin);
            enemy.setScale(scale, scale);
            enemies.push_back(enemy);
            enemySpawnClock.restart();
        }

        for (auto b = bullets.begin(); b != bullets.end();)
        {
            b->move(0, bulletSpeed * powerUpBulletSpeed);
            if (b->getPosition().y < 0)
            {
                b = bullets.erase(b);
            }

            else
            {
                ++b;
            }
        }

        for (auto e = enemies.begin(); e != enemies.end();)
        {
            e->move(0, enemySpeed * powerUpEnemySpeed);

            bool enemyErased = false;
            for (auto b = bullets.begin(); b != bullets.end();)
            {
                if (e->getGlobalBounds().intersects(b->getGlobalBounds()))
                {
                    enemyErased = true;
                    b = bullets.erase(b);
                    sf::Sprite explosion(explosionTexture);
                    explosion.setScale(scale, scale);
                    if (colorTheme != 0)
                    {
                        explosion.setColor(color);
                    }
                    explosion.setPosition(e->getPosition().x, e->getPosition().y);
                    explosions.push_back(std::make_pair(sf::Clock(), explosion));
                    if (sounds)
                    {
                        explosionSound.play();
                    }
                    // spawn power up with 20% chance
                    if (rand() % 5 == 0)
                    {
                        sf::Sprite powerUp(powerUpTexture);
                        powerUp.setPosition(e->getPosition().x, e->getPosition().y);
                        powerUp.setScale(scale, scale);
                        powerUp.setColor(color);
                        powerUps.push_back(powerUp);
                    }
                    curScore += scoreIncrement * powerUpScoreBoost;
                    break;
                }
                else
                {
                    ++b;
                }
            }
            if (e->getGlobalBounds().intersects(player.getGlobalBounds()) || e->getPosition().y > window.getSize().y)
            {
                if (shields > 0)
                {
                    shields--;
                    shieldsIndicators.pop_back();
                    shieldsSprites.pop_back();
                    e = enemies.erase(e);
                }
                else
                {
                    lifes--;
                    lifesSprites.pop_back();
                    e = enemies.erase(e);
                }
            }
            else if (enemyErased)
            {
                e = enemies.erase(e);
            }
            else
            {
                ++e;
            }
        }

        for (auto p = powerUps.begin(); p != powerUps.end();)
        {
            p->move(0, enemySpeed);
            if (p->getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                if (!powerUpActive)
                {
                    p = powerUps.erase(p);
                    int powerUpType = rand() % 6;
                    if (powerUpType == 0)
                    {
                        powerUpScoreBoost = 2;
                        powerUpLabel.setString("Score Boost");
                        powerUpClock.restart();
                        powerUpActive = true;
                    }
                    else if (powerUpType == 1)
                    {
                        powerUpBulletRate = 10;
                        powerUpLabel.setString("Bullet Rate");
                        powerUpClock.restart();
                        powerUpActive = true;
                    }
                    else if (powerUpType == 2)
                    {
                        if (lifes < MAX_LIFES && lifeSystem)
                        {
                            lifes++;
                            sf::Sprite life(lifeTexture);
                            life.setPosition(margin + (lifes - 1) * (life.getGlobalBounds().width + 10), margin);
                            life.setColor(color);
                            lifesSprites.push_back(life);
                            powerUpLabel.setString("Life Up!");
                        }
                        else
                        {
                            curScore += scoreIncrement * powerUpScoreBoost;
                            powerUpLabel.setString("+" + std::to_string(scoreIncrement * powerUpScoreBoost));
                        }
                    }
                    else if (powerUpType == 3)
                    {
                        powerUpBulletSpeed = 2;
                        powerUpLabel.setString("Bullet Speed");
                        powerUpClock.restart();
                        powerUpActive = true;
                    }
                    else if (powerUpType == 4)
                    {
                        powerUpEnemySpeed = 0.5;
                        powerUpLabel.setString("Slow Motion");
                        powerUpClock.restart();
                        powerUpActive = true;
                    }
                    else if (powerUpType == 5)
                    {
                        if (shields < MAX_SHIELDS)
                        {
                            powerUpShield = true;
                            powerUpLabel.setString("Shield");
                            if (sounds)
                            {
                                shieldSound.play();
                            }
                            shields++;
                            sf::Sprite shield(indicatorShieldTexture);
                            shield.setPosition(margin + (shields - 1) * (shield.getGlobalBounds().width + 10), margin * 2 + 10);
                            shield.setColor(color);
                            shieldsIndicators.push_back(shield);
                            if (shields < MAX_SHIELDS)
                            {
                                sf::Sprite shieldSprite(baseShieldTexture);
                                shieldSprite.scale(scale, scale);
                                shieldSprite.setPosition(player.getPosition().x - (player.getGlobalBounds().width / 4), player.getPosition().y - (shieldSprite.getGlobalBounds().height / 2));
                                shieldsSprites.push_back(shieldSprite);
                            }
                            else
                            {
                                sf::Sprite shieldSprite(fullShieldTexture);
                                shieldSprite.scale(scale, scale);
                                shieldSprite.setPosition(player.getPosition().x + (player.getGlobalBounds().width / 2), player.getPosition().y - (shieldSprite.getGlobalBounds().height / 2));
                                shieldsSprites.push_back(shieldSprite);
                            }
                        }
                        else
                        {
                            curScore += scoreIncrement * powerUpScoreBoost;
                            powerUpLabel.setString("+" + std::to_string(scoreIncrement * powerUpScoreBoost));
                        }
                    }
                }
                else
                {
                    curScore += scoreIncrement * powerUpScoreBoost;
                    powerUpLabel.setString("+" + std::to_string(scoreIncrement * powerUpScoreBoost));
                    p = powerUps.erase(p);
                }
            }
            else if (p->getPosition().y > window.getSize().y)
            {
                p = powerUps.erase(p);
            }
            else
            {
                ++p;
            }
        }

        for (auto ex = explosions.begin(); ex != explosions.end();)
        {
            if (ex->first.getElapsedTime().asMilliseconds() >= 500)
            {
                ex = explosions.erase(ex);
            }
            else
            {
                window.draw(ex->second);
                ++ex;
            }
        }

        for (auto enemy : enemies)
        {
            if (colorTheme != 0)
            {
                enemy.setColor(color);
            }
            if (colorTheme == 0)
            {
                if (powerUpEnemySpeed < 1)
                {
                    enemy.setColor(sf::Color::Cyan);
                }
                else
                {
                    enemy.setColor(sf::Color::White);
                }
            }
            window.draw(enemy);
        }

        for (auto powerUp : powerUps)
        {
            window.draw(powerUp);
        }
        for (auto bullet : bullets)
        {
            if (colorTheme != 0)
            {
                bullet.setColor(color);
            }
            if (colorTheme == 0)
            {
                // se lo scudo è attivo, i proiettili sono ciano
                if (powerUpBulletRate > 4)
                {
                    bullet.setColor(sf::Color::Red);
                }
                else if (powerUpShield)
                {
                    bullet.setColor(sf::Color::Cyan);
                }
                else
                {
                    bullet.setColor(sf::Color::White);
                }
            }
            window.draw(bullet);
        }
        for (auto l : lifesSprites)
        {
            window.draw(l);
        }
        for (auto sh : shieldsIndicators)
        {
            window.draw(sh);
        }

        if (lifes <= 0)
        {
            score = curScore > score ? curScore : score;
            saveCsvSettings();
            return GameState::MAIN_MENU;
        }

        if (powerUpClock.getElapsedTime().asMilliseconds() >= 5000)
        {
            // reset power ups
            if (powerUpActive)
            {
                powerUpBulletRate = 4;
                powerUpScoreBoost = 1;
                powerUpBulletSpeed = 1;
                powerUpEnemySpeed = 1;
                powerUpActive = false;
                powerUpClock.restart();
            }
            powerUpLabel.setString("");
        }

        scoreLabel.setPosition(window.getSize().x - scoreLabel.getGlobalBounds().width - margin, margin);
        scoreLabel.setString("Score: " + std::to_string(curScore));
        difficultyLabel.setString(std::to_string(curDifficulty));
        powerUpLabel.setPosition(window.getSize().x / 2 - powerUpLabel.getGlobalBounds().width / 2, margin);
        window.draw(scoreLabel);
        window.draw(difficultyLabel);
        window.draw(powerUpLabel);
        window.draw(player);
        if (shields > 0)
        {
            if (shields == 3)
            {
                shieldsSprites.back().setPosition(player.getPosition().x, player.getPosition().y);
            }
            else
            {
                shieldsSprites.back().setPosition(player.getPosition().x - (player.getGlobalBounds().width / 4), player.getPosition().y - (shieldsSprites.back().getGlobalBounds().height / 2));
            }
            window.draw(shieldsSprites.back());
        }
        window.display();
    }

    return GameState::MAIN_MENU;
}

void readCsvSettings()
{
    std::ifstream file(CSV_PATH);

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::string key, value;
            std::stringstream ss(line);
            std::getline(ss, key, ',');
            std::getline(ss, value, ',');

            if (key == "score")
            {
                score = std::stoi(value);
            }
            else if (key == "difficulty")
            {
                difficulty = std::stoi(value);
            }
            else if (key == "colorTheme")
            {
                colorTheme = std::stoi(value);
            }
            else if (key == "music")
            {
                music = value == "true" ? true : false;
            }
            else if (key == "sounds")
            {
                sounds = value == "true" ? true : false;
            }
            else if (key == "lifeSystem")
            {
                lifeSystem = value == "true" ? true : false;
            }
        }
    }
    file.close();
}

int main()
{
    if (!font.loadFromFile(FONT_PATH))
    {
        std::cout << "Error loading font" << std::endl;
        window.close();
    }

    GameState gameState = GameState::MAIN_MENU;
    readCsvSettings();

    while (true)
    {
        switch (gameState)
        {
        case GameState::MAIN_MENU:
            gameState = showMainMenu();
            break;
        case GameState::SETTINGS_MENU:
            gameState = showSettingsMenu();
            break;
        case GameState::GAME:
            gameState = playGame();
            break;
        }
    }

    return 0;
}