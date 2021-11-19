# Minishell
Minishell is a simple shell.

# contributors
<a href="https://github.com/42joonpark">
	<img src="https://github.com/42joonpark.png?size=50">
</a>

<a href="https://github.com/pdh9311">
	<img src="https://github.com/pdh9311.png?size=50">
</a>

# Make
> Note: `readline is required.`
```sh
brew install readline
```
add includes path and dir in Makefile

# Builtins
1. [cd](#cd)
2. [pwd](#pwd)
3. [echo](#echo)
4. [exit](#exit)
5. [export](#export)
6. [env](#env)
7. [unset](#unset)

# cd [option] [dst]
### change the working directory ###
- '-' \
	cd to OLDPWD

- '~' \
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
### Close the terminal ###
- Argument : no \
	Terminal is terminated.
	```sh
	zsh$ bash
	bash$ exit
	exit
	zsh$
	```

- Argument : number < INT_MAX \
	Argument of integer value is returned to the parent process and terminated.
	```sh
	zsh$ bash
	bash$ exit 7
	exit
	zsh$ echo $?
	7
	```



# export
### set the export attribute for variables ###

Only the form of <span style="color:red"> a=b </span> is recognized.

Forms such as a=b, a=b, 'a'=b, a='b'etc are not allowed.

Duplicate names are changed to new values.

# env
### print environment ###

# unset
### Remove variable ###

# errors
any input with ; or \ are syntax error.

# Diagram #
![Untitled Diagram](https://user-images.githubusercontent.com/83530766/142572055-78e0d113-9b9f-43ea-bd89-9c6f65ac5e72.png)
