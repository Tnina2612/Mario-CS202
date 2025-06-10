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

- State machine for character behavior

- Level loading from tilemaps

- Scene management system (title, play, game over, etc.)

## UML Class Diagram

[![UML Class Diagram](https://img.plantuml.biz/plantuml/png/nLTHRzis47utuF_0jxbeNGnx5BAWITEqnfebgnjqUwGbncP2aG99ENNN_VVTaPH4Cewj0GMMXoJwUCSxtdrtFBunbchRrc8wcKxC0vSDrRGcfQ36d5ch-QgrR54gkUJV6FaPfNuYlpxpWsldr33o5jK9bHLPIClq7IsPEQmudT2LiPgMrjicxsdDhbVt382_fnD2vkHhGUw4ejP_xPAlHrxPJO9i65zlR0Iz95iE9wM2j4r5BPkzACXMyIfTgpHztB-Yv5ib13TSoPbQtHUHXxtyFtWGtXsPB9OM37d_Xuqs41V15h9fxNvBX_nZkFdiMOFl9Ajtvsn3jrpft72jjcp6KA8WJl3eEVSAvpQlLuRfBUlDAVcxilnkDsDRyBOWa5Okry_7g8so_9BGgkesX32ROjW_yLOpFCqOINdKcSE4lgAQAzZ7vV8eYprvlKxWhK758f31Gzmiv9RBagy4hAoK4XuNVClW812Te5egpQBlBHEgv7RtPqBr3lqhORjXrbcScSvs4XOCtqTsbr4GqKzOE2bytzPDYkpZwDFQ6LCp8UbBFEgiKN1M7u54mD87Ta5hkcOPztsybpKLmWMzHzg6wGIvv9e5O3e9bNdo_VNhH3d1eorYFDh8vta-F-rAlO3gDiSvXGN5nvB9LLz7fbMexIAhzQxfKO5zS21GmrYLaAK2xqiB2UcbVcGoevoyLwfUqUxhDwKQ-bdZxmwwuPhA3RqH5Fteq2zKF0o72idSC25oy594XvzEV9HEli_dlUK8Iin7UEv3ra1TlbEFzaba_kqJsUkj8qugN93Mi14CEeUIVnX982VR4OYRCqZ_DcaxmDc5PVK0OR8_S7kC4QQXZn8r4SQ_2G7EDIyVdEqE-QDb1gcNWDW93JR2W4udtb-NdtYF2CusYbQUxdOuZkZro32Yw115h0LWFbPN7BK0pshi38M_28v4CQ--A8HNhTa0QUkuXrqAzSZwAhYMxBPnp4NlN0W6fG6B5GUqLpuSeuzmTmetpNtcWjMq6HSlhnO2Pa4J-ZfkS8KR8CPy5opWsZFsnDN1QUXoZjrXmMNorCSA-bW5iMqkELwSsMK-hfL5uGtUP3x-Sa6erdJtNBxMpABYcPrzTJtq5SwY_i9o7NN4JB4iuUp_TI9sIlbCnsLUfZzapDHCLl6S6Q-LWb7PDiz4r0hc7EtxkTAYWbU0LWaC7NUN0EuoWTaj0IyOjPk0J2S-08wviPq8Vc8iMeiiHcXcDbf9RVVQhcc7wpy57TzpyCFjHGwzmqdqYaeOPlHngjmk8FHEPMIR0ek4rmqKAkhau_dJcTBoElvCHz2Zq_p1-efFclYKpFnpeeABNSNtFf_-Rs-2n7LtJtSR7K_P9TIiqhknqvs5qJseTDLTQY2Vly9cTjV4hIxSQuEKwvkvb0DZANTBPqBHZNtuG5WaiEMQ0uDdIr0Mp2hvOjm1KJdeXdINhOR-Obr552IK62xeLahOFRvHeTak9BoWPEawrR1PE1nqkRLl1FZESV-ad6XbHit87ynhC9-XhctsDPejtcnsXfUcy-DOz3unGN5OCHlU7AtXw4M1rtH1IZzGc7Z9pplmrk28-wz8nOrbiE0lODToF1q6e9-Eta2ZRslnBm00)](https://img.plantuml.biz/plantuml/png/nLTHRzis47utuF_0jxbeNGnx5BAWITEqnfebgnjqUwGbncP2aG99ENNN_VVTaPH4Cewj0GMMXoJwUCSxtdrtFBunbchRrc8wcKxC0vSDrRGcfQ36d5ch-QgrR54gkUJV6FaPfNuYlpxpWsldr33o5jK9bHLPIClq7IsPEQmudT2LiPgMrjicxsdDhbVt382_fnD2vkHhGUw4ejP_xPAlHrxPJO9i65zlR0Iz95iE9wM2j4r5BPkzACXMyIfTgpHztB-Yv5ib13TSoPbQtHUHXxtyFtWGtXsPB9OM37d_Xuqs41V15h9fxNvBX_nZkFdiMOFl9Ajtvsn3jrpft72jjcp6KA8WJl3eEVSAvpQlLuRfBUlDAVcxilnkDsDRyBOWa5Okry_7g8so_9BGgkesX32ROjW_yLOpFCqOINdKcSE4lgAQAzZ7vV8eYprvlKxWhK758f31Gzmiv9RBagy4hAoK4XuNVClW812Te5egpQBlBHEgv7RtPqBr3lqhORjXrbcScSvs4XOCtqTsbr4GqKzOE2bytzPDYkpZwDFQ6LCp8UbBFEgiKN1M7u54mD87Ta5hkcOPztsybpKLmWMzHzg6wGIvv9e5O3e9bNdo_VNhH3d1eorYFDh8vta-F-rAlO3gDiSvXGN5nvB9LLz7fbMexIAhzQxfKO5zS21GmrYLaAK2xqiB2UcbVcGoevoyLwfUqUxhDwKQ-bdZxmwwuPhA3RqH5Fteq2zKF0o72idSC25oy594XvzEV9HEli_dlUK8Iin7UEv3ra1TlbEFzaba_kqJsUkj8qugN93Mi14CEeUIVnX982VR4OYRCqZ_DcaxmDc5PVK0OR8_S7kC4QQXZn8r4SQ_2G7EDIyVdEqE-QDb1gcNWDW93JR2W4udtb-NdtYF2CusYbQUxdOuZkZro32Yw115h0LWFbPN7BK0pshi38M_28v4CQ--A8HNhTa0QUkuXrqAzSZwAhYMxBPnp4NlN0W6fG6B5GUqLpuSeuzmTmetpNtcWjMq6HSlhnO2Pa4J-ZfkS8KR8CPy5opWsZFsnDN1QUXoZjrXmMNorCSA-bW5iMqkELwSsMK-hfL5uGtUP3x-Sa6erdJtNBxMpABYcPrzTJtq5SwY_i9o7NN4JB4iuUp_TI9sIlbCnsLUfZzapDHCLl6S6Q-LWb7PDiz4r0hc7EtxkTAYWbU0LWaC7NUN0EuoWTaj0IyOjPk0J2S-08wviPq8Vc8iMeiiHcXcDbf9RVVQhcc7wpy57TzpyCFjHGwzmqdqYaeOPlHngjmk8FHEPMIR0ek4rmqKAkhau_dJcTBoElvCHz2Zq_p1-efFclYKpFnpeeABNSNtFf_-Rs-2n7LtJtSR7K_P9TIiqhknqvs5qJseTDLTQY2Vly9cTjV4hIxSQuEKwvkvb0DZANTBPqBHZNtuG5WaiEMQ0uDdIr0Mp2hvOjm1KJdeXdINhOR-Obr552IK62xeLahOFRvHeTak9BoWPEawrR1PE1nqkRLl1FZESV-ad6XbHit87ynhC9-XhctsDPejtcnsXfUcy-DOz3unGN5OCHlU7AtXw4M1rtH1IZzGc7Z9pplmrk28-wz8nOrbiE0lODToF1q6e9-Eta2ZRslnBm00)

## Reference

[1] The Spriters Resources: [Super Mario Bros](https://www.spriters-resource.com/nes/supermariobros/?fbclid=IwY2xjawKw1ABleHRuA2FlbQIxMQABHmjffl3_AHI1ruxnMnNfH3v1R_NXRe9ij0y9fkRcn45ro0t7jzzqvnV5jU0G_aem_MsrA5rZbZEvkfA96d0h-Ww)

[2] Mario Mayhem: [Super Mario Bros](https://www.mariomayhem.com/downloads/sprites/super_mario_bros_sprites.php?fbclid=IwY2xjawKw2v1leHRuA2FlbQIxMQABHsk_004iqqvzIyKZMuiEVccjJ2P6MaMWv4SX6fh5ZeMsVKKxzm3rLK1nKjPo_aem_VwWVHayuh1ylnaleJHwEow)
