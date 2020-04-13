# ft_select
ft_select, an introduction to termcaps

## How to build the project
```
git clone https://github.com/lubenard/ft_select
cd ft_select
make
```

## How to launch ft_select
After building it, just type:
```
./ft_select arg1 arg2...
```

### <a name="Shortcut">Shortcut</a>
```
arrow right            : cursor moves right
arrow left             : cursor moves left
arrow up               : cursor move up
arrow down             : cursor move down
space                  : select the argument on the list
return                 : return the list of arguments
backspace / delete key : delete the argument the cursor is on
ctrl-r                 : delete last character of research
ctrl-u                 : delete the research
ctrl-a                 : add new element to list
```

### Features

CLI option: Ascii sort

```
--sort

Usage : ./ft_select my options are the best --sort
```

Dynamic research : just type !

