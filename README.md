# ft_select
ft_select, an introduction to termcaps

[Subject FR](ft_select.fr.pdf)

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
ctrl-r                 : delete last character of research, but is overriden when adding element
ctrl-u                 : delete the research, but is overriden when adding element
ctrl-a                 : add new element to list
```

### Features

- #### CLI option: Ascii sort:

    ```
    Usage : ./ft_select my options are the best --sort
    ```

- #### Dynamic research : just type !

- #### Add element to the list:

      Type Ctrl + a. 

      You can now type the name of the element you want to add to the list.

      To remove a character, Ctrl + r remove the last character, and Ctrl + u clear the line.

      Press Enter to validate the name.

      If you want to hide the character adding temporarily, press Ctrl + a.

      The line will not be cleared
