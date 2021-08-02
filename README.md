# Doom-Nukem

Doom-Nukem is a game engine based on the famous Duke Nukem game from the '90s.

It was coded from scratch and valided on our [42](https://www.42.fr/) cursus at [19 Coding School](https://www.s19.be/)

## System Requirements

Tested on macOS Mojave (10.14.*) and Linux. SDL2 + SDL_mixer source included in project.

You might have to install graphic and audio dependencies on linux machine : 

```shell
sudo dpkg --configure -a
sudo apt-get install libasound2-dev libpulse-dev libgl1-mesa-dev
```

## Run on MacOS Big Sur

SDL2 & SDL2_mixer Libraries aren't working on Big Sur when compiling directly from the repo.

A work around to fix this issue is to past SDL2 and SDL_2.mixer framework on the : /Library/Frameworks/ path.

Those frameworks can be downloaded using those links : 

- SDL2 : https://www.libsdl.org/release/SDL2-2.0.14.dmg
- SDL2_mixer : https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.dmg

Once the folders : SDL2_mixer.framework and SDL2.framework are copied on the /Library/Frameworks/ folder of your machine you need to update the current Makefile.

Replace line 73 & 74 by those two bellow :

```c
CFLAGS =  -I common -Wall -Wextra -Werror -g -I /Library/Frameworks/SDL2.framework/Headers -I /Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers
LDFLAGS = -lpthread -F/Library/Frameworks -framework SDL2 -framework SDL2_mixer common/ft_printf/libftprintf.a
```

Now save your new MakeFile and run the make command, you can skip the Installation chapter of this ReadMe.


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
