# Super Mario Bros 1985. - Project CS202

A simple 2D Mario-style platformer game built with [Raylib](https://www.raylib.com/) and C++. It features a basic game engine structure with scenes, entities, behaviors, and levels.

## Project Structure

```
MarioRaylib/ 
│
├── assets/                     # Textures, spritesheets, sounds, fonts, etc.
│   ├── images/
│   ├── sounds/
│   └── maps/
│
├── include/                    # Header files
│   ├── core/                   # Core engine files
│   │   ├── GameEngine.hpp
│   │   ├── Scene.hpp
│   │   ├── InputManager.hpp
│   │   └── EventManager.hpp
│   │
│   ├── entities/               # Mario, enemies, blocks, items
│   │   ├── GameObject.hpp
│   │   ├── Mario.hpp
│   │   ├── Enemy.hpp
│   │   ├── Block.hpp
│   │   ├── Item.hpp
│   │   ├── HUD.hpp
│   │   └── EntityFactory.hpp
│   │
│   ├── behaviors/              # Interfaces and states
│   │   ├── IState.hpp
│   │   ├── MarioStates.hpp
│   │   ├── IEnemyBehavior.hpp
│   │   └── EnemyBehaviors.hpp
│   │
│   ├── scenes/                 # Game scenes
│   │   ├── TitleScene.hpp
│   │   ├── PlayScene.hpp
│   │   ├── WorldIntroScene.hpp
│   │   ├── GameOverScene.hpp
│   │   └── DeathScene.hpp
│   │
│   └── level/                  # Tile and level related
│       ├── Level.hpp
│       └── TileMap.hpp
│
├── src/                        # Source files
│   ├── core/
│   ├── entities/
│   ├── behaviors/
│   ├── scenes/
│   └── level/
│
├── CMakeLists.txt              # CMake build config
├── main.cpp
└── README.md
```

## Features

- Basic 2D platforming physics

- tate machine for character behavior

- Level loading from tilemaps

- Scene management system (title, play, game over, etc.)

## UML Class Diagram

![UML Class Diagram](https://img.plantuml.biz/plantuml/png/nLTBSzis4BvhHly1jygZEDF9aUDwOiUMeqbTkvKzFKFaMaG40Xm0bCCc-U_5KmIe5zrBSyXO7x2BVNpxu4Ufi51DHSUZyKYk2Qknm1NAAPRoIYb1bes2USxPWlm3w5TpwnVqsu5_vkmQIq2VZ3Z2h41pfa2yu1paSS7n22-b4ZXNxcrqXojuM7u53NmVZn0wHzyoz48vLkvNc_nw9OKg4wG4iYfL0c56AgouoD2L_ylWKzJK1LOmESlGXfF2OON0hntoqnZex0gYmQgy4GAOckceGOO8ys_9MX05Yn90s_04trGZuCFDYVU2X--stgKMa11CD5yehSBPC4MbZZI5EQiRbMhTzn8O9PE3YcyPLEqrb7X3WfDJLF5DJmjddpYbH1BE3kjwM4eG6zYguUmFhiXBEu6DjY93Ek64hGxxs4Jvdo9S547XX2zbrkbFB6CddpXEu7ii2DTwR8HFijQHmibuHaWZcFaKEOZ8ETiGbfCbrITBpgd3ATc0Z5cJSz6nQ8eaAAjb8eE-a-bDYTjF5Lz-pQBIsaVmHOKfjGvjaQO6aI0p8i03uv7duiMFz-yJuGIFLCHueiX5yVpyCj0xqyoMlIZRavdk4roqWHcv00swIAcsXYZj8Gi_qmTsL9tcXIqlj6YbWceOAwp4FMPurPN0lfGH-GNQHm5IGZ5PGtiMA6ADDjcwPIl2m8KcKdhQQ5FDP2YBRUa75Yzz2yXwBU6_CcyVrUuuhvOu_Fh2UOsVXFa_G8z4O5RYHufDHGJqRqpNdJcUeoLGsWTdD39xF7B-NVmuFz--7479yn7Ujw7N8IsDKulstUZPj-_ANcjjojFB6Meao06JcF9yFJ3rzcv8FP5NkTATgUjK9fMVYHeu8gy5oTTMOq3-R40gpO84D2rHcexeqV78MM6Z7kk8u9wYw6HNsuborcKyC3ZcQZV23ALrwvnKfeLahfCCYyjz8qlDhohkeZFANs5Bs0S6pxKbcNdI-jK9TLWisA5RuUEE_wud8xMxsHEXKE5wM12Sc6U8qf9w91a5zqQ1mS2rcamFDQakB6KlVIknHFG7DZsNBb9wmobq7EiPeR0pgj-ycNbhUZP-k45O2DmU53uUhKMk_Nhhxcg50cC8wnVEczOrlLmMyRvcvnq5p9hwG1GK1Ml0jbroGGkzXmkUmBgXjGbWrmAzJINWZPwifKV68-UOPLlyJWJlF1QTHIz6QE_Pw2Hz-tYU7ijMabo-QJvx6JzSmvPPrxIz4xhLglRWkkGI8pdTGB9RNSMtto6DN1zUjtg3FR7cjCFFSst3hLbo1tQnpyytY5IrBdaZy-Rb_6ZfMJl2fXC_yl-iyDkTRjZMetIgzswKjbVrDqe_NxfRjjNrRramlcNwzCvoQgawm2535UIvCbbeOGgAixDX3aOyIxzPRMbbo5UOEH0DOrfxFFXNeEPCVzAmt3QcJfbtJZUpbUi3vYF5_f6MITFV_Owx-XTGR2QyB4bzajdH5uCPWndAtN2MyP5R4lIt137ujWbrtm5zq8wwFgZBfm_5h1-Ft82qkCjz1oJRIcIjhF4hapkTm2SaAIeh5Oh5kFvHpuMcely2)