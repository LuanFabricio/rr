# What is this project?
- A simple River Raid clone written in C with Raylib.

# Requiriments
| Name                                        |  Version    |  Dev. dependency | Lib type|
| :-----------------------------------------: | :---------: | :--------------: | :-----: |
| [Raylib](https://github.com/raysan5/raylib) | 5.0         | Yes              | Shared  |
| [gcc](https://gcc.gnu.org/)                 | >=13        | Yes              | -       |

# How can I build?
## Release mode
```bash
./build.sh release
```
## Debug mode
```bash
./build.sh
```
- In this mode you have hot reload for the `src/player.c`, `src/collision.c` and `src/fuel.c` source files.

# Running the project
- After build the project you can run `./build/main` to execute the game.
