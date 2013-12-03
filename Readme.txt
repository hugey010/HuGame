11/13/2013

Against Professor Boggus' recommendation, I decided to make  my lab 6 an iPhone game based made with the cocos2d-x framework. The main algorithms involved that I'm expecting to be graded on are the generation of enemy npc units and collision detection. There are also algorithms for projectile positioning and rotation as well as the culling and memory management involved in destroying enemy npcs. The swipe functionality is something to behold as it works actually very well. Here's the rundown:

As far as programming practices, I tried to make each functional group on the screen its own CCLayer. The HUD, enemy npcs, friendly npcs, fortress, and swipe attacks are all their own layers.

In general, I tried to follow the rule of threes, but in some cases I only had time to follow the rule of twos. Two enemy unit types, two friendly unit types, two projectile types, three health upgrades...

Each enemy unit type extends from a virtual class HuEnemyNPC. This allowed some base functionaliy and each sublcass to implement its special characteristics (ie ranged attacks, suicide). My friendly npcs are all the same class because their functionality is very similar. Just the damage and type of projectiles they fire differ.

Friendly units are purchasable at the end round menu. These fire projectiles at enemy units. There is no collision detection here (friendlies never miss enemies and enemies).

My projectiles class is flexible enough to be used by both friendlies and enemies alike. It is able to determine the proper angle of the projectile from its destination and starting point. The speed and sprite depends on the type of projectile.

The only human attack is swipe based. I generate a polygon from the initial and end points and then detect if any of the npc sprite positions are within the bounding box. If they are I do raycasting to check if the point is actually contained in the polygon. 

Another consideration I took great care to implement involved portability of cocos2d-x. Since the framework is meant to be very portable I handle differing screen sizes (not only among iOS but Android as well). All of my 'hard coded' values use macros for the screen height and width.

Player information is accessed through the HuPlayer class which is a singleton. This is important because most classes base their decisions on the current state of the player, so having one and only one instance is key. Player information is persistently stored in a sqlite database. I do allow the continuance of the previous game in progress. I didn't have time to allow choosing of previous saved games but this would be an easy feature to implement. A high score section could be created with something like keeping track of the total coins obtained.

Game balancing alrogithm
-- Goals --
Get harder as the levels increase
Start easy, end impossibly

Method: The purchasable npcs pick the damage gained in the previous round (plus a little extra). This means the user has to outdamage the change in total enemy health. This is both easy, because swipe is an area of effect attack, and difficult, because the change is an exponential function.
What remains constant:
Enemies - health, damage per second, reward amount, speed
Friendlies - damage per second, cost

What changes:
Enemies - the number per round is a function of the current user level to the power of 1.7. Ranged enemies are generated at half the rate of melee enemies.

The result: A game that starts easy and becomes exponentially more difficult.

Miscellaneous:
-I really wanted to implement flying enemies but ran out of time. It makes swiping much more difficult when you have to cover more vertical area.
- It is frustrating to click the buttons on the menu.
