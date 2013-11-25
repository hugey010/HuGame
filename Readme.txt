HuGame Readme
Tyler Hugenberg
11/13/2013

Against Professor Boggus' recommendation, I decided to make  my lab 6 an iPhone game based made with the cocos2d-x framework. The main algorithms involve I am expecting to be graded on are mainly involving the generation of enemy npc units and collision detection. Here's the rundown:

Each unit type extends from a base class EnemyNPC.
This class lets use NPCCatapult for example, has a constructor taking parameters
- round time - milliseconds

Friendly units are purchasable at the end round menu. These fire projectiles at enemy units. There is no collision detection here (friendlies never miss enemies).

My projectiles class is flexible enough to be used by both friendlies and enemies alike.

The only human attack is swipe based. I generate a polygon from the initial and end points and then detect if any of the npc sprite positions are within the bounding box. If they are I do raycasting to check if the point is actually contained in the polygon. Human hits are shown with a special yellow explosion. 
