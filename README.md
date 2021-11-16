<h1 align="center">
    <img alt="42Lausanne" title="42Lausanne" src="https://github.com/MarJC5/42/blob/main/42_logo.svg" width="140"> </br>
    Project n°2 - get_next_line
    <h4 align="center" style="width: 50%; margin: 2rem auto; font-weight: normal;"> 
    Function which returns a line read from a file descriptor.
    </h4>
</h1>

## Description

Calling the function ``char *get_next_line(int fd)`` in a loop will allow you to read the text
available on the file descriptor one line at a time until the end of it.

The file must be read line by line until he founds a new line (ASCII = '\n') and not more. Read all the file in one time isn't recommended this is why we use a global ``BUFFER_SIZE`` to set how many octet the function will read.

## Functions needed
- malloc(), free()
- read() (open() and close() are used only in the main)
- [ft_strchr()](https://github.com/MarJC5/Libft/blob/main/libft/ft_strchr.c), [ft_strlen()](https://github.com/MarJC5/Libft/blob/main/libft/ft_strlen.c), [ft_strdup()](https://github.com/MarJC5/Libft/blob/main/libft/ft_strdup.c), [ft_substr()](https://github.com/MarJC5/Libft/blob/main/libft/ft_substr.c), [ft_strjoin()](https://github.com/MarJC5/Libft/blob/main/libft/ft_strjoin.c)

## Set-by-step

### 1. Setup variables
For this function we need to use 2 importants variable:
- ``static char *save``: A static variable is able to save the data passed to it even after the function is ended, this will allow us to re-use the data in it after a new call of the function.
- ``char *buf``: Will be used to store the current read value regarding the ``BUFFER_SIZE``.

### 2. Check if our ``file descriptor`` is valid
To read a file, we use the function ``read()`` who takes an ``int fd`` as argument. The ``fd`` return the number of octet that he reads, 0 if it is the end of the file and -1 if the file descriptor isn't valid.

### 3. Check the ``BUFFER_SIZE`` and malloc
As we need a buffer to know how many octet the program will read each times, the ``BUFFER_SIZE`` must be bigger than 0. If the step 1 and 2 aren't good we return (null).

Then if ``BUFFER_SIZE`` is ok, we can create a ``malloc()`` regarding his size and add +1 for the '\0'.

We secure the ``malloc()`` by checking if ``buf`` isn't NULL and we create an empty ``malloc()`` in the static ``save`` only if he doesn't have a value in it (this is a security for later in the program).

As everything is now setup we can proceed to the next step of the program and call the function ``char *ft_read_file(int fd, char **save, char *buf)``.

### 4. Read the file
2 variables is needed:
- ``int file``: To store the return value of ``read()``
- ``char *tmp``: To save data and swap it later

A while loop is used to loop the file until the ``file`` is equal to 0. The loop will:
- Add a '\0' at the end of the file, this will tell us when to stop as the file is ended.
- Join to our static ``*save`` all the ``buf`` content that we just read. This is why we need to set an empty ``malloc()`` as ``ft_strjoin()`` doesn't work with NULL value.
- Next step is to ``free()`` our static to save her new data in it. (This to avoid leaks of memory)
- Before to ``read()`` more the file we check with ``ft_strchr()`` if we already got a '\n' in our ``buf``.
    - ``NO``: Do the loop again until a '\n' is founded
    - ``YES``: We leave the loop and ``free()`` the ``buf``, then check the line with the function ``char *ft_return_line(char **save, char *res).``

### 5. Check the line and return the value
As we have now found the newline we need to loop the static ``*save`` to see what to return.
- Loop the ``*save`` with a counter to found the '\n' position
- Substract the line from the start to the '\n' include
- If no '\n' is found, we check with ``ft_strchr()`` if a '\0' is founded
    - ``\n found``: We save in ``tmp`` the value static ``*save`` whitout the line that we will return. It means now ``tmp`` is equal ``*save`` minus all we got until '\n'. (ex: Hello \n world -> world) Then we can ``free()`` the static to asign the new value en return the line.
    - ``\0 found``: If the satatic ``**save`` is == '\0' we return NULL as their is no line at all in the static. don't forger to free the static as we set it to a size of ``malloc(1)`` a the beggining of the program. (to avoid leaks). Otherwise the line as some date included '\0', we simply return the value of the static.
