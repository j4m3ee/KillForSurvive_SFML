#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "Platform.h"
#include "Menu.h"
#include "Bullet.h"
#include "Print.h"
#include "Item.h"
#include "GUI.h"
#include "itemSlot.h"
#include "Input.h"
#include "leaderBoard.h"
#include "deathBomb.h"
#include "printText.h"
#include "dropPlane.h"
#include "pauseMenu.h"

unsigned int VIEW_HEIGHT = 1080;
unsigned int VIEW_WIDTH = 1920;
const int mapSize = 80;
float gridSizeF = 50.0f;
//const int Nenermy = 25;
const int Nitem = 40;
const int Ngrass = 30;
const int Nbox = 30;
const int magSize1 = 20,magSize2 = 40,magSize3 =5;
float detectArea = 500.0f;
string ttf("Res/Fonts/");
string png("Res/Textures/");
string wav("Res/Music/");

void ResizeView(const RenderWindow& window, View& view) 
{
	float aspectRatio = (float)window.getSize().x / (float)window.getSize().y;
	view.setSize((float)VIEW_HEIGHT * aspectRatio, (float)VIEW_HEIGHT);
}


using namespace std;
using namespace sf;

int main()
{
	char lastChar = ' ';
	int MainMenu = 0,hide = 0; 
	int Nenermy = 20;
	bool pause = false, nameState = false,onPlane = true,saw = true; 
	bool planeFly = false, genbot = false, pauseOn = false;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView,shotgunView,botshotgunView;
	Vector2i mousePosGrid;
	srand((unsigned int)time(0));
	
	//Text
	Font font;
	font.loadFromFile(ttf + "Cascadia.ttf");
	Text text,kill,timeShow,magazine,dropOff;
	text.setCharacterSize(20);
	text.setOutlineThickness(2);
	text.setOutlineColor(Color::Black);
	text.setFillColor(Color::White);
	text.setFont(font);
	kill.setCharacterSize(40);
	kill.setOutlineThickness(2);
	kill.setOutlineColor(Color::Black);
	kill.setFillColor(Color::Red);
	kill.setFont(font);
	timeShow.setCharacterSize(30);
	timeShow.setOutlineThickness(2);
	timeShow.setOutlineColor(Color::Black);
	timeShow.setFillColor(Color::White);
	timeShow.setFont(font);
	magazine.setCharacterSize(20);
	magazine.setOutlineThickness(2);
	magazine.setOutlineColor(Color::Black);
	magazine.setFillColor(Color::White);
	magazine.setFont(font);
	dropOff.setCharacterSize(50);
	dropOff.setOutlineThickness(5);
	dropOff.setOutlineColor(Color::Black);
	dropOff.setFillColor(Color(255,255,102,255));
	dropOff.setFont(font);
	dropOff.setString("Enter -> SpaceBar <- To Drop off");

	RenderWindow window(VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Kill For Survive !!!",Style::Fullscreen);
	String nameInput;
	leaderBoard scoreBoard(&font); 
	printText gamePlay(&font);

	//------------------------- Cursor -------------------------
	Cursor cursor;
	Image image_cursor;
	if (!image_cursor.loadFromFile(png + "cursor.png")) {
		cout << "Load \"cursor.png\" failed" << endl;
	}
	if (cursor.loadFromPixels(image_cursor.getPixelsPtr(), image_cursor.getSize(), { 8, 8 })) {
		window.setMouseCursor(cursor);
	}
	window.setIcon(32,32, image_cursor.getPixelsPtr());

	Menu menu(&font);
	pauseMenu PauseMenu(&font);
	window.setFramerateLimit(120);
	View view(Vector2f(0.0f, 0.0f), Vector2f((float)VIEW_WIDTH, (float)VIEW_HEIGHT));
	RectangleShape Menu(Vector2f(1920.0f,1080.0f)); //Menu0
	RectangleShape Win(Vector2f(1920.0f, 1080.0f));
	RectangleShape HTP(Vector2f(1920.0f, 1080.0f));
	RectangleShape Interface(Vector2f(1920.0f, 1080.0f)); //Menu1
	RectangleShape nameEnter(Vector2f(1920.0f, 1080.0f)); 
	Menu.setPosition(0.0f,0.0f);

	Texture MenuBG; MenuBG.loadFromFile(png + "BG.png");
	Texture WinBG; WinBG.loadFromFile(png + "Win.png");
	Texture HTPBG; HTPBG.loadFromFile(png + "HTP.png");
	Texture PlayerTex; PlayerTex.loadFromFile(png + "survivor.png");
	Texture EnermyTex; EnermyTex.loadFromFile(png + "enermy.png");
	Texture Platformtex; Platformtex.loadFromFile(png + "texglass.png");
	Texture bullTexture; bullTexture.loadFromFile(png + "Bullet.png");
	Texture itemTex; itemTex.loadFromFile(png + "Item.png");
	Texture knife; knife.loadFromFile(png + "survivorKnife.png");
	Texture grass; grass.loadFromFile(png + "Grass.png");
	Texture piston; piston.loadFromFile(png + "survivorPiston.png");
	Texture shotgun; shotgun.loadFromFile(png + "survivorShotgun.png");
	Texture GamePlay; GamePlay.loadFromFile(png + "GamePlay.png");
	Texture bullBot; bullBot.loadFromFile(png + "BulletBot.png");
	Texture bomb; bomb.loadFromFile(png + "deathBomb.png");
	Texture box; box.loadFromFile(png + "box.png");
	Texture plane; plane.loadFromFile(png + "plane.png");

	Menu.setTexture(&MenuBG);
	Win.setTexture(&WinBG);
	HTP.setTexture(&HTPBG);
	Interface.setTexture(&GamePlay);
	Interface.setOrigin(Interface.getSize() / 2.0f);

	Player player(&piston, Vector2u(5, 5), 0.3f,200.0f,Vector2f(0.0f,0.0f));
	GUI hpBar(20), armorBar(20);
	itemSlot slot(&itemTex);
	Input name(&font);
	dropPlane Plane(&plane, 250.0f);
	
	//------------------------- MapMaking -------------------------
	RectangleShape grid(Vector2f(gridSizeF, gridSizeF));

	vector<vector<RectangleShape>>tileMap;
	tileMap.resize(mapSize, vector<RectangleShape>());
	
	for (int x = 0; x < mapSize; x++) {
		tileMap[x].resize(mapSize, RectangleShape());
		for (int y = 0; y < mapSize; y++) {
			tileMap[x][y].setSize(Vector2f(gridSizeF, gridSizeF));
			tileMap[x][y].setTexture(&Platformtex);
			tileMap[x][y].setOutlineColor(Color::Black);
			tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
		}
	}
	RectangleShape tileSelector(Vector2f(gridSizeF, gridSizeF));
	tileSelector.setFillColor(Color::Transparent);
	tileSelector.setOutlineThickness(2.0f);
	tileSelector.setOutlineColor(Color::Blue);

	//------------------------- Glass <vector> -------------------------
	Platform Glass(&grass, Vector2f(200.0f, 200.0f), Vector2f(50.0f, 50.0f), Vector2f(400.0f, 400.0f));
	vector<Platform> Vgrass;
	Vgrass.push_back(Platform(Glass));
	//------------------------- Box <vector> -------------------------
	Platform Box(&box, Vector2f(50.0f, 50.0f), Vector2f(50.0f, 50.0f), Vector2f(400.0f, 400.0f));
	vector<Platform> Vbox;
	Vbox.push_back(Platform(Box));

	//------------------------- Enermy <vector> -------------------------
	Enermy enermy(&EnermyTex, Vector2u(5, 5), 0.3f, 100.0f);
	vector<Enermy> bot;
	bot.push_back(Enermy(enermy));

	//------------------------- Bullet <vector> -------------------------
	bool shot = true;
	Vector2f playerCenter,aimDir,botCenter,botDir;
	Bullet b1(&bullTexture),b2(&bullBot);
	vector<Bullet> bullets,botBullets;
	bullets.push_back(Bullet(b1));
	botBullets.push_back(Bullet(b2));

	//------------------------- Item <vector> -------------------------
	Item item(&itemTex);
	vector<Item> iTem;
	iTem.push_back(Item(item));

	//------------------------- DeathBomb <vector> -------------------------
	deathBomb Bomb(&bomb, Vector2u(6, 7), 0.05f);
	vector<deathBomb> Bomber;
	Bomber.push_back(deathBomb(Bomb));
	
	//------------------------- Music & Sound -------------------------
	Music music; music.openFromFile(wav + "PUBG.wav"); 
	music.setVolume(10.0f); music.play();
	Music jet; jet.openFromFile(wav + "jetFly.ogg");
	jet.setVolume(20.0f);
	SoundBuffer soundBuffer,pickBuf,ShotgunBuf,reloadBuf,boomBuf,dropBuf;
	Sound sound,pick,Shotgun,reload,boom,drop;
	soundBuffer.loadFromFile(wav + "Shoot.wav");
	pickBuf.loadFromFile(wav + "Pickup.ogg");
	ShotgunBuf.loadFromFile(wav + "Shotgun.wav");
	reloadBuf.loadFromFile(wav + "Reload.ogg");
	boomBuf.loadFromFile(wav + "Bomb.wav");
	dropBuf.loadFromFile(wav + "Parachute.ogg");
	sound.setVolume(5.0f); sound.setBuffer(soundBuffer);
	pick.setVolume(10.0f); pick.setBuffer(pickBuf);
	Shotgun.setVolume(10.0f); Shotgun.setBuffer(ShotgunBuf);
	reload.setVolume(30.0f); reload.setBuffer(reloadBuf);
	boom.setVolume(10.0f); boom.setBuffer(boomBuf);
	drop.setVolume(50.0f); drop.setBuffer(dropBuf);
	bool musicStart = false;

	float deltaTime = 0.0f,tempTimer;
	float Time = 0.0f,Timer = 0.0f,GameTime = 0.0f;
	Clock clock,delay,timer;
	system("dir");
	scoreBoard.fistWriteText();
	while (window.isOpen())
	{
		
		if (MainMenu == 0 && musicStart == false) {
			music.play();
			jet.stop();
			musicStart = true;
		}
		deltaTime = clock.restart().asSeconds();
		
		Time = delay.getElapsedTime().asSeconds();

		//Update mouse position
		mousePosScreen = Mouse::getPosition();
		mousePosWindow = Mouse::getPosition(window);
		mousePosView = window.mapPixelToCoords(mousePosWindow);
		if(mousePosView.x >= 0.0f)
			mousePosGrid.x = (int)mousePosView.x / gridSizeU;
		if (mousePosView.y >= 0.0f)
			mousePosGrid.y = (int)mousePosView.y / gridSizeU;

		
		
		//Update game element
		tileSelector.setPosition(mousePosGrid.x * gridSizeF,mousePosGrid.y * gridSizeF);

		stringstream ss,ssKill,ssTime,ssAmmo;
		ss << "Screen " << mousePosScreen.x << " " << mousePosScreen.y << endl
			<< "Window " << mousePosWindow.x << " " << mousePosWindow.y << endl
			<< "View " << mousePosView.x << " " << mousePosView.y << endl
			<< "Grid  " << mousePosGrid.x << " " << mousePosGrid.y << endl
			<< "Row " << player.getRow() << endl
			<< "Enermy " << bot.size() << endl
			<< "Item " << iTem.size() << endl
			<< "DetectArea " << detectArea << endl;
		text.setString(ss.str());
		ssKill << "Allive : " << bot.size()-1 << endl;
		kill.setString(ssKill.str());
		
		ssAmmo << player.mag1 << "/" << player.Ammo1 << "   "
			<< player.mag2 << "/" << player.Ammo2 << "   " 
			<< player.mag3 << "/" << player.Ammo3 << endl;
		magazine.setString(ssAmmo.str());
		gamePlay.setValue();

		Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::KeyReleased:
				if (lastChar != ' ') lastChar = ' ';
				switch (evnt.key.code) {
				case Keyboard::Up:
					menu.MoveUp();
					if (pauseOn) PauseMenu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					if (pauseOn) PauseMenu.MoveDown();
					break;

				case Keyboard::Return:

					if (pauseOn == true) {
						switch (PauseMenu.GetPressedItem())
						{
						case 0:
							MainMenu = 1;
							nameInput.clear();
							name.Update((string)nameInput);
							pauseOn = false;
							if (onPlane == true) jet.play();
							break;
						case 1:
							if (MainMenu != 0) {
								MainMenu = 0;
								musicStart = false;
							}
							for (size_t i = 1; i < iTem.size(); i++) {
								iTem.erase(iTem.begin() + i);
							}
							for (size_t i = 1; i < bullets.size(); i++) {
								bullets.erase(bullets.begin() + i);
							}
							for (size_t i = 1; i < bot.size(); i++) {
								bot.erase(bot.begin() + i);
							}
							for (size_t i = 1; i < Vgrass.size(); i++) {
								Vgrass.erase(Vgrass.begin() + i);
							}
							for (size_t i = 1; i < Vbox.size(); i++) {
								Vbox.erase(Vbox.begin() + i);
							}
							gamePlay.point = 0;
							player.kill = 0;
							player.hp = 100;
							nameInput.clear();
							name.Update((string)nameInput);
							pauseOn = false;
							menu.MoveUp();
							break;
						case 2:
							window.close();
							break;
						default:
							break;
						}
					}
					else switch (menu.GetPressedItem()) {
					case 0:
						if (MainMenu == 0&& nameInput.getSize()!=0) {
							gamePlay.point = 0;
							player.Reset();
							slot.reStart();
							
							cout << "Play pressed" << endl;
							onPlane = true;
							Plane.setPosition(Vector2f(100.0f, 500.0f + rand() % 3000));
							player.setPosition(Plane.GetPosition());
							//-------   Item - Gen   -------
							for (int i = 0; i < Nitem; i++) {
								item.setPosition(Vector2f(((rand() % 70)+5)* gridSizeF, ((rand() % 70)+5)* gridSizeF), rand() % 12);
								iTem.push_back(Item(item));
							}
							//-------   Bot - Gen   -------
							for (int i = 0; i < Nenermy; i++) {
								enermy.setPosition(Vector2f((float)(1000 + rand() % 2000), (float)(1000 + rand() % 2000)), rand() % 7);
								if (enermy.getType() == 0 || enermy.getType() == 1 || enermy.getType() == 2) {
									enermy.UpdateTex(&piston);

								}
								else if (enermy.getType() == 3 || enermy.getType() == 4 || enermy.getType() == 5) {
									enermy.UpdateTex(&PlayerTex);

								}
								else if (enermy.getType() == 6) {
									enermy.UpdateTex(&shotgun);
								}
								else
								{
									enermy.UpdateTex(&PlayerTex);
								}
								bot.push_back(Enermy(enermy));
							}
							//-------   Grass - Gen   -------
							for (int i = 0; i < Ngrass; i++) {
								Glass.setPosition(Vector2f((rand() % 80)* gridSizeF, (rand() % 80)* gridSizeF));
								Vgrass.push_back(Platform(Glass));
							}
							//-------   Box - Gen   -------
							for (int i = 0; i < Nbox; i++) {
								Box.setPosition(Vector2f((rand()%80)*gridSizeF, (rand() % 80)* gridSizeF));
								Vbox.push_back(Platform(Box));
							}

							player.UpdateTex(&piston, 0);
							slot.updateSlot(0);
							player.hp = 100; player.Armor = 0;
							MainMenu = 1; gamePlay.point = 0;
							music.stop(); jet.play();
							musicStart = true;
							Time = delay.restart().asSeconds();
							Timer = timer.restart().asSeconds();
						}
						break;
					case 1:
						cout << "HowToPlay pressed" << endl;
						MainMenu = 3;
						break;
					case 2:
						cout << "HightScore pressed" << endl;
						MainMenu = 2;
						break;
					case 3:
						window.close();
						break;
					default:
						break;
					}
					break;


				case Keyboard::Num1:
					if (slot.nowSlot != 1) {
						if (slot.slotType1 == 0 || slot.slotType1 == 1 || slot.slotType1 == 2) {
							player.UpdateTex(&piston, slot.slotType1);
						}
						else if (slot.slotType1 == 3 || slot.slotType1 == 4 || slot.slotType1 == 5) {
							player.UpdateTex(&PlayerTex, slot.slotType1);
						}
						else if (slot.slotType1 == 6) {
							player.UpdateTex(&shotgun, slot.slotType1);
						}
						shot = true; slot.nowSlot = 1; player.otherType = slot.slotType2;
					}
					break;
				case Keyboard::Num2:
					if (slot.nowSlot != 2) {
						if (slot.slotType2 == 0 || slot.slotType2 == 1 || slot.slotType2 == 2) {
							player.UpdateTex(&piston, slot.slotType2);
						}
						else if (slot.slotType2 == 3 || slot.slotType2 == 4 || slot.slotType2 == 5) {
							player.UpdateTex(&PlayerTex, slot.slotType2);
						}
						else if (slot.slotType2 == 6) {
							player.UpdateTex(&shotgun, slot.slotType2);
						}
						shot = true; slot.nowSlot = 2; player.otherType = slot.slotType1;
					}
					break;
				case Keyboard::R:
					switch (player.ammoType)
					{
					case 1:
						if (player.mag1 < magSize1 && player.Ammo1>0) {
							reload.play();
							player.Ammo1 = player.Ammo1 - (magSize1 - player.mag1);
							if (player.Ammo1 < 0) player.Ammo1 = 0;
							if (player.Ammo1 >= magSize1) player.mag1 = magSize1;
							if (player.Ammo1 < magSize1) {
								player.mag1 = magSize1;
								player.Ammo1 = player.Ammo1 - (magSize1 - player.mag1);
							}
						}
						break;
					case 2:
						if (player.mag2 < magSize2 && player.Ammo2>0) {
							reload.play();
							player.Ammo2 = player.Ammo2 - (magSize2 - player.mag2);
							if (player.Ammo2 < 0) player.Ammo2 = 0;
							if (player.Ammo2 >= magSize2) player.mag2 = magSize2;
							if (player.Ammo2 < magSize2) {
								player.mag2 = magSize2;
								player.Ammo2 = player.Ammo2 - (magSize2 - player.mag2);
							}
						}
						break;
					case 3:
						if (player.mag3 < magSize3 && player.Ammo3>0) {
							reload.play();
							player.Ammo3 = player.Ammo3 - (magSize3 - player.mag3);
							if (player.Ammo3 < 0) player.Ammo3 = 0;
							if (player.Ammo3 >= magSize3) player.mag3 = magSize3;
							if (player.Ammo3 < magSize3) {
								player.mag3 = magSize3;
								player.Ammo3 = player.Ammo3 - (magSize3 - player.mag3);
							}
						}
						break;
					default:
						break;
					}
					break;
				case Keyboard::M: 
					if (MainMenu == 1 || MainMenu == 2 || MainMenu ==3) {
						if (MainMenu != 0) {
							MainMenu = 0;
							musicStart = false;
						}
						for (size_t i = 1; i < iTem.size(); i++) {
							iTem.erase(iTem.begin() + i);
						}
						for (size_t i = 1; i < bullets.size(); i++) {
							bullets.erase(bullets.begin() + i);
						}
						for (size_t i = 1; i < bot.size(); i++) {
							bot.erase(bot.begin() + i);
						}
						for (size_t i = 1; i < Vgrass.size(); i++) {
							Vgrass.erase(Vgrass.begin() + i);
						}
						for (size_t i = 1; i < Vbox.size(); i++) {
							Vbox.erase(Vbox.begin() + i);
						}
						gamePlay.point = 0;
						player.kill = 0;
						player.hp = 100;
						nameInput.clear();
						name.Update((string)nameInput);
					}
				case Keyboard::Space:
					if (onPlane == true) {
						onPlane = false;
						saw = false;
						if(MainMenu == 1) drop.play();
					}
					break;
				case Keyboard::Escape:
					if (MainMenu == 1) {
						tempTimer = Timer;
						Timer = tempTimer;
						pauseOn = true;
						if (onPlane == true) jet.pause();
					}
					break;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				ResizeView(window,view);
				cout << "Width : " << evnt.size.width << " Height : " << evnt.size.height << endl;
				break;
			case Event::TextEntered:
				if (lastChar != evnt.text.unicode && evnt.text.unicode == 8 
					&& nameInput.getSize()>0 && MainMenu == 0 ) {
					lastChar = evnt.text.unicode;
					nameInput.erase(nameInput.getSize() - 1);
					name.Update((string)nameInput);
					cout << (string)nameInput << endl;
				}
				else if (lastChar != evnt.text.unicode && nameInput.getSize() <= 14 &&
					MainMenu == 0 && (evnt.text.unicode >= 'a' && evnt.text.unicode <= 'z' ||
						evnt.text.unicode >= 'A' && evnt.text.unicode <= 'Z' ||
						evnt.text.unicode >= '0' && evnt.text.unicode <= '9'
					)) {
					cout << char(evnt.text.unicode) << endl;
					lastChar = evnt.text.unicode;
					nameInput += evnt.text.unicode;
					cout << (string)nameInput << endl;
					name.Update((string)nameInput);
				}
			}
		}

		//------- Set View ----------
		if (MainMenu != 1 ) {
			view.setCenter(Vector2f((float)(VIEW_WIDTH / 2), (float)(VIEW_HEIGHT / 2)));
			window.setView(view);
		}
		else if (player.GetPosition().x >= 960.0f || player.GetPosition().y >= 540.0f
				|| player.GetPosition().x <= 3040.0f || player.GetPosition().y <= 3460.0f) {
			if (player.GetPosition().x <= 960.0f) {
				view.setCenter(960.0f, player.GetPosition().y);
			}
			if (player.GetPosition().y <= 540.0f) {
				view.setCenter(player.GetPosition().x, 540.0f);
			}
			if (player.GetPosition().x >= 3040.0f) {
				view.setCenter(3040.0f, player.GetPosition().y);
			}
			if (player.GetPosition().y >= 3460.0f) {
				view.setCenter(player.GetPosition().x, 3460.0f);
			}
			if (player.GetPosition().x <= 960.0f && player.GetPosition().y <= 540.0f) {
				view.setCenter(960.0f, 540.0f);
			}
			if (player.GetPosition().x <= 960.0f && player.GetPosition().y >= 3460.0f) {
				view.setCenter(960.0f, 3460.0f);
			}
			if (player.GetPosition().x >= 3040.0f && player.GetPosition().y <= 540.0f) {
				view.setCenter(3040.0f, 540.0f);
			}
			if (player.GetPosition().x >= 3040.0f && player.GetPosition().y >= 3460.0f) {
				view.setCenter(3040.0f, 3460.0f);
			}
			if (player.GetPosition().x >= 960.0f && player.GetPosition().y >= 540.0f
				&& player.GetPosition().x <= 3040.0f && player.GetPosition().y <= 3460.0f) {
				view.setCenter(player.GetPosition());
			}
			Interface.setPosition(view.getCenter());
			slot.Update(view.getCenter(),player.ammoType);
			window.setView(view);
		}

		if (MainMenu == 1 && pauseOn == false) {

			//-------  Timer -------

			Timer = timer.getElapsedTime().asSeconds();
			ssTime << (int)Timer / 60 << " : " << (int)Timer % 60 << endl;
			timeShow.setString(ssTime.str());

			//-------  Update -------
			if (Plane.GetPosition().x < 4300.0f && Plane.GetPosition().y > 0.0f) {
				Plane.Update(deltaTime, view.getCenter());
				if (Plane.GetPosition().x > 3900.0f && onPlane == true) {
					onPlane = false;
					saw = false;
					drop.play();
				}
			}
			else jet.stop();
				
			if (onPlane == true) {
				player.setPosition(Plane.GetPosition());
				saw = true;
			}else 
			player.Update(deltaTime, view.getCenter(), shot); player.Rotate(mousePosView);

			hpBar.Update(player.hp, view.getCenter(),Vector2f(-900,460));
			armorBar.Update(player.Armor, view.getCenter(), Vector2f(-900, 500));
			text.setPosition(view.getCenter().x - 910, view.getCenter().y - 450);
			kill.setPosition(view.getCenter().x - 900, view.getCenter().y + 400);
			timeShow.setPosition(view.getCenter().x - 800, view.getCenter().y - 530);
			magazine.setPosition(view.getCenter().x + 645, view.getCenter().y + 500);
			gamePlay.setPosition(view.getCenter());
			dropOff.setPosition(view.getCenter().x - 450, view.getCenter().y + 200);
			
			//-------   Bomb - Gen   -------
			for (size_t i = 0; i < Bomber.size(); i++) {
				Bomber[i].Update(deltaTime);
				if (Bomber[i].done == true) Bomber.erase(Bomber.begin() + i);
			}
		
			//-------   Bot - Gen   -------
			for (size_t i = 0; i < bot.size(); i++) {
				if (i != 0) bot[i].Update(deltaTime, player.GetPosition(), detectArea,saw);
			}

			if((int)Timer < 60) detectArea = 300.0f;
			else if((int)Timer < 90) detectArea = 500.0f;
			else if((int)Timer < 120) detectArea = 600.0f;
			else {
				detectArea = 800.0f;
				Nenermy = 25;
			}

			if (bot.size() < Nenermy) {
					enermy.setPosition(Vector2f((float)(1000 + rand() % 2000), (float)(1000 + rand() % 2000)), rand() % 7);
					if (enermy.getType() == 0 || enermy.getType() == 1 || enermy.getType() == 2) {
						enermy.UpdateTex(&piston);

					}
					else if (enermy.getType() == 3 || enermy.getType() == 4 || enermy.getType() == 5) {
						enermy.UpdateTex(&PlayerTex);

					}
					else if (enermy.getType() == 6) {
						enermy.UpdateTex(&shotgun);
					}
					else
					{
						enermy.UpdateTex(&PlayerTex);
					}
					bot.push_back(Enermy(enermy));

					item.setPosition(Vector2f(((rand() % 70) + 5)* gridSizeF, ((rand() % 70) + 5)* gridSizeF), rand() % 12);
					iTem.push_back(Item(item));
			}

			//-------   Shooting   -------
			if (Time > player.fireRate && shot == true) {
				shot = false;
			}

			if (Mouse::isButtonPressed(Mouse::Left) && MainMenu == 1 && shot == false && onPlane == false)
			{
				if (bullets.size() < 40) {
					playerCenter = Vector2f(player.GetPosition().x, player.GetPosition().y);
					b1.setPosition(player.GetPosition(),player.damage);
					aimDir = mousePosView - playerCenter;
					aimDir = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
					if (player.getType() == 6 && player.mag3 != 0) {
						for (int i = -2; i <= 2; i++) {
							shotgunView.x = mousePosView.x + (10 * i);
							shotgunView.y = mousePosView.y + (10 * i);
							aimDir = shotgunView - playerCenter;
							aimDir = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
							b1.currVelocity = aimDir * b1.maxSpeed;
							bullets.push_back(Bullet(b1));
						}
						shot = true;
						Shotgun.play();
						player.mag3--;
					}
					else if (player.getType() == 0 || player.getType() == 1 ||
						player.getType() == 2) {
							if(player.mag1 != 0) {
								aimDir = mousePosView - playerCenter;
								aimDir = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
								b1.currVelocity = aimDir * b1.maxSpeed;
								bullets.push_back(Bullet(b1));
								sound.play(); shot = true;
								player.mag1--;
							}
					}
					else if (player.getType() == 3 || player.getType() == 4 ||
						player.getType() == 5) {
						if (player.mag2 != 0) {
							aimDir = mousePosView - playerCenter;
							aimDir = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
							b1.currVelocity = aimDir * b1.maxSpeed;
							bullets.push_back(Bullet(b1));
							sound.play(); shot = true;
							player.mag2--;
						}
					}
				}
				Time = delay.restart().asSeconds();
			}

			for (size_t i = 0; i < bot.size(); i++) {
				if (bot[i].shoot == false && MainMenu == 1) {
					botCenter = Vector2f(bot[i].GetPosition().x, bot[i].GetPosition().y);
					botDir = player.GetPosition() - botCenter;
					botDir = botDir / sqrt(pow(botDir.x, 2) + pow(botDir.y, 2));
					b2.currVelocity = botDir * b2.maxSpeed;
					b2.setPosition(bot[i].GetPosition(), bot[i].damage);
					botBullets.push_back(Bullet(b2));
					bot[i].shoot = true; bot[i].resetTime = true;
					sound.play();
				}
			}
			
			for (size_t i = 0; i < bullets.size(); i++) bullets[i].Update(bullets[i].currVelocity);
			for (size_t i = 0; i < botBullets.size(); i++) botBullets[i].Update(botBullets[i].currVelocity);

			//-------  CheckCollition -------
			for (size_t j = 0; j < bot.size(); j++) // bot & playerBullet
				for (size_t i = 0; i < bullets.size(); i++) {

					for (size_t j = 0; j < Vbox.size(); j++) {
						if (bullets[i].GetCollider().CheckCollision(Vbox[j].GetCollider(), 0.0f)) {
							bullets.erase(bullets.begin() + i);
							break;
						}
					}

					if (bullets[i].GetCollider().CheckCollision(bot[j].GetCollider(), 0.0f)) {
						if (j != 0) {
							bot[j].hp = bot[j].hp - player.getDamage();
							if (bot[j].hp <= 0) {
								Bomb.setPosition(bot[j].GetPosition());
								Bomber.push_back(deathBomb(Bomb));
								boom.play();
								item.setPosition(Vector2f(bot[j].GetPosition().x/gridSizeF, bot[j].GetPosition().y / gridSizeF)* gridSizeF, rand() % 12);
								iTem.push_back(Item(item));
								bot.erase(bot.begin() + j);
								player.kill++; gamePlay.point += 10;
								if (bot.size() == 1) {
									gamePlay.point += 50;
									if(Timer<=60) gamePlay.point += 80;
									else if(Timer<=90) gamePlay.point += 60;
									else if (Timer <= 120) gamePlay.point += 30;
									MainMenu = 2;
									scoreBoard.writeText((string)nameInput, gamePlay.point);
									player.kill = 0; gamePlay.point = 0;
									nameInput.clear();
									name.Update((string)nameInput);
								}
							}
							bullets.erase(bullets.begin() + i);
							break;
						}
					}

					if (bullets[i].GetCollider().CheckCollision(Glass.GetCollider(), 0.0f)) {
						bullets.erase(bullets.begin() + i);
						break;
					}

					if (bullets[i].GetPosition().x > 4000 ||
						bullets[i].GetPosition().y > 4000 ||
						bullets[i].GetPosition().x < 0 ||
						bullets[i].GetPosition().y < 0)
					{
						bullets.erase(bullets.begin() + i);
					}
				}

			for (size_t i = 0; i < botBullets.size(); i++) //Bot Bullet && Player
			{
				if (botBullets[i].GetCollider().CheckCollision(player.GetCollider(), 0.0f)) {
					botBullets.erase(botBullets.begin() + i);
					if (player.Armor > 0) player.Armor -= botBullets[i].damage;
					else player.hp -= botBullets[i].damage;
					break;
				}

				if (botBullets[i].GetPosition().x > 4000 ||
					botBullets[i].GetPosition().y > 4000 ||
					botBullets[i].GetPosition().x < 0 ||
					botBullets[i].GetPosition().y < 0)
				{
					botBullets.erase(botBullets.begin() + i);
				}

				if (player.hp <= 0) {
					MainMenu = 2;
					scoreBoard.writeText((string)nameInput, gamePlay.point);
					gamePlay.point = 0;
					player.kill = 0;
					player.hp = 100;
					nameInput.clear();
					name.Update((string)nameInput);
					jet.stop();
				}

				for (size_t j = 0; j < Vbox.size(); j++) {
					if (botBullets[i].GetCollider().CheckCollision(Vbox[j].GetCollider(), 0.0f)) {
						botBullets.erase(botBullets.begin() + i);
						break;
					}
				}
			}
				
			for (size_t i = 0; i < iTem.size(); i++) { //Player && Item
				if (player.GetCollider().CheckCollision(iTem[i].GetCollider(), 0.0f)
					&& Keyboard::isKeyPressed(Keyboard::Key::E)) {
					if (iTem[i].getType() == 0 || iTem[i].getType() == 1 || iTem[i].getType() == 2) {
						player.UpdateTex(&piston, iTem[i].getType());
					}
					else if (iTem[i].getType() == 3 || iTem[i].getType() == 4 || iTem[i].getType() == 5) {
						player.UpdateTex(&PlayerTex, iTem[i].getType());
					}
					else if (iTem[i].getType() == 6) {
						player.UpdateTex(&shotgun, iTem[i].getType()); 
					}
					else
					{
						player.UpdateTex(&PlayerTex, iTem[i].getType());
					}
					slot.updateSlot(iTem[i].getType());
					cout << "Pick" << endl;
					iTem.erase(iTem.begin() + i);
					pick.play();
				}
			}

			hide = 0; //Hide in grass
			for (size_t i = 0; i < Vgrass.size(); i++) {
				player.GetCollider().CheckCollision(Vgrass[i].GetCollider(), 0.0f);
				if (Vgrass[i].Hiding(player.GetPosition())) {
					hide ++;
				}
			}
			if (hide == 1) saw = true;
			else if (hide == 0) saw = false;

			for (size_t i = 0; i < Vbox.size(); i++) {
				player.GetCollider().CheckCollision(Vbox[i].GetCollider(), 0.0f);
			}

			for (size_t j = 0; j < bot.size(); j++)
				for (size_t i = 0; i < Vgrass.size(); i++)
				{
					bot[j].GetCollider().CheckCollision(Vgrass[i].GetCollider(), 0.0f);
				}

			for (size_t j = 0; j < bot.size(); j++)
				for (size_t i = 0; i < Vbox.size(); i++)
				{
					bot[j].GetCollider().CheckCollision(Vbox[i].GetCollider(), 0.0f);
				}

			Glass.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

		}

		//------- Game - Over -------
		if (MainMenu != 1) {
			for (size_t i = 1; i < iTem.size(); i++) {
				iTem.erase(iTem.begin() + i);
			}
			for (size_t i = 1; i < bullets.size(); i++) {
				bullets.erase(bullets.begin() + i);
			}
			for (size_t i = 1; i < bot.size(); i++) {
				bot.erase(bot.begin() + i);
			}
			for (size_t i = 1; i < Vgrass.size(); i++) {
				Vgrass.erase(Vgrass.begin() + i);
			}
			for (size_t i = 1; i < botBullets.size(); i++) {
				botBullets.erase(botBullets.begin() + i);
			}
			for (size_t i = 1; i < Vbox.size(); i++) {
				Vbox.erase(Vbox.begin() + i);
			}
			Timer = timer.restart().asSeconds();
		}

		if (pauseOn) PauseMenu.pauseActive(view.getCenter());
		
		//-------  Window Draw -------
		window.clear();

		switch (MainMenu) {
		case 0:
			window.draw(Menu);
			menu.draw(window);
			name.Update(deltaTime);
			name.Draw(window);
			
			break;
		case 1:
			for (int x = 0; x < mapSize; x++) {
				for (int y = 0; y < mapSize; y++) {
					window.draw(tileMap[x][y]);
				}
			}
			for (size_t i = 0; i < iTem.size(); i++) {
				iTem[i].Draw(window);
			}
			for (size_t i = 0; i < bullets.size(); i++) {
				bullets[i].Draw(window);
			}
			for (size_t i = 0; i < botBullets.size(); i++) {
				botBullets[i].Draw(window);
			}
			for (size_t i = 0; i < bot.size(); i++) {
				bot[i].Draw(window);
			}
			//window.draw(tileSelector);
			player.Draw(window);
			for (size_t i = 0; i < Vbox.size(); i++) {
				Vbox[i].Draw(window);
			}
			for (size_t i = 0; i < Vgrass.size(); i++) {
				Vgrass[i].Draw(window);
			}
			for (size_t i = 0; i < Bomber.size(); i++) {
				Bomber[i].Draw(window);
			}
			Plane.Draw(window);
			hpBar.Draw(window); armorBar.Draw(window);
			//window.draw(text);
			//window.draw(kill);
			window.draw(Interface);
			window.draw(timeShow);
			slot.Draw(window);
			window.draw(magazine);
			gamePlay.Draw(window);
			if (onPlane == true) window.draw(dropOff);
			if (pauseOn == true) PauseMenu.draw(window);
			break;
		case 2: //Result
			window.draw(Win);
			scoreBoard.Draw(window);
			break;
		case 3:
			window.draw(HTP);
			break; 
		case 4:
			break;
		}
		window.display();
	}
	return 0;
}

