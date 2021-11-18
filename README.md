# Minishell
Minishell is a simple shell.

# contributors
<a href="https://github.com/42joonpark">
  <img src="https://github.com/42joonpark.png?size=50">
</a>

<a href="https://github.com/pdh9311">
  <img src="https://github.com/pdh9311.png?size=50">
</a>

# Build
> Note: `readline is required.`
```sh
brew install readline
```
add includes path and dir in Makefile

# Builtins
1. cd
2. pwd
3. echo
4. exit
5. export
6. env
7. unset

# cd [option] [dst]
### cd to dst directory ###
- '-'

    cd to OLDPWD

- '~'

    cd to $HOME dir

- relative path

- absolute path

# pwd
### return working directory name ### 

# echo
### write arguments to the standard output ###

- n

    Do not print the trailing newline character.
    
# exit
### ###

# export
### ###

# env
### ###

# unset
### ###

# errors
any input with ; or \ are syntax error.
