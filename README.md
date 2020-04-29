# Doom-Nukem

Doom-Nukem is a game engine based on the famous Duke Nukem game from the '90s.

It was coded from scratch and valided on our [42](https://www.42.fr/) cursus at [19 coding school](https://www.s19.be/)

## System Requirements

Tested on macOS Mojave (10.14.*) and Linux. SDL2 + SDL_mixer source included in project.

You might have to install graphic and audio dependencies on linux machine : 

```shell
sudo dpkg --configure -a
sudo apt-get install libasound2-dev libpulse-dev libgl1-mesa-dev
```

## Installation

```shell
git clone https://github.com/lvanbei/Doom-Nukem.git
make sdl
make
```

## Usage

### Launch the Game
```shell
./doom-nukem maps/map_1
```

### Launch the Game Editor
```shell
./vis_ed a_new_or_existing_map_name
```

## Created By
[hde-moff](https://www.linkedin.com/in/henri-de-moffarts-862bb5164)

[lvan-bei](https://www.linkedin.com/in/lvanbei)

## Preview

![alt text](https://github.com/lvanbei/Doom-Nukem/blob/master/README_img/doom_github_preview.jpg "img1")
