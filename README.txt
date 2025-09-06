## 1. Title
**Insaniquarium Deluxe – Interactive Virtual Aquarium Game**

## 2. Written by:
**Adir Cohen**
**Beni Hananis**

## 3. Project Description:
Insaniquarium Deluxe is a real-time strategy and simulation game where players manage a virtual aquarium filled with colorful fish, helpful pets, and alien invaders.

The core gameplay revolves around feeding fish, collecting coins, upgrading tanks, and defending against hostile monsters. As the player progresses, new enemies, and challenges are introduced.

The player must balance resource management, fast reactions, and strategic pet selection to survive increasingly difficult levels.

---

## 4. Components Overview:

### AquariumManager
- Controls all entities inside the tank: fish, food, coins, pets, and aliens.
- Handles interactions, collisions, and level transitions.
- Responsible for spawning enemies and triggering animations.

### Fish / Pirana
- Core entities that must be fed to stay alive.
- Fish generate coins when grown; Pirana generates diamonds and eat small fish.
- If not fed, fish lose health and eventually die.

### Aliens – NormalMonstar, SquidMonstar
- Hostile entities that invade the tank and kill fish.
- SquidMonstar changes color: **blue** = invulnerable and self-healing when shoting it.
- Must be repelled by shooting or pet synergy.

### Pets – HelperSnail, HelperJellyfish
- Passive helpers that collect coins for the player.
- Snail moves along the bottom and slowly gathers coins.
- Jellyfish moves quickly and collects coins in mid-water.
- Both inherit from a base class `HelperSeekCoin`.

### Coins
- In-game currency (Silver, Gold, Diamond).
- Used to buy food, animals, and upgrades.
- Can be collected manually or automatically by pets.

### Game
- Manages the main game loop and window using SFML.
- Routes events to the ScreenManager.

### EventManager
- Implements the Observer pattern.
- Manages communication between gameplay systems via events (e.g., coin creation, game over, level up, etc.).

---

## 5. Main Data Structures:

• `std::list<std::unique_ptr<GameObject>> m_eatables`  
  Stores all active objects in the aquarium: fish, food, coins, aliens.  
  Used for updates, drawing, and collision checks.

• `std::vector<std::function<void()>> m_eventSubscriptions`  
  Stores unsubscription callbacks for cleanup.  
  Ensures safe removal of event handlers during reset.

• `enum class Foodtype { Worst, Medium, Best }`  
  Represents the current food tier and is upgraded as the game progresses.

• `std::vector<sf::Sprite> m_hitMark`  
  Used for hit animations when aliens are attacked.

• `enum class ScreenType { Menu, Game, GameOver }`  
  Tracks the current screen in use (menu, in-game, or game over).

• `std::unordered_map<std::string, sf::Texture> m_textures`  
  Manages all loaded textures in `ResourceManager` for easy access and memory reuse.

---

## 6. Notable Algorithms:

- **Fish Hunger & Death**: Health decreases every 0.5s without food. Fish dies if health reaches 0, triggering an animation.

- **Alien Behavior**:
  - Aliens spawn periodically with increasing difficulty, if you shot .
  - **NormalMonstar** attacks fish.
  - **SquidMonstar** switches between two modes:
    - **Red mode** (default): vulnerable and behaves like a regular alien.
    - **Blue mode** (temporary): becomes invulnerable and **should not be attacked** (only if you must change is direction by shoting). Any attack during this phase actually heals it.
    - The switch between red and blue occurs at random intervals.

- **Knockback Direction on Alien Hit**:
  - When an alien is clicked, it is pushed **in the opposite direction** of the click.
  - For example, clicking the bottom-left corner of the alien pushes it up-right.
  - This mechanic allows skilled players to **control alien movement**, pushing them away from fish or toward tank edges.
  - If the alien is hit repeatedly during its "blue" (invulnerable) phase, it may bounce around and heal instead of taking damage.

- **Pet Coin Seeking**: Pets like Snail and Jellyfish actively search for nearby coins and move toward them to collect.

- **Collision System**: All `GameObject` instances are tested against each other. When overlap is detected, logic such as eating or blocking is applied depending on the object types.

- **Alien Knockback**: When the player clicks on an alien, it takes damage and is knocked back. If its health reaches zero, it dies and drops a diamond.

- **Food Tier System**: As the player progresses, they unlock better food types which restore more health and evolve fish faster.

- **Dynamic Event System**: An `EventManager` allows components like AquariumManager and UI to respond to gameplay events in real time (e.g., monster death, coin creation, food purchases).


---

## 7. Design Overview:

### Game
- Handles the main game loop using SFML.
- Renders and updates current screen.

### AquariumManager
- Manages all game entities and core logic.
- Processes user input, updates, and collision.

### GameObject Hierarchy
- All entities derive from a base `GameObject` class.
- Each implements `update()`, `draw()`, `getBounds()`, and custom logic.

### GameObjectFactory
- Dynamically creates objects by name (e.g., "GoldFish", "Money_Diamond").
- Implements a flexible and extensible Factory pattern.

### ResourceManager
- Handles loading and slicing spritesheets.
- Manages fonts, textures, and game assets.

---

## 8. Known Bugs:


---

## 9. Additional Comments:

- The game features whimsical art, humorous animations, and dynamic difficulty.
- Success requires balancing feeding, upgrades, and pet combinations.
- Each level introduces new mechanics and synergies to discover.
- Proper timing and reaction are just as important as long-term planning.
